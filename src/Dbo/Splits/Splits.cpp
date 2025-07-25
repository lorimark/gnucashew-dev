#line 2 "src/Dbo/Splits.cpp"

#include "../App.h"

#include "Splits.h"
#include "../Transactions/Transactions.h"

const char * GCW::Dbo::Splits::s_tableName = "splits";

namespace {

/*!
** \brief Splits Sorter
**
** This is a little (private) vector sorter used to sort
**  the items pulled from the database.  The database can
**  produce items in random order, and the 'date' is
**  contained on the 'transaction' so sorting by date
**  requires a lookup in to the transaction.
**
** The sorted vector_of_splits is used in the Account
**  Register editor, whereby the items need to be in
**  correct chronological order so as to be able to
**  calculate a running balance.
**
*/
void sort( GCW::Dbo::Splits::Item::Vector & _splitItems )
{
  /*!
  ** Sort the vector of splits by transaction date so that they can be loaded
  **  in to the model in proper sequential order.
  **
  */
  std::sort
  (
   _splitItems.begin(),
   _splitItems.end(),
   []( const GCW::Dbo::Splits::Item::Ptr item1,
       const GCW::Dbo::Splits::Item::Ptr item2
     )
     {
       auto trans1 = GCW::Dbo::Transactions::byGuid( item1-> tx_guid() );
       auto trans2 = GCW::Dbo::Transactions::byGuid( item2-> tx_guid() );

       if( trans1
        && trans2
         )
       {
         /*
         ** return .bool. if the .trans1. date is .less than. the .trans2. date
         **
         ** note: it is possible to string-compare these date values, as they are
         **        represented as ISO dates (YYYY-mm-DD HH:MM:ss) which is
         **        sortable.  Alternatively, we can convert this string to an
         **        internal WDate element, but it's an unnecessary step.
         */
         return trans1-> post_date()
              < trans2-> post_date();
//         return trans1-> post_date_as_date()
//              < trans2-> post_date_as_date();
       }

       return false;

     }
  );

} // endvoid sort( GCW::Dbo::Splits::Item::Vector & _splitItems )

} // endnamespace {

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
    **
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

  if( _accountGuid != "" )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    /*
    ** grab the raw data items out of the storage
    */
    auto results =
      GCW::app()-> gnucashew_session().find< GCW::Dbo::Splits::Item >()
      .where( "account_guid = ?" )
      .bind( _accountGuid )
      .resultList()
      ;

    /*
    ** vector everything
    */
    for( auto result : results )
      retVal.push_back( result );

    /*
    ** sort the vector
    */
    sort( retVal );

  } // endif( _accountGuid != "" )

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
  **
  */
  if( splitItem )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    auto results =
      GCW::app()-> gnucashew_session().find< GCW::Dbo::Splits::Item >()
      .where( "tx_guid = ?" )
      .bind( splitItem-> tx_guid() )
      .resultList()
      ;

    /*
    ** Load the vector, but skip the one that
    **  matches our incoming split guid.
    **
    */
    for( auto result : results )
      if( result-> guid() != _splitGuid )
        retVal.push_back( result );

    /*!
    ** The vector is sorted by transction-date before
    **  returning to the caller.
    **
    */
    sort( retVal );

  } // endif( GCW::app()-> gnucashew_session().isOpen() )

  return retVal;

} // endbySplit( const std::string & _splitGuid )-> GCW::Dbo::Splits::Item::Vector

auto
GCW::Dbo::Splits::
byTransaction( const std::string & _txGuid )-> GCW::Dbo::Splits::Item::Vector
{
  GCW::Dbo::Splits::Item::Vector retVal;

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  auto results =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Splits::Item >()
    .where( "tx_guid = ?" )
    .bind( _txGuid )
    .resultList()
    ;

  for( auto result : results )
    retVal.push_back( result );

  /*!
  ** The vector is sorted by transction-date before
  **  returning to the caller.
  **
  */
  sort( retVal );

  return retVal;

} // endbyTransaction( const std::string & _txGuid )-> GCW::Dbo::Splits::Item::Vector

auto
GCW::Dbo::Splits::Item::
set_value( GCW_NUMERIC _value )-> void
{
  m_value_num   = (_value * 100).getAsInteger();
  m_value_denom = 100;

} // endset_value( GCW_NUMERIC _value )-> void

auto
GCW::Dbo::Splits::Item::
set_quantity( GCW_NUMERIC _value )-> void
{
  m_quantity_num   = (_value * 100).getAsInteger();
  m_quantity_denom = 100;

} // endset_quantity( GCW_NUMERIC _value )-> void

