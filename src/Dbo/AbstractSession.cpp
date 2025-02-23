#line 2 "src/Dbo/AbstractSession.cpp"

#include <iostream>

#include <Wt/Dbo/backend/Sqlite3.h>

#include <gcwglobal.h>

#include "GncLock/GncLock.h"
#include "Accounts/Accounts.h"
#include "Commodities/Commodities.h"
#include "Books/Books.h"
#include "BillTerms/BillTerms.h"
#include "Invoices/Invoices.h"
#include "Entries/Entries.h"
#include "Jobs/Jobs.h"
#include "Customers/Customers.h"
#include "Employees/Employees.h"
#include "Slots/Slots.h"
#include "Splits/Splits.h"
#include "Transactions/Transactions.h"
#include "Versions/Versions.h"
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
  mapClass< GCW::Dbo:: Accounts     ::Item >( GCW::Dbo:: Accounts     ::s_tableName );
  mapClass< GCW::Dbo:: BillTerms    ::Item >( GCW::Dbo:: BillTerms    ::s_tableName );
  mapClass< GCW::Dbo:: Books        ::Item >( GCW::Dbo:: Books        ::s_tableName );
  mapClass< GCW::Dbo:: Commodities  ::Item >( GCW::Dbo:: Commodities  ::s_tableName );
  mapClass< GCW::Dbo:: Customers    ::Item >( GCW::Dbo:: Customers    ::s_tableName );
  mapClass< GCW::Dbo:: Employees    ::Item >( GCW::Dbo:: Employees    ::s_tableName );
  mapClass< GCW::Dbo:: Entries      ::Item >( GCW::Dbo:: Entries      ::s_tableName );
  mapClass< GCW::Dbo:: GncLock      ::Item >( GCW::Dbo:: GncLock      ::s_tableName );
  mapClass< GCW::Dbo:: Invoices     ::Item >( GCW::Dbo:: Invoices     ::s_tableName );
  mapClass< GCW::Dbo:: Jobs         ::Item >( GCW::Dbo:: Jobs         ::s_tableName );
  mapClass< GCW::Dbo:: Slots        ::Item >( GCW::Dbo:: Slots        ::s_tableName );
  mapClass< GCW::Dbo:: Splits       ::Item >( GCW::Dbo:: Splits       ::s_tableName );
  mapClass< GCW::Dbo:: Transactions ::Item >( GCW::Dbo:: Transactions ::s_tableName );
  mapClass< GCW::Dbo:: Vars         ::Item >( GCW::Dbo:: Vars         ::s_tableName );
  mapClass< GCW::Dbo:: Versions     ::Item >( GCW::Dbo:: Versions     ::s_tableName );

  /*
  ** This never opens true.
  **
  */
  return false;

} // endbool GCW::Dbo::AbstractSession::open( const std::string & _path )


