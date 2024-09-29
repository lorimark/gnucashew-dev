#line 2 "src/Dbo/BaseItem.h"

#ifndef __DBO_BASEITEM_H___
#define __DBO_BASEITEM_H___

#include <Wt/Dbo/Dbo.h>

namespace GCW {

/*!
** \brief Database Object Namespace
**
** This namespace is reserved for objects that are used to interface
**  to the back-end datasets directly.
**
** At present, the Session object is only set up to access sqlite
**  data files.
**
** The primary gnucash Dbo classes are intended to be direct-maps of
**  the sqlite underlying schema.
**
** It is possible to have gnucashew modify the existing gnucash schema
**  so as to add additional tables and fields, but it is also possible
**  to simply have gnucashew keep is customized data in a separate
**  database.
**
** \ref see: https://wiki.gnucash.org/wiki/SQL
**
** \ref see: https://wiki.gnucash.org/wiki/images/8/86/Gnucash_erd.png
*/
  namespace Dbo {

template <class C>
  class BaseItem
: public Wt::Dbo::Dbo< C >
{
  public:

    using Ptr = Wt::Dbo::ptr< C >;
    using Collection = Wt::Dbo::collection< Ptr >;
    using Vector = std::vector< Ptr >;

    BaseItem():Wt::Dbo::Dbo<C>() {}

}; // endclass BaseItem

  } // endnamespace Dbo
} // endnamespace GCW {

#endif // end#ifndef __BASEITEM_H___


