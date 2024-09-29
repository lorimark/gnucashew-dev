#line 2 "src/Dbo/Users/Auth.h"

#ifndef __DBO_USERS_AUTH_H___
#define __DBO_USERS_AUTH_H___

#include <Wt/Dbo/Session.h>
#include <Wt/Auth/Login.h>
#include <Wt/Auth/Dbo/UserDatabase.h>

#include "User.h"

namespace GCW {
  namespace Dbo {
    namespace Users {

using AuthInfo     = Wt::Auth::Dbo::AuthInfo< GCW::Dbo::Users::Item >;
using UserDatabase = Wt::Auth::Dbo::UserDatabase< AuthInfo >;

auto mapClasses( Wt::Dbo::Session & session )-> void ;
auto postCreateTables( Wt::Dbo::Session & session )-> void ;

auto configure()-> void ;
auto service()-> const Wt::Auth::AuthService & ;
auto passwordService()-> const Wt::Auth::PasswordService & ;
auto oService()-> const std::vector<const Wt::Auth::OAuthService *> ;

    } // namespace Users {
  } // namespace Dbo {
} // namespace GCW {

#endif // __DBO_USERS_SESSION_H___




