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
#include <Wt/WTable.h>
#include <Wt/WTemplate.h>
#include <Wt/WTabWidget.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WTextEdit.h>

#include "../AccountComboBox.h"

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

    class PaymentTable
    : public Wt::WContainerWidget
    {
      public:

        PaymentTable();

        Wt::WTable * m_table = nullptr ;

    }; // endclass PaymentTable

  public:

    PaymentWidget( const std::string & _bpGuid );

    auto loadData()-> void ;
    auto saveData()-> void ;

  private:

    std::string m_bpGuid;

    Wt::WPushButton  * m_pbSave    = nullptr ;
    Wt::WPushButton  * m_pbCancel  = nullptr ;
    PaymentTable     * m_payTable  = nullptr ;
    Wt::WLineEdit    * m_trans     = nullptr ;
    Wt::WLineEdit    * m_date      = nullptr ;
    Wt::WLineEdit    * m_memo      = nullptr ;
    Wt::WLineEdit    * m_amount    = nullptr ;
    Wt::WTextArea    * m_confirm   = nullptr ;

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


