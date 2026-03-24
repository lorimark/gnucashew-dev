#line 2 "src/Gui/AccountEditor.h"

#ifndef __GUI_ACCOUNTEDITOR_H___
#define __GUI_ACCOUNTEDITOR_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTabWidget.h>
#include <Wt/WTemplateFormView.h>

#include "../GnuCashew.h"
#include "AccountsTreeView.h"

namespace GCW {
  namespace Gui {

/*!
** \brief Account Editor
**
*/
class AccountEditor
: public Wt::WContainerWidget
{
  class Tab1
  : public Wt::WContainerWidget
  {
    public:

      Tab1();

      Wt::WLineEdit   * m_name           = nullptr ;
      Wt::WLineEdit   * m_code           = nullptr ;
      Wt::WLineEdit   * m_desc           = nullptr ;
      Wt::WComboBox   * m_parent         = nullptr ;
      Wt::WComboBox   * m_accountType    = nullptr ;
      Wt::WComboBox   * m_security       = nullptr ;
      Wt::WComboBox   * m_fraction       = nullptr ;
      Wt::WPushButton * m_color          = nullptr ;
      Wt::WTextArea   * m_notes          = nullptr ;
      Wt::WCheckBox   * m_placeholder    = nullptr ;
      Wt::WCheckBox   * m_hidden         = nullptr ;
      Wt::WCheckBox   * m_autoTransfer   = nullptr ;
      Wt::WCheckBox   * m_taxRelated     = nullptr ;
      Wt::WCheckBox   * m_openingBalance = nullptr ;

      auto loadData( const std::string & _accountGuid )-> void ;
      auto saveData( const std::string & _accountGuid )-> void ;

  }; // endclass Tab1

  class Tab2
  : public Wt::WContainerWidget
  {
    public:

      Tab2();

      auto loadData( const std::string & _accountGuid )-> void ;
      auto saveData( const std::string & _accountGuid )-> void ;

  }; // endclass Tab2

  public:

    AccountEditor();

    Wt::WTabWidget * tabWidget() { return m_tabWidget; }

    auto tab1()-> Tab1 * { return m_tab1; }
    auto tab2()-> Tab2 * { return m_tab2; }

    auto loadData( const std::string & _accountGuid )-> void ;
    auto saveData( const std::string & _accountGuid )-> void ;

    auto isDirty   () const-> bool ;
    auto save      ()      -> Wt::Signal<> & { return m_save;   }
    auto cancel    ()      -> Wt::Signal<> & { return m_cancel; }

  private:

    auto do_help   ()-> void ;
    auto do_cancel ()-> void ;
    auto do_ok     ()-> void ;

    std::string                  m_accountGuid              ;
    Wt::Signal<>                 m_save                     ;
    Wt::Signal<>                 m_cancel                   ;
    Wt::WText                  * m_accountName    = nullptr ;
    Wt::WTabWidget             * m_tabWidget      = nullptr ;
    Tab1                       * m_tab1           = nullptr ;
    Tab2                       * m_tab2           = nullptr ;

}; // endclass AccountEditor

class AccountEditorDialog
: public Wt::WDialog
{
  public:

    AccountEditorDialog( const std::string & _accountGuid );

  private:

}; // endclass AccountEditorDialog

  } //endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_ACCOUNTSWIDGET_H___



