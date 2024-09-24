#line 2 "src/Dbo/Versions/Versions.h"

#ifndef __DBO_VERSIONS_H___
#define __DBO_VERSIONS_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Versions {

/*!
** \brief Load Version by Table Name
**
*/
auto load( const std::string & _table_name )-> Item::Ptr;

    } // Versions
  } // Dbo
} // GCW



#endif // __DBO_VERSIONS_H___


