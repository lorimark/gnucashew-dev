#line 2 "src/App.h"

#ifndef __APP_H___
#define __APP_H___

#include <Wt/WApplication.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WTimer.h>

#include "Config.h"
#include "Dbo/SessionGnuCash.h"
#include "Dbo/SessionGnuCashew.h"
#include "Eng/Engine.h"
#include "Gui/MainWidget.h"

namespace GCW {



class App
: public Wt::WApplication
{
  public:

    App( const Wt::WEnvironment & env );

    GCW::Eng::Engine        & engine  () { return m_engine;             }
    Dbo::AbstractSession    & session ();

#ifdef USE_GNUCASH_ENGINE
    Dbo::GnuCash::Session   & gnucash_session   () { return m_gnucash_session;    }
#endif

#ifdef USE_GNUCASHEW_SESSION
    Dbo::GnuCashew::Session & gnucashew_session () { return m_gnucashew_session;  }
#endif

    GCW::Gui::MainWidget    * mainWidget        () { return m_mainWidget;         }

  private:

    auto showWelcome      ()-> void ;
    auto buildSite        ()-> void ;
    auto buildLogin       ()-> void ;
    auto buildLoggedIn    ()-> void ;
    auto createAuthWidget ()-> std::unique_ptr< Wt::Auth::AuthWidget >;

#ifdef USE_GNUCASH_ENGINE
    Dbo::GnuCash::Session         m_gnucash_session;
#endif

#ifdef USE_GNUCASHEW_SESSION
    Dbo::GnuCashew::Session       m_gnucashew_session;
#endif

    Wt::WContainerWidget                    * m_mainContainer = nullptr ;
    std::unique_ptr< Wt::Auth::AuthWidget >   m_authWidget              ;
    Wt::Auth::AuthWidget                    * m_authPointer   = nullptr ;
    std::unique_ptr< Wt::WTimer           >   m_timer                   ;
    GCW::Gui::MainWidget                    * m_mainWidget    = nullptr ;
    GCW::Eng::Engine                          m_engine                  ;

}; // endclass App

App * app();

} // endnamespace GCW {


#endif // end#ifndef __APP_H___


