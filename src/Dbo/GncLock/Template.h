#line 2 "src/Dbo/GncLock/Template.h"

#ifndef __DBO_GNCLOCK_TEMPLATE_H___
#define __DBO_GNCLOCK_TEMPLATE_H___

#include <string>

#include <Wt/Dbo/Dbo.h>

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the GncLock class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace GncLock {
      class Item;
    }
  }
}

/*
** Define these dbo_traits to prevent the system from
**  automatically generating an ID field or a VERSION
**  field, and instead substitute the guid field
**  as the primary key.
**
*/
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::GncLock::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return "Hostname"; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::GncLock::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::GncLock::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace GncLock {

template <class C>
class Template
: public GCW::Dbo::BaseItem<C>
{
  public:

    Template(){}

    template<class Action>
    void persist( Action & a )
    {
//      Wt::Dbo::field( a, m_hostname , GCW::Dbo::GncLock::FieldDef::hostname );
      Wt::Dbo::field( a, m_pid      , GCW::Dbo::GncLock::FieldDef::pid      );

    } // endvoid persist( Action & a )

    std::string m_hostname          ;
    int         m_pid          = -1 ;

}; // endclass Template

    } // endnamespace GncLock {
  } // endnamespace Dbo {
} // endnamespace Swims {

#endif // #ifndef __DBO_GNCLOCK_TEMPLATE_H___


