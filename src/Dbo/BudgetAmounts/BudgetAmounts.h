#line 2 "src/Dbo/BudgetAmounts/BudgetAmounts.h"

#ifndef __DBO_BUDGETAMOUNTS_H___
#define __DBO_BUDGETAMOUNTS_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace BudgetAmounts {

/*!
** \brief Load BudgetAmount by Guid
*/
auto load( const std::string & _guid )-> Item::Ptr;

/*!
** \brief Load BudgetAmount by Guid
*/
auto byGuid( const std::string & _guid )-> Item::Ptr;

    } // BudgetAmounts
  } // Dbo
} // GCW



#endif // __DBO_BUDGETAMOUNTS_H___


