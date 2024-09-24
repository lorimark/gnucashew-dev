#line 2 "src/Dbo/Books/Books.h"

#ifndef __DBO_BOOKS_H___
#define __DBO_BOOKS_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Books {

/*!
** \brief Load Books by Guid
**
*/
auto load( const std::string & _guid )-> Item::Ptr;

/*!
** \brief Load Books by Guid
**
*/
auto byGuid( const std::string & _guid )-> Item::Ptr;

    } // Books
  } // Dbo
} // GCW



#endif // __DBO_BOOKS_H___


