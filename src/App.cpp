#line 2 "src/App.cpp"

/*
** USER_LOGIN is a switch that sets up the UI with
**  a user-login-widget.  It's not working yet.
**
*/
//#define USER_LOGIN

#include <Wt/Date/tz.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/WDate.h>
#include <Wt/WDialog.h>
#include <Wt/WEnvironment.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WLocale.h>
#include <Wt/WServer.h>
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>

#include "App.h"
#include "Dbo/Users/Auth.h"
#include "GnuCashew.h"
#include "Dbo/Commodities/Commodities.h"

extern std::string g_dbName;

namespace {

void showEnvironment()
{
  auto app = GCW::app();

  std::cout << __FILE__ << ":" << __LINE__
    << "\n title:              " << app-> title()
    << "\n appRoot:            " << app-> appRoot()
    << "\n docRoot:            " << app-> docRoot()
    << "\n sessionId:          " << app-> sessionId()
    << "\n metaHeader:         " << app-> metaHeader( Wt::MetaHeaderType::Meta, "*" )
    << "\n bodyClass:          " << app-> bodyClass()
    << "\n htmlClass:          " << app-> htmlClass()
    << "\n url:                " << app-> url()
    << "\n bookmarkUrl:        " << app-> bookmarkUrl()
    << "\n internalPath:       " << app-> internalPath()
    << "\n javaScriptClass:    " << app-> javaScriptClass()
    << "\n resourcesUrl:       " << app-> resourcesUrl()
    << "\n r-resourcesUrl:     " << app-> relativeResourcesUrl()
    << "\n referrer:           " << app-> environment().referer()
    << "\n accept:             " << app-> environment().accept()
    << "\n X-Forwarded-For:    " << app-> environment().headerValue( "X-Forwarded-For" )
    << "\n X-Forwarded-Client: " << app-> environment().headerValue( "X-Forwarded-Client" )
    << "\n X-Forwarded-Xyz:    " << app-> environment().headerValue( "X-Forwarded-Xyz" )
    << "\n clientAddress:      " << app-> environment().clientAddress()
    << std::endl
    ;

  for( const auto & pair : app-> environment().getParameterMap() )
    for( const auto & value : pair.second )
      std::cout << __FILE__ << ":" << __LINE__ << " " << pair.first << "=" << value << std::endl;

} // endvoid showEnvironment()

} // endnamespace {

GCW::App * GCW::app()
{
  return static_cast< GCW::App* >( Wt::WApplication::instance() );
}

