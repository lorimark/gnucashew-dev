#line 2 "src/Dbo/Manager.cpp"

#include "../Glb/Core.h"
#include "Manager.h"

GCW::Dbo::Transactions::Manager::
Manager()
{

} // endManager()

GCW::Dbo::Transactions::Manager::
Manager( GCW::Dbo::Splits::Item::Ptr _splitItem )
{

} // endManager()

auto
GCW::Dbo::Transactions::Manager::
newTransaction( const std::string & _accountGuid1, const std::string & _accountGuid2 )-> void
{
  /*!
  ** The process begins by loading up the two accounts.  The two account
  **
  */
  auto accountItem1 = GCW::Dbo::Accounts::load( _accountGuid1 );

  /*
  ** create a new transaction with two splits
  **
  */
  m_transaction = GCW::Dbo::Transactions::add( GCW::Core::newGuid() );

  /*
  ** hook everything together
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  // transaction
  m_transaction.modify()-> set_currency_guid( accountItem1-> commodity_guid() );
  // Split1
  auto split1 = GCW::Dbo::Splits::add( GCW::Core::newGuid() );
  split1.modify()-> set_tx_guid         ( m_transaction-> guid() );
  split1.modify()-> set_account_guid    ( _accountGuid1          );
  split1.modify()-> set_reconcile_state ( GCW_RECONCILE_NO       );
  split1.modify()-> set_reconcile_date  ( GCW_DEFAULT_DATE       );
  // Split2
  auto split2 = GCW::Dbo::Splits::add( GCW::Core::newGuid() );
  split2.modify()-> set_tx_guid         ( m_transaction-> guid() );
  split2.modify()-> set_account_guid    ( _accountGuid2          );
  split2.modify()-> set_reconcile_state ( GCW_RECONCILE_NO       );
  split2.modify()-> set_reconcile_date  ( GCW_DEFAULT_DATE       );

  /*
  ** record the splits
  */
  m_splitItems.push_back( split1 );
  m_splitItems.push_back( split2 );

} // endnewTransaction()-> void

auto
GCW::Dbo::Transactions::Manager::
loadTransaction( const std::string & _transactionGuid )-> void
{
  /*
  ** set the transaction
  */
  m_transaction = GCW::Dbo::Transactions::load( _transactionGuid );

  /*
  ** set the splits
  */
  m_splitItems = GCW::Dbo::Splits::byTransaction( m_transaction-> guid() );

} // endloadTransaction( const std::string & _transactionGuid )-> void

auto
GCW::Dbo::Transactions::Manager::
deleteTransaction()-> void
{

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transaction.remove();
  for( auto & splitItem : m_splitItems )
    splitItem.remove();

} // enddeleteTransaction()-> void

auto
GCW::Dbo::Transactions::Manager::
loadSplit( const std::string & _splitGuid )-> void
{
  /*
  ** in the words of spock: 'remember'
  */
  m_splitGuid = _splitGuid;

  /*
  ** get the split so we can grab the transaction
  */
  auto splitItem = GCW::Dbo::Splits::load( _splitGuid );

  /*
  ** set the transaction
  */
  loadTransaction( splitItem-> tx_guid() );

} // endloadSplit( const std::string & _splitGuid )-> void

auto
GCW::Dbo::Transactions::Manager::
otherGuid() const-> std::string
{
  for( auto & splitItem : m_splitItems )
    if( splitItem-> guid() != m_splitGuid )
      return splitItem-> guid();

  return "";

} // endotherGuid()-> std::string

auto
GCW::Dbo::Transactions::Manager::
split( const std::string & _splitGuid ) const-> GCW::Dbo::Splits::Item::Ptr
{
  for( auto & splitItem : m_splitItems )
    if( splitItem-> guid() == _splitGuid )
      return splitItem;

  return GCW::Dbo::Splits::Item::Ptr();

} // endsplit( const std::string & _splitGuid ) const-> GCW::Dbo::Splits::Item::Ptr

auto
GCW::Dbo::Transactions::Manager::
thisSplit() const-> GCW::Dbo::Splits::Item::Ptr
{
  return split( m_splitGuid );

} // endthisSplit() const-> GCW::Dbo::Splits::Item::Ptr

auto
GCW::Dbo::Transactions::Manager::
thatSplit() const-> GCW::Dbo::Splits::Item::Ptr
{
  return split( otherGuid() );

} // endthatSplit() const-> GCW::Dbo::Splits::Item::Ptr

auto
GCW::Dbo::Transactions::Manager::
getDate() const-> Wt::WDateTime
{
  return m_transaction-> post_date_as_date();

} // endgetDate() const-> Wt::WDateTime &;

auto
GCW::Dbo::Transactions::Manager::
setDate( const Wt::WDateTime & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transaction.modify()-> set_post_date( _value );

} // endsetDate( const Wt::WDateTime & _value )-> void

auto
GCW::Dbo::Transactions::Manager::
setAction( const std::string & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transaction.modify()-> set_num( _value );

} // endsetAction( const std::string & _value )-> void

auto
GCW::Dbo::Transactions::Manager::
getDescription() const-> std::string
{
  return m_transaction-> description();

} // endgetDescription() const-> std::string &

auto
GCW::Dbo::Transactions::Manager::
setDescription( const std::string & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transaction.modify()-> set_description( _value );

} // endsetDescription( const std::string & _value )-> void

auto
GCW::Dbo::Transactions::Manager::
setTransferGuid( const std::string & _value  )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  thatSplit().modify()-> set_account_guid( _value );

} // endsetTransferGuid( const std::string & _value  )-> void

auto
GCW::Dbo::Transactions::Manager::
setReconcile( const std::string & _value  )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  thisSplit().modify()-> set_reconcile_state( _value );

} // endsetReconcile( const std::string & _value  )-> void

auto
GCW::Dbo::Transactions::Manager::
getValue() const-> GCW_NUMERIC
{
  return thisSplit()-> value();

} // endgetValue() const-> GCW_NUMERIC

auto
GCW::Dbo::Transactions::Manager::
getValueAsString() const-> std::string
{
  return thisSplit()-> valueAsString();

} // endgetValue() const-> GCW_NUMERIC

auto
GCW::Dbo::Transactions::Manager::
setValue( GCW_NUMERIC _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  thisSplit().modify()-> set_value( _value      );
  thatSplit().modify()-> set_value( _value * -1 );

} // endsetDebit( GCW_NUMERIC _value )-> void

auto
GCW::Dbo::Transactions::Manager::
setNotes( const std::string & _value  )-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << " " << _value << std::endl;

} // endsetNotes( const std::string & _value  )-> void



