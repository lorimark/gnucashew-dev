#line 2 "src/Dbo/Employees/Employees.h"

#ifndef __DBO_EMPLOYEES_H___
#define __DBO_EMPLOYEES_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Employees {

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

    } // Employees
  } // Dbo
} // GCW



#endif // __DBO_EMPLOYEES_H___


