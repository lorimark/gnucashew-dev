#line 2 "src/Dbo/Transactions.cpp"

#include "../App.h"
#include "Transactions.h"

const char * GCW::Dbo::Transactions::s_tableName = "transactions";

auto
GCW::Dbo::Transactions::Item::
set_num( const std::string & _value )-> void
{
  m_num = _value;

}

auto
GCW::Dbo::Transactions::Item::
set_enter_date ( const std::string & _value )-> void
{
  m_enter_date = _value;
}

auto
GCW::Dbo::Transactions::Item::
set_enter_date ( const Wt::WDate & _value )-> void
{
  auto dateTime = Wt::WDateTime( _value, GCW_DATE_DEFAULT_TIME );
  set_enter_date( dateTime.toString( GCW_DATETIME_FORMAT_STORAGE ).toUTF8() );
}

auto
GCW::Dbo::Transactions::Item::
set_enter_date ( const Wt::WDateTime & _value )-> void
{
  set_enter_date ( _value.toString( GCW_DATETIME_FORMAT_STORAGE ).toUTF8() );
}

auto
GCW::Dbo::Transactions::Item::
set_post_date( const std::string & _value )-> void
{
  m_post_date = _value;
}

auto
GCW::Dbo::Transactions::Item::
set_post_date( const Wt::WDate & _value )-> void
{
  auto dateTime = Wt::WDateTime( _value, GCW_DATE_DEFAULT_TIME );

  set_post_date( dateTime.toString( GCW_DATETIME_FORMAT_STORAGE ).toUTF8() );

} // endset_post_date( const Wt::WDate & _value )-> void

auto
GCW::Dbo::Transactions::Item::
set_post_date( const Wt::WDateTime & _value )-> void
{
  /*
  ** BUGBUG: This is a very weird thing!  The gnucash system seems to post transactions
  **          with a post_date of "yyyy-MM-dd 10:59:00" with the 'hours and minutes'
  **          set to that value accordingly.  If the record is posted as '00:00:00'
  **          hours, gnucash will interpret the date as being in the day before.
  **
  **         So, therefore, when posting the 'post_date' of a transaction, it is
  **          a requirement that the hours be set like this.
  */
  set_post_date( _value.toString( "yyyy-MM-dd 10:59:00" ).toUTF8() );

} // endset_post_date( const Wt::WDateTime & _value )-> void

auto
GCW::Dbo::Transactions::Item::
set_description( const std::string & _value )-> void
{
  m_description = _value;
}

auto
GCW::Dbo::Transactions::
load( const std::string & _txGuid )-> GCW::Dbo::Transactions::Item::Ptr
{
  GCW::Dbo::Transactions::Item::Ptr retVal;

  /*
  ** If the session isn't open then there's nothing to load.
  **
  */
  if( GCW::app()-> gnucashew_session().isOpen() )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    retVal =
      GCW::app()-> gnucashew_session().find< GCW::Dbo::Transactions::Item >()
      .where( "guid = ?" )
      .bind( _txGuid )
      ;

  } // endif( GCW::app()-> gnucashew_session().isOpen() )


  return retVal;

} // endGCW::Dbo::Transactions::Item::Ptr GCW::Dbo::Transactions::byGuid( const std::string & _txGuid )

auto
GCW::Dbo::Transactions::
byGuid( const std::string & _txGuid )-> GCW::Dbo::Transactions::Item::Ptr
{
  return load( _txGuid );

} // endGCW::Dbo::Transactions::Item::Ptr GCW::Dbo::Transactions::byGuid( const std::string & _txGuid )

auto
GCW::Dbo::Transactions::
add( const std::string & _txGuid )-> Item::Ptr
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  return
    GCW::app()-> gnucashew_session().addNew< Item >( _txGuid );

} // endadd( const std::string & _txGuid )-> Item::Ptr

auto
GCW::Dbo::Transactions::
byAccount( const std::string & _accountGuid )-> GCW::Dbo::Transactions::Item::Vector
{
  GCW::Dbo::Transactions::Item::Vector retVal;

  /*
  ** If the session isn't open then there's nothing to load.
  **
  */
  if( GCW::app()-> gnucashew_session().isOpen() )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    /*
    ** Pull all transactions that have a split that matches this
    **  account.  Sort the results by post_date:ascending, so that any
    **  subsequent views can process the items in sequential order.
    **
    */
    auto results =
      GCW::app()-> gnucashew_session().find< GCW::Dbo::Transactions::Item >()
      .where( "guid in (select tx_guid from splits where account_guid = ?)" )
      .bind( _accountGuid )
      .orderBy( "post_date" )
      .resultList();
      ;

    for( auto result : results )
      retVal.push_back( result );

  } // endif( GCW::app()-> gnucashew_session().isOpen() )

  return retVal;

} // endGCW::Dbo::Transactions::Item::Vector GCW::Dbo::Transactions::byAccount( const std::string & _accountGuid )

auto
GCW::Dbo::Transactions::
byAccountMonth( const std::string & _accountGuid, int _month )-> GCW::Dbo::Transactions::Item::Vector
{
  GCW::Dbo::Transactions::Item::Vector retVal;

  auto thisYear = Wt::WDate::currentDate().year();

  /*
  ** if the transaction item is within this month and year
  **  then it's a keeper
  */
  for( auto item : byAccount( _accountGuid ) )
    if( item-> post_date_as_date().date().month() == _month
     && item-> post_date_as_date().date().year()  == thisYear
      )
      retVal.push_back( item );

  return retVal;

} // endbyAccountMonth( const std::string & _accountGuid, int _month )-> GCW::Dbo::Transactions::Item::Vector

auto
GCW::Dbo::Transactions::
byNumMonth( const std::string & _num, int _month )-> GCW::Dbo::Transactions::Item::Vector
{
  GCW::Dbo::Transactions::Item::Vector retVal;

  auto date = Wt::WDate( Wt::WDate::currentDate().year(), _month, 1 ).toString( "yyyy-MM" );

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  auto results =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Transactions::Item >()
    .where( "num = ? and post_date LIKE ?" )
    .bind( _num )
    .bind( date + "%" )
    .orderBy( "post_date" )
    .resultList();
    ;

  for( auto item : results )
    retVal.push_back( item );

  return retVal;

} // endbyNumMonth( const std::string & _num, int _month )-> GCW::Dbo::Transactions::Item::Vector

