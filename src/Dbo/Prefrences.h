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

enum class ReverseBalanceAccounts
{
  /// no account balances are reversed
  NONE           = 0x01,

  /// income and expense account balances are reversed
  INCOME_EXPENSE = 0x02,

  /// credit account balances are reversed
  CREDIT         = 0x03
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
  NONE         = 0x01,

  /// normal handling - neg values are red
  NORMAL       = 0x02,

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

    auto reverseBalanceAccounts()   const-> ReverseBalanceAccounts;
    auto accountRegisterHighlight( AccountRegisterHighlight _value ) const-> bool;

  private:

    GCW::Dbo::Vars::Item m_varItem;

}; // endclass Item

GCW::Dbo::Prefrences::Item get();

    } // endnamespace Prefrences {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __PREFRENCES_H___

