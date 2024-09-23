#line 2 "src/Dbo/GncLock/GncLock.h"

#ifndef __DBO_GNCLOCK_H___
#define __DBO_GNCLOCK_H___

namespace Wt {
  namespace Dbo {
    class Session;
  }
}

#include "Item.h"

namespace GCW {
  namespace Dbo {

    /*!
    ** \brief GncLock
    **
    **
    */
    namespace GncLock {

auto mapClasses      ( Wt::Dbo::Session & session )-> void;
auto postCreateTables( Wt::Dbo::Session & session )-> void;

auto load          ( int _id                     )-> GCW::Dbo::GncLock::Item::Ptr;
auto addNew        (                             )-> GCW::Dbo::GncLock::Item::Ptr;

    } // endnamespace GncLock {
  } // endnamespace Dbo {
} // endnamespace Swims {

#endif // __DBO_GNCLOCK_H___
