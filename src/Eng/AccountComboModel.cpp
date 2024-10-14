#line 2 "src/Eng/AccountComboModel.cpp"

#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>

#include "../App.h"
#include "../Dbo/Accounts/Accounts.h"
#include "AccountComboModel.h"

GCW::Eng::AccountComboModel::
AccountComboModel()
: Wt::WStandardItemModel( 0, 2 )
{

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  for( auto accountItem : GCW::Dbo::Accounts::allAccounts() )
  {
     std::vector< std::unique_ptr< Wt::WStandardItem > > row;
     row.push_back( std::make_unique< Wt::WStandardItem >( accountItem-> guid()                                 ) );
     row.push_back( std::make_unique< Wt::WStandardItem >( GCW::Dbo::Accounts::fullName( accountItem-> guid() ) ) );
     appendRow( std::move( row ) );

  } // endfor( auto accountItem : GCW::Dbo::Accounts::allAccounts() )

} // endAccountSuggestionModel()


