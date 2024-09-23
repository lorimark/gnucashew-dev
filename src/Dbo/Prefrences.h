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
  NONE           = 0x01,
  INCOME_EXPENSE = 0x02,
  CREDIT         = 0x03
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

    ReverseBalanceAccounts reverseBalanceAccounts() const;


  private:

    GCW::Dbo::Vars::Item m_varItem;

}; // endclass Item

GCW::Dbo::Prefrences::Item get();

    } // endnamespace Prefrences {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __PREFRENCES_H___

