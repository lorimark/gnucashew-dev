#line 2 "src/Gui/BillPay/SummaryWidget.cpp"

#include <fstream>
#include <filesystem>

#include <Wt/WMenuItem.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WMessageBox.h>

#include "../../Eng/AccountComboModel.h"
#include "../../Glb/Core.h"
#include "BillPay.h"

namespace {

/*
** this produces a 'ordinal suffix' which is a thing
**  that is attached to the end of a number as follows;
**     1st
**     2nd
**     3rd
**     4th
**
*/
auto ordinalSuffix( signed int _number )-> std::string
{
  /*
  ** must be greater than zero to have a suffix
  */
  if( _number > 0 )
  {
    /*
    ** edge detectors
    */
    int lastTwo = _number % 100;
    int lastOne = _number % 10;

    /*
    ** these are straight forward 'th' for the special case
    **  of 11, 12, and 13.
    */
    if( lastTwo >= 11
     && lastTwo <= 13
      )
      return "th";

    /*
    ** switch on 1, 2 or 3 accordingly
    */
    switch( lastOne )
    {
      case 1:  return "st";
      case 2:  return "nd";
      case 3:  return "rd";
      default: return "th";

    } // endswitch()

  } // endif( _number > 0 )

  /*
  ** no suffix
  */
  return "";

} // endauto ordinalSuffix( signed int number )-> std::string

} // endnamespace {


GCW::Gui::BillPay::SummaryWidget::
SummaryWidget()
: Wt::WContainerWidget()
{
  addStyleClass( "SummaryWidget" );

  m_title = addWidget( std::make_unique< Wt::WText  >() );
  m_title-> setStyleClass( "SummaryTitle" );
  m_table = addWidget( std::make_unique< Wt::WTable >() );
  m_table-> setStyleClass( "SummaryTable" );

} // endSummaryWidget( const std::string & _accountGuid )


auto
GCW::Gui::BillPay::SummaryWidget::
showSummaryDetail( bool _state )-> void
{
  m_showDetail = _state;

  refreshReport();

} // endshowSummaryDetail( bool _state )-> void


auto
GCW::Gui::BillPay::SummaryWidget::
setDate( int _month, int _year )-> void
{
  m_month = _month;
  m_year  = _year;

  refreshReport();

} // endsetDate( int _month, int _year )-> void


auto
GCW::Gui::BillPay::SummaryWidget::
refreshReport() -> void
{
  /*
  ** post the month we're in
  */
  m_title->
    setText
    (
     Wt::WString( TR("gcw.billPay.lbl.selectedMonth") )
     .arg( TR("gcw.billPay.ttp." + toString( m_month ) ) )
     .arg( toString( m_year ) )
    );

  generateReport( m_table, m_showDetail );

  outputReport();

} // endrefreshReport() -> void

