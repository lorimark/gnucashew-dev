#line 2 "src/Glb/Core.h"

#ifndef __WTX_CORE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__
#define __WTX_CORE_H_234e0174_6b7d_11e8_b503_fb1ef3651ec0__

#include <string>
#include <vector>

#include <Wt/Json/Object.h>

//#define COUT_FLF  __FILE__, __LINE__, __FUNCTION__
//#define COUT_BEG  std::cout << __FILE__ << ":" << __LINE__ << "(" << __PRETTY_FUNCTION__ << ") "
//#define COUT_END  std::endl
//#define COUT_LINE std::cout << __FILE__ << ":" << __LINE__ << "(" << __PRETTY_FUNCTION__ << ")" << COUT_END
//#define COUT_(x)  COUT_BEG << x << COUT_END


namespace Wtx {

  /*!
  ** \brief functions and features
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

  } // endnamespace Core
} // endnamespace Wtx

#endif

