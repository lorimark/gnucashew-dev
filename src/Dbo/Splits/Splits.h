

#ifndef __DBO_SPLITS_H___
#define __DBO_SPLITS_H___

#include <Wt/WDate.h>

#include "../../GnuCashew.h"
#include "../BaseItem.h"

/*
** Predefine the Account class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Splits {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Splits::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static IdType invalidId() { return std::string(); }
  static const char * surrogateIdField() { return nullptr; }
  static const char * versionField()     { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Splits::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Splits::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Splits {

/*!
** \brief Split Item Class
**
** This class represents an 'split' within gnucash
**
** \code
**
**  CREATE TABLE splits
**  (
**   guid text(32) PRIMARY KEY NOT NULL,
**   tx_guid text(32) NOT NULL,
**   account_guid text(32) NOT NULL,
**   memo text(2048) NOT NULL,
**   action text(2048) NOT NULL,
**   reconcile_state text(1) NOT NULL,
**   reconcile_date text(19),
**   value_num bigint NOT NULL,
**   value_denom bigint NOT NULL,
**   quantity_num bigint NOT NULL,
**   quantity_denom bigint NOT NULL,
**   lot_guid text(32)
**  );
**
**  CREATE INDEX splits_tx_guid_index ON splits(tx_guid);
**  CREATE INDEX splits_account_guid_index ON splits(account_guid);
**
**  sqlite> select * from accounts;
**  guid
**  822a857c5f484affa5a6a3e62f4b700f|Checking Account|BANK|10b24d11b4b94b8789d1830da2695bbb|100|0|b61b07c024fc463489f5db031135a29e||Checking Account|0|0
**  d934f2e5606c4da6b25c703c4661d747|Opening Balances|EQUITY|10b24d11b4b94b8789d1830da2695bbb|100|0|745365afce5946b19d4189c593b9f6aa||Opening Balances|0|0
**  sqlite> select * from transactions;
**  guid
**  4b2259ef3fbb486bad1b42f28ec84346|10b24d11b4b94b8789d1830da2695bbb||2023-05-28 10:59:00|2023-05-28 21:46:09|
**  sqlite> select * from splits;
**  guid                             tx_guid                          account_guid
**  c68c279c3ef64d00ae682f5573bb55bc|4b2259ef3fbb486bad1b42f28ec84346|822a857c5f484affa5a6a3e62f4b700f|||n|1970-01-01 00:00:00|100|100|100|100|
**  a67a975bc58a4fa1bd00421b37fed115|4b2259ef3fbb486bad1b42f28ec84346|d934f2e5606c4da6b25c703c4661d747|||n|1970-01-01 00:00:00|-100|100|-100|100|
**
** \endcode
**
*/
class Item
: public GCW::Dbo::BaseItem< Item >
{
  public:

    /*!
    ** Split GUID
    */
    auto guid() const-> const std::string & { return m_guid; }

    /*!
    ** Transaction GUID
    */
    auto tx_guid() const-> const std::string & { return m_tx_guid; }

    /*!
    ** Account GUID
    */
    auto account_guid() const-> const std::string & { return m_account_guid; }

    /*!
    ** Memo field
    */
    auto memo() const-> const std::string & { return m_memo; }

    /*!
    ** Action field
    */
    auto action() const-> const std::string & { return m_action; }

    /*!
    ** Reconcile State field
    */
    auto reconcile_state() const-> const std::string & { return m_reconcile_state; }

    /*!
    ** Reconcile Date field
    */
    auto reconcile_date() const-> const std::string & { return m_reconcile_date; }

    /*!
    ** Value Number field
    */
    auto value_num() const-> int { return m_value_num; }

    /*!
    ** Value Denominator field
    */
    auto value_denom() const-> int { return m_value_denom; }

    /*!
    ** Quantity Number field
    */
    auto quantity_num() const-> int { return m_quantity_num; }

    /*!
    ** Quantity Denominator field
    */
    auto quantity_denom() const-> int { return m_quantity_denom; }

    /*!
    ** Lot GUID field
    */
    auto lot_guid() const-> const std::string & { return m_lot_guid; }

    /*!
    ** \brief Return 'value' as a decimal.h number.
    **
    ** This converts the stored number in to a proper decimal<>
    **  number type.  It can then be used in regular accounting
    **  calculations.  The inversion flag can be used to 'reset'
    **  the sign of the value for the purpose of displaying
    **  (otherwise negative) numbers with positive values only.
    */
    GCW_NUMERIC value( bool invert = false ) const
    {
      auto inv = invert? -1:1;
      GCW_NUMERIC retVal( value_num()*inv );
      retVal /= value_denom();
      return retVal;
    }

    /*!
    ** \brief Test for Negative
    **
    ** This returns 'true' if the number is considered less
    **  than zero.
    */
    bool valueIsNegative() const
    {
      return value() < 0;
    }

    /*!
    ** \brief Return Value as a formatted String
    **
    ** This uses the decimal.h library to format the number
    **  as a std::string.
    **
    ** \sa GCW::Cfg::decimal_format()
    **
    */
    std::string valueAsString( bool negate = false ) const
    {
      return toString( value(negate), GCW::Cfg::decimal_format() );
    }

    /*!
    ** \brief Return 'quantity' as a decimal.h number.
    **
    ** This converts the stored number in to a proper decimal<>
    **  number type.  It can then be used in regular accounting
    **  calculations.
    */
    GCW_NUMERIC quantity() const
    {
      GCW_NUMERIC retVal( quantity_num() );
      retVal /= quantity_denom();
      return retVal;
    }

    std::string quantityAsString() const
    {
      return toString( quantity(), GCW::Cfg::decimal_format() );
    }

    bool quantityIsNegative() const
    {
      return quantity() < 0;
    }

    template< class Action > void persist( Action & action )
    {
      Wt::Dbo::id   ( action, m_guid            , "guid"            ,   32 ); // text(32) PRIMARY KEY NOT NULL,
      Wt::Dbo::field( action, m_tx_guid         , "tx_guid"         ,   32 ); // text(32) NOT NULL,
      Wt::Dbo::field( action, m_account_guid    , "account_guid"    ,   32 ); // text(32) NOT NULL,
      Wt::Dbo::field( action, m_memo            , "memo"            , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_action          , "action"          , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_reconcile_state , "reconcile_state" ,    1 ); // text(1) NOT NULL,
      Wt::Dbo::field( action, m_reconcile_date  , "reconcile_date"  ,   19 ); // text(19),
      Wt::Dbo::field( action, m_value_num       , "value_num"              ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_value_denom     , "value_denom"            ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_quantity_num    , "quantity_num"           ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_quantity_denom  , "quantity_denom"         ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_lot_guid        , "lot_guid"        ,   32 ); // text(32)

    } // endtemplate< class Action > void persist( Action & action )

  private:

    std::string m_guid            ; // text(32) PRIMARY KEY NOT NULL,
    std::string m_tx_guid         ; // text(32) NOT NULL,
    std::string m_account_guid    ; // text(32) NOT NULL,
    std::string m_memo            ; // text(2048) NOT NULL,
    std::string m_action          ; // text(2048) NOT NULL,
    std::string m_reconcile_state ; // text(1) NOT NULL,
    std::string m_reconcile_date  ; // text(19),
    int         m_value_num       ; // bigint NOT NULL,
    int         m_value_denom     ; // bigint NOT NULL,
    int         m_quantity_num    ; // bigint NOT NULL,
    int         m_quantity_denom  ; // bigint NOT NULL,
    std::string m_lot_guid        ; // text(32)

}; // endclass Item