auto
GCW::Gui::BillPay::SummaryWidget::
generateReport( Wt::WTable * _table, bool _showDetail ) -> void
{
  /*
  ** open a transaction, helps all the queries to run faster
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  /*
  ** reset the report
  */
  auto rowCount = _table-> rowCount();
  _table-> clear();

  _table-> setAttributeValue( "updated", Wt::WDateTime::currentDateTime().toString() );

  /*
  ** gather up all the payment splits and process them
  **  in to the report
  */
  Splits splits( m_month, m_year );
  int row = 0;
  std::vector< DayTotal_t > dayTotals;

  for( auto payFromAcct : splits.payFroms() )
  {
    /*
    ** all payFromDay
    */
    for( auto payFromDay : splits.payFromDays( payFromAcct ) )
    {
      /*
      ** put up the what-day-paid title
      **  example: "1st ~ 4350-Mark"
      */
      auto acctDay =
        Wt::WString("<span style=\"border-bottom:1px solid black;\">{1}<sup>{2}</sup> ~ {3}</span>")
        .arg( payFromDay )
        .arg( ordinalSuffix( payFromDay ) )
        .arg( payFromAcct )
        .toUTF8()
        ;

      _table-> elementAt( row, 0 )-> addNew< Wt::WText >( acctDay );
      _table-> elementAt( row, 0 )-> setStyleClass( "acctDay" );
      _table-> elementAt( row, 0 )-> setColumnSpan( 2 );
      row++;

      /*
      ** loop through the splits for this pay-from-day and post them to the table
      */
      GCW_NUMERIC subTotal(0);
      GCW::Dbo::Accounts::Item::Ptr acctItem;
      for( auto paymentSplit : splits.paymentSplits( payFromAcct, payFromDay ) )
      {
        auto splitItem = GCW::Dbo:: Splits       ::byGuid( paymentSplit               );
             acctItem  = GCW::Dbo:: Accounts     ::byGuid( splitItem-> account_guid() );
        auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid()      );

        _table-> elementAt( row, 0 )-> addNew< Wt::WText >( splitItem   -> valueAsString( true ) );
        _table-> elementAt( row, 1 )-> addNew< Wt::WText >( txItem      -> description()         );

        if( _showDetail )
        {
          auto otherSplit = GCW::Dbo::Splits::bySplitExcept( paymentSplit );
          if( otherSplit.size() > 0 )
          {
            _table-> elementAt( row, 2 )-> addNew< Wt::WText >( otherSplit[0] -> memo() );
          }
        }

        _table-> elementAt( row, 1 )-> clicked().connect( [=](){ m_clicked.emit( txItem-> description() ); } );
        row++;

        subTotal += splitItem-> value( true );

      } // endfor( ..all payments.. )

      _table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( subTotal, GCW::Cfg::decimal_format()  ) ) );
      _table-> elementAt( row,   0 )-> setStyleClass( "du" ); // double-underline
      _table-> elementAt( row-1, 0 )-> setStyleClass( "su" ); // single-underline
      row++;

      /*
      ** record the day total for the subsequent report
      **
      ** \todo total unbelievable hack
      **
      ** This 'hack' causes this summary report to print ~only~ the values
      **  that are considered payments that came from a 'bank' or some type
      **  of ASSET account.  Note, that bills can also be paid with LIABILITY
      **  account types, but we don't want those accounts to appear in the
      **  transfer totals since the transfer totals are for showing how much
      **  money needs to be transferred out of the checking account(s).
      */
      if( Dbo::Accounts::isType( acctItem, Dbo::Accounts::Type::ASSET ) )
      {
        DayTotal_t dayTotal;
        dayTotal.day   = payFromDay;
        dayTotal.bank  = payFromAcct;
        dayTotal.value = subTotal;
        dayTotals.push_back( dayTotal );
      }

    } // endall payFromDay

  } // endfor( ..all payFroms.. )

  _table-> elementAt( row, 0 )-> addNew< Wt::WText >( TR("gcw.billPay.lbl.transfers") );
  _table-> elementAt( row, 0 )-> setStyleClass( "acctDay" );
  _table-> elementAt( row, 0 )-> setAttributeValue( "style", "text-align:center;border-bottom: 1px solid black;" );
  _table-> elementAt( row, 0 )-> setColumnSpan( 2 );
  row++;

  std::sort
    (
     dayTotals.begin(),
     dayTotals.end(),
     []( DayTotal_t a, DayTotal_t b )
     {
     return a.day < b.day;
     }
    );

  GCW_NUMERIC grand(0);
  GCW_NUMERIC sum(0);
  int day = 0;
  for( auto dayTotal : dayTotals )
  {
    if( day != dayTotal.day )
    {
      auto payDay =
        Wt::WString("<u>{1}<sup>{2}</sup></u>")
        .arg( day )
        .arg( ordinalSuffix( day ) )
        .toUTF8()
        ;

      if( day != 0 )
      {
        _table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}") .arg( toString( sum, GCW::Cfg::decimal_format()  ) ) );
        _table-> elementAt( row,   1 )-> addNew< Wt::WText >( Wt::WString(TR("gcw.billPay.lbl.totalfor")) .arg( payDay ) );
        _table-> elementAt( row,   0 )-> setStyleClass( "du" );
        _table-> elementAt( row-1, 0 )-> setStyleClass( "su" );
        row++;
        grand += sum;
        sum = 0;

        _table-> elementAt( row, 0 )-> addNew< Wt::WText >( "" );
        _table-> elementAt( row, 0 )-> setColumnSpan( 2 );
        _table-> elementAt( row, 0 )-> setAttributeValue( "style", "border-bottom:1px solid black;" );
        row++;

      } // endif( day != 0 )

      day = dayTotal.day;

    } // endif( day != dayTotal.day )

    _table-> elementAt( row, 0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( dayTotal.value, GCW::Cfg::decimal_format() ) ) );
    _table-> elementAt( row, 1 )-> addNew< Wt::WText >( dayTotal.bank );
    row++;

    sum += dayTotal.value;

  } // endfor( auto day : splits.dayTotals() )

  if( day != 0 )
  {
    auto payDay =
      Wt::WString("<u>{1}<sup>{2}</sup></u>")
      .arg( day )
      .arg( ordinalSuffix( day ) )
      .toUTF8()
      ;

    _table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( sum, GCW::Cfg::decimal_format() ) ) );
    _table-> elementAt( row,   1 )-> addNew< Wt::WText >( Wt::WString(TR("gcw.billPay.lbl.totalfor")).arg( payDay ) );
    _table-> elementAt( row,   0 )-> setStyleClass( "du" ); // double-underline
    _table-> elementAt( row-1, 0 )-> setStyleClass( "su" ); // single-underline
    row++;
    grand += sum;
    sum = 0;
    _table-> elementAt( row, 0 )-> addNew< Wt::WText >( "" );
    _table-> elementAt( row, 0 )-> setColumnSpan( 2 );
    _table-> elementAt( row, 0 )-> setAttributeValue( "style", "border-bottom:1px double black;" );
    row++;

  } // endif( day != 0 )

  _table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( grand, GCW::Cfg::decimal_format() ) ) );
  _table-> elementAt( row,   1 )-> addNew< Wt::WText >( Wt::WString(TR("gcw.billPay.lbl.totalfor")).arg( TR("gcw.billPay.ttp." + toString( m_month ) ) ) );
  row++;

  _table-> elementAt( row, 0 )-> addNew< Wt::WText >( "" );
  _table-> elementAt( row, 0 )-> setColumnSpan( 2 );
  _table-> elementAt( row, 0 )-> setAttributeValue( "style", "border-bottom:1px double black;" );
  row++;

} // endgenerateReport( Wt::WTable * _table ) -> void

