#line 2 "src/Dbo/Transactions.h"

#ifndef __DBO_TRANSACTIONS_H___
#define __DBO_TRANSACTIONS_H___

#include <Wt/Dbo/Dbo.h>
#include <Wt/WDate.h>
#include <Wt/WDateTime.h>

#include "../../Glb/gcwglobal.h"
#include "../Splits/Splits.h"

/*
** Predefine the Account class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Transactions {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Transactions::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static IdType invalidId() { return std::string(); }
  static const char * surrogateIdField() { return nullptr; }
  static const char * versionField()     { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Transactions::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Transactions::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Transactions {

extern const char * s_tableName;

/*!
** \brief Transaction Item
**
**
** \code
**  CREATE TABLE transactions
**  (
**   guid text(32) PRIMARY KEY NOT NULL,
**   currency_guid text(32) NOT NULL,
**   num text(2048) NOT NULL,
**   post_date text(19),
**   enter_date text(19),
**   description text(2048)
**  );
**  CREATE INDEX tx_post_date_index ON transactions(post_date);
**   sqlite> select * from transactions;
**   4b2259ef3fbb486bad1b42f28ec84346|10b24d11b4b94b8789d1830da2695bbb||2023-05-28 10:59:00|2023-05-28 21:46:09|transaction memo
**   8e841d9c97914cd5a5bd47062e7c91e3|10b24d11b4b94b8789d1830da2695bbb||2023-07-04 10:59:00|2023-07-05 16:19:43|2nd transaction
** \endcode
**
*/
class Item
: public Wt::Dbo::Dbo< Item >
{
  public:

    using Ptr = Wt::Dbo::ptr< Item >;
    using Collection = Wt::Dbo::collection< Ptr >;
    using Vector = std::vector< Ptr >;

    Item() {};
    Item( const std::string & _txGuid ) { m_guid = _txGuid; }

    auto guid              () const-> const std::string & { return m_guid          ; }
    auto currency_guid     () const-> const std::string & { return m_currency_guid ; }
    auto num               () const-> const std::string & { return m_num           ; }
    auto post_date         () const-> const std::string & { return m_post_date     ; }
    auto enter_date        () const-> const std::string & { return m_enter_date    ; }
    auto description       () const-> const std::string & { return m_description   ; }

    auto set_currency_guid ( const std::string & _guid )-> void
    {
      m_currency_guid = _guid;
    }

    auto set_enter_date ( const Wt::WDate     & _value )-> void;
    auto set_enter_date ( const Wt::WDateTime & _value )-> void;
    auto set_num        ( const std::string   & _value )-> void;

    /*!
    ** \brief Post Date as String
    **
    ** This pulls the post-date from the back-end and formats it with
    **  the requested format.  This is used for screen-representations
    **  of the date.
    **
    */
    auto post_date_as_string( const std::string & _format ) const-> std::string
    {
      auto d = Wt::WDateTime::fromString( post_date(), GCW_DATETIME_FORMAT_STORAGE );
      return d.toString( _format ).toUTF8();
    }

    /*!
    ** \brief Date as WDate
    **
    ** This will take the stored string-date of the transaction and covert it to
    **  a system WDateTime value.
    **
    */
    auto post_date_as_date() const-> Wt::WDateTime
    {
      return
        Wt::WDateTime::fromString( post_date(), GCW_DATETIME_FORMAT_STORAGE );
    }

    auto set_post_date( const Wt::WDate & _value )-> void ;
    auto set_post_date( const Wt::WDateTime & _value )-> void ;

    auto set_description( const std::string & _value )-> void ;

    template< class Action > void persist( Action & action )
    {
      Wt::Dbo::id   ( action, m_guid           , "guid"           ,   32 ); // text(32) PRIMARY KEY NOT NULL,
      Wt::Dbo::field( action, m_currency_guid  , "currency_guid"  ,   32 ); // text(32) NOT NULL,
      Wt::Dbo::field( action, m_num            , "num"            , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_post_date      , "post_date"      ,   19 ); // text(19),
      Wt::Dbo::field( action, m_enter_date     , "enter_date"     ,   19 ); // text(19),
      Wt::Dbo::field( action, m_description    , "description"    , 2048 ); // text(2048)
    }

  private:

    auto set_enter_date ( const std::string & _value )-> void ;
    auto set_post_date( const std::string & _value )-> void ;

    std::string m_guid           ;
    std::string m_currency_guid  ;
    std::string m_num            ;
    std::string m_post_date      ;
    std::string m_enter_date     ;
    std::string m_description    ;

}; // endclass Item

/*!
** \brief Load Transaction by Guid
**
*/
auto load( const std::string & _txGuid )-> Item::Ptr ;

/*!
** \brief Load Transaction by Guid
**
*/
auto byGuid( const std::string & _txGuid )-> Item::Ptr ;

/*!
** \brief Add Transaction with Guid
**
*/
auto add( const std::string & _txGuid )-> Item::Ptr ;

/*!
** \brief Load Transactions for Account Guid
**
*/
auto byAccount( const std::string & _accountGuid )-> Item::Vector ;

/*
** \brief Load Transaction for Account Guid and Month
**
*/
auto byAccountMonth( const std::string & _accountGuid, int _month )-> Item::Vector ;

/*!
** \brief Load Transactions for 'num' and Month
**
** The 'num' column is the column immediately to the right of the
**  date field.  This query is used to find all the transactions
**  that have this value in the 'num' field for a particular month.
**
*/
auto byNumMonth( const std::string & _num, int _month )-> Item::Vector ;

    } // endnamespace Transactions {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __TRANSACTIONS_H___


