#line 2 "src/Eng/TransactionManager.cpp"

#include "../Glb/Core.h"
#include "TransactionManager.h"

GCW::Eng::Transaction::Manager::
Manager()
{

} // endManager()

GCW::Eng::Transaction::Manager::
Manager( GCW::Dbo::Splits::Item::Ptr _splitItem )
{

} // endManager()

auto
GCW::Eng::Transaction::Manager::
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
  m_splits.push_back( split1 );
  m_splits.push_back( split2 );

} // endnewTransaction()-> void

auto
GCW::Eng::Transaction::Manager::
loadTransaction( const std::string & _transactionGuid )-> void
{
  /*
  ** set the transaction
  */
  m_transaction = GCW::Dbo::Transactions::load( _transactionGuid );

  /*
  ** set the splits
  */
  m_splits = GCW::Dbo::Splits::byTransaction( m_transaction-> guid() );

} // endloadTransaction( const std::string & _transactionGuid )-> void

auto
GCW::Eng::Transaction::Manager::
deleteTransaction()-> void
{

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transaction.remove();
  for( auto & splitItem : m_splits )
    splitItem.remove();

} // enddeleteTransaction()-> void

auto
GCW::Eng::Transaction::Manager::
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
GCW::Eng::Transaction::Manager::
otherGuid() const-> std::string
{
  for( auto & splitItem : m_splits )
    if( splitItem-> guid() != m_splitGuid )
      return splitItem-> guid();

  return "";

} // endotherGuid()-> std::string

auto
GCW::Eng::Transaction::Manager::
split( const std::string & _splitGuid ) const-> GCW::Dbo::Splits::Item::Ptr
{
  for( auto & splitItem : m_splits )
    if( splitItem-> guid() == _splitGuid )
      return splitItem;

  return GCW::Dbo::Splits::Item::Ptr();

} // endsplit( const std::string & _splitGuid ) const-> GCW::Dbo::Splits::Item::Ptr

auto
GCW::Eng::Transaction::Manager::
thisSplit() const-> GCW::Dbo::Splits::Item::Ptr
{
  return split( m_splitGuid );

} // endthisSplit() const-> GCW::Dbo::Splits::Item::Ptr

auto
GCW::Eng::Transaction::Manager::
thatSplit() const-> GCW::Dbo::Splits::Item::Ptr
{
  return split( otherGuid() );

} // endthatSplit() const-> GCW::Dbo::Splits::Item::Ptr

auto
GCW::Eng::Transaction::Manager::
forAccountSplit( const std::string & _accountGuid ) const-> GCW::Dbo::Splits::Item::Ptr
{
  GCW::Dbo::Splits::Item::Ptr retVal;

  for( auto & split : m_splits )
    if( split-> account_guid() == _accountGuid )
      retVal = split;

  return retVal;

} // endforAccount( const std::string * _accountGuid ) const-> GCW::Dbo::Splits::Item::Ptr

auto
GCW::Eng::Transaction::Manager::
getDate() const-> Wt::WDateTime
{
  return m_transaction-> post_date_as_date();

} // endgetDate() const-> Wt::WDateTime &;

auto
GCW::Eng::Transaction::Manager::
setDate( const Wt::WDateTime & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transaction.modify()-> set_post_date( _value );

} // endsetDate( const Wt::WDateTime & _value )-> void

auto
GCW::Eng::Transaction::Manager::
setAction( const std::string & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transaction.modify()-> set_num( _value );

} // endsetAction( const std::string & _value )-> void

auto
GCW::Eng::Transaction::Manager::
getDescription() const-> std::string
{
  return m_transaction-> description();

} // endgetDescription() const-> std::string &

auto
GCW::Eng::Transaction::Manager::
setDescription( const std::string & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transaction.modify()-> set_description( _value );

} // endsetDescription( const std::string & _value )-> void

auto
GCW::Eng::Transaction::Manager::
setDescription( const Wt::WString & _value )-> void
{
  setDescription( _value.toUTF8() );

} // ensetDescription( const Wt::WString & _value )-> void

auto
GCW::Eng::Transaction::Manager::
setTransferGuid( const std::string & _value  )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  thatSplit().modify()-> set_account_guid( _value );

} // endsetTransferGuid( const std::string & _value  )-> void

auto
GCW::Eng::Transaction::Manager::
setReconcile( const std::string & _value  )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  thisSplit().modify()-> set_reconcile_state( _value );

} // endsetReconcile( const std::string & _value  )-> void

auto
GCW::Eng::Transaction::Manager::
getValue() const-> GCW_NUMERIC
{
  return thisSplit()-> value();

} // endgetValue() const-> GCW_NUMERIC

auto
GCW::Eng::Transaction::Manager::
getValueAsString() const-> std::string
{
  return thisSplit()-> valueAsString();

} // endgetValue() const-> GCW_NUMERIC

auto
GCW::Eng::Transaction::Manager::
setValue( GCW_NUMERIC _value )-> void
{
//  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
//  thisSplit().modify()-> set_value( _value      );
//  thatSplit().modify()-> set_value( _value * -1 );

} // endsetDebit( GCW_NUMERIC _value )-> void

auto
GCW::Eng::Transaction::Manager::
setValue( const std::string & _acctGuid, GCW_NUMERIC _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  forAccountSplit( _acctGuid ).modify()-> set_value( _value );

} // endsetValue( const std::string & _acctGuid, GCW_NUMERIC _value )-> void

auto
GCW::Eng::Transaction::Manager::
setNotes( const std::string & _acctGuid, const std::string & _value  )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  forAccountSplit( _acctGuid ).modify()-> set_memo( _value );

} // endsetNotes( const std::string & _value  )-> void



