#line 2 "src/Dbo/Users/Auth.cpp"

#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Auth/GoogleService.h>
#include <Wt/Auth/FacebookService.h>
#include <Wt/Auth/Dbo/AuthInfo.h>

#include "Auth.h"

namespace
{
  Wt::Auth::AuthService                                    myAuthService                      ;
  Wt::Auth::PasswordService                                myPasswordService( myAuthService ) ;
  std::vector< std::unique_ptr< Wt::Auth::OAuthService > > myOAuthServices                    ;
}

auto
GCW::Dbo::Users::
mapClasses( Wt::Dbo::Session & _session )-> void
{
  _session.mapClass< GCW::Dbo::Users::Item      >( "gcw_users"    );
  _session.mapClass< AuthInfo                   >( "gcw_info"     );
  _session.mapClass< AuthInfo::AuthIdentityType >( "gcw_identity" );
  _session.mapClass< AuthInfo::AuthTokenType    >( "gcw_token"    );

} // endmapClasses( Wt::Dbo::Session & session )-> void

auto
GCW::Dbo::Users::
postCreateTables( Wt::Dbo::Session & session )-> void
{
#ifdef NEVER
  /*
  ** we will create a single default 'admin' user in the system
  **  that can be used to log in to the interface.
  **
  */
  typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

  Wt::Dbo::Transaction t(session);
  UserDatabase users( session, &Wtx::Sys::Auth::service() );

  auto authUser = users.registerNew();
  authUser.addIdentity( Wt::Auth::Identity::LoginName, "admin" );
  authUser.setEmail( "mark@lorimarksolutions.com" );
  passwordService().updatePassword( authUser, "ABC123!!!" );
#endif

} // endpostCreateTables( Wt::Dbo::Session & session )-> void

auto
GCW::Dbo::Users::
configure()-> void
{
  myAuthService.setAuthTokensEnabled( true, "logincookie" );
  myAuthService.setEmailVerificationEnabled( true );
  myAuthService.setEmailVerificationRequired( true );
  myAuthService.setIdentityPolicy( Wt::Auth::IdentityPolicy::EmailAddress );

  auto verifier
    = std::make_unique<Wt::Auth::PasswordVerifier>();
  verifier->addHashFunction( std::make_unique<Wt::Auth::BCryptHashFunction>(7) );
  myPasswordService.setVerifier( std::move(verifier) );
  myPasswordService.setAttemptThrottlingEnabled( true );
  myPasswordService.setStrengthValidator( std::make_unique<Wt::Auth::PasswordStrengthValidator>() );

  if( Wt::Auth::GoogleService::configured() )
    myOAuthServices.push_back( std::make_unique<Wt::Auth::GoogleService>( myAuthService ) );

  if( Wt::Auth::FacebookService::configured() )
    myOAuthServices.push_back( std::make_unique<Wt::Auth::FacebookService>( myAuthService ) );

  for( unsigned i = 0; i < myOAuthServices.size(); ++i )
    myOAuthServices[i]-> generateRedirectEndpoint();

} // endconfigure()-> void

auto
GCW::Dbo::Users::
service()-> const Wt::Auth::AuthService &
{
  return myAuthService;

} // endservice()-> const Wt::Auth::AuthService &

auto
GCW::Dbo::Users::
passwordService()-> const Wt::Auth::PasswordService &
{
  return myPasswordService;

} // endpasswordService()-> const Wt::Auth::PasswordService &

auto
GCW::Dbo::Users::
oService()-> const std::vector<const Wt::Auth::OAuthService *>
{
  std::vector<const Wt::Auth::OAuthService *> result;

  for( auto & auth : myOAuthServices )
    result.push_back( auth.get() );

  return result;

} // endoService()-> const std::vector<const Wt::Auth::OAuthService *>


