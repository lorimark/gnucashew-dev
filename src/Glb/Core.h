#line 2 "src/Glb/Core.h"

#ifndef __GCW_CORE_H___
#define __GCW_CORE_H___

#include <string>
#include <vector>

#include <Wt/Json/Object.h>

#include "Numeric.h"

//#define COUT_FLF  __FILE__, __LINE__, __FUNCTION__
//#define COUT_BEG  std::cout << __FILE__ << ":" << __LINE__ << "(" << __PRETTY_FUNCTION__ << ") "
//#define COUT_END  std::endl
//#define COUT_LINE std::cout << __FILE__ << ":" << __LINE__ << "(" << __PRETTY_FUNCTION__ << ")" << COUT_END
//#define COUT_(x)  COUT_BEG << x << COUT_END


namespace GCW {

  /*!
  ** \brief helper functions and features
  **
  */
  namespace Core {


std::vector<std::string> split( const std::string & value, char delim );

extern const char* trim_ws;
std::string & rtrim( std::string & s, const char* t = trim_ws );
std::string & ltrim( std::string & s, const char* t = trim_ws );
std::string & trim( std::string & s, const char* t = trim_ws );
std::string toupper( const std::string & s );
std::string tolower( const std::string & s );

Wt::Json::Object toJson( Wt::WTreeView * _view );

std::string hexDump( const std::string & data, int start = -1, int end = -1 );

/*!
** \brief Generate new GUID string value
**
** This GUID is suitable for use as the primary-guid-key value for the
**  data tables.
**
*/
auto newGuid()-> std::string ;

/*!
** \brief Current Date/Time
**
** This will return the current date/time suitable for back-end storage
**
*/
auto currentDateTime()-> Wt::WDateTime ;
auto currentDateTimeStorageString()-> std::string ;
auto currentDateTimeDisplayString()-> std::string ;

  } // endnamespace Core
} // endnamespace GCW

#endif

