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
    namespace BudgetAmounts {
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
//  using IdType = std::string;
//  static auto invalidId()-> IdType { return std::string(); }
//  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Invoices::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Invoices::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace BudgetAmounts {

/*!
** \brief BudgetAmounts Class
**
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

    std::string m_budget_guid      ; // text(32) NOT NULL
    std::string m_account_guid     ; // text(32) NOT NULL
    int         m_period_num       ; // integer  NOT NULL
    int         m_amount_num       ; // bigint   NOT NULL
    int         m_amount_denom     ; // bigint   NOT NULL

}; // endclass Item

    } // endnamespace BudgetAmounts {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_BUDGETAMOUNTS_ITEM_H___

