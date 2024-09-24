#line 2 "src/Dbo/Entries/Item.h"

#ifndef __DBO_ENTRIES_ITEM_H___
#define __DBO_ENTRIES_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the Entries class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Entries {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Entries::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Entries::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Entries::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Entries {

/*!
** \brief Entries Class
**
**
** \dot
** digraph EntriesMap
** {
**   EntriesItem;
** }
** \enddot
**
** \par Native GnuCash Account Sqlite Schema
** \code
**   CREATE TABLE entries
**   (
**    guid text(32) PRIMARY KEY NOT NULL,
**    date text(19) NOT NULL,
**    date_entered text(19),
**    description text(2048),
**    action text(2048),
**    notes text(2048),
**    quantity_num bigint,
**    quantity_denom bigint,
**    i_acct text(32),
**    i_price_num bigint,
**    i_price_denom bigint,
**    i_discount_num bigint,
**    i_discount_denom bigint,
**    invoice text(32),
**    i_disc_type text(2048),
**    i_disc_how text(2048),
**    i_taxable integer,
**    i_taxincluded integer,
**    i_taxtable text(32),
**    b_acct text(32),
**    b_price_num bigint,
**    b_price_denom bigint,
**    bill text(32),
**    b_taxable integer,
**    b_taxincluded integer,
**    b_taxtable text(32),
**    b_paytype integer,
**    billable integer,
**    billto_type integer,
**    billto_guid text(32),
**    order_guid text(32)
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
      Wt::Dbo::id   ( action, m_guid             , GCW::Dbo::Entries::Field::guid             ,   32 ); // text(32) PRIMARY KEY NOT NULL,
      Wt::Dbo::field( action, m_date             , GCW::Dbo::Entries::Field::date             ,   19 ); //  text(19) NOT NULL,
      Wt::Dbo::field( action, m_date_entered     , GCW::Dbo::Entries::Field::date_entered     ,   19 ); //  text(19),
      Wt::Dbo::field( action, m_description      , GCW::Dbo::Entries::Field::description      , 2048 ); //  text(2048),
      Wt::Dbo::field( action, m_action           , GCW::Dbo::Entries::Field::action           , 2048 ); //  text(2048),
      Wt::Dbo::field( action, m_notes            , GCW::Dbo::Entries::Field::notes            , 2048 ); // text(2048),
      Wt::Dbo::field( action, m_quantity_num     , GCW::Dbo::Entries::Field::quantity_num            ); // bigint,
      Wt::Dbo::field( action, m_quantity_denom   , GCW::Dbo::Entries::Field::quantity_denom          ); // bigint,
      Wt::Dbo::field( action, m_i_acct           , GCW::Dbo::Entries::Field::i_acct           ,   32 ); // text(32),
      Wt::Dbo::field( action, m_i_price_num      , GCW::Dbo::Entries::Field::i_price_num             ); // bigint,
      Wt::Dbo::field( action, m_i_price_denom    , GCW::Dbo::Entries::Field::i_price_denom           ); // bigint,
      Wt::Dbo::field( action, m_i_discount_num   , GCW::Dbo::Entries::Field::i_discount_num          ); // bigint,
      Wt::Dbo::field( action, m_i_discount_denom , GCW::Dbo::Entries::Field::i_discount_denom        ); // bigint,
      Wt::Dbo::field( action, m_invoice          , GCW::Dbo::Entries::Field::invoice          ,   32 ); // text(32),
      Wt::Dbo::field( action, m_i_disc_type      , GCW::Dbo::Entries::Field::i_disc_type      , 2048 ); // text(2048),
      Wt::Dbo::field( action, m_i_disc_how       , GCW::Dbo::Entries::Field::i_disc_how       , 2048 ); // text(2048),
      Wt::Dbo::field( action, m_i_taxable        , GCW::Dbo::Entries::Field::i_taxable               ); // integer,
      Wt::Dbo::field( action, m_i_taxincluded    , GCW::Dbo::Entries::Field::i_taxincluded           ); // integer,
      Wt::Dbo::field( action, m_i_taxtable       , GCW::Dbo::Entries::Field::i_taxtable       ,   32 ); // text(32),
      Wt::Dbo::field( action, m_b_acct           , GCW::Dbo::Entries::Field::b_acct           ,   32 ); // text(32),
      Wt::Dbo::field( action, m_b_price_num      , GCW::Dbo::Entries::Field::b_price_num             ); // bigint,
      Wt::Dbo::field( action, m_b_price_denom    , GCW::Dbo::Entries::Field::b_price_denom           ); // bigint,
      Wt::Dbo::field( action, m_bill             , GCW::Dbo::Entries::Field::bill             ,   32 ); // text(32),
      Wt::Dbo::field( action, m_b_taxable        , GCW::Dbo::Entries::Field::b_taxable               ); // integer,
      Wt::Dbo::field( action, m_b_taxincluded    , GCW::Dbo::Entries::Field::b_taxincluded           ); // integer,
      Wt::Dbo::field( action, m_b_taxtable       , GCW::Dbo::Entries::Field::b_taxtable       ,   32 ); // text(32),
      Wt::Dbo::field( action, m_b_paytype        , GCW::Dbo::Entries::Field::b_paytype               ); // integer,
      Wt::Dbo::field( action, m_billable         , GCW::Dbo::Entries::Field::billable                ); // integer,
      Wt::Dbo::field( action, m_billto_type      , GCW::Dbo::Entries::Field::billto_type             ); // integer,
      Wt::Dbo::field( action, m_billto_guid      , GCW::Dbo::Entries::Field::billto_guid      ,   32 ); // text(32),
      Wt::Dbo::field( action, m_order_guid       , GCW::Dbo::Entries::Field::order_guid       ,   32 ); // text(32)

    } // endpersist( Action & action )-> void

  private:

    std::string m_guid             ; // text(32) PRIMARY KEY NOT NULL,
    std::string m_date             ; // text(19) NOT NULL,
    std::string m_date_entered     ; // text(19),
    std::string m_description      ; // text(2048),
    std::string m_action           ; // text(2048),
    std::string m_notes            ; // text(2048),
    int         m_quantity_num     ; // bigint,
    int         m_quantity_denom   ; // bigint,
    std::string m_i_acct           ; // text(32),
    int         m_i_price_num      ; // bigint,
    int         m_i_price_denom    ; // bigint,
    int         m_i_discount_num   ; // bigint,
    int         m_i_discount_denom ; // bigint,
    std::string m_invoice          ; // text(32),
    std::string m_i_disc_type      ; // text(2048),
    std::string m_i_disc_how       ; // text(2048),
    int         m_i_taxable        ; // integer,
    int         m_i_taxincluded    ; // integer,
    std::string m_i_taxtable       ; // text(32),
    std::string m_b_acct           ; // text(32),
    int         m_b_price_num      ; // bigint,
    int         m_b_price_denom    ; // bigint,
    std::string m_bill             ; // text(32),
    int         m_b_taxable        ; // integer,
    int         m_b_taxincluded    ; // integer,
    std::string m_b_taxtable       ; // text(32),
    int         m_b_paytype        ; // integer,
    int         m_billable         ; // integer,
    int         m_billto_type      ; // integer,
    std::string m_billto_guid      ; // text(32),
    std::string m_order_guid       ; // text(32)

}; // endclass Item

    } // endnamespace Entries {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_ENTRIES_ITEM_H___

