#line 2 "src/Dbo/Versions/Item.h"

#ifndef __DBO_VERSIONS_ITEM_H___
#define __DBO_VERSIONS_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Versions {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Versions::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Versions::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Versions::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Versions {

/*!
** \brief Versions Class
**
**
** \dot
** digraph VersionsMap
** {
**   VersionsItem;
** }
** \enddot
**
** \par Native GnuCash Invoice Sqlite Schema
** \code
**   CREATE TABLE versions
**   (
**    table_name text(50) PRIMARY KEY NOT NULL,
**    table_version integer NOT NULL
**   );
** \endcode
**
*/
class Item
: public GCW::Dbo::BaseItem< Item >
{
  public:

    /*!
    ** \brief ctor
    */
    Item(){}

    /*!
    ** \brief ctor with guid
    */
    Item( const std::string & _table_name ): m_table_name( _table_name ){}

    template< class Action > auto
    persist( Action & action )-> void
    {
      Wt::Dbo::id   ( action, m_table_name    , GCW::Dbo::Versions::Field::table_name    );
      Wt::Dbo::field( action, m_table_version , GCW::Dbo::Versions::Field::table_version );

    } // endpersist( Action & action )-> void

  private:

    std::string m_table_name       ; // text(50) PRIMARY KEY NOT NULL,
    int         m_table_version    ; // integer NOT NULL

}; // endclass Item

    } // endnamespace Versions {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_VERSIONS_ITEM_H___

