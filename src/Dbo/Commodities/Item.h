#line 2 "src/Dbo/Commodities/Item.h"

#ifndef __DBO_COMMODITIES_ITEM_H___
#define __DBO_COMMODITIES_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the Account class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Commodities {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Commodities::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Commodities::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Commodities::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Commodities {

/*!
** \brief Commodity Item Class
**
** This class represents an 'commodity' within gnucash.  This is a Dbo object
**  so this class is used as the interface between the gnucashew application
**  and the back-end database.
**
** \dot
** digraph AccountMap
** {
**   CommodityItem;
** }
** \enddot
**
** \par Native GnuCash Commodity Sqlite Schema
** \code
**  CREATE TABLE commodities
**  (
**   guid           text(32) PRIMARY KEY NOT NULL,
**   namespace      text(2048) NOT NULL,
**   mnemonic       text(2048) NOT NULL,
**   fullname       text(2048),
**   cusip          text(2048),
**   fraction       integer NOT NULL,
**   quote_flag     integer NOT NULL,
**   quote_source   text(2048),
**   quote_tz       text(2048)
**  );
**  sqlite> select * from "commodities";
**  0824002aba074c8aa1326c6697649d65|CURRENCY|USD|US Dollar|840|100|1|currency|
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
    ** \brief ctor with guid.
    */
    Item( const std::string & _guid ): m_guid( _guid ){}

    /*!
    ** \brief GUID
    **
    ** Return account 'guid' value - the primary key for the account
    */
    auto guid() const-> const std::string & { return m_guid; }

    /*!
    ** \brief Name
    **
    ** Return account printable 'name' value
    */
    auto nameSpace() const-> const std::string & { return m_nameSpace; }

    /*!
    ** \brief persist the data
    **
    ** This connects this object to the back-end database.
    */
    template< class Action > void persist( Action & action )
    {
      Wt::Dbo::id   ( action, m_guid          , GCW::Dbo::Commodities::Field::guid         ,   32 ); // text(32) PRIMARY KEY NOT NULL
      Wt::Dbo::field( action, m_nameSpace     , GCW::Dbo::Commodities::Field::nameSpace    , 2048 ); // text(2048) NOT NULL
      Wt::Dbo::field( action, m_mnemonic      , GCW::Dbo::Commodities::Field::mnemonic     , 2048 ); // text(2048) NOT NULL
      Wt::Dbo::field( action, m_fullname      , GCW::Dbo::Commodities::Field::fullname     , 2048 ); // text(2048)
      Wt::Dbo::field( action, m_cusip         , GCW::Dbo::Commodities::Field::cusip        , 2048 ); // text(2048)
      Wt::Dbo::field( action, m_fraction      , GCW::Dbo::Commodities::Field::fraction            ); // integer NOT NULL
      Wt::Dbo::field( action, m_quote_flag    , GCW::Dbo::Commodities::Field::quote_flag          ); // integer NOT NULL
      Wt::Dbo::field( action, m_quote_source  , GCW::Dbo::Commodities::Field::quote_source , 2048 ); // text(2048)
      Wt::Dbo::field( action, m_quote_tz      , GCW::Dbo::Commodities::Field::quote_tz     , 2048 ); // text(2048)
    }

  private:

    std::string m_guid         ;
    std::string m_nameSpace    ;
    std::string m_mnemonic     ;
    std::string m_fullname     ;
    std::string m_cusip        ;
    int         m_fraction     ;
    int         m_quote_flag   ;
    std::string m_quote_source ;
    std::string m_quote_tz     ;

}; // endclass Item

    } // endnamespace Commodities {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __COMMODITIES_H___