extern const char * s_tableName;

/*!
** \brief Load a single split
**
** This function returns a split based on the GUID.
**
*/
Item::Ptr load( const std::string & _splitGuid );

/*!
** \brief Load Splits by Account
**
** This function returns a vector of Split items, sorted
**  by transaction date.  The result includes ~all~ splits
**  associated with a single account.
**
** \return Vector of Items sorted by Transction Date
*/
Item::Vector byAccount
(
 /** Account GUID */
 const std::string & _accountGuid
);

/*!
** \brief Load Splits by Split
**
** This function returns a vector of Split items, sorted
**  by transaction date.  The result includes ~all~ splits
**  associated with a transaction except for the split
**  ID used to identify the transaction.  This function
**  acts as a convenience function for a split to quickly
**  identify all of the 'other' splits.
**
** \return Vector of Items sorted by Transction Date
*/
Item::Vector bySplit
(
 /** Split GUID */
 const std::string & _splitGuid
);

/*!
** \brief Load Splits by Transaction
**
** This function returns a vector of Split items, sorted
**  by transaction date.  The result includes ~all~ splits
**  associated with a transaction
**
** \return Vector of Items sorted by Transction Date
*/
Item::Vector byTransaction
(
 /** Transaction GUID */
 const std::string & _txGuid
);

    } // endnamespace Splits {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __SPLITS_H___

