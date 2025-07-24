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
**  for that same month.  The check-box values equate as follows;
**
**  - unpaid  == (no)    unchecked
**  - paid    == (yes)   checked
**  - pending == (maybe) semi-checked
**
** \note these values are internal, not stored
**
*/
enum class Status
{
  /// Unpaid Status
  Unpaid,

  /// Pending Status
  Pending,

  /// Paid Status
  Paid,

  /// Disabled Status
  Inactive
};

/*!
** \brief Get Status as String
**
** This returns the 'string' representation of the status code.
**
*/
auto asString( Status _status )-> std::string ;

/*!
** \brief Get Status as Style Class
**
** The style-class is used to alter the display rendering based
**  on the status.
**
*/
auto asStyleClass( Status _status )-> std::string ;

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_STATUS_H___



