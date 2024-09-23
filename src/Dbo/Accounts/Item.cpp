#line 2 "src/Dbo/Accounts/Item.cpp"

#include <gnucash/gnc-session.h>
#include <gnucash/Account.h>

#include "../App.h"
#include "../Glb/Core.h"
#include "../Transactions/Transactions.h"
#include "../Slots/Slots.h"
#include "Definition.h"

namespace {

/*!
** \brief Accounts Sorter
**
**
*/
auto sort( GCW::Dbo::Accounts::Item::Vector & _accountItems )-> void
{
  /*!
  ** Sort the vector of accounts by fullname so that they can be loaded
  **  in to the model in proper sequential order.
  **
  */
  std::sort
  (
   _accountItems.begin(),
   _accountItems.end(),
   []( const GCW::Dbo::Accounts::Item::Ptr item1,
       const GCW::Dbo::Accounts::Item::Ptr item2
     )
     {
       auto fullName1 = GCW::Dbo::Accounts::fullName( item1-> guid() );
       auto fullName2 = GCW::Dbo::Accounts::fullName( item2-> guid() );

       /*
       ** return .bool. if the .fullName1. is .less than. the .fullName2. date
       **
       */
       return fullName1
            < fullName2;
     }
  );

} // endvoid sort( GCW::Dbo::Splits::Item::Vector & _splitItems )

} // endnamespace {

auto
GCW::Dbo::Accounts::Item::
accountDef() const-> const GCW::Dbo::Accounts::AccountDef_t &
{
  auto atn = accountTypeName();

  for( auto & val : GCW::Dbo::Accounts::s_accountDefs )
    if( val.name == accountTypeName() )
      return val;

  return GCW::Dbo::Accounts::s_accountDefs.at(0);
}

auto
GCW::Dbo::Accounts::Item::
accountDrCr() const-> GCW::Dbo::Accounts::DrCr
{
  auto atn = accountTypeName();

  for( auto & val : GCW::Dbo::Accounts::s_accountDefs )
    if( val.name == accountTypeName() )
      return val.drcr;

  return GCW::Dbo::Accounts::DrCr::NONE;
}

auto
GCW::Dbo::Accounts::Item::
accountType() const-> GCW::Dbo::Accounts::Type
{
  auto atn = accountTypeName();

  for( auto & val : GCW::Dbo::Accounts::s_accountDefs )
    if( val.name == accountTypeName() )
      return val.type;

  return GCW::Dbo::Accounts::Type::NONE;
}

static
auto
rootSql()-> GCW::Dbo::Accounts::Item::Ptr
{
  GCW::Dbo::Accounts::Item::Ptr retVal;

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  /*
  ** Get a handle on the root account.  The root account is the only
  **  account that has no parent, and has a name == "Root Account".
  **  There should only be one of these.
  **
  */
  auto results =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Accounts::Item >()
    .where( "(parent_guid = '' OR parent_guid IS NULL) AND name = 'Root Account'" )
    .resultList()
    ;

  if( results.size() == 1 )
  {
    retVal = *results.begin();
  }

  return retVal;

} // endrootSql()-> GCW::Dbo::Accounts::Item::Ptr

auto
GCW::Dbo::Accounts::
root()-> GCW::Dbo::Accounts::Item::Ptr
{
  return rootSql();
//  return rootGnc();

} // endroot()-> GCW::Dbo::Accounts::Item::Ptr

auto
GCW::Dbo::Accounts::
load( const std::string & _guid )-> GCW::Dbo::Accounts::Item::Ptr
{
  GCW::Dbo::Accounts::Item::Ptr retVal;

  if( _guid != "" )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    try
    {
      retVal =
        GCW::app()-> gnucashew_session().load< GCW::Dbo::Accounts::Item >( _guid )
        ;
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }
  }

  return retVal;

} // endload( const std::string & _guid )-> GCW::Dbo::Accounts::Item::Ptr

auto
GCW::Dbo::Accounts::
byGuid( const std::string & _guid )-> GCW::Dbo::Accounts::Item::Ptr
{
  return load( _guid );

} // endbyGuid( const std::string & _guid )-> GCW::Dbo::Accounts::Item::Ptr

auto
GCW::Dbo::Accounts::
byChildName( const std::string & _parentGuid, const std::string & _childName )-> GCW::Dbo::Accounts::Item::Ptr
{
  GCW::Dbo::Accounts::Item::Ptr retVal;

  retVal =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Accounts::Item >()
    .where( "parent_guid = ? AND name = ?" )
    .bind( _parentGuid )
    .bind( _childName )
    .resultValue()
    ;

  return retVal;

} // endbyChildName( const std::string & _parentGuid, const std::string & _childName )-> GCW::Dbo::Accounts::Item::Ptr

