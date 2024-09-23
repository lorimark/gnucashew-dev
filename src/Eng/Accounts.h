#line 2 "src/Eng/Accounts.h"

#ifndef __ENG_ACCOUNTS_H___
#define __ENG_ACCOUNTS_H___

#include <string>

#include "../Dbo/Accounts/Accounts.h"

namespace GCW {
  namespace Eng {

class Accounts
{
  public:

    Accounts();

    static GCW::Dbo::Accounts::Item::Ptr byGuid( const std::string & _accountGuid );

  private:

}; // endclass Accounts

  } //  namespace Eng {
} // endnamespace GCW {


#endif // #ifndef __ENG_ACCOUNTS_H___



