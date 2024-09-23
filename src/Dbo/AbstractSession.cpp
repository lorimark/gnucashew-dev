#line 2 "src/Dbo/AbstractSession.cpp"

#include <iostream>

#include <Wt/Dbo/backend/Sqlite3.h>

#include <gcwglobal.h>

#include "GncLock/GncLock.h"
#include "Accounts/Accounts.h"
#include "Customers/Customers.h"
#include "Slots/Slots.h"
#include "Splits/Splits.h"
#include "Transactions/Transactions.h"
#include "Vars/Vars.h"
#include "AbstractSession.h"

auto
GCW::Dbo::AbstractSession::
open( const std::string & _path )-> bool
{
  /*
  ** Clear this so that if we don't get opened, then we don't
  **  accidently indicate that we are open.
  **
  */
  m_isOpen = false;

  /*
  ** Remember the path.
  **
  */
  m_path = _path;

  /*
  ** Dynamicals
  **
  */
  std::cout << __FILE__ << ":" << __LINE__ << " " << GCW::Dbo:: GncLock      ::s_tableName << std::endl;

  mapClass< GCW::Dbo:: GncLock      ::Item >( GCW::Dbo:: GncLock      ::s_tableName );
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

  mapClass< GCW::Dbo:: Accounts     ::Item >( GCW::Dbo:: Accounts     ::s_tableName );
  mapClass< GCW::Dbo:: Customers    ::Item >( GCW::Dbo:: Customers    ::s_tableName );
  mapClass< GCW::Dbo:: Transactions ::Item >( GCW::Dbo:: Transactions ::s_tableName );
  mapClass< GCW::Dbo:: Slots        ::Item >( GCW::Dbo:: Slots        ::s_tableName );
  mapClass< GCW::Dbo:: Splits       ::Item >( GCW::Dbo:: Splits       ::s_tableName );
  mapClass< GCW::Dbo:: Vars         ::Item >( GCW::Dbo:: Vars         ::s_tableName );

  /*
  ** This never opens true.
  **
  */
  return false;

} // endbool GCW::Dbo::AbstractSession::open( const std::string & _path )


