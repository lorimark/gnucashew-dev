#line 2 "src/Dbo/Prefrences.cpp"

#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Serializer.h>

#include "../App.h"
#include "Prefrences.h"


GCW::Dbo::Prefrences::Item::
Item( GCW::Dbo::Vars::Item::Ptr _varItem )
{
}


GCW::Dbo::Prefrences::Item
GCW::Dbo::Prefrences::
get()
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  GCW::Dbo::Prefrences::Item retVal( GCW::Dbo::Vars::get( "prefrences", "system" ) );

  return retVal;

} // endget()

GCW::Dbo::Prefrences::ReverseBalanceAccounts
GCW::Dbo::Prefrences::Item::
reverseBalanceAccounts() const
{
//  return GCW::Dbo::Prefrences::ReverseBalanceAccounts::NONE;
//  return GCW::Dbo::Prefrences::ReverseBalanceAccounts::INCOME_EXPENSE;
  return GCW::Dbo::Prefrences::ReverseBalanceAccounts::CREDIT;
}


