/* -*- Mode: C -*- */
/*======================================================================
  FILE: icalenum.c
  CREATOR: eric 29 April 1999
  
  $Id: icalenums.c,v 1.7 2001-02-22 05:03:56 ebusboom Exp $


 (C) COPYRIGHT 2000, Eric Busboom, http://www.softwarestudio.org

 This program is free software; you can redistribute it and/or modify
 it under the terms of either: 

    The LGPL as published by the Free Software Foundation, version
    2.1, available at: http://www.fsf.org/copyleft/lesser.html

  Or:

    The Mozilla Public License Version 1.0. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

  The original code is icalenum.c

  ======================================================================*/


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "icalenums.h"

#include <stdio.h> /* For fprintf */
#include <stdio.h> /* For stderr */
#include <string.h> /* For strncmp */
#include <assert.h>




struct icalparameter_kind_map {
	icalparameter_kind kind;
	char name[20];
};

static struct icalparameter_kind_map parameter_map[] = 
{
    { ICAL_ALTREP_PARAMETER, "ALTREP"},
    { ICAL_CN_PARAMETER, "CN"},
    { ICAL_CUTYPE_PARAMETER, "CUTYPE"},
    { ICAL_DELEGATEDFROM_PARAMETER, "DELEGATED-FROM"},
    { ICAL_DELEGATEDTO_PARAMETER, "DELEGATED-TO"},
    { ICAL_DIR_PARAMETER, "DIR"},
    { ICAL_ENCODING_PARAMETER, "ENCODING"},
    { ICAL_FBTYPE_PARAMETER, "FBTYPE"},
    { ICAL_FMTTYPE_PARAMETER, "FMTTYPE"},
    { ICAL_LANGUAGE_PARAMETER, "LANGUAGE"},
    { ICAL_MEMBER_PARAMETER, "MEMBER"},
    { ICAL_PARTSTAT_PARAMETER, "PARTSTAT"},
    { ICAL_RANGE_PARAMETER, "RANGE"},
    { ICAL_RELATED_PARAMETER, "RELATED"},
    { ICAL_RELTYPE_PARAMETER, "RELTYPE"},
    { ICAL_ROLE_PARAMETER, "ROLE"},
    { ICAL_RSVP_PARAMETER, "RSVP"},
    { ICAL_SENTBY_PARAMETER, "SENT-BY"},
    { ICAL_TZID_PARAMETER, "TZID"},
    { ICAL_VALUE_PARAMETER, "VALUE"},
    { ICAL_X_PARAMETER, "X"},

    /* CAP parameters */

    /* libical private parameters */
    { ICAL_XLICERRORTYPE_PARAMETER, "X-LIC-ERRORTYPE"},
    { ICAL_XLICCOMPARETYPE_PARAMETER, "X-LIC-COMPARETYPE"},

    /* End of list */
    { ICAL_NO_PARAMETER, ""}
};

const char* icalenum_parameter_kind_to_string(icalparameter_kind kind)
{
    int i;

    for (i=0; parameter_map[i].kind != ICAL_NO_PARAMETER; i++) {
	if (parameter_map[i].kind == kind) {
	    return parameter_map[i].name;
	}
    }

    return 0;

}

icalparameter_kind icalenum_string_to_parameter_kind(const char* string)
{
    int i;

    if (string ==0 ) { 
	return ICAL_NO_PARAMETER;
    }

    for (i=0; parameter_map[i].kind  != ICAL_NO_PARAMETER; i++) {
	if (strcmp(parameter_map[i].name, string) == 0) {
	    return parameter_map[i].kind;
	}
    }

    if(strncmp(string,"X-",2)==0){
	return ICAL_X_PARAMETER;
    }

    return ICAL_NO_PARAMETER;
}

struct icalvalue_kind_map {
	icalvalue_kind kind;
	char name[20];
};

