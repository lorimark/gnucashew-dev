#line 2 "src/Gui/BillPay/PaymentWidget.h"

#ifndef __GUI_BILLPAY_PAYMENTWIDGET_H___
#define __GUI_BILLPAY_PAYMENTWIDGET_H___

#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WImage.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WSpinBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WTabWidget.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WTextEdit.h>

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \brief Payment Widget
**
** This will pop a dialog to accept a payment
**
*/
class PaymentWidget
: public Wt::WContainerWidget
{
  public:

    PaymentWidget( const std::string & _bpGuid );

  private:

    auto loadData()-> void ;
    auto saveData()-> void ;

    std::string m_bpGuid;

}; // endclass PaymentWidget

/*!
** \brief Edit Widget Dialog
**
** Bill Pay Payment Form editor dialog.
**
*/
class PaymentWidgetDialog
: public Wt::WDialog
{
  public:

    PaymentWidgetDialog( const std::string & _bpGuid );

  private:

}; // endclass PaymentWidgetDialog

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_PAYMENTWIDGET_H___