auto
GCW::Gui::BillPay::SummaryWidget::
outputReport() -> void
{
  Wt::WTable table;

  table.setStyleClass( "SummaryTable" );

  generateReport( &table, true );

  auto fileName =
    Wt::WString( "logs/{1}-{2}-billPay.html" )
    .arg( m_year )
    .arg( toString( m_month ) )
    .toUTF8()
    ;

  std::ofstream file( fileName, std::ios_base::out );

  file << TR("gcw.billPay.report.head");
  table.htmlText( file );
  file << TR("gcw.billPay.report.foot");

} // endoutputReport() const -> void


GCW::Gui::BillPay::SummaryWidget::Splits::
Splits( int _month, int _year )
: m_month( _month ),
  m_year( _year )
{
  /*
  ** get all the transactions that happened for this account for this month
  */
  auto txItems = GCW::Dbo::Transactions::byNumDate( "bp", m_month, m_year );

  /*
  ** if transactions happened, get them open and see if they should be in the summary report
  */
  for( auto txItem : txItems )
  {
    /*
    ** loop through all the splits
    */
    for( auto split : GCW::Dbo::Splits::byTransaction( txItem-> guid() ) )
    {
      /*
      ** We want the pay-from account.
      */
      if( split-> value() < 0 )
      {
        m_splitGuids.push_back( split-> guid() );

      } // endif( ..pay-from account.. )

    } // endfor( auto split : GCW::Dbo::Splits::byTransaction( txItem-> guid() ) )

  } // endfor( auto txItem : txItems )

} // endSplits( int _month )


