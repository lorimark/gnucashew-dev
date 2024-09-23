#line 2 "src/GnuCashew.h"

#ifndef __GNUCASHEW_H___
#define __GNUCASHEW_H___

#define DEC_NAMESPACE DECIMAL
#include "Glb/gcwglobal.h"
#include "3rd/decimal.h"
#include "define.h"
#include "App.h"
#include "Dbo/Vars/Vars.h"

namespace GCW {

  /*!
  ** \brief Config Namespace
  **
  ** The config namespace provides access to the various 
  **  configuration variables.
  **
  */
  namespace Cfg {

/*!
** \brief Decimal Format Specifier
**
** This provides the DECIMAL<2>() library with the formatting
**  specification for converting DECIMAL numbers to strings.
**
*/
DECIMAL::decimal_format decimal_format();

/*!
** \brief Date Format Specifier
**
**
*/
std::string date_format();

/*!
** \brief Time Format Specifier
**
**
*/
std::string time_format();

  } // endnamespace Cfg {
} // endnamespace GCW {

#endif // end#ifndef __GNUCASHEW_H___


