#line 2 "src/Gui/TransactionDetailWidget.cpp"

#include <Wt/WDateEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WSuggestionPopup.h>
#include <Wt/WText.h>
#include <Wt/WTemplate.h>
#include <Wt/WTableView.h>
#include <Wt/WTheme.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WMessageBox.h>

#include "../define.h"
#include "../Eng/TransactionManager.h"
#include "TransactionDetailWidget.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * */


GCW::Gui::TransactionDetailWidget::
TransactionDetailWidget( const std::string & _tx_guid )
: Wt::WContainerWidget(),
  m_tx_guid( _tx_guid )
{

  auto templt = addNew< Wt::WTemplate >( TR("gcw.AccountRegister.details.contents") );

  mtxt_guid        = templt-> bindNew< Wt::WText  >( "guid"          );
  mtxt_currency    = templt-> bindNew< Wt::WText  >( "currency_guid" );
  mtxt_num         = templt-> bindNew< Wt::WText  >( "num"           );
  mtxt_post_date   = templt-> bindNew< Wt::WText  >( "post_date"     );
  mtxt_enter_date  = templt-> bindNew< Wt::WText  >( "enter_date"    );
  mtxt_description = templt-> bindNew< Wt::WText  >( "description"   );
  m_splitsTable    = templt-> bindNew< Wt::WTable >( "splitsTable"   );

} // endTransactionDetailWidget()



auto
GCW::Gui::TransactionDetailWidget::
setTxGuid( const std::string & _tx_guid )-> void
{

} // endsetTxGuid( const std::string & _tx_guid )-> void



auto
GCW::Gui::TransactionDetailWidget::
setSplitGuid( const std::string & _guid )-> void
{
  auto transMan = GCW::Eng::Transaction::Manager();
  transMan.loadSplit( _guid );
  mtxt_guid        -> setText( transMan.transactionItem()-> guid()          );
  mtxt_currency    -> setText( transMan.transactionItem()-> currency_guid() );
  mtxt_num         -> setText( transMan.transactionItem()-> num()           );
  mtxt_post_date   -> setText( transMan.transactionItem()-> post_date()     );
  mtxt_enter_date  -> setText( transMan.transactionItem()-> enter_date()    );
  mtxt_description -> setText( transMan.transactionItem()-> description()   );

  m_splitsTable-> clear();
  int row = 0;
  for( auto splitItem : transMan.splits() )
  {
    m_splitsTable-> elementAt( row, 0 )-> addNew< GCW::Gui::TransactionDetailWidget::SplitWidget >( splitItem-> guid() );
  }

} // endsetSplitGuid( const std::string & _guid )-> void


auto
GCW::Gui::TransactionDetailWidget::
saveData()-> void
{
  // nothing to do, not saving yet
}


GCW::Gui::TransactionDetailWidget::SplitWidget::
SplitWidget( const std::string & _guid )
: Wt::WContainerWidget(),
  m_guid( _guid )
{

  auto splitItem = GCW::Dbo::Splits::load( _guid );

  auto templt = addNew< Wt::WTemplate >( TR("gcw.AccountRegister.details.contents.split") );

  auto _reconcile_state = [splitItem]()
  {
    std::string retVal = splitItem-> reconcile_state();

    if( splitItem-> reconcile_state() == "y" )
      retVal += " (reconciled)";

    if( splitItem-> reconcile_state() == "n" )
      retVal += " (not reconciled)";

    if( splitItem-> reconcile_state() == "c" )
      retVal += " (cleared)";

    retVal += " " + splitItem-> reconcile_date();

    return retVal;

  };

  templt-> bindString( "guid",      splitItem-> guid()            );
  templt-> bindString( "account",   GCW::Dbo::Accounts::fullName( splitItem-> account_guid() ) );
  templt-> bindString( "memo",      splitItem-> memo()            );
  templt-> bindString( "action",    splitItem-> action()          );
  templt-> bindString( "reconcile", _reconcile_state()            );
  templt-> bindString( "value",     splitItem-> valueAsString()   );

} // endTransactionDetailWidget()


