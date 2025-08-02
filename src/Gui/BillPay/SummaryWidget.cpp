#line 2 "src/Gui/BillPay/SummaryWidget.cpp"

//#define VERSION_SOSO
#define VERSION_LITTLEBETTER

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

namespace {

auto ordinalSuffix( int number )-> std::string
{
  int lastTwo = number % 100;
  int lastOne = number % 10;

  if (lastTwo >= 11 && lastTwo <= 13)
    return "th";

  switch( lastOne )
  {
    case 1:  return "st";
    case 2:  return "nd";
    case 3:  return "rd";
    default: return "th";
  }

  return "";

} // endauto ordinalSuffix( int number )-> std::string

} // endnamespace {

#ifdef VERSION_LITTLEBETTER
auto
GCW::Gui::BillPay::SummaryWidget::
setMonth( int _month )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  /*
  ** reset the report
  */
  m_table-> clear();
  m_table-> setStyleClass( "SummaryTable" );

  /*
  ** post the month we're in
  */
  m_month = _month;
  m_title-> setText( Wt::WString( "Selected Month: {1}" ).arg( TR("gcw.billPay.ttp." + toString( m_month ) ) ) );

  /*
  ** gather up all the payment splits and process them
  **  in to the report
  */
  Splits splits( _month );
  int row = 0;
  std::vector< DayTotal_t > dayTotals;
  for( auto payFrom : splits.payFroms() )
  {
    /*
    ** all payFromDay
    */
    for( auto payFromDay : splits.payFromDays( payFrom ) )
    {
      auto acctDay =
        Wt::WString("<span style=\"border-bottom:1px solid black;\">{1}<sup>{3}</sup> ~ {2}</span>")
        .arg( payFromDay )
        .arg( payFrom )
        .arg( ordinalSuffix( payFromDay ) )
        .toUTF8()
        ;

      m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( acctDay );
      m_table-> elementAt( row, 0 )-> setStyleClass( "acctDay" );
      m_table-> elementAt( row, 0 )-> setColumnSpan( 2 );
      row++;

      GCW_NUMERIC subTotal(0);
      for( auto paymentSplit : splits.paymentSplits( payFrom, payFromDay ) )
      {
        auto splitItem = GCW::Dbo:: Splits       ::byGuid( paymentSplit               );
        auto acctItem  = GCW::Dbo:: Accounts     ::byGuid( splitItem-> account_guid() );
        auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid()      );

        m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( splitItem -> valueAsString( true ) );
        m_table-> elementAt( row, 1 )-> addNew< Wt::WText >( txItem    -> description()         );
        m_table-> elementAt( row, 1 )-> clicked().connect( [=](){ m_clicked.emit( txItem-> description() ); } ); row++;

        subTotal += splitItem-> value( true );

      } // endfor( ..all payments.. )

      m_table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( subTotal, GCW::Cfg::decimal_format()  ) ) );
      m_table-> elementAt( row,   0 )-> setStyleClass( "du" );
      m_table-> elementAt( row-1, 0 )-> setStyleClass( "su" );
      row++;

      /*
      ** record the day total for the subsequent report
      */
      DayTotal_t dayTotal;
      dayTotal.day   = payFromDay;
      dayTotal.bank  = payFrom;
      dayTotal.value = subTotal;
      dayTotals.push_back( dayTotal );

    } // endall payFromDay

  } // endfor( ..all payFroms.. )

  m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( " * * * TRANSFERS * * * " );
  m_table-> elementAt( row, 0 )-> setStyleClass( "acctDay" );
  m_table-> elementAt( row, 0 )-> setAttributeValue( "style", "text-align:center;border-bottom: 1px solid black;" );
  m_table-> elementAt( row, 0 )-> setColumnSpan( 2 );
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
        m_table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( sum, GCW::Cfg::decimal_format()  ) ) );
        m_table-> elementAt( row,   1 )-> addNew< Wt::WText >( Wt::WString("Total for {1}").arg( payDay ) );
        m_table-> elementAt( row,   0 )-> setStyleClass( "du" );
        m_table-> elementAt( row-1, 0 )-> setStyleClass( "su" );
        row++;
        grand += sum;
        sum = 0;

        m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( "" );
        m_table-> elementAt( row, 0 )-> setColumnSpan( 2 );
        m_table-> elementAt( row, 0 )-> setAttributeValue( "style", "border-bottom:1px solid black;" );
        row++;

      }

      day = dayTotal.day;
    }

    m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( dayTotal.value, GCW::Cfg::decimal_format()  ) ) );
    m_table-> elementAt( row, 1 )-> addNew< Wt::WText >( dayTotal.bank );
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

    m_table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( sum, GCW::Cfg::decimal_format()  ) ) );
    m_table-> elementAt( row,   1 )-> addNew< Wt::WText >( Wt::WString("Total for {1}").arg( payDay ) );
    m_table-> elementAt( row,   0 )-> setStyleClass( "du" );
    m_table-> elementAt( row-1, 0 )-> setStyleClass( "su" );
    row++;
    grand += sum;
    sum = 0;
    m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( "" );
    m_table-> elementAt( row, 0 )-> setColumnSpan( 2 );
    m_table-> elementAt( row, 0 )-> setAttributeValue( "style", "border-bottom:1px double black;" );
    row++;

  }

  m_table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( grand, GCW::Cfg::decimal_format()  ) ) );
  m_table-> elementAt( row,   1 )-> addNew< Wt::WText >( Wt::WString("Total for {1}").arg( TR("gcw.billPay.ttp." + toString( m_month ) ) ) );
  row++;

  m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( "" );
  m_table-> elementAt( row, 0 )-> setColumnSpan( 2 );
  m_table-> elementAt( row, 0 )-> setAttributeValue( "style", "border-bottom:1px double black;" );
  row++;

} // endloadData()-> void
#endif

