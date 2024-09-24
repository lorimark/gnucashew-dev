#line 2 "src/Dbo/Entries/Entries.h"

#ifndef __DBO_ENTRIES_H___
#define __DBO_ENTRIES_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Entries {

/*!
** \brief Load Account by Guid
**
*/
auto load( const std::string & _guid )-> Item::Ptr;

/*!
** \brief Load Account by Guid
**
*/
auto byGuid( const std::string & _guid )-> Item::Ptr;

    } // Entries
  } // Dbo
} // GCW



#endif // __DBO_ENTRIES_H___