GCW::App::App( const Wt::WEnvironment & env )
: Wt::WApplication( env )
{
  root()-> addStyleClass( "GnuCashewRoot" );

  setTitle( "GnuCashew ~ " + g_dbName );

#ifdef NEVER
  // something to note about the X-Forwarded-For haproxy value.  This setting
  //  needs to be set within the 'haproxy.cfg haproxy_loop' section.  To
  //  troubleshoot this, open the /var/log/haproxy.log file and look for the
  //  reported IP address;
  //    Oct 10 09:45:26 lsus1 haproxy[31634]: 104.28.50.130:50944 [10/Oct/2024:09:45:24.526] www-https~ haproxy_loop/haproxy_loop 0/0/1998 297 -- 6/3/2/1/0 0/0
  //    Oct 10 09:45:27 lsus1 haproxy[31634]: 127.0.0.1:43110 [10/Oct/2024:09:45:26.362] www-http gnucashew/gnucashew_wt 976/0/0/6/982 200 3777 - - ---- 6/3/0/1/0 0/0 "POST /demo?wtd=wDqiKVj7Wjibd276 HTTP/1.1"
  //  note in the first-line, haproxy_loop, the IP address noted is the actual
  //  ip address of the incoming client.  this is the section that needs to
  //  carry the 'option forwardfor' setting to forward that address along to
  //  the next section;
  //    backend haproxy_loop
  //      mode http
  //      option forwardfor
  //      server haproxy_loop localhost:80
  //
  //  note: also that the wt_config.xml file needs to posess the
  //         <behind-reverse-proxy>true</behind-reverse-proxy> value
  //  note: that the wthttp back-end does not regard the X-Forwarded-For value
  //         and therefore will report the incorrect IP address to the console
  //
  std::cout << __FILE__ << ":" << __LINE__ << " " << environment().headerValue( "X-Forwarded-For" ) << std::endl;
  for( const auto & kvp : environment().getParameterMap() )
    for( const auto vvv : kvp.second )
      std::cout << __FILE__ << ":" << __LINE__ << " " << kvp.first << " " << vvv << std::endl;
#endif

#ifndef NEVER
  std::cout
    << __FILE__ << ":" << __LINE__ << std::endl
    << __FILE__ << ":" << __LINE__
    << " [" << Wt::WDateTime::currentDateTime().toString()
    << "] " << environment().clientAddress()
    << " "  << sessionId()
    << " "  << url() << std::endl
    << __FILE__ << ":" << __LINE__
    << std::endl;
#endif

#ifdef USE_GNUCASH_ENGINE
  gnucash_session()  .open( g_dbName );
#endif

#ifdef USE_GNUCASHEW_SESSION
  gnucashew_session().open( g_dbName );
#endif

  engine().open( g_dbName );

//  showEnvironment();

  /*
  ** Utilize the bootstrap theme.
  **
  */
  auto bootstrapTheme = std::make_shared<Wt::WBootstrapTheme>();
  bootstrapTheme-> setVersion( Wt::BootstrapVersion::v3 );
  bootstrapTheme-> setResponsive( true );
  setTheme( bootstrapTheme );
  useStyleSheet( "resources/themes/bootstrap/3/bootstrap-theme.min.css" );
  useStyleSheet( "styles/gcw.css" );

  /*
  ** GnuCashew english language translations
  **
  ** Note on the 'language elements' files.
  **  The 'files' are located in the docroot folder.  The main "united states english"
  **  translation file is called "gcw.xml".  This file contains all the words used in
  **  the system called upon by Wt::WString::tr("id value").  Each 'language' file is
  **  therefore;
  **    "gcw_nl.xml" Dutch (netherlands)
  **    "gcw_sp.xml" Spanish
  **
  ** It is only necessary to reference the english "gcw.xml" file, and the other language
  **  files will get loaded automatically when the language changes.
  **
  ** See "Gui/MainWidget.cpp" for the references to the 'langCombo' code.
  **
  */
  messageResourceBundle().use( docRoot() + "/styles/gcw"     );  // Language Elements
  messageResourceBundle().use( docRoot() + "/styles/gcw_gui" );  // UI elements

  /*
  ** set the date format to the browser.
  **
  */
#ifdef NEVER
  auto loc = locale();
  auto tz = date::locate_zone( environment().timeZoneName() );
  loc.setTimeZone( tz );
#endif

#ifdef USER_LOGIN
  auto lw = root()-> setLayout( std::make_unique< Wt::WVBoxLayout >() );

  lw-> addWidget( std::move( createAuthWidget() ) );

  m_mainContainer = lw-> addWidget( std::make_unique< Wt::WContainerWidget >(), 1 );

  /*
  ** If the login status changes, respond to it.
  **
  */
  gnucashew_session().login().changed().connect( this, &App::buildSite );
#endif

  /*
  ** build the site
  **
  */
  buildSite();

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " \tcommodity.isocode"
    << " \tcommodity.unitname"
    << " \tcommodity.partname"
    << " \tcommodity.nameSpace"
    << " \tcommodity.exchangeCode"
    << " \tcommodity.partsPerUnit"
    << " \tcommodity.smallestFraction"
    << " \tcommodity.localSymbol"
    << " \tcommodity.fullname"
    << std::endl;
  for( auto & commodity : GCW::Dbo::Commodities::getIso4217Commodities() )
  {
    std::cout << __FILE__ << ":" << __LINE__
      << " \t" << commodity.isocode
      << " \t" << commodity.unitname
      << " \t" << commodity.partname
      << " \t" << commodity.nameSpace
      << " \t" << commodity.exchangeCode
      << " \t" << commodity.partsPerUnit
      << " \t" << commodity.smallestFraction
      << " \t" << commodity.localSymbol
      << " \t" << commodity.fullname
      << std::endl;
  }
#endif

#ifdef SIMPLE_REPEATING_TIMER_FOR_TESTING_THINGS
  m_timer = std::make_unique< Wt::WTimer >();
  m_timer-> setInterval( std::chrono::seconds(1) );
  m_timer-> start();
  m_timer->
    timeout().connect( [&]( Wt::WMouseEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " testing something..." << std::endl;
    });
#endif

} // endGCW::App::App( const Wt::WEnvironment & env )

