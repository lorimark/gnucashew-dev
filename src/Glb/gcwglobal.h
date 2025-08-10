#line 2 "src/Glb/gcwglobal.h"

#ifndef __GLOBAL_H___
#define __GLOBAL_H___

/*
** set up some common global definitions
**
*/

#define ISO_DATE_FORMAT         "yyyy-MM-ddThh:mm:ss.zzzZ"
#define GCW_DATE_FORMAT_STORAGE "yyyy-MM-dd hh:mm:ss"
#define GCW_DATE_FORMAT_DISPLAY "MM/dd/yyyy"
//#define GCW_DATE_FORMAT_DISPLAY "yyyy-MM-dd"

/*!
** \brief Default Time
**
** This is the default-time that is applied to the split items
**  date column.  Since the user-interface only accepts 'date'
**  values and not 'time' values, the time-component that gets
**  posted to the back-end database is set to this default value.
**
*/
#define GCW_DATE_DEFAULT_TIME   { 10, 59, 0 }
#define GCW_DEFAULT_DATE        "1970-01-01 00:00:00"
#define GCW_RECONCILE_NO        "n"
#define GCW_RECONCILE_YES       "y"
#define GCW_RECONCILE_CLEARED   "c"

/*!
** \brief Internal Numeric Type
**
** This DECIMAL library is used to handle 'currency' type values, which
**  are notably difficult to handle within native C code.
**
*/
#define GCW_NUMERIC DECIMAL::decimal<2>

#define FUNCTION_HEADER __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << ":<start>"
#define FUNCTION_FOOTER __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << ":<end>"
#define BREAKER std::endl << std::endl << std::endl
#define BREAKHEADER BREAKER << FUNCTION_HEADER
#define BREAKFOOTER FUNCTION_FOOTER  << BREAKER

#endif

