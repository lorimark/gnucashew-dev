#line 2 "src/Dbo/Accounts/Accounts.h"

#ifndef __DBO_ACCOUNTS_H___
#define __DBO_ACCOUNTS_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Accounts {

/*!
** \brief Load Root Account
**
*/
auto rootAccount()-> Item::Ptr ;

/*!
** \brief Load Account by GUID
*/
auto load( const std::string & _guid )-> Item::Ptr ;

/*!
** \brief Load Account by GUID
*/
auto byGuid( const std::string & _guid )-> Item::Ptr ;

/*!
** \brief Load Account by 'child name' and 'parent id'
*/
auto byChildName( const std::string & _parentGuid, const std::string & _childName )-> Item::Ptr ;

/*!
** \brief Load Account by 'full name' with ':' account separator
*/
auto byFullName( const std::string & _fullName )-> Item::Ptr ;
auto byFullName( const char * _fullName )-> Item::Ptr ;
auto byFullName( const Wt::WString & _fullName )-> Item::Ptr ;

/*!
** \brief Load all accounts
*/
auto allAccounts()-> Item::Vector ;

/*!
** \brief Load accounts as; if( !hidden() && !placeHolder() )
*/
auto activeAccounts()-> Item::Vector ;

/*!
** \brief Account Fullname via GUID
*/
auto fullName( const std::string & _guid )-> std::string ;

/*!
** \brief Account Fullname via Item
*/
auto fullName( Item::Ptr _item )-> std::string ;

/*!
** \brief Is Account Type
**
** This returns .true. if the account is an _type account,
**  meaning, if the acccount itself is not designated as an
**  _type (could be BANK or CASH or something), then the
**  parent tree is walked all the way to root and returns
**  .true. if any of the parent accounts are an _type account.
*/

auto isType( const Item::Ptr _acctItem, GCW::Dbo::Accounts::Type _type )-> bool ;
auto isType( const std::string & _guid, GCW::Dbo::Accounts::Type _type )-> bool ;

/*!
** \brief Account Children Namespace
*/
namespace Children {

/*!
** \brief Child Accounts via parent
**
*/
auto byParent( const std::string & _parentGuid )-> Item::Vector;

      } // Children
    } // Accounts
  } // Dbo
} // GCW



#endif // __DBO_ACCOUNTS_H___


