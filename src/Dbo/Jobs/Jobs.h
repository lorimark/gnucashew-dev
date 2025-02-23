#line 2 "src/Dbo/Jobs/Jobs.h"

#ifndef __DBO_JOBS_H___
#define __DBO_JOBS_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Jobs {

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

    } // Jobs
  } // Dbo
} // GCW



#endif // __DBO_JOBS_H___


