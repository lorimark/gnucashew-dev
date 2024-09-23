#line 2 "src/Gui/FilePropertiesWidget.h"

#ifndef __GUI_FILEPROPERTIESWIDGET_H___
#define __GUI_FILEPROPERTIESWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WTableView.h>

namespace GCW {
  namespace Gui {

/*!
** \brief Customer Overview
**
**
*/
class FilePropertiesWidget
: public Wt::WContainerWidget
{
  public:

    FilePropertiesWidget();

  private:

    void do_applyGnuCashewExtensions();

};  // endclass FilePropertiesWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_FILEPROPERTIESWIDGET_H___


