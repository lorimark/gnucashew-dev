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

      Tab1( const std::string & _accountGuid );

      Wt::WLineEdit              * m_name           = nullptr ;
      Wt::WLineEdit              * m_code           = nullptr ;
      Wt::WLineEdit              * m_desc           = nullptr ;
      GCW::Gui::AccountsTreeView * m_parent         = nullptr ;
      Wt::WLineEdit              * m_accountType    = nullptr ;
      Wt::WLineEdit              * m_security       = nullptr ;
      Wt::WLineEdit              * m_fraction       = nullptr ;
      Wt::WLineEdit              * m_color          = nullptr ;
      Wt::WLineEdit              * m_notes          = nullptr ;
      Wt::WLineEdit              * m_placeholder    = nullptr ;
      Wt::WLineEdit              * m_hidden         = nullptr ;
      Wt::WLineEdit              * m_autoTransfer   = nullptr ;
      Wt::WLineEdit              * m_taxRelated     = nullptr ;
      Wt::WLineEdit              * m_openingBalance = nullptr ;

      std::string m_accountGuid;
  };

  class Tab2
  : public Wt::WContainerWidget
  {
    public:

      Tab2( const std::string & _accountGuid );

      std::string m_accountGuid;
  };

  public:

    AccountEditor( const std::string & _accountGuid );

    Wt::WTabWidget * tabWidget() { return m_tabWidget; }

    auto t1()-> Tab1 * { return m_t1; }
    auto t2()-> Tab2 * { return m_t2; }

    auto save   ()-> Wt::Signal<> & { return m_save;   }
    auto cancel ()-> Wt::Signal<> & { return m_cancel; }

  private:

    auto do_help   ()-> void;
    auto do_cancel ()-> void;
    auto do_ok     ()-> void;

    std::string                  m_accountGuid              ;
    Wt::Signal<>                 m_save                     ;
    Wt::Signal<>                 m_cancel                   ;
    Wt::WTabWidget             * m_tabWidget      = nullptr ;
    Tab1                       * m_t1             = nullptr ;
    Tab2                       * m_t2             = nullptr ;

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



