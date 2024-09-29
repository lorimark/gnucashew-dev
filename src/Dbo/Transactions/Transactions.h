#line 2 "src/Dbo/Transactions.h"

#ifndef __DBO_TRANSACTIONS_H___
#define __DBO_TRANSACTIONS_H___

#include <Wt/Dbo/Dbo.h>
#include <Wt/WDate.h>
#include <Wt/WDateTime.h>

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

    const std::string & guid          () const { return m_guid          ; }
    const std::string & currency_guid () const { return m_currency_guid ; }
    const std::string & num           () const { return m_num           ; }
    const std::string & post_date     () const { return m_post_date     ; }
    const std::string & enter_date    () const { return m_enter_date    ; }
    const std::string & description   () const { return m_description   ; }

    std::string post_date( const std::string & _format ) const
    {
      auto d = Wt::WDateTime::fromString( post_date(), "yyyy-MM-dd hh:mm:ss" );
      return d.toString( _format ).toUTF8();
    }

    /*!
    ** \brief Date as Date :)
    **
    ** This will take the stored string-date of the transaction and covert it to
    **  a system WDate value.
    **
    */
    Wt::WDate post_date_as_date() const
    {
      auto d = Wt::WDateTime::fromString( post_date(), "yyyy-MM-dd hh:mm:ss" );
      return d.date();
    }

    void set_post_date( const Wt::WDate & _value );

    template< class Action > void persist( Action & action )
    {
      Wt::Dbo::id   ( action, m_guid           , "guid"           ,   32 ); // text(32) PRIMARY KEY NOT NULL,
      Wt::Dbo::field( action, m_currency_guid  , "currency_guid"  ,   32 ); // text(32) NOT NULL,
      Wt::Dbo::field( action, m_num            , "num"            , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_post_date      , "post_date"      ,   19 ); // text(19),
      Wt::Dbo::field( action, m_enter_date     , "enter_date"     ,   19 ); // text(19),
      Wt::Dbo::field( action, m_description    , "description"    , 2048 ); // text(2048)
    }

    std::string m_guid           ;
    std::string m_currency_guid  ;
    std::string m_num            ;
    std::string m_post_date      ;
    std::string m_enter_date     ;
    std::string m_description    ;

}; // endclass Item

extern const char * s_tableName;

/*!
** \brief Load Transaction by Guid
**
*/
Item::Ptr load( const std::string & _txGuid );
Item::Ptr byGuid( const std::string & _txGuid );
Item::Vector byAccount( const std::string & _accountGuid );

    } // endnamespace Transactions {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __TRANSACTIONS_H___


