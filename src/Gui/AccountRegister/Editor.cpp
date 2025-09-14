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
} // endEditor( GCW::Gui::TableView * _tableView )


auto
GCW::Gui::AccountRegister::Editor::
model( Wt::WModelIndex _index )-> Model *
{
  return
    const_cast< Model * >( static_cast< const Model* >( _index.model() ) );

} // endmodel( Wt::WModelIndex _index )-> Model *

auto
GCW::Gui::AccountRegister::Editor::
delegateHeader()-> std::shared_ptr< DelegateHeader >
{
  return
    std::static_pointer_cast< DelegateHeader >
    (
     tableView()-> headerItemDelegate()
    );
}

auto
GCW::Gui::AccountRegister::Editor::
delegateDate()-> std::shared_ptr< DelegateDate >
{
  return
    std::static_pointer_cast< DelegateDate >
    (
     tableView()-> itemDelegateForColumn( asInt( Col::DATE ) )
    );
}

auto
GCW::Gui::AccountRegister::Editor::
delegateNum()-> std::shared_ptr< DelegateSuggestion >
{
  return
    std::static_pointer_cast< DelegateSuggestion >
    (
     tableView()-> itemDelegateForColumn( asInt( Col::ACTION ) )
    );
}

auto
GCW::Gui::AccountRegister::Editor::
delegateMemo()-> std::shared_ptr< DelegateSuggestion >
{
  return
    std::static_pointer_cast< DelegateSuggestion >
    (
     tableView()-> itemDelegateForColumn( asInt( Col::DESCRIPTION ) )
    );
}

auto
GCW::Gui::AccountRegister::Editor::
delegateAcct()-> std::shared_ptr< DelegateAccount >
{
  return
    std::static_pointer_cast< DelegateAccount >
    (
     tableView()-> itemDelegateForColumn( asInt( Col::TRANSFER ) )
    );
}

auto
GCW::Gui::AccountRegister::Editor::
delegateReco()-> std::shared_ptr< DelegateReconcile >
{
  return
    std::static_pointer_cast< DelegateReconcile >
    (
     tableView()-> itemDelegateForColumn( asInt( Col::RECONCILE ) )
    );
}

auto
GCW::Gui::AccountRegister::Editor::
delegateDr()-> std::shared_ptr< DelegateValue >
{
  return
    std::static_pointer_cast< DelegateValue >
    (
     tableView()-> itemDelegateForColumn( asInt( Col::DEBIT ) )
    );
}

auto
GCW::Gui::AccountRegister::Editor::
delegateCr()-> std::shared_ptr< DelegateValue >
{
  return
    std::static_pointer_cast< DelegateValue >
    (
     tableView()-> itemDelegateForColumn( asInt( Col::CREDIT ) )
    );
}

auto
GCW::Gui::AccountRegister::Editor::
delegateBal()-> std::shared_ptr< DelegateBalance >
{
  return
    std::static_pointer_cast< DelegateBalance >
    (
     tableView()-> itemDelegateForColumn( asInt( Col::BALANCE ) )
    );
}

auto
GCW::Gui::AccountRegister::Editor::
applyDelegates( GCW::Gui::TableView * _tableView )-> void
{
  _tableView-> setHeaderItemDelegate    (                            std::make_shared< DelegateHeader     >() );
  _tableView-> setItemDelegateForColumn ( asInt( Col::DATE        ), std::make_shared< DelegateDate       >() );
  _tableView-> setItemDelegateForColumn ( asInt( Col::ACTION      ), std::make_shared< DelegateSuggestion >() );
  _tableView-> setItemDelegateForColumn ( asInt( Col::DESCRIPTION ), std::make_shared< DelegateSuggestion >() );
  _tableView-> setItemDelegateForColumn ( asInt( Col::TRANSFER    ), std::make_shared< DelegateAccount    >() );
  _tableView-> setItemDelegateForColumn ( asInt( Col::RECONCILE   ), std::make_shared< DelegateReconcile  >() );
  _tableView-> setItemDelegateForColumn ( asInt( Col::DEBIT       ), std::make_shared< DelegateValue      >() );
  _tableView-> setItemDelegateForColumn ( asInt( Col::CREDIT      ), std::make_shared< DelegateValue      >() );
  _tableView-> setItemDelegateForColumn ( asInt( Col::BALANCE     ), std::make_shared< DelegateBalance    >() );

} // endapplyDelegates( GCW::Gui::TableView * _tableView )-> void

auto
GCW::Gui::AccountRegister::Editor::
editRow( Wt::WModelIndex _index )-> void
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(" << _index.row() << "," << _index.column() << ")" << std::endl;

  auto row = _index.row();
  auto mdl = model( _index );

  /*
  ** edit all the columns
  */
  for( int col=0; col< mdl-> columnCount(); col++ )
  {
    auto item  = mdl-> item( row, col );
    auto index = mdl-> indexFromItem( item );

    m_tableView-> edit( index );

  } // for( ..all columns except balance.. )

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


