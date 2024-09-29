#line 2 "src/Dbo/Accounts/Item.h"

#ifndef __DBO_ACCOUNTS_ITEM_H___
#define __DBO_ACCOUNTS_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Predefine the Account class that fixin to come up.
**
*/
namespace GCW {
  namespace Dbo {
    namespace Accounts {
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
template<> struct Wt::Dbo::dbo_traits< GCW::Dbo::Accounts::Item >
: public Wt::Dbo::dbo_default_traits
{
  using IdType = std::string;
  static auto invalidId()-> IdType { return std::string(); }
  static auto surrogateIdField()-> const char * { return nullptr; }
  static auto versionField()-> const char * { return nullptr; }
};

template<> struct Wt::Dbo::dbo_traits< const GCW::Dbo::Accounts::Item > : Wt::Dbo::dbo_traits< GCW::Dbo::Accounts::Item > {};

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Accounts {

/*!
** \brief Account Item Class
**
** This class represents an 'account' within gnucash.  This is a Dbo object
**  so this class is used as the interface between the gnucashew application
**  and the back-end database.
**
** \dot
** digraph AccountMap
** {
**   AccountsItem;
** }
** \enddot
**
** \par Native GnuCash Account Sqlite Schema
** \code
**  CREATE TABLE accounts
**  (
**   guid           text(32) PRIMARY KEY NOT NULL,
**   name           text(2048) NOT NULL,
**   account_type   text(2048) NOT NULL,
**   commodity_guid text(32),
**   commodity_scu  integer NOT NULL,
**   non_std_scu    integer NOT NULL,
**   parent_guid    text(32),
**   code           text(2048),
**   description    text(2048),
**   hidden         integer,
**   placeholder    integer
**  );
**  sqlite> select * from accounts;
**  guid                             name             type  commodity                        scu nss parent                           code desc             h p
**  aa283385e0cf4f57b3360ca5a843bde5|Root Account    |ROOT |10b24d11b4b94b8789d1830da2695bbb|100|0  |                                |    |                |0|0
**  6e5313b77b4247039f0240ca79e4d871|Assets          |ASSET|10b24d11b4b94b8789d1830da2695bbb|100|0  |aa283385e0cf4f57b3360ca5a843bde5|    |Assets          |0|1
**  b61b07c024fc463489f5db031135a29e|Current Assets  |ASSET|10b24d11b4b94b8789d1830da2695bbb|100|0  |6e5313b77b4247039f0240ca79e4d871|    |Current Assets  |0|1
**  822a857c5f484affa5a6a3e62f4b700f|Checking Account|BANK |10b24d11b4b94b8789d1830da2695bbb|100|0  |b61b07c024fc463489f5db031135a29e|    |Checking Account|0|0
**  9e851f524a6a44ef8c93a6b52b004cae|Savings Account |BANK |10b24d11b4b94b8789d1830da2695bbb|100|0  |b61b07c024fc463489f5db031135a29e|    |Savings Account |0|0
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
    ** \brief Account Definition
    **
    ** Return the definition object for the account.
    */
    auto accountDef() const-> const GCW::Dbo::Accounts::AccountDef_t &;

    /*!
    ** \brief Account Debit/Credit
    **
    ** Return the account Debit/Credit type.
    */
    auto accountDrCr() const-> GCW::Dbo::Accounts::DrCr;

    /*!
    ** \brief Account Type
    **
    ** Return the account Type as an enum.
    */
    auto accountType() const-> GCW::Dbo::Accounts::Type;

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
    auto name() const-> const std::string & { return m_name; }

    /*!
    ** \brief Type Name
    **
    ** Return account type as a 'string' value.  This is, in fact, how the account
    **  type is actually recorded in the back-end database, as a 'text' string such
    **  as 'BANK', 'CASH', 'INCOME' and so forth.  GnuCashew takes this text value
    **  and uses that to switch to the GCW::Dbo::Accounts::Type account type enum.
    **
    ** \ref Item::accountType()
    */
    auto accountTypeName() const-> const std::string & { return m_account_typeName; }

    /*!
    ** \brief Commodity GUID
    **
    **
    */
    auto commodity_guid() const-> const std::string & { return m_commodity_guid; }

    /*!
    ** \brief Commodity SCU (Special Currency Unit)
    **
    ** Currency Unit is usually 1/100.  This field allows it to be changed.  If this value
    **  is non-standard, the Item::non_std_scu() will return true.
    **
    */
    auto commodity_scu() const-> const int { return m_commodity_scu; }

    /*!
    ** \brief Non Standard SCU (Special Currency Unit)
    **
    ** If the Item::commodity_scu() is non-standard, this returns true
    **
    */
    auto non_std_scu() const-> const int { return m_non_std_scu; }

    /*!
    ** \brief Parent GUID
    **
    ** Link to a parent account.
    **
    ** \note All accounts 'require' a parent account link, with the exception
    **        of the internal 'root' account.
    */
    auto parent_guid() const-> const std::string & { return m_parent_guid      ; }

    /*!
    ** \brief Code
    **
    ** Use this to carry the 'account number' or other code related to the account
    */
    auto code() const-> const std::string & { return m_code; }

    /*!
    ** \brief Description
    **
    */
    auto description() const-> const std::string & { return m_description; }

    /*!
    ** \brief Hidden
    **
    ** 'true' causes this account to not appear in a lot of the lists and things
    */
    auto hidden() const-> const int { return m_hidden; }

    /*!
    ** \brief Placeholder
    **
    ** 'true' causes this account to not allow transactions to be posted in to
    */
    auto placeHolder() const-> const int { return m_placeHolder; }

    /*!
    ** \brief Full Name
    **
    ** Return the 'full name representation' of the account.  This includes all
    **  parent accounts, using the ':' separator.
    **
    ** \par Example
    ** \code
    **    Assets:Current Assets:Checking Account
    ** \endcode
    **
    */
    auto fullName() const-> std::string;

    /*!
    ** \brief Has Color
    **
    ** Returns 'true' if this account has a color assigned to it.
    */
    auto hasColor() const-> bool;

    /*!
    ** \brief Color
    **
    ** Return the color as a string-value.
    */
    auto color() const-> std::string;

    /*!
    ** \brief persist the data
    **
    ** This connects this object to the back-end database.
    */
    template< class Action > void persist( Action & action )
    {
      Wt::Dbo::id   ( action, m_guid             , GCW::Dbo::Accounts::Field::guid             ,   32 ); // text(32) PRIMARY KEY NOT NULL
      Wt::Dbo::field( action, m_name             , GCW::Dbo::Accounts::Field::name             , 2048 ); // text(2048) NOT NULL
      Wt::Dbo::field( action, m_account_typeName , GCW::Dbo::Accounts::Field::account_typeName , 2048 ); // text(2048) NOT NULL
      Wt::Dbo::field( action, m_commodity_guid   , GCW::Dbo::Accounts::Field::commodity_guid   ,   32 ); // text(32)
      Wt::Dbo::field( action, m_commodity_scu    , GCW::Dbo::Accounts::Field::commodity_scu           ); // integer NOT NULL
      Wt::Dbo::field( action, m_non_std_scu      , GCW::Dbo::Accounts::Field::non_std_scu             ); // integer NOT NULL
      Wt::Dbo::field( action, m_parent_guid      , GCW::Dbo::Accounts::Field::parent_guid      ,   32 ); // text(32)
      Wt::Dbo::field( action, m_code             , GCW::Dbo::Accounts::Field::code             , 2048 ); // text(2048)
      Wt::Dbo::field( action, m_description      , GCW::Dbo::Accounts::Field::description      , 2048 ); // text(2048)
      Wt::Dbo::field( action, m_hidden           , GCW::Dbo::Accounts::Field::hidden                  ); // integer
      Wt::Dbo::field( action, m_placeHolder      , GCW::Dbo::Accounts::Field::placeHolder             ); // integer
    }

  private:

    std::string m_guid             ;
    std::string m_name             ;
    std::string m_account_typeName ;
    std::string m_commodity_guid   ;
    int         m_commodity_scu    ;
    int         m_non_std_scu      ;
    std::string m_parent_guid      ;
    std::string m_code             ;
    std::string m_description      ;
    int         m_hidden           ;
    int         m_placeHolder      ;

}; // endclass Item

    } // endnamespace Accounts {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __ACCOUNTS_H___

