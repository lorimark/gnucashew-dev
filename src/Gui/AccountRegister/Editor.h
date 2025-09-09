#line 2 "src/Gui/AccountRegister/Editor.h"

#ifndef __GUI_ACCOUNTREGISTER_EDITOR_H___
#define __GUI_ACCOUNTREGISTER_EDITOR_H___

#include <Wt/Json/Object.h>
#include <Wt/WBatchEditProxyModel.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WSortFilterProxyModel.h>
#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WItemDelegate.h>
#include <Wt/WPopupMenu.h>

#include "../../GnuCashew.h"
#include "../TableView.h"
#include "Model.h"

namespace GCW {
  namespace Gui {
    namespace AccountRegister {
      class DelegateHeader     ;
      class DelegateDate       ;
      class DelegateSuggestion ;
      class DelegateSuggestion ;
      class DelegateAccount    ;
      class DelegateReconcile  ;
      class DelegateValue      ;
      class DelegateValue      ;
      class DelegateBalance    ;


/*!
** \brief Account Register Editor
**
** This object is a controller for editing of line items in the Account Register.  The editor
**  is a local(friend?) to the account register object that provides the delegates for the
**  table view, and manipulates the delegates in relation to each other so as to be able to
**  handle tabbing, up and down arrowing, and so on, within the table view, and keeping all
**  the editors open, and saving them correctly when the user is done bla bla bla.
*/
class Editor
{
  public:

    Editor();

    auto setTableView( GCW::Gui::TableView * _tableView )-> void ;

    /*!
    ** \brief Table View
    */
    auto tableView()-> GCW::Gui::TableView * { return m_tableView; }

    /*!
    ** \brief Edit Row
    */
    auto editRow( Wt::WModelIndex _index )-> void ;

    auto setDirty( Wt::WModelIndex _index ) const-> void ;

    /*!
    ** \brief Delegate Handles
    **
    ** Here we're going to hold on to the Delegate handles so
    **  we can interact with the UI a little bit
    */
    std::shared_ptr< DelegateHeader     > m_delegateHeader ; //
    std::shared_ptr< DelegateDate       > m_delegateDate   ; // 0
    std::shared_ptr< DelegateSuggestion > m_delegateNum    ; // 1
    std::shared_ptr< DelegateSuggestion > m_delegateMemo   ; // 2
    std::shared_ptr< DelegateAccount    > m_delegateAcct   ; // 3
    std::shared_ptr< DelegateReconcile  > m_delegateReco   ; // 4
    std::shared_ptr< DelegateValue      > m_delegateIn     ; // 5
    std::shared_ptr< DelegateValue      > m_delegateOut    ; // 6
    std::shared_ptr< DelegateBalance    > m_delegateBal    ; // 7

    Wt::WModelIndex                       m_index               ;
    GCW::Gui::TableView                 * m_tableView = nullptr ;

};  // endclass Editor

    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_ACCOUNTREGISTER_EDITOR_H___



