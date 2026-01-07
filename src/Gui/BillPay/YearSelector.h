#line 2 "src/Gui/BillPay/YearSelector.h"

#ifndef __GUI_BILLPAY_YEARSELECTOR_H___
#define __GUI_BILLPAY_YEARSELECTOR_H___

#include <Wt/WComboBox.h>

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \brief Year Selector
**
** This is a combo-box widet containing a list of possible years
**  to use for the bill-pay effort.
**
** This widget self-remembers the last used year.
**
*/
class YearSelector
: public Wt::WComboBox
{
  public:

    YearSelector( );

}; // endclass YearSelector

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_YEARSELECTOR_H___


