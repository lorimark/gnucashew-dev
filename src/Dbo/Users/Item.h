#line 2 "src/Dbo/Users/Item.h"

#ifndef __DBO_USERS_ITEM_H___
#define __DBO_USERS_ITEM_H___

#include "../BaseItem.h"
#include "Definition.h"

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Dbo {
    namespace Users {

/*!
** \brief User Item Class
**
** This class represents an 'user' within gnucashew.  This object provides a
**  binding between the authentication services and the gnucash system 'Employee'
**  items.  GnuCash supports 'employees' and GnuCashew supports 'authenticated users'.
**  An Authenticated User is also an Employee, but an Employee is not necessarily
**  an authenticated user.
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
    ** \brief persist the data
    **
    ** This connects this object to the back-end database.
    */
    template< class Action > void persist( Action & action )
    {
      Wt::Dbo::field( action, m_employee_guid    , GCW::Dbo::Users::Field::name             , 2048 ); // text(2048) NOT NULL
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

