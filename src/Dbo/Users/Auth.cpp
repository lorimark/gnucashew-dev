#line 2 "src/Dbo/Users/Auth.cpp"

#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/OAuthService.h>

#include "Auth.h"

namespace 
{
  Wt::Auth::AuthService                                    myAuthService                      ;
  Wt::Auth::PasswordService                                myPasswordService( myAuthService ) ;
  std::vector< std::unique_ptr< Wt::Auth::OAuthService > > myOAuthServices                    ;
}

auto
GCW::Dbo::Users::
mapClasses( Wt::Dbo::Session & session )-> void
{
  session.mapClass< GCW::Dbo::Users::Item      >( "gcw_users"         );
  session.mapClass< AuthInfo                   >( "gcw_auth_info"     );
  session.mapClass< AuthInfo::AuthIdentityType >( "gcw_auth_identity" );
  session.mapClass< AuthInfo::AuthTokenType    >( "gcw_auth_token"    );

} // endmapClasses( Wt::Dbo::Session & session )-> void


