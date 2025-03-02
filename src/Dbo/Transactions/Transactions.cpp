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
set_enter_date ( const Wt::WDateTime & _value )-> void
{
  m_enter_date = _value.toString( GCW_DATE_FORMAT_STORAGE ).toUTF8();
}

auto
GCW::Dbo::Transactions::Item::
set_post_date( const std::string & _value )-> void
{
  m_post_date = _value;
}

auto
GCW::Dbo::Transactions::Item::
set_post_date( const Wt::WDateTime & _value )-> void
{
  m_post_date = _value.toString( "yyyy-MM-dd 00:00:00" ).toUTF8();
}

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
      GCW::app()-> gnucashew_session().load< GCW::Dbo::Transactions::Item >( _txGuid )
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

