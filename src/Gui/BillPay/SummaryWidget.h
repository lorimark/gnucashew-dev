#line 2 "src/Gui/BillPay/SummaryWidget.h"

#ifndef __GUI_BILLPAY_SUMMARYWIDGET_H___
#define __GUI_BILLPAY_SUMMARYWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>

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

    /*!
    ** \brief Splits
    **
    ** This returns all the splits in the selected month
    **
    */
    auto splitGuids()-> std::set< std::string > ;

    int          m_month = -1      ;
    Wt::WText  * m_title = nullptr ;
    Wt::WTable * m_table = nullptr ;

}; // endclass SummaryWidget

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_SUMMARYWIDGET_H___