#ifdef VERSION_SOSO
auto
GCW::Gui::BillPay::SummaryWidget::
setMonth( int _month )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  /*
  ** reset the report
  */
  m_table-> clear();
  m_table-> setStyleClass( "SummaryTable" );

  /*
  ** post the month we're in
  */
  m_month = _month;
  m_title-> setText( Wt::WString( "Selected Month: {1}" ).arg( m_month ) );

  /*
  ** gather up all the payment splits and process them
  **  in to the report
  */
  Splits splits( _month );
  int row = 0;
  std::vector< DayTotal_t > dayTotals;
  for( auto payFrom : splits.payFroms() )
  {
    for( auto payFromDay : splits.payFromDays( payFrom ) )
    {
      auto acctDay =
        Wt::WString("{1}<sup>{3}</sup> ~ {2}")
        .arg( payFromDay )
        .arg( payFrom )
        .arg( ordinalSuffix( payFromDay ) )
        .toUTF8()
        ;

      m_table-> elementAt( row, 0 )-> setAttributeValue( "style", "padding-top: 10px;" );
      m_table-> elementAt( row, 1 )-> setAttributeValue( "style", "padding-top: 10px;" );

      GCW_NUMERIC subTotal(0);
      for( auto paymentSplit : splits.paymentSplits( payFrom, payFromDay ) )
      {
        auto splitItem = GCW::Dbo:: Splits       ::byGuid( paymentSplit               );
        auto acctItem  = GCW::Dbo:: Accounts     ::byGuid( splitItem-> account_guid() );
        auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid()      );

        m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( splitItem -> valueAsString( true ) );
        m_table-> elementAt( row, 1 )-> addNew< Wt::WText >( txItem    -> description()         );
        row++;

        subTotal += splitItem-> value( true );

      } // endfor( ..all payments.. )

      m_table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( subTotal, GCW::Cfg::decimal_format()  ) ) );
      m_table-> elementAt( row,   0 )-> setStyleClass( "du" );
      m_table-> elementAt( row-1, 0 )-> setStyleClass( "su" );
      m_table-> elementAt( row,   1 )-> addNew< Wt::WText >( acctDay );
      row++;

      /*
      ** record the day total for the subsequent report
      */
      DayTotal_t dayTotal;
      dayTotal.day   = payFromDay;
      dayTotal.bank  = payFrom;
      dayTotal.value = subTotal;
      dayTotals.push_back( dayTotal );

    } // endfor( ..all payFromDays.. )

    m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( "------------------------------------" );
    m_table-> elementAt( row, 0 )-> setColumnSpan( 2 );
    row++;

  } // endfor( ..all payFroms.. )

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
          Wt::WString("{1}<sup>{2}</sup>")
          .arg( day )
          .arg( ordinalSuffix( day ) )
          .toUTF8()
          ;

      if( day != 0 )
      {
        m_table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( sum, GCW::Cfg::decimal_format()  ) ) );
        m_table-> elementAt( row,   1 )-> addNew< Wt::WText >( Wt::WString("Total for {1}").arg( payDay ) );
        m_table-> elementAt( row,   0 )-> setStyleClass( "du" );
        m_table-> elementAt( row-1, 0 )-> setStyleClass( "su" );
        row++;
        grand += sum;
        sum = 0;

    m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( "------------------------------------" );
    m_table-> elementAt( row, 0 )-> setColumnSpan( 2 );
    row++;


      }

      day = dayTotal.day;
    }

    m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( dayTotal.value, GCW::Cfg::decimal_format()  ) ) );
    m_table-> elementAt( row, 1 )-> addNew< Wt::WText >( dayTotal.bank );
    row++;

    sum += dayTotal.value;