static struct icalvalue_kind_map value_map[] = 
{
    { ICAL_BINARY_VALUE, "BINARY"},
    { ICAL_BOOLEAN_VALUE, "BOOLEAN"},
    { ICAL_CALADDRESS_VALUE, "CAL-ADDRESS"},
    { ICAL_DATE_VALUE, "DATE"},
    { ICAL_DATETIME_VALUE, "DATE-TIME"},
    { ICAL_DURATION_VALUE, "DURATION"},
    { ICAL_FLOAT_VALUE, "FLOAT"},
    { ICAL_INTEGER_VALUE, "INTEGER"},
    { ICAL_PERIOD_VALUE, "PERIOD"},
    { ICAL_RECUR_VALUE, "RECUR"},
    { ICAL_TEXT_VALUE, "TEXT"},
    { ICAL_TIME_VALUE, "TIME"},
    { ICAL_URI_VALUE, "URI"},
    { ICAL_UTCOFFSET_VALUE, "UTC-OFFSET"},
    { ICAL_METHOD_VALUE, "METHOD"}, /* Not an RFC2445 type */
    { ICAL_STATUS_VALUE, "STATUS"}, /* Not an RFC2445 type */
    { ICAL_GEO_VALUE, "FLOAT"}, /* Not an RFC2445 type */
    { ICAL_ATTACH_VALUE, "ATTACH"}, /* Not an RFC2445 type */
    { ICAL_DATETIMEDATE_VALUE, "DATETIMEDATE"}, /* Not an RFC2445 type */
    { ICAL_DATETIMEPERIOD_VALUE, "DATETIMEPERIOD"}, /* Not an RFC2445 type */
    { ICAL_TRIGGER_VALUE, "TRIGGER"}, /* Not an RFC2445 type */
    { ICAL_QUERY_VALUE, "QUERY"},
    { ICAL_NO_VALUE, ""},
};

const char* icalenum_value_kind_to_string(icalvalue_kind kind)
{
    int i;

    for (i=0; value_map[i].kind != ICAL_NO_VALUE; i++) {
	if (value_map[i].kind == kind) {
	    return value_map[i].name;
	}
    }

    return 0;

}

struct icalcomponent_kind_map {
	icalcomponent_kind kind;
	char name[20];
};

  

static struct icalcomponent_kind_map component_map[] = 
{
    { ICAL_VEVENT_COMPONENT, "VEVENT" },
    { ICAL_VTODO_COMPONENT, "VTODO" },
    { ICAL_VJOURNAL_COMPONENT, "VJOURNAL" },
    { ICAL_VCALENDAR_COMPONENT, "VCALENDAR" },
    { ICAL_VFREEBUSY_COMPONENT, "VFREEBUSY" },
    { ICAL_VTIMEZONE_COMPONENT, "VTIMEZONE" },
    { ICAL_VALARM_COMPONENT, "VALARM" },
    { ICAL_XSTANDARD_COMPONENT, "STANDARD" }, /*These are part of RFC2445 */
    { ICAL_XDAYLIGHT_COMPONENT, "DAYLIGHT" }, /*but are not really components*/
    { ICAL_X_COMPONENT, "X" },
    { ICAL_VSCHEDULE_COMPONENT, "SCHEDULE" },

    /* CAP components */
    { ICAL_VQUERY_COMPONENT, "VQUERY" },  
    { ICAL_VCAR_COMPONENT, "VCAR" },  
    { ICAL_VCOMMAND_COMPONENT, "VCOMMAND" },  

    /* libical private components */
    { ICAL_XLICINVALID_COMPONENT, "X-LIC-UNKNOWN" },  
    { ICAL_XLICMIMEPART_COMPONENT, "X-LIC-MIME-PART" },  
    { ICAL_ANY_COMPONENT, "ANY" },  
    { ICAL_XROOT_COMPONENT, "XROOT" },  

    /* End of list */
    { ICAL_NO_COMPONENT, "" },
};

const char* icalenum_component_kind_to_string(icalcomponent_kind kind)
{
    int i;

    for (i=0; component_map[i].kind != ICAL_NO_COMPONENT; i++) {
	if (component_map[i].kind == kind) {
	    return component_map[i].name;
	}
    }

    return 0;

}

icalcomponent_kind icalenum_string_to_component_kind(const char* string)
{
    int i;

    if (string ==0 ) { 
	return ICAL_NO_COMPONENT;
    }

    for (i=0; component_map[i].kind  != ICAL_NO_COMPONENT; i++) {
	if (strcmp(component_map[i].name, string) == 0) {
	    return component_map[i].kind;
	}
    }

    return ICAL_NO_COMPONENT;
}


