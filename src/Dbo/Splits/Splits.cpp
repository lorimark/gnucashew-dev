#line 2 "src/Dbo/Splits.cpp"

#include <chrono>

#include "../App.h"

#include "Splits.h"
#include "../Transactions/Transactions.h"

const char * GCW::Dbo::Splits::s_tableName = "splits";

auto
GCW::Dbo::Splits::
load( const std::string & _splitGuid )-> GCW::Dbo::Splits::Item::Ptr
{
  GCW::Dbo::Splits::Item::Ptr retVal;

  if( _splitGuid != "" )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    retVal =
      GCW::app()-> gnucashew_session().load< GCW::Dbo::Splits::Item >( _splitGuid )
      ;
  }

  return retVal;

} // endload( const std::string & _splitGuid )

auto
GCW::Dbo::Splits::
find( const std::string & _splitGuid )-> GCW::Dbo::Splits::Item::Ptr
{
  GCW::Dbo::Splits::Item::Ptr retVal;

  if( _splitGuid != "" )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    /*
    ** grab the raw data items out of the storage
    */
    auto results =
      GCW::app()-> gnucashew_session().find< Item >()
      .where( "guid = ?" )
      .bind( _splitGuid )
      .resultList()
      ;

    /*
    ** We should find only one item
    */
    if( results.size() == 1 )
      retVal = *results.begin();

  } // endif( _splitGuid != "" )

  return retVal;

} // endfind( const std::string & _splitGuid )-> GCW::Dbo::Splits::Item::Ptr

auto
GCW::Dbo::Splits::
add( const std::string & _splitGuid )-> Item::Ptr
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  return
    GCW::app()-> gnucashew_session().addNew< Item >( _splitGuid );

} // endadd( const std::string & _splitGuid )-> Item::Ptr

auto
GCW::Dbo::Splits::
byAccount( const std::string & _accountGuid )-> GCW::Dbo::Splits::Item::Vector
{
  GCW::Dbo::Splits::Item::Vector retVal;

//  const auto start = std::chrono::system_clock::now();

  if( _accountGuid != "" )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    /*
    ** this sql will sort the results of the query by date,value(desc)
    **  without having to sort in code.  this is way freaking faster
    */
    std::string sql =
      "SELECT s "
      "FROM splits s "
      "JOIN transactions t ON s.tx_guid = t.guid "
      "WHERE s.account_guid = ? "
      "ORDER BY t.post_date, s.value_num desc";

#ifdef SQL_THAT_CAN_RETURN_RUNNING_BALANCE

SELECT s
    SUM(s.value_num * 1.0 / s.value_denom) OVER (
        PARTITION BY s.account_guid
        ORDER BY t.post_date, s.guid
        ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
    ) AS running_balance,
FROM splits s
JOIN transactions t ON s.tx_guid = t.guid
WHERE s.account_guid = ?
ORDER BY t.post_date, s.value_num;

#endif

    /*
    ** grab the raw data items out of the storage
    */
    auto results =
      GCW::app()->
        gnucashew_session()
        .query< GCW::Dbo::Splits::Item::Ptr >( sql )
        .bind( _accountGuid )
        .resultList()
        ;

    /*
    ** vector everything
    */
    for( auto result : results )
      retVal.push_back( result );

  } // endif( _accountGuid != "" )

//  std::cout << __FILE__ << ":" << __LINE__
//    << " " << std::chrono::duration_cast< std::chrono::milliseconds >
//            ( std::chrono::system_clock::now() - start ).count()
//    << "mS load time for"
//    << " " << retVal.size() << " items"
//    << std::endl;

  return retVal;

} // endbyAccount( const std::string & _accountGuid )-> GCW::Dbo::Splits::Item::Vector

auto
GCW::Dbo::Splits::
bySplitExcept( const std::string & _splitGuid )-> GCW::Dbo::Splits::Item::Vector
{
  GCW::Dbo::Splits::Item::Vector retVal;

  auto splitItem = GCW::Dbo::Splits::load( _splitGuid );

  /*
  ** If we don't have a splitItem then we can't do nuthin.
  */
  if( splitItem )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    std::string sql =
      "SELECT s "
      "FROM splits s "
      "JOIN transactions t ON s.tx_guid = t.guid "
      "WHERE s.tx_guid = ? "
      "AND   s.guid != ? "
      "ORDER BY t.post_date, s.value_num desc";

    auto results =
      GCW::app()-> gnucashew_session().query< GCW::Dbo::Splits::Item::Ptr >( sql )
      .bind( splitItem-> tx_guid() )
      .bind( splitItem-> guid() )
      .resultList()
      ;

    /*
    ** Load the vector, but skip the one that
    **  matches our incoming split guid.
    */
    for( auto result : results )
      retVal.push_back( result );

  } // endif( GCW::app()-> gnucashew_session().isOpen() )

  return retVal;

} // endbySplit( const std::string & _splitGuid )-> GCW::Dbo::Splits::Item::Vector

auto
GCW::Dbo::Splits::
byTransaction( const std::string & _txGuid )-> GCW::Dbo::Splits::Item::Vector
{
  GCW::Dbo::Splits::Item::Vector retVal;

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  std::string sql =
    "SELECT s "
    "FROM splits s "
    "JOIN transactions t ON s.tx_guid = t.guid "
    "WHERE s.tx_guid = ? "
    "ORDER BY t.post_date, s.value_num desc";

  auto results =
    GCW::app()-> gnucashew_session().query< GCW::Dbo::Splits::Item::Ptr >( sql )
    .bind( _txGuid )
    .resultList()
    ;

  for( auto result : results )
    retVal.push_back( result );

  return retVal;

} // endbyTransaction( const std::string & _txGuid )-> GCW::Dbo::Splits::Item::Vector

auto
GCW::Dbo::Splits::Item::
set_value( GCW_NUMERIC _value )-> void
{
  auto account = GCW::Dbo::Accounts::byGuid( account_guid() );

  m_value_num   = (_value * account-> commodity_scu() ).getAsInteger();
  m_value_denom = account-> commodity_scu();

} // endset_value( GCW_NUMERIC _value )-> void

auto
GCW::Dbo::Splits::Item::
set_quantity( GCW_NUMERIC _value )-> void
{
  auto account = GCW::Dbo::Accounts::byGuid( account_guid() );

  m_quantity_num   = (_value * account-> commodity_scu() ).getAsInteger();
  m_quantity_denom = account-> commodity_scu() ;

} // endset_quantity( GCW_NUMERIC _value )-> void

