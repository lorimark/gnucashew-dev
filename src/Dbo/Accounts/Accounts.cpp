#line 2 "src/Dbo/Accounts/Accounts.cpp"

#include "../Glb/Core.h"
#include "../App.h"
#include "Accounts.h"

const char * GCW::Dbo::Accounts::s_tableName = "accounts";

/*!
** \code
** {   type                                   dbcr                                name           colAccount   colDr        colCr
** \endcode
**
** These are the account-types, debit/credit types, and register column labels for said accounts.
**
** \ref GCW::Eng::AccountRegisterModel::refreshFromDisk() "refreshFromDisk()"
*/
const std::vector< GCW::Dbo::Accounts::AccountDef_t > GCW::Dbo::Accounts::s_accountDefs =
{// type                                   dbcr                                name           colAccount   colDr        colCr
  { GCW::Dbo::Accounts::Type::INVALID    , GCW::Dbo::Accounts::DrCr::NONE   ,  "INVALID"    , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::NONE       , GCW::Dbo::Accounts::DrCr::NONE   ,  "NONE"       , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::BANK       , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "BANK"       , "transfer" , "deposit"  , "withdrawal"  },
  { GCW::Dbo::Accounts::Type::CASH       , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "CASH"       , "transfer" , "receive"  , "spend"       },
  { GCW::Dbo::Accounts::Type::CREDIT     , GCW::Dbo::Accounts::DrCr::CREDIT ,  "CREDIT"     , "blank"    , "payment"  , "charge"      },
  { GCW::Dbo::Accounts::Type::ASSET      , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "ASSET"      , "transfer" , "deposit"  , "withdrawal"  },
  { GCW::Dbo::Accounts::Type::LIABILITY  , GCW::Dbo::Accounts::DrCr::CREDIT ,  "LIABILITY"  , "account"  , "payment"  , "charge"      },
  { GCW::Dbo::Accounts::Type::STOCK      , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "STOCK"      , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::MUTUAL     , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "MUTUAL"     , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::CURRENCY   , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "CURRENCY"   , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::INCOME     , GCW::Dbo::Accounts::DrCr::CREDIT ,  "INCOME"     , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::EXPENSE    , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "EXPENSE"    , "transfer" , "expense"  , "rebate"      },
  { GCW::Dbo::Accounts::Type::EQUITY     , GCW::Dbo::Accounts::DrCr::CREDIT ,  "EQUITY"     , "transfer" , "decrease" , "increase"    },
  { GCW::Dbo::Accounts::Type::RECEIVABLE , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "RECEIVABLE" , "transfer" , "invoice"  , "payment"     },
  { GCW::Dbo::Accounts::Type::PAYABLE    , GCW::Dbo::Accounts::DrCr::CREDIT ,  "PAYABLE"    , "account"  , "payment"  , "charge"      },
  { GCW::Dbo::Accounts::Type::ROOT       , GCW::Dbo::Accounts::DrCr::NONE   ,  "ROOT"       , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::TRADING    , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "TRADING"    , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::CHECKING   , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "CHECKING"   , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::SAVINGS    , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "SAVINGS"    , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::MONEYMRKT  , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "MONEYMRKT"  , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::CREDITLINE , GCW::Dbo::Accounts::DrCr::CREDIT ,  "CREDITLINE" , "account"  , "debit"    , "credit"      },
};

const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::guid             = "guid"           ; // text(32) PRIMARY KEY NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::name             = "name"           ; // text(2048) NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::account_typeName = "account_type"   ; // text(2048) NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::commodity_guid   = "commodity_guid" ; // text(32)
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::commodity_scu    = "commodity_scu"  ; // integer NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::non_std_scu      = "non_std_scu"    ; // integer NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::parent_guid      = "parent_guid"    ; // text(32)
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::code             = "code"           ; // text(2048)
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::description      = "description"    ; // text(2048)
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::hidden           = "hidden"         ; // integer
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::placeHolder      = "placeholder"    ; // integer

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

} // endnamespace {

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
  auto split = GCW::Core::split( _fullName, ':' );

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