auto
GCW::Gui::BillPay::SummaryWidget::Splits::
splitGuids() const-> const std::vector< std::string > &
{
  return m_splitGuids;

} // endsplitGuids() const-> std::vector< std::string >


auto
GCW::Gui::BillPay::SummaryWidget::Splits::
days() const-> std::set< int >
{
  std::set< int > retVal;

  /*
  ** loop through all the splits and produce a set
  **  of days that payments were made
  */
  for( auto splitGuid : splitGuids() )
  {
    auto splitItem = GCW::Dbo:: Splits       ::byGuid( splitGuid             );
    auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid() );

    retVal.insert( txItem-> post_date_as_date().date().day() );

  } // endfor( auto splitGuid : splitGuids() )

  return retVal;

} // enddays() const-> std::set< int >


auto
GCW::Gui::BillPay::SummaryWidget::Splits::
payFroms() const-> std::set< std::string >
{
  std::set< std::string > retVal;

  /*
  ** loop throught all the splits and produce a set
  **  of 'account name' that were used to make payments
  */
  for( auto splitGuid : splitGuids() )
  {
    auto splitItem = GCW::Dbo:: Splits   ::byGuid( splitGuid                  );
    auto acctItem  = GCW::Dbo:: Accounts ::byGuid( splitItem-> account_guid() );

    retVal.insert( acctItem-> name() );

  } // endfor( auto splitGuid : splitGuids() )

  return retVal;

} // enddays() const-> std::set< int >


auto
GCW::Gui::BillPay::SummaryWidget::Splits::
payFromDays( const std::string & _payFrom ) const-> std::set< int >
{
  std::set< int > retVal;

  /*
  ** loop through all the splits and produce a set of
  **  days that an account made payments on
  */
  for( auto splitGuid : splitGuids() )
  {
    auto splitItem = GCW::Dbo:: Splits       ::byGuid( splitGuid                  );
    auto acctItem  = GCW::Dbo:: Accounts     ::byGuid( splitItem-> account_guid() );
    auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid()      );

    if( acctItem-> name() == _payFrom )
      retVal.insert( txItem-> post_date_as_date().date().day() );

  } // endfor( auto splitGuid : splitGuids() )

  return retVal;

} // enddays() const-> std::set< int >


auto
GCW::Gui::BillPay::SummaryWidget::Splits::
paymentSplits( const std::string & _payFrom, int _day ) const-> std::vector< std::string >
{
  std::vector< std::string > retVal;

  /*
  ** loop through all the splits and produce a vector
  **  of all the splits used from an account on specific
  **  day
  */
  for( auto splitGuid : splitGuids() )
  {
    auto splitItem = GCW::Dbo:: Splits       ::byGuid( splitGuid                  );
    auto acctItem  = GCW::Dbo:: Accounts     ::byGuid( splitItem-> account_guid() );
    auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid()      );

    if( acctItem-> name() == _payFrom
     && txItem-> post_date_as_date().date().day() == _day
      )
      retVal.push_back( splitGuid );

  } // endfor( auto splitGuid : splitGuids() )

  return retVal;

} // endpaymentSplits( const std::string & _payFrom, int _day ) const-> std::vector< std::string >


auto
GCW::Gui::BillPay::SummaryWidget::Splits::
dayPayments( int _day ) const-> std::vector< std::string >
{
  std::vector< std::string > retVal;

  /*
  ** loop through all the splits and produce a list of
  **  splits that were on a specific day.
  */
  for( auto splitGuid : splitGuids() )
  {
    auto splitItem = GCW::Dbo:: Splits       ::byGuid( splitGuid             );
    auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid() );

    if( txItem-> post_date_as_date().date().day() == _day )
      retVal.push_back( splitGuid );

  } // endfor( auto splitGuid : splitGuids() )

  return retVal;

} // enddayPayments( int _day ) const-> std::vector< std::string >


