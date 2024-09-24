#line 2 "src/Dbo/BillTermis/Item.h"

#ifndef __DBO_BILLTERMS_ITEM_H___
#define __DBO_BILLTERMS_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the Entries class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace BillTerms {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::BillTerms::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::BillTerms::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::BillTerms::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace BillTerms {

/*!
** \brief BillTerms Class
**
**
** \dot
** digraph BillTermsMap
** {
**   BillTermsItem;
** }
** \enddot
**
** \par Native GnuCash BillTerms Sqlite Schema
** \code
**   CREATE TABLE billterms
**   (
**    guid text(32) PRIMARY KEY NOT NULL,
**    name text(2048) NOT NULL,
**    description text(2048) NOT NULL,
**    refcount integer NOT NULL,
**    invisible integer NOT NULL,
**    parent text(32),
**    type text(2048) NOT NULL,
**    duedays integer,
**    discountdays integer,
**    discount_num bigint,
**    discount_denom bigint,
**    cutoff integer
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
      Wt::Dbo::id   ( action, m_guid           , GCW::Dbo::BillTerms::Field::guid           ,   32 ); // text(32) PRIMARY KEY NOT NULL,
      Wt::Dbo::field( action, m_name           , GCW::Dbo::BillTerms::Field::name           ,   32 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_description    , GCW::Dbo::BillTerms::Field::description    ,   32 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_refcount       , GCW::Dbo::BillTerms::Field::refcount              ); // integer NOT NULL,
      Wt::Dbo::field( action, m_invisible      , GCW::Dbo::BillTerms::Field::invisible             ); // integer NOT NULL,
      Wt::Dbo::field( action, m_parent         , GCW::Dbo::BillTerms::Field::parent         ,   32 ); // text(32),
      Wt::Dbo::field( action, m_type           , GCW::Dbo::BillTerms::Field::type           ,   32 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_duedays        , GCW::Dbo::BillTerms::Field::duedays               ); // integer,
      Wt::Dbo::field( action, m_discountdays   , GCW::Dbo::BillTerms::Field::discountdays          ); // integer,
      Wt::Dbo::field( action, m_discount_num   , GCW::Dbo::BillTerms::Field::discount_num          ); // bigint,
      Wt::Dbo::field( action, m_discount_denom , GCW::Dbo::BillTerms::Field::discount_denom        ); // bigint,
      Wt::Dbo::field( action, m_cutoff         , GCW::Dbo::BillTerms::Field::cutoff                ); // integer

    } // endpersist( Action & action )-> void

  private:

    std::string m_guid           ; // text(32) PRIMARY KEY NOT NULL,
    std::string m_name           ; // text(2048) NOT NULL,
    std::string m_description    ; // text(2048) NOT NULL,
    int         m_refcount       ; // integer NOT NULL,
    int         m_invisible      ; // integer NOT NULL,
    std::string m_parent         ; // text(32),
    std::string m_type           ; // text(2048) NOT NULL,
    int         m_duedays        ; // integer,
    int         m_discountdays   ; // integer,
    int         m_discount_num   ; // bigint,
    int         m_discount_denom ; // bigint,
    int         m_cutoff         ; // integer

}; // endclass Item

    } // endnamespace BillTerms {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_BILLTERMS_ITEM_H___

