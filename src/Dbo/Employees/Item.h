#line 2 "src/Dbo/Employees/Item.h"

#ifndef __DBO_EMPLOYEES_ITEM_H___
#define __DBO_EMPLOYEES_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the Account class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Employees {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Employees::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Employees::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Employees::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Employees {

/*!
** \brief Employee Item Class
**
** This class represents an 'employee' within gnucash.  This is a Dbo object
**  so this class is used as the interface between the gnucashew application
**  and the back-end database.
**
** \dot
** digraph EmployeeMap
** {
**   EmployeesItem;
** }
** \enddot
**
** \par Native GnuCash Employee Sqlite Schema
** \code
**   CREATE TABLE employees
**   (
**    guid           text(32) PRIMARY KEY NOT NULL,
**    username       text(2048) NOT NULL,
**    id             text(2048) NOT NULL,
**    language       text(2048) NOT NULL,
**    acl            text(2048) NOT NULL,
**    active         integer NOT NULL,
**    currency       text(32) NOT NULL,
**    ccard_guid     text(32),
**    workday_num    bigint NOT NULL,
**    workday_denom  bigint NOT NULL,
**    rate_num       bigint NOT NULL,
**    rate_denom     bigint NOT NULL,
**    addr_name      text(1024),
**    addr_addr1     text(1024),
**    addr_addr2     text(1024),
**    addr_addr3     text(1024),
**    addr_addr4     text(1024),
**    addr_phone     text(128),
**    addr_fax       text(128),
**    addr_email     text(256)
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
    ** \brief persist the data
    **
    ** This connects this object to the back-end database.
    */
    template< class Action > void persist( Action & action )
    {
      Wt::Dbo::id   ( action, m_guid            , GCW::Dbo::Employees::Field::guid           ,   32 ); // text(32) PRIMARY KEY NOT NULL,
      Wt::Dbo::field( action, m_username        , GCW::Dbo::Employees::Field::username       , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_id              , GCW::Dbo::Employees::Field::id             , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_language        , GCW::Dbo::Employees::Field::language       , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_acl             , GCW::Dbo::Employees::Field::acl            , 2048 ); // text(2048) NOT NULL,
      Wt::Dbo::field( action, m_active          , GCW::Dbo::Employees::Field::active                ); // integer NOT NULL,
      Wt::Dbo::field( action, m_currency        , GCW::Dbo::Employees::Field::currency       ,   32 ); // text(32) NOT NULL,
      Wt::Dbo::field( action, m_ccard_guid      , GCW::Dbo::Employees::Field::ccard_guid     ,   32 ); // text(32),
      Wt::Dbo::field( action, m_workday_num     , GCW::Dbo::Employees::Field::workday_num           ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_workday_denom   , GCW::Dbo::Employees::Field::workday_denom         ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_rate_num        , GCW::Dbo::Employees::Field::rate_num              ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_rate_denom      , GCW::Dbo::Employees::Field::rate_denom            ); // bigint NOT NULL,
      Wt::Dbo::field( action, m_addr_name       , GCW::Dbo::Employees::Field::addr_name      , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_addr1      , GCW::Dbo::Employees::Field::addr_addr1     , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_addr2      , GCW::Dbo::Employees::Field::addr_addr2     , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_addr3      , GCW::Dbo::Employees::Field::addr_addr3     , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_addr4      , GCW::Dbo::Employees::Field::addr_addr4     , 1024 ); // text(1024),
      Wt::Dbo::field( action, m_addr_phone      , GCW::Dbo::Employees::Field::addr_phone     ,  128 ); // text(128),
      Wt::Dbo::field( action, m_addr_fax        , GCW::Dbo::Employees::Field::addr_fax       ,  128 ); // text(128),
      Wt::Dbo::field( action, m_addr_email      , GCW::Dbo::Employees::Field::addr_email     ,  256 ); // text(256)

    }

  private:

    std::string m_guid            ; // text(32) PRIMARY KEY NOT NULL,
    std::string m_username        ; // text(2048) NOT NULL,
    std::string m_id              ; // text(2048) NOT NULL,
    std::string m_language        ; // text(2048) NOT NULL,
    std::string m_acl             ; // text(2048) NOT NULL,
    int         m_active          ; // integer NOT NULL,
    std::string m_currency        ; // text(32) NOT NULL,
    std::string m_ccard_guid      ; // text(32),
    int         m_workday_num     ; // bigint NOT NULL,
    int         m_workday_denom   ; // bigint NOT NULL,
    int         m_rate_num        ; // bigint NOT NULL,
    int         m_rate_denom      ; // bigint NOT NULL,
    std::string m_addr_name       ; // text(1024),
    std::string m_addr_addr1      ; // text(1024),
    std::string m_addr_addr2      ; // text(1024),
    std::string m_addr_addr3      ; // text(1024),
    std::string m_addr_addr4      ; // text(1024),
    std::string m_addr_phone      ; // text(128),
    std::string m_addr_fax        ; // text(128),
    std::string m_addr_email      ; // text(256)

}; // endclass Item

    } // endnamespace Employees {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __EMPLOYEES_H___

