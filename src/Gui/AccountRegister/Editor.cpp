#line 2 "src/Gui/AccountRegister/Editor.cpp"

#include <Wt/WDateEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WSuggestionPopup.h>
#include <Wt/WText.h>
#include <Wt/WTableView.h>
#include <Wt/WTheme.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WMessageBox.h>

#include "../define.h"
#include "../App.h"
#include "../Dbo/Accounts/Accounts.h"
#include "../Dbo/Prefrences.h"
#include "../Dbo/Splits/Splits.h"
#include "../Eng/TransactionManager.h"
#include "DelegateBase.h"
#include "DelegateAccount.h"
#include "DelegateBalance.h"
#include "DelegateDate.h"
#include "DelegateHeader.h"
#include "DelegateReconcile.h"
#include "DelegateSuggestion.h"
#include "DelegateValue.h"
#include "SuggestionPopup.h"
#include "Editor.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * */


GCW::Gui::AccountRegister::Editor::
Editor()
{
} // endAccountRegisterEditor()

GCW::Gui::AccountRegister::Editor::
Editor( GCW::Gui::TableView * _tableView )
: m_tableView( _tableView )
{
  m_delegateHeader = std::static_pointer_cast< DelegateHeader     >( tableView()-> headerItemDelegate()       );
  m_delegateDate   = std::static_pointer_cast< DelegateDate       >( tableView()-> itemDelegateForColumn( 0 ) );
  m_delegateNum    = std::static_pointer_cast< DelegateSuggestion >( tableView()-> itemDelegateForColumn( 1 ) );
  m_delegateMemo   = std::static_pointer_cast< DelegateSuggestion >( tableView()-> itemDelegateForColumn( 2 ) );
  m_delegateAcct   = std::static_pointer_cast< DelegateAccount    >( tableView()-> itemDelegateForColumn( 3 ) );
  m_delegateReco   = std::static_pointer_cast< DelegateReconcile  >( tableView()-> itemDelegateForColumn( 4 ) );
  m_delegateIn     = std::static_pointer_cast< DelegateValue      >( tableView()-> itemDelegateForColumn( 5 ) );
  m_delegateOut    = std::static_pointer_cast< DelegateValue      >( tableView()-> itemDelegateForColumn( 6 ) );
  m_delegateBal    = std::static_pointer_cast< DelegateBalance    >( tableView()-> itemDelegateForColumn( 7 ) );

} // endEditor( GCW::Gui::TableView * _tableView )

auto
GCW::Gui::AccountRegister::Editor::
applyDelegates( GCW::Gui::TableView * _tableView )-> void
{
  m_tableView = _tableView;

  m_delegateHeader = std::make_shared< DelegateHeader     >( this );
  m_delegateDate   = std::make_shared< DelegateDate       >( this );
  m_delegateNum    = std::make_shared< DelegateSuggestion >( this );
  m_delegateMemo   = std::make_shared< DelegateSuggestion >( this );
  m_delegateAcct   = std::make_shared< DelegateAccount    >( this );
  m_delegateReco   = std::make_shared< DelegateReconcile  >( this );
  m_delegateIn     = std::make_shared< DelegateValue      >( this );
  m_delegateOut    = std::make_shared< DelegateValue      >( this );
  m_delegateBal    = std::make_shared< DelegateBalance    >( this );

  tableView()-> setHeaderItemDelegate    (    m_delegateHeader );
  tableView()-> setItemDelegateForColumn ( 0, m_delegateDate   );
  tableView()-> setItemDelegateForColumn ( 1, m_delegateNum    );
  tableView()-> setItemDelegateForColumn ( 2, m_delegateMemo   );
  tableView()-> setItemDelegateForColumn ( 3, m_delegateAcct   );
  tableView()-> setItemDelegateForColumn ( 4, m_delegateReco   );
  tableView()-> setItemDelegateForColumn ( 5, m_delegateIn     );
  tableView()-> setItemDelegateForColumn ( 6, m_delegateOut    );
  tableView()-> setItemDelegateForColumn ( 7, m_delegateBal    );

} // endapplyDelegates( GCW::Gui::TableView * _tableView )-> void

auto
GCW::Gui::AccountRegister::Editor::
editRow( Wt::WModelIndex _index )-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

  return;

#ifndef NEVER
  if( _index.isValid() )
  {
    std::cout << __FILE__ << ":" << __LINE__
      << " " << __FUNCTION__ << "(" << _index.row() << "," << _index.column() << ")"
      << std::endl;
  }
#endif

  /*
  ** before editing the row, ask if the user wants to
  **  save the existing row
  */
  if( m_index.isValid() )
  {
    if( m_index.row() != _index.row() )
    {



//      Wt::WMessageBox::show( "Data Changed", "Do you want to record these changes?", Wt::StandardButton::Yes | Wt::StandardButton::No );
    }
  }

  if( _index.isValid() )
  {
    /*
    ** if more than one other row is selected (should NEVER happen!)
    **  then for sure we'll clear any selections.  But, if the row
    **  number is the same, then we don't want to clear, since it's
    **  the same row.
    */
    if( tableView()-> selectedIndexes().size() > 1
     || tableView()-> selectedIndexes().begin()-> row() != _index.row()
      )
    {
      tableView()-> clearSelection();
      tableView()-> closeEditors( true );
    }

    /*
    **  make sure it is in view.
    */
    tableView()-> scrollTo( _index );

    for( int column=0; column< tableView()-> model()-> columnCount(); column++ )
    {
      tableView()-> edit( tableView()-> model()-> index( _index.row(), column ) );
    }

  } // endif( _index.isValid() )

  /*
  ** remember what we're editing
  */
  m_index = _index;

} // endeditRow( Wt::WModelIndex _index )-> void


auto
GCW::Gui::AccountRegister::Editor::
setDirty( Wt::WModelIndex _index ) const-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << _index.isValid() << std::endl;

  std::cout << __FILE__ << ":" << __LINE__ << " " << m_index.isValid() << std::endl;

  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << "(): " << m_index.isValid()
    << "(): " << _index.row()
    << std::endl;
#endif

} // endsetDirty( Wt::WModelIndex _index )-> void


