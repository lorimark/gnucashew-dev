#line 2 "src/Config.h"

#ifndef __CONFIG_H___
#define __CONFIG_H___

#include <string>

namespace GCW {

/*!
** \brief Application Configuration
**
** The Application Configuration is controlled through this single object.
**  The configuration includes multiples 'areas' followed by specific settings
**  in each area.  The areas included are;
**
**  -# Global - stored for all applications
**  -# App    - stored for the application specifically
**  -# User   - stored for the currently logged in user
**
*/
class Config
{
  enum class Area
  {
    GLOBAL,
    APP,
    FILE,
    USER
  };

  public:

    Config();
    Config( const Area _area );

    std::string asString( const std::string & _field );
    int asInt( const std::string & _field );

};

} // endnamespace GCW {

#endif // end#ifndef __CONFIG_H___


