#line 2 "src/GnuCashew.h"

#ifndef __GNUCASHEW_H___
#define __GNUCASHEW_H___

/*
** need to set up a namespace for the DECIMAL library, but
**  definining the macro is somewhat problemmatic, so we
**  moved the definition in to the CMakeLists so that the
**  definition was made there, insuring it's global for
**  the whole compilation process.
**
*/
// #define DEC_NAMESPACE DECIMAL ... this got moved to CMakeLists so that it is totally global

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