auto
GCW::App::
showWelcome()-> void
{
  Wt::WDialog dialog( TR( "gcw.welcome.title" )  );
  dialog.rejectWhenEscapePressed( true );
  dialog.setClosable( true );
  dialog.contents()-> addNew< Wt::WText >( TR( "gcw.welcome.body" ) );
  dialog.exec();

} // endshowWelcome()-> void

auto
GCW::App::
createAuthWidget() -> std::unique_ptr< Wt::Auth::AuthWidget >
{
  auto retVal = std::make_unique< Wt::Auth::AuthWidget >
    (
     GCW::Dbo::Users::service(),
     gnucashew_session().users(),
     gnucashew_session().login()
    );

  retVal-> model()-> addPasswordAuth( & GCW::Dbo::Users::passwordService() );
  retVal-> model()-> addOAuth(          GCW::Dbo::Users::oService()        );
  retVal-> setRegistrationEnabled( true );
  retVal-> processEnvironment();

  return std::move( retVal );

} // endcreateLoginWidget() -> std::unique_ptr< Wt::Auth::AuthWidget >


auto
GCW::App::
buildSite()-> void
{
#ifdef USER_LOGIN
  std::cout << __FILE__ << ":" << __LINE__ << " " << gnucashew_session().login().loggedIn() << std::endl;

  if( m_mainWidget )
      m_mainContainer-> removeWidget( m_mainWidget );
//  m_mainContainer-> clear();

  std::cout << __FILE__ << ":" << __LINE__ << " " << gnucashew_session().login().loggedIn() << std::endl;

//  if( gnucashew_session().login().loggedIn() )
//  if( true )
  if( bookmarkUrl() == "demo" || gnucashew_session().login().loggedIn() )
    buildLoggedIn();
  else
    buildLogin();
#else

  buildLoggedIn();

#endif

} // endbuildSite()-> void

auto
GCW::App::
buildLogin()-> void
{

} // endbuildLogin()-> void

auto
GCW::App::
buildLoggedIn()-> void
{

#ifdef USER_LOGIN
  /*
  ** Set a layout manager on the root widget so that everything can
  **  be laid out correctly.
  **
  */
  auto lw = m_mainContainer-> setLayout( std::make_unique< Wt::WVBoxLayout >() );
       lw-> setSpacing( 0 );

  /*
  ** Build and install the main desktop widget.
  **
  */
  m_mainWidget = lw-> addWidget( std::make_unique< GCW::Gui::MainWidget >() );

#else

  /*
  ** Set a layout manager on the root widget so that everything can
  **  be laid out correctly.
  **
  */
  auto lw = root()-> setLayout( std::make_unique< Wt::WVBoxLayout >() );
  lw-> setSpacing( 0 );

  /*
  ** Build and install the main desktop widget.
  **
  */
  m_mainWidget = lw-> addWidget( std::make_unique< GCW::Gui::MainWidget >() );

#endif

  /*
  ** If this is the demo, wait a second and pop a welcome screen.
  **
  ** For whatever reason, just firing off this pop-up dialog at the
  **  beginning of the program start causes the widget to not display
  **  properly.  Instead of resizing the dialog to fit the available
  **  space in the browser, it makes a super-wide dialog with all the
  **  text on just one line.  By delaying the dialog just a bit, it
  **  seems to mitigate this issue.
  **
  */
//  if( bookmarkUrl() == "demo" )
  if( g_dbName.find( "LorimarkSolutions" ) == std::string::npos )
    Wt::WTimer::singleShot( std::chrono::seconds(1), this, &App::showWelcome );

  /*
  ** If we have the gnucashew extensions, then record that we logged on.
  **
  */
//  if( engine().hasGnuCashewExtensions() )
//  {
//    Wt::Dbo::Transaction t( gnucashew_session() );
//    auto item = GCW::Dbo::Vars::get( "logon","sys" );
//    item.modify()-> setVar( "logonOn", Wt::WDateTime::currentDateTime().toString( ISO_DATE_FORMAT ) );
//    item.modify()-> setVar( "logonBy", "dev(0)" );
//  }

} // endbuildLoggedIn()-> void



