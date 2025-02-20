#line 2 "src/Gui/CustomerReportWidget.h"

#ifndef __GUI_CUSTOMERREPORTWIDGET_H___
#define __GUI_CUSTOMERREPORTWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WTableView.h>

namespace GCW {
  namespace Gui {

/*!
** \brief Customer Report
**
**
*/
class CustomerReportWidget
: public Wt::WContainerWidget
{
  public:

    CustomerReportWidget( const std::string & _customerGuid );

  private:

    std::string m_customerGuid;

};  // endclass CustomerReportWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_CUSTOMERREPORTWIDGET_H___


