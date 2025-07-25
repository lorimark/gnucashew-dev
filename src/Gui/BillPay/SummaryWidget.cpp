#line 2 "src/Gui/BillPay/SummarytWidget.cpp"

#include <Wt/WMenuItem.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WMessageBox.h>

#include "../../Eng/AccountComboModel.h"
#include "../../Glb/Core.h"
#include "BillPay.h"

GCW::Gui::BillPay::SummaryWidget::
SummaryWidget()
: Wt::WContainerWidget()
{
  addStyleClass( "SummaryWidget" );

  m_title = addWidget( std::make_unique< Wt::WText  >() );
  m_table = addWidget( std::make_unique< Wt::WTable >() );

} // endSummaryWidget( const std::string & _accountGuid )

auto
GCW::Gui::BillPay::SummaryWidget::
setMonth( int _month )-> void
{
  m_month = _month;
  m_table-> clear();
  m_title-> setText( Wt::WString( "Selected Month: {1}" ).arg( m_month ) );

  for( auto splitGuid : splitGuids() )
  {
    auto splitItem = GCW::Dbo:: Splits       ::byGuid( splitGuid                  );
    auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid()      );
    auto acctItem  = GCW::Dbo:: Accounts     ::byGuid( splitItem-> account_guid() );

    std::cout << __FILE__ << ":" << __LINE__
      << " " << splitGuid
      << " " << GCW::Dbo::Accounts::fullName( acctItem-> guid() )
      << " " << splitItem-> value()
      << " " << txItem-> post_date_as_date().date().day()
      << std::endl;

  } // endfor( auto splitGuid : splitGuids() )


} // endloadData()-> void


auto
GCW::Gui::BillPay::SummaryWidget::
splitGuids()-> std::set< std::string >
{
  std::set< std::string > retVal;

  /*
  ** here we loop through all the bp items and look at all the transactions
  **  within this month.  We then see if the transaction was used for
  **  bill-pay (num='bp') and will then generate a full report on all the
  **  payments made.
  */
  for( auto bpItem : bpItems() )
  {
    /*
    ** get all the transactions that happened for this account for this month
    */
    auto txItems = GCW::Dbo::Transactions::byAccountMonth( bpItem.accountGuid(), m_month );

    /*
    ** if transactions happened, get them open and see if they should be in the summary report
    */
    for( auto txItem : txItems )
    {
      /*
      ** if this transaction is a bp transction, we want it in the summary report
      */
      if( txItem-> num() == "bp" )
      {
        /*
        ** loop through all the splits
        */
        for( auto split : GCW::Dbo::Splits::byTransaction( txItem-> guid() ) )
        {
          if( split-> account_guid() != bpItem.accountGuid() )
          {
            retVal.insert( split-> guid() );

#ifdef NEVER
            std::cout << __FILE__ << ":" << __LINE__
              << " " << split-> guid()
              << " " << bpItem.accountGuid()
              << " " << split-> account_guid()
              << " " << GCW::Dbo::Accounts::fullName( split-> account_guid() )
              << " " << bpItem.nickname()
              << " " << split-> value()
              << std::endl;
#endif

          } // endif( ..other account.. )

        } // endfor( auto split : GCW::Dbo::Splits::byTransaction( txItem-> guid() ) )

      } // endif( txItem-> num() == "bp" )

    } // endfor( auto txItem : txItems )

  } // endfor( auto bpItem : bpItems() )

  return retVal;

} //  endsplitGuids()-> std::vector< std::string >



