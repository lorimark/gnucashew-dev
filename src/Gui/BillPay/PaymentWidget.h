#line 2 "src/Gui/BillPay/PaymentWidget.h"

#ifndef __GUI_BILLPAY_PAYMENTWIDGET_H___
#define __GUI_BILLPAY_PAYMENTWIDGET_H___

#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDateEdit.h>
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
#include "../AccountSuggestionEdit.h"
#include "Item.h"

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

    auto bpGuid() const-> const std::string & { return m_bpGuid; }

    auto loadData()-> void ;
    auto saveData()-> void ;

  private:

    auto table()-> Wt::WTable * { return m_table; }

    /*!
    ** \brief Value
    **
    ** This returns +val or -val depending on if the value
    **  was entered in to the 'debit' 'credit' column.
    **
    */
    auto value()-> GCW_NUMERIC ;

    std::string             m_bpGuid            ;
    Wt::WTable            * m_table   = nullptr ;
    Wt::WDateEdit         * m_date    = nullptr ;
    Wt::WLineEdit         * m_num     = nullptr ;
    Wt::WLineEdit         * m_desc    = nullptr ;
    AccountSuggestionEdit * m_acct    = nullptr ;
    Wt::WLineEdit         * m_recon   = nullptr ;
    Wt::WLineEdit         * m_debit   = nullptr ;
//    Wt::WLineEdit         * m_credit  = nullptr ;
    Wt::WTextArea         * m_confirm = nullptr ;

    std::vector< std::vector< Wt::WFormWidget * > > m_tableWidgets ;

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


