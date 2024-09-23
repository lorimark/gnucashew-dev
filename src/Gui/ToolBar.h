#line 2 "src/Gui/ToolBar.h"

#ifndef __GUI_TOOLBAR_H___
#define __GUI_TOOLBAR_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WToolBar.h>

#include "CentralWidget.h"
#include "ToolBar.h"

namespace GCW {
  namespace Gui {

/*!
** \brief Main Tool Bar
**
** This widget acts as the 'tool bar' for the site.  The toolBar
**  is a container widget with a bunch of buttons that are context
**  sensitive.  Every time a different view is opened, the tool
**  bar in the main window updates to reflect buttons that are
**  context appropriate for that particular view.
**
**
*/
class ToolBar
: public Wt::WContainerWidget
{
  public:

};

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // #ifndef __GUI_TOOLBAR_H___



