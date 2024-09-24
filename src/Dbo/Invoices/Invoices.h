#line 2 "src/Dbo/Invoices/Invoices.h"

#ifndef __DBO_INVOICES_H___
#define __DBO_INVOICES_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Invoices {

/*!
** \brief Load Invoice by Guid
**
*/
auto load( const std::string & _guid )-> Item::Ptr;

/*!
** \brief Load Invoice by Guid
**
*/
auto byGuid( const std::string & _guid )-> Item::Ptr;

    } // Invoices
  } // Dbo
} // GCW



#endif // __DBO_INVOICES_H___


