#line 2 "src/Gui/MainWidget.h"

#ifndef __GUI_MAINWIDGET_H___
#define __GUI_MAINWIDGET_H___

/*
** STATUS_BAR_CLOCK
** I like the idea of a clock on the status bar,
**  it can be subtly handy if the PC you're on
**  doesn't have a clock immediately visible.
**  But, this WTimer based update machine is
**  taxing on the server as it continually stuffs
**  events to a browser that might not be responding.
**  It creates problems.  So, for now, we'll not use it.
*/
//#define STATUS_BAR_CLOCK

#include <Wt/WContainerWidget.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WToolBar.h>

#include "CentralWidget.h"
#include "MainMenu.h"
#include "ToolBar.h"

namespace GCW {
  namespace Gui {

/*!
** \brief Site Main Widget
**
** This is the GnuCashew main site container.  It contains
**  a top-line menu navigation bar, a push-button tool bar,
**  bottom-line status bar, and the main central workspace
**  area for the account tree view and other panes.
**
** \image html MainWidget.png width=480
**
** \ref see also; CentralWidget
**
*/
class MainWidget
: public Wt::WContainerWidget
{
  public:

    MainWidget();

    auto navBar        ()-> Wt::WNavigationBar      * { return m_navBar        ; }
    auto toolBar       ()-> Wt::WToolBar            * { return m_toolBar       ; }
    auto statusBar     ()-> Wt::WContainerWidget    * { return m_statusBar     ; }
    auto centralWidget ()-> CentralWidget           * { return m_centralWidget ; }

    auto load()                   -> void ;
    auto open_customersOverview() -> void ;
    auto open_properties()        -> void ;
    auto open_aboutWidget()       -> void ;
    auto openSelectedAccount()    -> void ;
    auto test()                   -> void ;

    auto setBasicLedger()-> void ;
    auto setAutosplit()-> void ;
    auto setTransaction()-> void ;
    auto setDoubleLine()-> void ;

  private:

    auto do_statusBarUpdate()-> void ;

    Wt::WNavigationBar   * m_navBar        = nullptr ;
    GCW::Gui::MainMenu   * m_mainMenu      = nullptr ;
    Wt::WToolBar         * m_toolBar       = nullptr ;
    Wt::WContainerWidget * m_statusBar     = nullptr ;
    CentralWidget        * m_centralWidget = nullptr ;

#ifdef STATUS_BAR_CLOCK
    Wt::WText            * m_clock         = nullptr ;
#endif

}; // endclass MainWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // #ifndef __MAINWIDGET_H___


