#line 2 "src/Dbo/Books/Item.h"

#ifndef __DBO_BOOKS_ITEM_H___
#define __DBO_BOOKS_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Books {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Books::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Books::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Books::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Books {

/*!
** \brief Books Class
**
**
** \dot
** digraph BooksMap
** {
**   BooksItem;
** }
** \enddot
**
** \par Native GnuCash Books Sqlite Schema
** \code
**   CREATE TABLE books
**   (
**     guid text(32) PRIMARY KEY NOT NULL,
**     root_account_guid text(32) NOT NULL,
**     root_template_guid text(32) NOT NULL
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
      Wt::Dbo::id   ( action, m_guid               , GCW::Dbo::Books::Field::guid               , 32 ); // text(32) PRIMARY KEY NOT NULL,
      Wt::Dbo::field( action, m_root_account_guid  , GCW::Dbo::Books::Field::root_account_guid  , 32 ); // text(32) NOT NULL,
      Wt::Dbo::field( action, m_root_template_guid , GCW::Dbo::Books::Field::root_template_guid , 32 ); // text(32) NOT NULL

    } // endpersist( Action & action )-> void

  private:

    std::string m_guid               ; // text(32) PRIMARY KEY NOT NULL,
    std::string m_root_account_guid  ; // text(32) NOT NULL,
    std::string m_root_template_guid ; // text(32) NOT NULL

}; // endclass Item

    } // endnamespace Books {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_BOOKS_ITEM_H___

