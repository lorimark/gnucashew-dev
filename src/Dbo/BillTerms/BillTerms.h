#line 2 "src/Dbo/BillTerms/BillTerms.h"

#ifndef __DBO_BILLTERMS_H___
#define __DBO_BILLTERMS_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace BillTerms {

/*!
** \brief Load by Guid
**
*/
auto load( const std::string & _guid )-> Item::Ptr;

/*!
** \brief Load by Guid
**
*/
auto byGuid( const std::string & _guid )-> Item::Ptr;

    } // BillTerms
  } // Dbo
} // GCW



#endif // __DBO_BILLTERMS_H___


