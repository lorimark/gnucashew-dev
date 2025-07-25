#line 2 "src/Gui/BillPay/SummaryWidget.cpp"

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
  m_title-> setText( Wt::WString( "Selected Month: {1}" ).arg( m_month ) );

  m_table-> clear();
  m_table-> setStyleClass( "SummaryTable" );
  int row = 0;
  for( auto split : splits() )
  {
    auto splitItem = GCW::Dbo:: Splits       ::byGuid( split.guid                 );
    auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid()      );
    auto acctItem  = GCW::Dbo:: Accounts     ::byGuid( splitItem-> account_guid() );

    m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( split.day ) );
    m_table-> elementAt( row, 1 )-> addNew< Wt::WText >( acctItem-> name()  );
    m_table-> elementAt( row, 2 )-> addNew< Wt::WText >( split.bill  );
    m_table-> elementAt( row, 3 )-> addNew< Wt::WText >( splitItem-> valueAsString() );

    row++;

  } // endfor( auto splitGuid : splits() )

} // endloadData()-> void


auto
GCW::Gui::BillPay::SummaryWidget::
splits()-> std::vector< Split_t >
{
  std::vector< Split_t > retVal;

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
          /*
          ** there is a bp-account, and the pay-from account.  We want the
          **  pay-from account.
          */
          if( split-> account_guid() != bpItem.accountGuid() )
          {
            /*
            ** gather up the relevant split info and stuff it
            */
            Split_t spt;
            spt.day   = txItem-> post_date_as_date().date().day();
            spt.guid  = split-> guid();
            spt.bank  = GCW::Dbo::Accounts::fullName( split-> account_guid() );
            spt.bill  = bpItem.nickname();
            spt.value = split-> value();
            retVal.push_back( spt );

#ifdef NEVER
            std::cout << __FILE__ << ":" << __LINE__
              << " " << txItem-> post_date_as_date().date().day()
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

} //  endsplits()-> std::vector< Split_t >



