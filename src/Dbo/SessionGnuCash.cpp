#line 2 "src/Dbo/SessionGnuCash.cpp"

#ifdef NEVER
#define TESTFILE "gnucash-dev.gnucash"

#include <iostream>

#include "../Glb/Core.h"

#include <gcwglobal.h>
#include "Accounts.h"
#include "Customers.h"
#include "Slots.h"
#include "Splits.h"
#include "Transactions.h"
#include "Vars.h"
#include "SessionGnuCash.h"

GCW::Dbo::GnuCash::Session::
~Session()
{
  if( isOpen() )
    closeGnuCash();
}

/*
 *

 This is a trace-output from the open() call:

src/Dbo/SessionGnuCash.cpp:43 /home/serveradmin/LorimarkSolutions.gnucash
src/Dbo/SessionGnuCash.cpp:49 qof_session_begin
src/Dbo/SessionGnuCash.cpp:58 error: 0
src/Dbo/SessionGnuCash.cpp:66 qof_session_load
* 11:24:47 ERROR <gnc.engine> void QofSessionImpl::load(QofPercentageFunc): assertion 'm_book && qof_book_empty(m_book)' failed
src/Dbo/SessionGnuCash.cpp:69 error: 0
src/Dbo/SessionGnuCash.cpp:76 qof_session_get_book
src/Dbo/SessionGnuCash.cpp:78 0x7f9480017070
src/Dbo/SessionGnuCash.cpp:80 gnc_book_get_root_account
src/Dbo/SessionGnuCash.cpp:82 rootAccount: 0x7f9480020430
src/Dbo/SessionGnuCash.cpp:84 count:2277
src/Dbo/SessionGnuCash.cpp:88 rootGuid: ba4d0360249c4a848cdf4d2955fff3e2
src/Dbo/SessionGnuCash.cpp:89 rootName: Root Account
src/Dbo/SessionGnuCash.cpp:90 rootCode: testing
src/Dbo/SessionGnuCash.cpp:91 rootDesc: testing 123
src/Dbo/SessionGnuCash.cpp:93 size: 8
src/Dbo/SessionGnuCash.cpp:99 index:0 guid: 5dc2c6d4adae4f00b19bd5b9a1c74b46 name: Expenses
src/Dbo/SessionGnuCash.cpp:99 index:1 guid: a078ee7908764913b4901cdda1401cba name: Liabilities
src/Dbo/SessionGnuCash.cpp:99 index:2 guid: 551b39dc9e7e48369b269d7d50b5fc8f name: Assets
src/Dbo/SessionGnuCash.cpp:99 index:3 guid: 0ab997bc52ae48998012fa8ed058c7be name: Income
src/Dbo/SessionGnuCash.cpp:99 index:4 guid: 1440f4545f164671a63dbf3e2fce5634 name: Equity
src/Dbo/SessionGnuCash.cpp:99 index:5 guid: 94282e4852634c8a92c95a80831b5b73 name: Personal
src/Dbo/SessionGnuCash.cpp:99 index:6 guid: df47015bd02642f198163f7099a3eddd name: Orphan-USD
src/Dbo/SessionGnuCash.cpp:99 index:7 guid: 6938eb9a9c014cf491e87fbba61d4325 name: Imbalance-USD
src/Dbo/SessionGnuCash.cpp:103 qof_session_save
src/Dbo/SessionGnuCash.cpp:121 open finished.
*/

QofSession *
GCW::Dbo::GnuCash::Session::
qofSession()
{
  return m_session;
}

bool
GCW::Dbo::GnuCash::Session::
open( const std::string & _path )
{
  if( isOpen() )
    return true;

  /*
  ** Call the base class.
  **
  */
  GCW::Dbo::AbstractSession::open( _path );

  std::cout << __FILE__ << ":" << __LINE__ << " " << path() << std::endl;

//  auto userdata_migration_msg = gnc_filepath_init();
  gnc_engine_init( 0, nullptr );
//  auto s = gnc_get_current_session(); // qof_session_new( qof_book_new() );
  m_session = qof_session_new( qof_book_new() );

  std::cout << __FILE__ << ":" << __LINE__ << " qof_session_begin" << std::endl;
  std::string url = "sqlite3://" + path();

//  qof_session_begin( s, url.c_str(), SESSION_NORMAL_OPEN    );
//  qof_session_begin( s, url.c_str(), SESSION_NEW_STORE      );
//  qof_session_begin( s, url.c_str(), SESSION_NEW_OVERWRITE  );
  qof_session_begin( m_session, url.c_str(), SESSION_READ_ONLY      );
//  qof_session_begin( s, url.c_str(), SESSION_BREAK_LOCK     );

  std::cout << __FILE__ << ":" << __LINE__ << " error: " << qof_session_get_error( m_session ) << std::endl;

  if( qof_session_get_error( m_session ) != 0 )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " error opening qof_session" << std::endl;
    return false;
  }

  std::cout << __FILE__ << ":" << __LINE__ << " qof_session_load" << std::endl;
  qof_session_load( m_session, NULL );

  std::cout << __FILE__ << ":" << __LINE__ << " error: " << qof_session_get_error( m_session ) << std::endl;


//  std::cout << __FILE__ << ":" << __LINE__ << " checking file path" << std::endl;
//  std::cout << __FILE__ << ":" << __LINE__ << " filePath:" << qof_session_get_file_path( m_session ) << std::endl;

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " qof_session_get_book" << std::endl;
  auto book = getBook();

  std::cout << __FILE__ << ":" << __LINE__ << " gnc_book_get_root_account" << std::endl;
  auto rootAccount = book.get_root_account(); // gnc_book_get_root_account( book );