#ifdef NEVER
    if( day != dayTotal.day )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

      if( day != 0 )
      {
        std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

        m_table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( sum, GCW::Cfg::decimal_format()  ) ) );
        m_table-> elementAt( row,   0 )-> setStyleClass( "du" );
        m_table-> elementAt( row-1, 0 )-> setStyleClass( "su" );
        row++;
        sum = 0;
      }

      day = dayTotal.day;
    }
#endif

  } // endfor( auto day : splits.dayTotals() )

      if( day != 0 )
      {
        auto payDay =
            Wt::WString("{1}<sup>{2}</sup>")
            .arg( day )
            .arg( ordinalSuffix( day ) )
            .toUTF8()
            ;

        m_table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( sum, GCW::Cfg::decimal_format()  ) ) );
        m_table-> elementAt( row,   1 )-> addNew< Wt::WText >( Wt::WString("Total for {1}").arg( payDay ) );
        m_table-> elementAt( row,   0 )-> setStyleClass( "du" );
        m_table-> elementAt( row-1, 0 )-> setStyleClass( "su" );
        row++;
        grand += sum;
        sum = 0;
    m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( "------------------------------------" );
    m_table-> elementAt( row, 0 )-> setColumnSpan( 2 );
    row++;

      }

        m_table-> elementAt( row,   0 )-> addNew< Wt::WText >( Wt::WString("{1}").arg( toString( grand, GCW::Cfg::decimal_format()  ) ) );
        m_table-> elementAt( row,   1 )-> addNew< Wt::WText >( Wt::WString("Total for {1}").arg( TR("gcw.billPay.ttp." + toString( m_month ) ) ) );
  row++;

  m_table-> elementAt( row, 0 )-> addNew< Wt::WText >( "********************************" );
  m_table-> elementAt( row, 0 )-> setColumnSpan( 2 );
  row++;


 } // endloadData()-> void
#endif

GCW::Gui::BillPay::SummaryWidget::Splits:: Splits( int _month )
: m_month( _month )
{
  /*
  ** get all the transactions that happened for this account for this month
  */
  auto txItems = GCW::Dbo::Transactions::byNumMonth( "bp", m_month );

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
splitGuids() const-> std::vector< std::string >
{
  return m_splitGuids;

} // endsplitGuids() const-> std::vector< std::string >

auto
GCW::Gui::BillPay::SummaryWidget::Splits::
days() const-> std::set< int >
{
  std::set< int > retVal;

  for( auto splitGuid : splitGuids() )
  {
    auto splitItem = GCW::Dbo:: Splits       ::byGuid( splitGuid                  );
    auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid()      );

    retVal.insert( txItem-> post_date_as_date().date().day() );

  } // endfor( auto splitGuid : splitGuids() )

  return retVal;

} // enddays() const-> std::set< int >

auto
GCW::Gui::BillPay::SummaryWidget::Splits::
payFroms() const-> std::set< std::string >
{
  std::set< std::string > retVal;

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

  for( auto splitGuid : splitGuids() )
  {
    auto splitItem = GCW::Dbo:: Splits       ::byGuid( splitGuid             );
    auto txItem    = GCW::Dbo:: Transactions ::byGuid( splitItem-> tx_guid() );

    if( txItem-> post_date_as_date().date().day() == _day )
      retVal.push_back( splitGuid );

  } // endfor( auto splitGuid : splitGuids() )

  return retVal;

} // enddayPayments( int _day ) const-> std::vector< std::string >






