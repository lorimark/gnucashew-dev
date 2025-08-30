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

    /*!
    ** \brief Find Menu Item
    **
    ** This will find a menu item by text() value.
    **
    ** This is a recursive function, and it will loop through all the menu
    **  items until it finds a match by text.  Since the menu items are also
    **  language translations, in order to find the correct menu item, make
    **  the call using the language translation strings, as follows;
    **
    ** \code
    **  if( auto item = menu-> menuItem( TR( "gcw.MainWidget.mu.view.doubleline" ), this ) )
    **  {
    **    std::cout << __FILE__ << ":" << __LINE__ << " " << item-> text() << std::endl;
    **  }
    ** \endcode
    **
    */
    auto menuItem( const Wt::WString & _text )-> Wt::WMenuItem * ;

  private:

    /*
    ** internal recursive search
    */
    auto menuItem( const Wt::WString & _text, Wt::WMenu * _menu )-> Wt::WMenuItem * ;

}; // endclass MainMenu

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // #ifndef __GUI_MAINMENU_H___