struct {
	 enum icalrequeststatus kind;
	int major;
	int minor;
	const char* str;
} request_status_map[] = {
    {ICAL_2_0_SUCCESS_STATUS, 2,0,"Success."},
    {ICAL_2_1_FALLBACK_STATUS, 2,1,"Success but fallback taken  on one or more property  values."},
    {ICAL_2_2_IGPROP_STATUS, 2,2,"Success, invalid property ignored."},
    {ICAL_2_3_IGPARAM_STATUS, 2,3,"Success, invalid property parameter ignored."},
    {ICAL_2_4_IGXPROP_STATUS, 2,4,"Success, unknown non-standard property ignored."},
    {ICAL_2_5_IGXPARAM_STATUS, 2,5,"Success, unknown non standard property value  ignored."},
    {ICAL_2_6_IGCOMP_STATUS, 2,6,"Success, invalid calendar component ignored."},
    {ICAL_2_7_FORWARD_STATUS, 2,7,"Success, request forwarded to Calendar User."},
    {ICAL_2_8_ONEEVENT_STATUS, 2,8,"Success, repeating event ignored. Scheduled as a  single component."},
    {ICAL_2_9_TRUNC_STATUS, 2,9,"Success, truncated end date time to date boundary."},
    {ICAL_2_10_ONETODO_STATUS, 2,10,"Success, repeating VTODO ignored. Scheduled as a  single VTODO."},
    {ICAL_2_11_TRUNCRRULE_STATUS, 2,11,"Success, unbounded RRULE clipped at some finite  number of instances  "},
    {ICAL_3_0_INVPROPNAME_STATUS, 3,0,"Invalid property name."},
    {ICAL_3_1_INVPROPVAL_STATUS, 3,1,"Invalid property value."},
    {ICAL_3_2_INVPARAM_STATUS, 3,2,"Invalid property parameter."},
    {ICAL_3_3_INVPARAMVAL_STATUS, 3,3,"Invalid property parameter  value."},
    {ICAL_3_4_INVCOMP_STATUS, 3,4,"Invalid calendar component."},
    {ICAL_3_5_INVTIME_STATUS, 3,5,"Invalid date or time."},
    {ICAL_3_6_INVRULE_STATUS, 3,6,"Invalid rule."},
    {ICAL_3_7_INVCU_STATUS, 3,7,"Invalid Calendar User."},
    {ICAL_3_8_NOAUTH_STATUS, 3,8,"No authority."},
    {ICAL_3_9_BADVERSION_STATUS, 3,9,"Unsupported version."},
    {ICAL_3_10_TOOBIG_STATUS, 3,10,"Request entity too large."},
    {ICAL_3_11_MISSREQCOMP_STATUS, 3,11,"Required component or property missing."},
    {ICAL_3_12_UNKCOMP_STATUS, 3,12,"Unknown component or property found."},
    {ICAL_3_13_BADCOMP_STATUS, 3,13,"Unsupported component or property found"},
    {ICAL_3_14_NOCAP_STATUS, 3,14,"Unsupported capability."},
    {ICAL_4_0_BUSY_STATUS, 4,0,"Event conflict. Date/time  is busy."},
    {ICAL_5_0_MAYBE_STATUS, 5,0,"Request MAY supported."},
    {ICAL_5_1_UNAVAIL_STATUS, 5,1,"Service unavailable."},
    {ICAL_5_2_NOSERVICE_STATUS, 5,2,"Invalid calendar service."},
    {ICAL_5_3_NOSCHED_STATUS, 5,3,"No scheduling support for  user."},
    {ICAL_UNKNOWN_STATUS, 0,0,"Error: Unknown request status"}
};


const char* icalenum_reqstat_desc(icalrequeststatus stat)
{

    int i;

    for (i=0; request_status_map[i].kind  != ICAL_UNKNOWN_STATUS; i++) {
	if ( request_status_map[i].kind ==  stat) {
	    return request_status_map[i].str;
	}
    }

    return 0;
}


