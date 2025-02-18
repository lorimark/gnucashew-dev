#line 2 "src/Dbo/Commodities/Commodities.h"

#ifndef __DBO_COMMODITIES_H___
#define __DBO_COMMODITIES_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Commodities {

/*!
** \brief Load Account by GUID
**
*/
auto load( const std::string & _guid )-> Item::Ptr;

/*!
** \brief Load Account by GUID
**
*/
auto byGuid( const std::string & _guid )-> Item::Ptr;

    } // Commodities
  } // Dbo
} // GCW



#endif // __DBO_COMMODITIES_H___


