#line 2 "src/Eng/AccountsTreeViewModel.cpp"

#include <any>

#include <Wt/Json/Array.h>
#include <Wt/Json/Parser.h>
#include <Wt/Json/Serializer.h>
#include <Wt/WText.h>
#include <Wt/WTreeTableNode.h>
#include <Wt/WVBoxLayout.h>

#include "../define.h"
#include "../GnuCashew.h"
#include "AccountsTreeViewModel.h"

auto
GCW::Eng::AccountsTreeViewModel::
load( int _columnCount )-> void
{
  m_columnCount = _columnCount;

  /*
  ** If the session isn't open then there's nothing to load.
  **
  */
  if( !GCW::app()-> gnucashew_session().isOpen() )
    return;

  /*
  ** load the data in to the model
  **
  */
  auto rootAccount = GCW::Dbo::Accounts::rootAccount();
  if( rootAccount-> guid() != "" )
  {
    load( invisibleRootItem(), rootAccount );

    /*
    ** define all the columns
    **
    */
    int col = 0;
    std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;

    if( col < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      setHeaderData( col++, TR( "gcw.AccountsTreeView.column.accountname"      ) );
    }

    if( col < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      setHeaderData( col++, TR( "gcw.AccountsTreeView.column.accountcode"      ) );
    }

    if( col < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      setHeaderData( col++, TR( "gcw.AccountsTreeView.column.description"      ) );
    }

    if( col < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      setHeaderData( col++, TR( "gcw.AccountsTreeView.column.taxinfo"          ) );
    }

    if( col < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      setHeaderData( col++, TR( "gcw.AccountsTreeView.column.notes"            ) );
    }

    if( col < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      setHeaderData( col++, TR( "gcw.AccountsTreeView.column.futureminimumusd" ) );
    }

    if( col < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      setHeaderData( col++, TR( "gcw.AccountsTreeView.column.total"            ) );
    }


  } // endif( rootAccount-> guid() != "" )

  std::cout << __FILE__ << ":" << __LINE__ << " columnCount:" << columnCount() << std::endl;

} // endload( int _columnCount )-> void

auto
GCW::Gui::AccountsTreeView::Model::
load( Wt::WStandardItem * _treeItem, GCW::Dbo::Accounts::Item::Ptr _parentAccount )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  /*
  ** This 'builds' a row of account info, with the account
  **  'name' on the first column, and other bits about the account
  **  on the remaining columns.
  **
  */
  auto _append = [=]( Wt::WStandardItem * _item, GCW::Dbo::Accounts::Item::Ptr _accountItem )
  {
    std::vector< std::unique_ptr< Wt::WStandardItem > > columns;

    auto accountName = std::make_unique< Wt::WStandardItem >( _accountItem-> name() );
    auto retVal = accountName.get();
    accountName-> setToolTip( _accountItem-> guid() );

#ifdef NEVER
    if( _accountItem-> hasColor() )
    {
      auto accountColor = _accountItem-> color();
      std::cout << __FILE__ << ":" << __LINE__ << " " << accountColor << std::endl;
    }
#endif

    /*
    ** set the 'model->data::User' element to contain the guid of the account, so
    **  we can recover it later.
    **
    */
    accountName-> setData( _accountItem-> guid(), Wt::ItemDataRole::User );
    int col = 0;
    std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;

    if( col++ < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      columns.push_back( std::move( accountName ) );
    }

    if( col++ < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      columns.push_back( std::make_unique< Wt::WStandardItem >( _accountItem-> code        () ) );
    }

    if( col++ < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      columns.push_back( std::make_unique< Wt::WStandardItem >( _accountItem-> description () ) );
    }

    if( col++ < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      columns.push_back( std::make_unique< Wt::WStandardItem >() );
    }

    if( col++ < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      columns.push_back( std::make_unique< Wt::WStandardItem >() );
    }

    if( col++ < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      columns.push_back( std::make_unique< Wt::WStandardItem >() );
    }

    if( col++ < m_columnCount )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << col << " " << m_columnCount << std::endl;
      columns.push_back( std::make_unique< Wt::WStandardItem >() );
    }

    _item-> appendRow( std::move( columns ) );

    return retVal;

  }; // end_append()

  /*
  ** Pick up all the accounts that are children to the
  **  specified account.
  **
  */
  auto childAccounts =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Accounts::Item >()
    .where( "parent_guid = ?" )
    .bind( _parentAccount-> guid() )
    .resultList()
    ;

  /*
  ** Loop through each child-account for this parent account
  **
  */
  for( auto account : childAccounts )
  {
    /*
    ** Append the tree-item
    **
    */
    auto  ti = _append( _treeItem, account );

    /*
    ** Perform a recursive-load on this account to pick up
    **  any more child accounts
    **
    */
    load( ti, account );

  } // endfor( auto account : accounts )

} // endload( Wt::WStandardItem * _treeItem, GCW::Dbo::Accounts::Item::Ptr _parentAccount )-> void


