#line 2 "src/Dbo/SessionGnuCashew.cpp"

#include <iostream>

#include <Wt/Dbo/backend/Sqlite3.h>

#include <gcwglobal.h>

#include "Accounts/Accounts.h"
#include "Customers/Customers.h"
#include "Slots/Slots.h"
#include "Splits/Splits.h"
#include "Transactions/Transactions.h"
#include "Vars/Vars.h"
#include "SessionGnuCashew.h"

bool
GCW::Dbo::GnuCashew::Session::
open( const std::string & _path )
{
  /*
  ** Call the base class.
  **
  */
  GCW::Dbo::AbstractSession::open( _path );

  /*
  ** Try to get the sqlite3 file open
  **
  */
  try
  {
    auto connection = std::make_unique< Wt::Dbo::backend::Sqlite3 >( _path );

//    connection-> setProperty( "show-queries", "true" );

    setConnection( std::move( connection ) );

  }

  /*
  ** Handle the error
  **
  */
  catch( std::exception & e )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
  }

  m_isOpen = true;

  return isOpen();

} // endopen( const std::string & _path )

bool
GCW::Dbo::GnuCashew::Session::
hasGnuCashewExtensions()
{
  /*
  ** assume no extensions
  */
  bool retVal = false;

  using ResultRow = std::tuple< std::string, std::string, std::string, int, std::string >;

  /*
  **  query the list of tables
  */
  Wt::Dbo::Transaction t( *this );
  auto results =
    query< ResultRow >
    (
     "select type,name,tbl_name,rootpage,sql from sqlite_master"
    )
    .resultList()
    ;

  /*
  ** loop the list, looking for the extension tables
  */
  for( auto result : results )
  {
    std::string _type;
    std::string _name;
    std::string tbl_name;
    int         rootpage;
    std::string _text;

    std::tie( _type, _name, tbl_name, rootpage, _text ) = result;

    if( _type != "table" )
      continue;

    if( _name == GCW::Dbo::Vars::s_tableName )
    {
      retVal = true;
      break;
    }

#ifdef NEVER
    std::cout << __FILE__ << ":" << __LINE__
      << " type:" << _type
      << " name:" << _name
//      << " tbln:" << tbl_name
//      << " root:" << rootpage
//      << " text:" << _text
      << std::endl
      ;
#endif

  } // endfor( auto result : results )

  return retVal;

} // endhasGnuCashewExtensions() const

bool
GCW::Dbo::GnuCashew::Session::
addGnuCashewExtensions()
{
  if( hasGnuCashewExtensions() )
    return true;

  Wt::Dbo::Transaction t( *this );

  /*
  ** Add a table to contain the vars
  **
  */
  auto sql =
    Wt::WString( TR("gcw_sql.create_vars") )
    .arg( GCW::Dbo::Vars::s_tableName )
    .toUTF8()
    ;

  execute( sql );

  /*
  ** poke some initial values in to the vars table
  **
  */
  auto item = GCW::Dbo::Vars::get( "gnucashew","sys" );

  item.modify()-> setVar( "createdOn",  Wt::WDateTime::currentDateTime().toString( ISO_DATE_FORMAT ) );
  item.modify()-> setVar( "gcwVersion", 1 );

  return true;

} // endaddGnuCashewExtensions()



