#!/usr/bin/perl 

use lib '.';

require 'readvaluesfile.pl';

use Getopt::Std;
getopts('chi:');

 #Options
 # c -> generate c code file
 # h-> generate header file   

 # Open with value-types.txt

my %h = read_values_file($ARGV[0]);


 # Write the file inline by copying everything before a demarcation
 # line, and putting the generated data after the demarcation

if ($opt_i) {
  
  open(IN,$opt_i) || die "Can't open input file $opt_i";
  
  while(<IN>){
    print;
  }    
}


 # Map type names to the value in the icalvalue_impl data union */

%union_map = (
	      BOOLEAN => 'int',
	      CALADDRESS=>'string',
	      DATE=>'time',
	      DATETIME=>'time',
	      DATETIMEDATE=>'time',
	      DATETIMEPERIOD=>'period',
	      DURATION=>'duration',
	      INTEGER=>'int',
	      TEXT=>'string',
	      URI=>'string',
	      UTCOFFSET=>'int',
	      QUERY=>'string',
	      BINARY=>'string'
	     );

foreach $value  (keys %h) {

  my $autogen = $h{$value}->{C}->[0];
  my $type = $h{$value}->{C}->[1];

  my $ucf = join("",map {ucfirst(lc($_));}  split(/-/,$value));
  
  my $lc = lc($ucf);
  my $uc = uc($lc);
  
  my $pointer_check = "icalerror_check_arg_rz( (v!=0),\"v\");\n" if $type =~ /\*/;
  my $pointer_check_rv = "icalerror_check_arg_rv( (v!=0),\"v\");\n" if $type =~ /\*/;
  
  my $assign;
  
  if ($type =~ /char/){
    $assign = "strdup(v);\n\n    if (impl->data.v_string == 0){\n      errno = ENOMEM;\n    }\n";
  } else {
    $assign = "v;";
  }
  
  my $union_data;
  
  if (exists $union_map{$uc} ){
    $union_data=$union_map{$uc};
  } else {
    $union_data = $lc;
  }
  
  if ($opt_c && $autogen) {
    
    print "\n\n\
icalvalue* icalvalue_new_${lc} ($type v){\
   struct icalvalue_impl* impl = icalvalue_new_impl(ICAL_${uc}_VALUE);\
   $pointer_check\
   icalvalue_set_${lc}((icalvalue*)impl,v);\
   return (icalvalue*)impl;\
}\
void icalvalue_set_${lc}(icalvalue* value, $type v) {\
    struct icalvalue_impl* impl; \
    icalerror_check_arg_rv( (value!=0),\"value\");\
    $pointer_check_rv\
    icalerror_check_value_type(value, ICAL_${uc}_VALUE);\
    impl = (struct icalvalue_impl*)value;\n";
    
    if( $union_data eq 'string') {
      
      print "    if(impl->data.v_${union_data}!=0) {free((void*)impl->data.v_${union_data});}\n";
    }
    
    print "\n    impl->data.v_$union_data = $assign \n }\n";

    print "$type\ icalvalue_get_${lc}(icalvalue* value)\ {\n\
    icalerror_check_arg( (value!=0),\"value\");\
    icalerror_check_value_type(value, ICAL_${uc}_VALUE);\
    return ((struct icalvalue_impl*)value)->data.v_${union_data};\n}\n";

    
  } elsif($opt_h && $autogen) {
    
    print "\n /* $value */ \
icalvalue* icalvalue_new_${lc}($type v); \
$type icalvalue_get_${lc}(icalvalue* value); \
void icalvalue_set_${lc}(icalvalue* value, ${type} v);\n\n";

  } 

}
  
  
if ($opt_h){
    print "#endif /*ICALVALUE_H*/\n";
  }
  
  
  __END__
  