//  std::cout << __FILE__ << ":" << __LINE__ << " gnc_book_count_transactions:" << gnc_book_count_transactions( book ) << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << " gnc_book_count_transactions:" << book.count_transactions() << std::endl;

//  auto guidString = rootAccount.getGUID(); // guid_to_string( xaccAccountGetGUID( rootAccount ) );

  std::cout << __FILE__ << ":" << __LINE__ << " rootGuid: "    << rootAccount.guid()        << std::endl; // guidString << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << " rootName: "    << rootAccount.name()        << std::endl; // xaccAccountGetName( rootAccount ) << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << " rootCode: "    << rootAccount.code()        << std::endl; // xaccAccountGetCode( rootAccount ) << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << " rootDesc: "    << rootAccount.description() << std::endl; // xaccAccountGetDescription( rootAccount ) << std::endl;

//  std::cout << __FILE__ << ":" << __LINE__ << " size: " << gnc_account_n_children( rootAccount ) << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << " size: " << rootAccount.children().size() << std::endl;
//  for( int i=0; i< gnc_account_n_children( rootAccount ); i++ )
  int i=0;
  for( auto child : rootAccount.children() )
  {
//    auto child = gnc_account_nth_child( rootAccount, i );
//    auto guid = guid_to_string( xaccAccountGetGUID( child ) );
//    std::cout << __FILE__ << ":" << __LINE__
//      << " index:" << i
//      << " guid: " << guid
//      << " name: " << xaccAccountGetName( child )
//      << std::endl;

    std::cout << __FILE__ << ":" << __LINE__
      << " index:" << i++
      << " guid: " << child.guid()
      << " name: " << child.name()
      << std::endl;

  } // endfor( ..all children.. )

  std::cout << __FILE__ << ":" << __LINE__ << " qof_session_save" << std::endl;
  qof_session_save( m_session, NULL );

//  AccountList *accountList;
//  gnc_accounts_and_all_descendants( accountList );

//  auto account = gnc_account_lookup_by_name( nullptr, "Assets" );

//  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

//  std::cout << __FILE__ << ":" << __LINE__ << " " << g_list_length( &accountList ) << std::endl;

//  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

//  accountList.next;

#endif

  std::cout << __FILE__ << ":" << __LINE__ << " open finished." << std::endl;
  m_isOpen = true;

  return isOpen();

} // endopen( const std::string & _path )

void
GCW::Dbo::GnuCash::Session::
closeGnuCash()
{
  std::cout << __FILE__ << ":" << __LINE__ << " qof_session_end" << std::endl;

  qof_session_end( m_session );

  m_session = nullptr;

  gnc_engine_shutdown();
}


GCW::Dbo::GnuCash::Book
GCW::Dbo::GnuCash::Session::
book()
{
  return Book( this );
}




/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


GCW::Dbo::GnuCash::Book::
Book( GCW::Dbo::GnuCash::Session * _session )
: m_session( _session )
{
  m_book = qof_session_get_book( m_session-> qofSession() );
}

GCW::Dbo::GnuCash::Account
GCW::Dbo::GnuCash::Book::
rootAccount()
{
  return Account( gnc_book_get_root_account( m_book ), this );
}


GCW::Dbo::GnuCash::Account
GCW::Dbo::GnuCash::Book::
accountByGuid( const std::string _guid )
{
  return GCW::Dbo::GnuCash::Account();
}

guint
GCW::Dbo::GnuCash::Book::
count_transactions()
{
  return gnc_book_count_transactions( m_book );
}



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

namespace {

std::string _to_string( const char * s )
{
  std::string retVal;

  if( s )
    retVal = s;

  return retVal;
}

} // endnamespace {

GCW::Dbo::GnuCash::Account::
Account( ::Account * _gncAccount, Book * _book )
: m_gncAccount( _gncAccount ),
  m_book( _book )
{
}

GCW::Dbo::GnuCash::Account::
Account( const Account & _copy )
: m_gncAccount( _copy.m_gncAccount ),
  m_book( _copy.m_book )
{
}

::Account *
GCW::Dbo::GnuCash::Account::
gncAccount()
{
  return m_gncAccount;
}

GCW::Dbo::GnuCash::Book *
GCW::Dbo::GnuCash::Account::
book()
{
  return m_book;
}

std::string
GCW::Dbo::GnuCash::Account::
guid()
{
  return _to_string( guid_to_string( xaccAccountGetGUID( gncAccount() ) ) );
}

std::string
GCW::Dbo::GnuCash::Account::
name()
{
  return _to_string( xaccAccountGetName( gncAccount() ) );
}

std::string
GCW::Dbo::GnuCash::Account::
code()
{
  return _to_string( xaccAccountGetCode( gncAccount() ) );
}

std::string
GCW::Dbo::GnuCash::Account::
description()
{
  return _to_string( xaccAccountGetDescription( gncAccount() ) );
}

std::string
GCW::Dbo::GnuCash::Account::
notes()
{
  return _to_string( xaccAccountGetNotes( gncAccount() ) );
}

std::vector< GCW::Dbo::GnuCash::Account >
GCW::Dbo::GnuCash::Account::
children()
{
  std::vector< GCW::Dbo::GnuCash::Account > retVal;

  for( int i=0; i< gnc_account_n_children( gncAccount() ); i++ )
    retVal.push_back( GCW::Dbo::GnuCash::Account( gnc_account_nth_child( gncAccount(), i ), book() ) );

  return retVal;

} // endchildren()

#endif


