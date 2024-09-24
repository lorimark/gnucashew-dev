#line 2 "src/Dbo/Invoices/Item.h"

#ifndef __DBO_INVOICES_ITEM_H___
#define __DBO_INVOICES_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the Entries class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Invoices {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Invoices::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Invoices::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Invoices::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Invoices {

/*!
** \brief Invoices Class
**
**
** \dot
** digraph InvoicesMap
** {
**   InvoicesItem;
** }
** \enddot
**
** \par Native GnuCash Invoice Sqlite Schema
** \code
**    CREATE TABLE invoices
**    (
**     guid text(32) PRIMARY KEY NOT NULL,
**     id text(2048) NOT NULL,
**     date_opened text(19),
**     date_posted text(19),
**     notes text(2048) NOT NULL,
**     active integer NOT NULL,
**     currency text(32) NOT NULL,
**     owner_type integer,
**     owner_guid text(32),
**     terms text(32),
**     billing_id text(2048),
**     post_txn text(32),
**     post_lot text(32),
**     post_acc text(32),
**     billto_type integer,
**     billto_guid text(32),
**     charge_amt_num bigint,
**     charge_amt_denom bigint
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
      Wt::Dbo::id   ( action, m_guid             , GCW::Dbo::Invoices::Field::guid             ,   32 ); // text(32) PRIMARY KEY NOT NULL,
      Wt::Dbo::field( action, m_id               , GCW::Dbo::Invoices::Field::id               , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_date_opened      , GCW::Dbo::Invoices::Field::date_opened      ,   19 ); // text(19),
      Wt::Dbo::field( action, m_date_posted      , GCW::Dbo::Invoices::Field::date_posted      ,   19 ); // text(19),
      Wt::Dbo::field( action, m_notes            , GCW::Dbo::Invoices::Field::notes            , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_active           , GCW::Dbo::Invoices::Field::active                  ); // integer NOT NULL,
      Wt::Dbo::field( action, m_currency         , GCW::Dbo::Invoices::Field::currency         ,   32 ); // text(32) NOT NULL,
      Wt::Dbo::field( action, m_owner_type       , GCW::Dbo::Invoices::Field::owner_type              ); // integer,
      Wt::Dbo::field( action, m_owner_guid       , GCW::Dbo::Invoices::Field::owner_guid       ,   32 ); // text(32),
      Wt::Dbo::field( action, m_terms            , GCW::Dbo::Invoices::Field::terms            ,   32 ); // text(32),
      Wt::Dbo::field( action, m_billing_id       , GCW::Dbo::Invoices::Field::billing_id       , 2048 ); // text(2048),
      Wt::Dbo::field( action, m_post_txn         , GCW::Dbo::Invoices::Field::post_txn         ,   32 ); // text(32),
      Wt::Dbo::field( action, m_post_lot         , GCW::Dbo::Invoices::Field::post_lot         ,   32 ); // text(32),
      Wt::Dbo::field( action, m_post_acc         , GCW::Dbo::Invoices::Field::post_acc         ,   32 ); // text(32),
      Wt::Dbo::field( action, m_billto_type      , GCW::Dbo::Invoices::Field::billto_type             ); // integer,
      Wt::Dbo::field( action, m_billto_guid      , GCW::Dbo::Invoices::Field::billto_guid      ,   32 ); // text(32),
      Wt::Dbo::field( action, m_charge_amt_num   , GCW::Dbo::Invoices::Field::charge_amt_num          ); // bigint,
      Wt::Dbo::field( action, m_charge_amt_denom , GCW::Dbo::Invoices::Field::charge_amt_denom        ); // bigint

    } // endpersist( Action & action )-> void

  private:

    std::string m_guid             ; // text(32) PRIMARY KEY NOT NULL,
    std::string m_id               ; // text(2048) NOT NULL,
    std::string m_date_opened      ; // text(19),
    std::string m_date_posted      ; // text(19),
    std::string m_notes            ; // text(2048) NOT NULL,
    int         m_active           ; // integer NOT NULL,
    std::string m_currency         ; // text(32) NOT NULL,
    int         m_owner_type       ; // integer,
    std::string m_owner_guid       ; // text(32),
    std::string m_terms            ; // text(32),
    std::string m_billing_id       ; // text(2048),
    std::string m_post_txn         ; // text(32),
    std::string m_post_lot         ; // text(32),
    std::string m_post_acc         ; // text(32),
    int         m_billto_type      ; // integer,
    std::string m_billto_guid      ; // text(32),
    int         m_charge_amt_num   ; // bigint,
    int         m_charge_amt_denom ; // bigint

}; // endclass Item

    } // endnamespace Invoices {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_INVOICES_ITEM_H___

