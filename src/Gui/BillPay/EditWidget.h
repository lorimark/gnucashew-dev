#line 2 "src/Gui/BillPay/EditWidget.h"

#ifndef __GUI_BILLPAY_EDITWIDGET_H___
#define __GUI_BILLPAY_EDITWIDGET_H___

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

#include "../AccountComboBox.h"

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \brief Edit Widget
**
** Bill Pay Detail Form editor container.
**
*/
class EditWidget
: public Wt::WContainerWidget
{
  public:

    EditWidget( const std::string & _bpGuid );

    auto loadData()-> void ;
    auto saveData()-> void ;

    auto saved     ()-> Wt::Signal<> & { return m_saved;     }
    auto canceled  ()-> Wt::Signal<> & { return m_canceled;  }
    auto deleted   ()-> Wt::Signal<> & { return m_deleted;   }
    auto processed ()-> Wt::Signal<> & { return m_processed; }

  private:

    auto processPayment()-> void ;
    auto accountIsDuplicated()-> bool ;

    Wt::Signal<> m_saved;
    Wt::Signal<> m_canceled;
    Wt::Signal<> m_deleted;
    Wt::Signal<> m_processed;

    std::string m_bpGuid;
    std::string m_lastPaymentDate;

    GCW::Gui::AccountRegister * m_register  = nullptr ;
    Wt::WPushButton           * m_pbSave    = nullptr ;
    Wt::WPushButton           * m_pbCancel  = nullptr ;
    Wt::WPushButton           * m_pbDelete  = nullptr ;
    Wt::WPushButton           * m_pbProcess = nullptr ;
    GCW::Gui::AccountComboBox * m_account   = nullptr ;
    Wt::WSpinBox              * m_dueDay    = nullptr ;
    Wt::WLineEdit             * m_minimum   = nullptr ;
    Wt::WLineEdit             * m_budget    = nullptr ;
    Wt::WLineEdit             * m_nickname  = nullptr ;
    Wt::WSpinBox              * m_group     = nullptr ;
    Wt::WLineEdit             * m_limit     = nullptr ;
    Wt::WLineEdit             * m_actual    = nullptr ;
    Wt::WLineEdit             * m_url       = nullptr ;
    Wt::WCheckBox             * m_ap        = nullptr ;
    Wt::WCheckBox             * m_isActive  = nullptr ;
    Wt::WCheckBox             * m_isVisible = nullptr ;
    Wt::WCheckBox             * m_autoPay   = nullptr ;
    Wt::WCheckBox             * m_payNow    = nullptr ;
    Wt::WTextArea             * m_note      = nullptr ;
//    Wt::WTextEdit             * m_note      = nullptr ;
    Wt::WLineEdit             * m_last4     = nullptr ;
    Wt::WLabel                * m_label     = nullptr ;
    Wt::WImage                * m_image     = nullptr ;
    Wt::WTabWidget            * m_tabWidget = nullptr ;
    std::vector< Wt::WCheckBox* > m_cbx;

}; // endclass EditWidget

/*!
** \brief Edit Widget Dialog
**
** Bill Pay Detail Form editor dialog.
**
*/
class EditWidgetDialog
: public Wt::WDialog
{
  public:

    EditWidgetDialog( const std::string & _bpGuid );

  private:

}; // endclass EditWidgetDialog

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_EDITWIDGET_H___


