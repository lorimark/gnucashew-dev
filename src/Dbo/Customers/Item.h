#line 2 "src/Dbo/Customers/Item.h"

#ifndef __DBO_CUSTOMERS_ITEM_H___
#define __DBO_CUSTOMERS_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the Account class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Customers {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Customers::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static IdType invalidId() { return std::string(); }
  static const char * surrogateIdField() { return nullptr; }
  static const char * versionField()     { return nullptr; }
};

template<>
  struct Wt::Dbo::dbo_traits< const GCW::Dbo::Customers::Item >
       : Wt::Dbo::dbo_traits< GCW::Dbo::Customers::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Customers {

/*!
** \brief Customer Item Class
**
** This class represents an 'customer' within gnucash.  This is a Dbo object
**  so this class is used as the interface between the gnucashew application
**  and the back-end database.
**
** \par Native GnuCash Account Sqlite Schema
** \code
**  CREATE TABLE customers
**  (
**   guid text(32) PRIMARY KEY NOT NULL,
**   name text(2048) NOT NULL,
**   id text(2048) NOT NULL,
**   notes text(2048) NOT NULL,
**   active integer NOT NULL,
**   discount_num bigint NOT NULL,
**   discount_denom bigint NOT NULL,
**   credit_num bigint NOT NULL,
**   credit_denom bigint NOT NULL,
**   currency text(32) NOT NULL,
**   tax_override integer NOT NULL,
**   addr_name text(1024),
**   addr_addr1 text(1024),
**   addr_addr2 text(1024),
**   addr_addr3 text(1024),
**   addr_addr4 text(1024),
**   addr_phone text(128),
**   addr_fax text(128),
**   addr_email text(256),
**   shipaddr_name text(1024),
**   shipaddr_addr1 text(1024),
**   shipaddr_addr2 text(1024),
**   shipaddr_addr3 text(1024),
**   shipaddr_addr4 text(1024),
**   shipaddr_phone text(128),
**   shipaddr_fax text(128),
**   shipaddr_email text(256),
**   terms text(32),
**   tax_included integer,
**   taxtable text(32)
**  );
**
**   sqlite> select * from customers;
**   f7bc3a5dec934b30bfa185060838a256|BishBash CPA|BBS||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0|Dick C. Cavett CPA PC|Sheffield Road, #720|Deluth, TX 22313-8178|||442-344-1886||jim@holocow.com||||||||||3|
**   3168628916994bf985b1477c3635ed4f|Flourtems|FTM||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0|Flourtems Fine Services|f442 Sadly Trail|Suite 123|Point, TX  42233||535-233-2477||femoins@ffs.com||||||||||3|
**   6f61a67518544d5bad98b571324a0ad3|Kid Bright|KFP||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0|Kid Bright Pediatrics|1234 Lavon Hollow|Suite #13|Brunch, TX  32345||972-233-4463|223-440-2442|mary@fbp.com||||||||||3|
**   cb894898e1654cd1a074c047a9c10fb3|BYOB|BYB||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0|BYOB Distribution|1230 Francis Drive|Suite 2220|Alabama, TX  22334||442-785-0083||hank@justsayno.co||||||||||3|
**   e640931e57854e60ad100b55d7492e27|Pishaww Colifloury|PCU||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0|Pichschaw Ancilary|3224 North 55th Street|Suite 123|Frankfruit, TX  22141||777-332-3567|332-322-6698|bilbowbagins@flouride.com||||||||||3|
**   b16870d305cd43d0b75aca0363fc5b0a|Ping Pong Botch|PPB||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0|Yes to Everything|1122 East Campgranada Road|Suite 220|Anklebracelette, Texas  75281||522-344-3500|234-332-3232|info@yesyesyes.com||||||||||3|
**   1dfb5117a9564046b833e6544df6ed22|Test|TST||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0||||||||||||||||||3|
**   d246b19706cb43df8e3b4cad1b78142a|Transfiber|TFT||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0|Telezokim Flampourneet|523 N. Ankle Street|Suite #3722|Alabony, TX  75211||224-344-0222|244-322-4442|gbckkd@hispster.com||||||||||3|
**   74031f41723a414e8f43ba1b36bf711d|Bring Broth Better|BBB||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0|Brunch Partners Recruiting|||||224-444-4211||heberewt@ddalzatraz.com||||||||||3|
**   a4279e038684453a848dab6efbb87d38|Ten Nine Eight|TNE||1|0|1|0|1|3d1e5462691a4289baec562fa9c26cfd|0|Ten Eight Nine|1235 Capitalone Hollow|Suite 125|Carrolzby, TN 22331||922-333-9177||cccounting@teneightyeleven.com|||||||||83bb345e87544d3e9c6b501881edd8fc|3|
**   sqlite>
** \endcode
**
*/
class Item
: public GCW::Dbo::BaseItem< Item >
{
  public:

    const std::string & guid           () const { return m_guid           ; }
    const std::string & name           () const { return m_name           ; }
    const std::string & id             () const { return m_id             ; }

    template< class Action > void persist( Action & action )
    {
      Wt::Dbo::id   ( action, m_guid           , GCW::Dbo::Customers::Field::guid            ,   32 ); // text(32) PRIMARY KEY NOT NULL
      Wt::Dbo::field( action, m_name           , GCW::Dbo::Customers::Field::name            , 2048 ); // text(2048) NOT NULL
      Wt::Dbo::field( action, m_id             , GCW::Dbo::Customers::Field::id              , 2048 ); // text(2048) NOT NULL
      Wt::Dbo::field( action, m_notes          , GCW::Dbo::Customers::Field::notes           , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_active         , GCW::Dbo::Customers::Field::active                 ); // integer NOT NULL,
      Wt::Dbo::field( action, m_discount_num   , GCW::Dbo::Customers::Field::discount_num           ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_discount_denom , GCW::Dbo::Customers::Field::discount_denom         ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_credit_num     , GCW::Dbo::Customers::Field::credit_num             ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_credit_denom   , GCW::Dbo::Customers::Field::credit_denom           ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_currency       , GCW::Dbo::Customers::Field::currency        ,   32 ); // text(32) NOT NULL,
      Wt::Dbo::field( action, m_tax_override   , GCW::Dbo::Customers::Field::tax_override           ); // integer NOT NULL,
      Wt::Dbo::field( action, m_addr_name      , GCW::Dbo::Customers::Field::addr_name       , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_addr1     , GCW::Dbo::Customers::Field::addr_addr1      , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_addr2     , GCW::Dbo::Customers::Field::addr_addr2      , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_addr3     , GCW::Dbo::Customers::Field::addr_addr3      , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_addr4     , GCW::Dbo::Customers::Field::addr_addr4      , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_phone     , GCW::Dbo::Customers::Field::addr_phone      ,  128 ); // text(128),
      Wt::Dbo::field( action, m_addr_fax       , GCW::Dbo::Customers::Field::addr_fax        ,  128 ); // text(128),
      Wt::Dbo::field( action, m_addr_email     , GCW::Dbo::Customers::Field::addr_email      ,  256 ); // text(256),
      Wt::Dbo::field( action, m_shipaddr_name  , GCW::Dbo::Customers::Field::shipaddr_name   , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_shipaddr_addr1 , GCW::Dbo::Customers::Field::shipaddr_addr1  , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_shipaddr_addr2 , GCW::Dbo::Customers::Field::shipaddr_addr2  , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_shipaddr_addr3 , GCW::Dbo::Customers::Field::shipaddr_addr3  , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_shipaddr_addr4 , GCW::Dbo::Customers::Field::shipaddr_addr4  , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_shipaddr_phone , GCW::Dbo::Customers::Field::shipaddr_phone  ,  128 ); // text(128),
      Wt::Dbo::field( action, m_shipaddr_fax   , GCW::Dbo::Customers::Field::shipaddr_fax    ,  128 ); // text(128),
      Wt::Dbo::field( action, m_shipaddr_email , GCW::Dbo::Customers::Field::shipaddr_email  ,  256 ); // text(256),
      Wt::Dbo::field( action, m_terms          , GCW::Dbo::Customers::Field::terms           ,   32 ); // text(32),
      Wt::Dbo::field( action, m_tax_included   , GCW::Dbo::Customers::Field::tax_included           ); // integer,
      Wt::Dbo::field( action, m_taxtable       , GCW::Dbo::Customers::Field::taxtable        ,   32 ); // text(32)

    } // endtemplate< class Action > void persist( Action & action )

  private:

    std::string m_guid           ;
    std::string m_name           ;
    std::string m_id             ;
    std::string m_notes          ; // text(2048) NOT NULL,
    int         m_active         ; // integer NOT NULL,
    int         m_discount_num   ; // bigint NOT NULL,
    int         m_discount_denom ; // bigint NOT NULL,
    int         m_credit_num     ; // bigint NOT NULL,
    int         m_credit_denom   ; // bigint NOT NULL,
    std::string m_currency       ; // text(32) NOT NULL,
    int         m_tax_override   ; // integer NOT NULL,
    std::string m_addr_name      ; // text(1024),
    std::string m_addr_addr1     ; // text(1024),
    std::string m_addr_addr2     ; // text(1024),
    std::string m_addr_addr3     ; // text(1024),
    std::string m_addr_addr4     ; // text(1024),
    std::string m_addr_phone     ; // text(128),
    std::string m_addr_fax       ; // text(128),
    std::string m_addr_email     ; // text(256),
    std::string m_shipaddr_name  ; // text(1024),
    std::string m_shipaddr_addr1 ; // text(1024),
    std::string m_shipaddr_addr2 ; // text(1024),
    std::string m_shipaddr_addr3 ; // text(1024),
    std::string m_shipaddr_addr4 ; // text(1024),
    std::string m_shipaddr_phone ; // text(128),
    std::string m_shipaddr_fax   ; // text(128),
    std::string m_shipaddr_email ; // text(256),
    std::string m_terms          ; // text(32),
    int         m_tax_included   ; // integer,
    std::string m_taxtable       ; // text(32)


}; // endclass Item

extern const char * s_tableName;

    } // endnamespace Customers {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // #ifndef __CUSTOMERS_H___


