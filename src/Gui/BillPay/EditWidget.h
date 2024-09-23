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
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WTabWidget.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>

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

    EditWidget( const std::string & _accountGuid );

    void loadData();
    void saveData();

    Wt::Signal<> & save()   { return m_save;   }
    Wt::Signal<> & cancel() { return m_cancel; }

  private:

    class ComboBox
    : public Wt::WComboBox
    {
      public:
        ComboBox();
    };

    Wt::Signal<> m_save;
    Wt::Signal<> m_cancel;
    Wt::Signal<> m_delete;

    std::string m_accountGuid;

    Wt::WPushButton * m_pbSave    = nullptr;
    Wt::WPushButton * m_pbCancel  = nullptr;
    Wt::WPushButton * m_pbDelete  = nullptr;
    ComboBox        * m_key       = nullptr;
    Wt::WLineEdit   * m_dueDay    = nullptr;
    Wt::WLineEdit   * m_minimum   = nullptr;
    Wt::WLineEdit   * m_budget    = nullptr;
    Wt::WLineEdit   * m_nickname  = nullptr;
    Wt::WLineEdit   * m_group     = nullptr;
    Wt::WLineEdit   * m_limit     = nullptr;
    Wt::WLineEdit   * m_actual    = nullptr;
    Wt::WCheckBox   * m_ap        = nullptr;
    Wt::WCheckBox   * m_isActive  = nullptr;
    Wt::WCheckBox   * m_isVisible = nullptr;
    Wt::WCheckBox   * m_autoPay   = nullptr;
    Wt::WCheckBox   * m_payNow    = nullptr;
    Wt::WTextArea   * m_note      = nullptr;
    Wt::WLineEdit   * m_last4     = nullptr;
    Wt::WLabel      * m_label     = nullptr;
    Wt::WImage      * m_image     = nullptr;
    Wt::WTabWidget  * m_tabWidget = nullptr;
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

    EditWidgetDialog( const std::string & _accountGuid );

  private:

}; // endclass EditWidgetDialog

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_EDITWIDGET_H___


