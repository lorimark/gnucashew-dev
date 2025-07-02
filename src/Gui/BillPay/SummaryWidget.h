#line 2 "src/Gui/BillPay/SummaryWidget.h"

#ifndef __GUI_BILLPAY_SUMMARYWIDGET_H___
#define __GUI_BILLPAY_SUMMARYWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \brief Summary Widget
**
** Bill Pay Summary Widget
**

*/
class SummaryWidget
: public Wt::WContainerWidget
{
  public:

    SummaryWidget( );

      auto setMonth( int _month )-> void ;

  private:

    Wt::WText * m_text = nullptr ;

}; // endclass SummaryWidget

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_SUMMARYWIDGET_H___


