#line 2 "src/Gui/MainMenu.h"

#ifndef __GUI_MAINMENU_H___
#define __GUI_MAINMENU_H___

#include <Wt/WMenu.h>

namespace GCW {
  namespace Gui {
    class MainWidget;

/*!
** \brief Site Main Menu
**
** This is the main menu for the whole site.  This is the menu that has the
**  "File", "Edit", "View" menu item, right at the top of the page.
**
*/
class MainMenu
: public Wt::WMenu
{
  public:

    MainMenu( MainWidget * _mainWidget );

}; // endclass MainMenu

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // #ifndef __GUI_MAINMENU_H___



