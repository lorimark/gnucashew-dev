#line 2 "src/Dbo/Slots/Slots.h"

#ifndef __DBO_SLOTS_H___
#define __DBO_SLOTS_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Slots {

auto get()-> GCW::Dbo::Slots::Item::Vector ;
auto get( const std::string & _guid, const std::string & _name )-> GCW::Dbo::Slots::Item::Ptr ;

    } // endSlots
  } // endDbo
} // endGCW

#endif // __DBO_SLOTS_H___


