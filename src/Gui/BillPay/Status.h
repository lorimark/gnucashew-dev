#line 2 "src/Gui/BillPay/Status.h"

#ifndef __GUI_BILLPAY_STATUS_H___
#define __GUI_BILLPAY_STATUS_H___

#include <string>

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \brief Bill Status
**
** Bills get loaded in to the model depending on their status.  A bills
**  status depends on the selected month, and the check-box status
**  for that same month.
**
*/
enum class Status
{
  /// Paid Status
  Paid,

  /// Unpaid Status
  Unpaid,

  /// Disabled Status
  Disabled
};

/*!
** \brief Get Status as String
**
** This returns the 'string' representation of the status code.
**
*/
std::string asString( Status _status );

/*!
** \brief Get Status as Style Class
**
** The style-class is used to alter the display rendering based
**  on the status.
**
*/
std::string asStyleClass( Status _status );

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_STATUS_H___



