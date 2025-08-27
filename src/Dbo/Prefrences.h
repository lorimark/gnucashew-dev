#line 2 "src/Dbo/Prefrences.h"

#ifndef __DBO_PREFRENCES_H___
#define __DBO_PREFRENCES_H___

#include "Vars/Vars.h"

/*
** Predefine the class that fixin to come up.
**
*/
//namespace GCW {
//  namespace Dbo {
//    namespace Prefrences {
//      class Item;
//    }
//  }
//}

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Prefrences {

/*!
** \brief Reversed Balance Accounts
**
** Reverse Balanced accounts: This option lets you determine whether account balances
**  will display as positive or negative numbers:
**
**  - Income & Expense assigns a positive credit balance to income account balances and a negative debit balance to expense account balances.
**  - Credit accounts (default) displays a positive balance for account types that would normally carry a credit balance (income, credit, liability, equity).
**  - None shows all credit balances as negative and all debit balances as positive.
**
*/
enum class ReverseBalanceAccounts
{
  /// no account balances are reversed
  NONE = 0x01,

  /// income and expense account balances are reversed
  INCOME_EXPENSE = 0x02,

  /// credit account balances are reversed
  CREDIT = 0x03
};

/*!
** \brief Account Register Highlighting
**
** This controls how some of the display features of the
**  account-register window are handled
**
*/
enum class AccountRegisterHighlight
{
  /// no highlight handling
  NONE = 0x01,

  /// normal handling - neg values are red
  NORMAL = 0x02,

  /// extra handling - neg values are gold-background-full-line
  NEGVAL_EXTRA = 0x03,
};

/*!
** \brief Variables Item Class
**
**
*/
class Item
{
  public:

    Item( GCW::Dbo::Vars::Item::Ptr _varItem );

    auto reverseBalanceAccounts() const-> ReverseBalanceAccounts;
    auto accountRegisterHighlight( AccountRegisterHighlight _value ) const-> bool;
    auto askOnDelete() const-> bool;

  private:

    GCW::Dbo::Vars::Item m_varItem;

}; // endclass Item

auto get()-> GCW::Dbo::Prefrences::Item;

    } // endnamespace Prefrences {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __PREFRENCES_H___

