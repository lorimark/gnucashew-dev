#line 2 "src/Dbo/Accounts/Item.cpp"

//#include <gnucash/gnc-session.h>
//#include <gnucash/Account.h>

#include "../Transactions/Transactions.h"
#include "../Slots/Slots.h"
#include "Definition.h"

auto
GCW::Dbo::Accounts::Item::
accountDef() const-> const GCW::Dbo::Accounts::AccountDef_t &
{
  auto atn = accountTypeName();

  for( auto & val : GCW::Dbo::Accounts::s_accountDefs )
    if( val.backend_name == accountTypeName() )
      return val;

  return GCW::Dbo::Accounts::s_accountDefs.at(0);
}

auto
GCW::Dbo::Accounts::Item::
accountDrCr() const-> GCW::Dbo::Accounts::DrCr
{
  auto atn = accountTypeName();

  for( auto & val : GCW::Dbo::Accounts::s_accountDefs )
    if( val.backend_name == accountTypeName() )
      return val.drcr;

  return GCW::Dbo::Accounts::DrCr::NONE;
}

auto
GCW::Dbo::Accounts::Item::
accountType() const-> GCW::Dbo::Accounts::Type
{
  auto atn = accountTypeName();

  for( auto & val : GCW::Dbo::Accounts::s_accountDefs )
    if( val.backend_name == accountTypeName() )
      return val.type;

  return GCW::Dbo::Accounts::Type::NONE;
}

auto
GCW::Dbo::Accounts::Item::
fullName() const-> std::string
{
  return GCW::Dbo::Accounts::fullName( self() );

} // endfullName() const-> std::string

auto
GCW::Dbo::Accounts::Item::
hasColor() const-> bool
{
  return GCW::Dbo::Slots::get( guid(), "color" ).get();

} // endhasColor() const-> bool

auto
GCW::Dbo::Accounts::Item::
color() const-> std::string
{
  std::string retVal;

  if( auto slotItem = GCW::Dbo::Slots::get( guid(), "color" ) )
  {
    retVal = slotItem-> string_val();
  }

  return retVal;

} // endcolor() const-> std::string


