#line 2 "src/Dbo/Users/User.h"

#ifndef __DBO_USERS_H___
#define __DBO_USERS_H___

#include "../BaseItem.h"

#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>

namespace GCW {
  namespace Dbo {
    namespace Users {

class Item
: public GCW::Dbo::BaseItem< Item >
{
  public:

    Item(){}

    template <class Action>
    auto persist( Action & a )-> void
    {
      Wt::Dbo::field( a, m_employee_guid , "employee_guid" , 32 ); // text(32) NOT NULL
    }

    std::string m_employee_guid;

};

    } // endnamespace Users
  } // endnamespace Dbo
} // endnamespace GCW

DBO_EXTERN_TEMPLATES( GCW::Dbo::Users::Item )

#endif // __DBO_USERS_H___



