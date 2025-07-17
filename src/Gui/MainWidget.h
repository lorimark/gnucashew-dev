#line 2 "src/Gui/MainWidget.h"

#ifndef __GUI_MAINWIDGET_H___
#define __GUI_MAINWIDGET_H___

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

  private:

    Wt::WNavigationBar   * m_navBar        = nullptr;
    GCW::Gui::MainMenu   * m_mainMenu      = nullptr;
    Wt::WToolBar         * m_toolBar       = nullptr;
    Wt::WContainerWidget * m_statusBar     = nullptr;
    CentralWidget        * m_centralWidget = nullptr;

}; // endclass MainWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // #ifndef __MAINWIDGET_H___


