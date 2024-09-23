#line 2 "src/Dbo/Customers/Customers.h"

#ifndef __DBO_CUSTOMERS_H___
#define __DBO_CUSTOMERS_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Customers {

/*!
** \brief Load Customer by Guid
**
*/
Item::Ptr byGuid( const std::string & _guid );

    } // endnamespace Customers

  } // endnamespace Dbo

} // endnamespace GCW

#endif // __DBO_CUSTOMERS_H___