short icalenum_reqstat_major(icalrequeststatus stat)
{
    int i;

    for (i=0; request_status_map[i].kind  != ICAL_UNKNOWN_STATUS; i++) {
	if ( request_status_map[i].kind ==  stat) {
	    return request_status_map[i].major;
	}
    }
    return -1;
}

short icalenum_reqstat_minor(icalrequeststatus stat)
{
    int i;

    for (i=0; request_status_map[i].kind  != ICAL_UNKNOWN_STATUS; i++) {
	if ( request_status_map[i].kind ==  stat) {
	    return request_status_map[i].minor;
	}
    }
    return -1;
}


icalrequeststatus icalenum_num_to_reqstat(short major, short minor)
{
    int i;

    for (i=0; request_status_map[i].kind  != ICAL_UNKNOWN_STATUS; i++) {
	if ( request_status_map[i].major ==  major && request_status_map[i].minor ==  minor) {
	    return request_status_map[i].kind;
	}
    }
    return 0;
}



struct {icalproperty_method method; const char* str;} method_map[] = {
    {ICAL_METHOD_PUBLISH,"PUBLISH"},
    {ICAL_METHOD_REQUEST,"REQUEST"},
    {ICAL_METHOD_REPLY,"REPLY"},
    {ICAL_METHOD_ADD,"ADD"},
    {ICAL_METHOD_CANCEL,"CANCEL"},
    {ICAL_METHOD_REFRESH,"REFRESH"},
    {ICAL_METHOD_COUNTER,"COUNTER"},
    {ICAL_METHOD_DECLINECOUNTER,"DECLINECOUNTER"},
    /* CAP Methods */
    {ICAL_METHOD_CREATE,"CREATE"},
    {ICAL_METHOD_READ,"READ"},
    {ICAL_METHOD_RESPONSE,"RESPONSE"},
    {ICAL_METHOD_MOVE,"MOVE"},
    {ICAL_METHOD_MODIFY,"MODIFY"},
    {ICAL_METHOD_GENERATEUID,"GENERATEUID"},
    {ICAL_METHOD_DELETE,"DELETE"},
    {ICAL_METHOD_NONE,"NONE"}
};


const char* icalenum_method_to_string(icalproperty_method method)
{
    int i;

    for (i=0; method_map[i].method  != ICAL_METHOD_NONE; i++) {
	if ( method_map[i].method ==  method) {
	    return method_map[i].str;
	}
    }

    return method_map[i].str; /* should be ICAL_METHOD_NONE */
}

icalproperty_method icalenum_string_to_method(const char* str)
{
    int i;

    while(*str == ' '){
	str++;
    }


    for (i=0; method_map[i].method  != ICAL_METHOD_NONE; i++) {
	if ( strcmp(method_map[i].str, str) == 0) {
	    return method_map[i].method;
	}
    }

    return ICAL_METHOD_NONE;
}


struct {icalproperty_status status; const char* str;} status_map[] = {
    {ICAL_STATUS_TENTATIVE,"TENTATIVE"},
    {ICAL_STATUS_CONFIRMED,"CONFIRMED"},
    {ICAL_STATUS_NEEDSACTION,"NEEDS-ACTION"},
    {ICAL_STATUS_CANCELLED,"CANCELLED"},
    {ICAL_STATUS_INPROCESS,"IN-PROCESS"},
    {ICAL_STATUS_DRAFT,"DRAFT"},
    {ICAL_STATUS_FINAL,"FINAL"},
    {ICAL_STATUS_NONE,"NONE"}
};

const char* icalenum_status_to_string(icalproperty_status status)
{
    int i;

    for (i=0; status_map[i].status  != ICAL_STATUS_NONE; i++) {
	if ( status_map[i].status ==  status) {
	    return status_map[i].str;
	}
    }

    return status_map[i].str; /* should be ICAL_STATUS_NONE */
}

icalproperty_status icalenum_string_to_status(const char* str)
{
    int i;

    while(*str == ' '){
	str++;
    }


    for (i=0; status_map[i].status  != ICAL_STATUS_NONE; i++) {
	if ( strcmp(status_map[i].str, str) == 0) {
	    return status_map[i].status;
	}
    }

    return ICAL_STATUS_NONE;
}