auto
GCW::Dbo::Accounts::
byFullName( const std::string & _fullName )-> GCW::Dbo::Accounts::Item::Ptr
{
  GCW::Dbo::Accounts::Item::Ptr retVal;

  /*
  ** Here we split the account full-name, so we can dive in
  **  to the accounts table and lope our way up to this
  **  account.
  **
  */
  auto split = Wtx::Core::split( _fullName, ':' );

  /*
  ** Start at the root and lope on up.  The return value
  **  will be filled-in as we go.  We should end on the final
  **  account, which is the one we wanted.
  **
  */
  retVal = root();
  for( int i=0; i< split.size(); i++ )
    retVal = byChildName( retVal-> guid(), split.at(i) );

  return retVal;

} // endbyFullName( const std::string & _fullName )-> GCW::Dbo::Accounts::Item::Ptr

auto
GCW::Dbo::Accounts::
allAccounts()-> GCW::Dbo::Accounts::Item::Vector
{
  GCW::Dbo::Accounts::Item::Vector retVal;

  auto results =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Accounts::Item >()
    .resultList()
    ;

  for( auto result : results )
    retVal.push_back( result );

  sort( retVal );

  return retVal;

} // endallAccounts()-> GCW::Dbo::Accounts::Item::Vector

auto
GCW::Dbo::Accounts::
activeAccounts()-> GCW::Dbo::Accounts::Item::Vector
{
  GCW::Dbo::Accounts::Item::Vector retVal;

  auto results =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Accounts::Item >()
    .resultList()
    ;

  for( auto result : results )
    if( !result-> hidden()
     && !result-> placeHolder()
      )
    retVal.push_back( result );

  return retVal;

} // endactiveAccounts()-> GCW::Dbo::Accounts::Item::Vector

auto
GCW::Dbo::Accounts::Children::
vector( const std::string & _parentGuid )-> GCW::Dbo::Accounts::Item::Vector
{
  GCW::Dbo::Accounts::Item::Vector retVal;


  return retVal;

} // endvector( const std::string & _parentGuid )-> GCW::Dbo::Accounts::Item::Vector

/*!
** \brief Compute Account Full-Name from Heirarchy
**
** This function will calculate the "full account name" from
**  the accountGuid up to the root parent.
**
*/
auto
GCW::Dbo::Accounts::
fullName( const std::string & _accountGuid )-> std::string
{
  /*!
  ** If the provided account guid is blank, then just return
  **  an empty string.
  **
  */
  if( _accountGuid == "" )
    return "";

  /*
  ** Fetch the account by Guid
  **
  */
  auto accountItem = byGuid( _accountGuid );

  /*!
  ** During the building process, even though the "root account"
  **  is a valid account, it is ignored and not included in the
  **  results.
  **
  */
  if( accountItem == root() )
    return "";

  /*
  ** This is a recursive function that extracts the portions of
  **  the account names and assembles them in to a contiguous
  **  string with ':' color separator.
  **
  */
  std::string retVal = fullName( accountItem-> parent_guid() );

  /*
  ** If we got anything then we need a separator
  **
  */
  if( retVal != "" )
      retVal += ":";

  /*
  ** And, finally the name of our account.
  **
  */
  retVal += accountItem-> name();

  /*!
  ** Recursively, this should generate a name such as;
  **   "Assets:2023:Cash:FGB:OLB:2300-LSI"
  **
  */
  return retVal;

} // endfullName( const std::string & _accountGuid )-> std::string

auto
GCW::Dbo::Accounts::
fullName( Item::Ptr _item )-> std::string
{
  return fullName( _item-> guid() );

} // endfullName( Item::Ptr _item )-> std::string

auto
GCW::Dbo::Accounts::Item::
fullName() const-> std::string
{
  return GCW::Dbo::Accounts::fullName( self() );

} // endfullName() const-> std::string

auto
GCW::Dbo::Accounts::Item::
hasColor() const-> bool
{
  return GCW::Dbo::Slots::get( guid(), "color" ).get();

} // endhasColor() const-> bool

auto
GCW::Dbo::Accounts::Item::
color() const-> std::string
{
  std::string retVal;

  if( auto slotItem = GCW::Dbo::Slots::get( guid(), "color" ) )
  {
    retVal = slotItem-> string_val();
  }

  return retVal;

} // endcolor() const-> std::string


