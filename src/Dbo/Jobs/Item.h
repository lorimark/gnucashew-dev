#line 2 "src/Dbo/Jobs/Item.h"

#ifndef __DBO_JOBS_ITEM_H___
#define __DBO_JOBS_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the Entries class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Jobs {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Jobs::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Jobs::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Jobs::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Jobs {

/*!
** \brief Jobs Class
**
**
** \dot
** digraph JobsMap
** {
**   JobsItem;
** }
** \enddot
**
** \par Native GnuCash Jobs Sqlite Schema
** \code
**    CREATE TABLE jobs
**    (
**     guid        text(32) PRIMARY KEY NOT NULL,
**     id          text(2048)           NOT NULL,
**     name        text(2048)           NOT NULL,
**     reference   text(2048)           NOT NULL,
**     active      integer              NOT NULL,
**     owner_type  integer,
**     owner_guid  text(32)
**    );
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
    Item( const std::string & _guid ): m_guid( _guid ){}

    /*!
    ** \brief GUID
    **
    ** Return account 'guid' value - the primary key for the account
    */
    auto guid() const-> const std::string & { return m_guid; }

    template< class Action > auto
    persist( Action & action )-> void
    {
      Wt::Dbo::id   ( action, m_guid             , GCW::Dbo::Jobs::Field::guid       ,   32 ); // text(32) PRIMARY KEY NOT NULL,
      Wt::Dbo::field( action, m_id               , GCW::Dbo::Jobs::Field::id         , 2048 ); // text(2048)           NOT NULL,
      Wt::Dbo::field( action, m_name             , GCW::Dbo::Jobs::Field::name       , 2048 ); // text(2048)           NOT NULL,
      Wt::Dbo::field( action, m_reference        , GCW::Dbo::Jobs::Field::reference  , 2048 ); // text(2048)           NOT NULL,
      Wt::Dbo::field( action, m_active           , GCW::Dbo::Jobs::Field::active            ); // integer              NOT NULL,
      Wt::Dbo::field( action, m_owner_type       , GCW::Dbo::Jobs::Field::owner_type        ); // integer,
      Wt::Dbo::field( action, m_owner_guid       , GCW::Dbo::Jobs::Field::owner_guid ,   32 ); // text(32),

    } // endpersist( Action & action )-> void

  private:

    std::string m_guid             ; // text(32) PRIMARY KEY NOT NULL,
    std::string m_id               ; // text(2048)           NOT NULL,
    std::string m_name             ; // text(2048)           NOT NULL,
    std::string m_reference        ; // text(2048)           NOT NULL,
    int         m_active           ; // integer              NOT NULL,
    int         m_owner_type       ; // integer,
    std::string m_owner_guid       ; // text(32),

}; // endclass Item

    } // endnamespace Jobs {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_JOBS_ITEM_H___

