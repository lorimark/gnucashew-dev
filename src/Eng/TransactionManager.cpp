#line 2 "src/Eng/TransactionManager.cpp"

#include "../Glb/Core.h"
#include "../Gui/AccountRegister/Model.h"
#include "TransactionManager.h"

GCW::Eng::Transaction::Manager::
Manager()
: m_prefrenceItem( GCW::Dbo::Prefrences::get() )
{

} // endManager()

GCW::Eng::Transaction::Manager::
Manager( Gui::AccountRegister::Model * _model )
: m_model( _model ),
  m_prefrenceItem( GCW::Dbo::Prefrences::get() )
{

} // endManager()

auto
GCW::Eng::Transaction::Manager::
newTransaction( const std::string & _accountGuid1, const std::string & _accountGuid2 )-> void
{
  /*!
  ** The process begins by loading up the two accounts.
  */
  auto accountItem1 = GCW::Dbo::Accounts::load( _accountGuid1 );

  /*
  ** create a new transaction with two splits
  */
  m_transactionItem = GCW::Dbo::Transactions::add( GCW::Core::newGuid() );

  /*
  ** hook everything together
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  // transaction
  m_transactionItem.modify()-> set_currency_guid( accountItem1-> commodity_guid() );
  m_transactionItem.modify()-> set_enter_date( Wt::WDateTime::currentDateTime() );
  // Split1
  auto split1 = GCW::Dbo::Splits::add( GCW::Core::newGuid() );
  split1.modify()-> set_tx_guid         ( m_transactionItem-> guid() );
  split1.modify()-> set_account_guid    ( _accountGuid1          );
  split1.modify()-> set_reconcile_state ( GCW_RECONCILE_NO       );
  split1.modify()-> set_reconcile_date  ( GCW_DEFAULT_DATE       );
  // Split2
  auto split2 = GCW::Dbo::Splits::add( GCW::Core::newGuid() );
  split2.modify()-> set_tx_guid         ( m_transactionItem-> guid() );
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
  m_transactionItem = GCW::Dbo::Transactions::load( _transactionGuid );

  /*
  ** set the splits
  */
  m_splits = GCW::Dbo::Splits::byTransaction( m_transactionItem-> guid() );

} // endloadTransaction( const std::string & _transactionGuid )-> void

auto
GCW::Eng::Transaction::Manager::
deleteTransaction()-> void
{

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transactionItem.remove();
  for( auto & splitItem : m_splits )
    splitItem.remove();

} // enddeleteTransaction()-> void

auto
GCW::Eng::Transaction::Manager::
setSplitItem( GCW::Dbo::Splits::Item::Ptr _splitItem )-> void
{
  if( !_splitItem )
    return;

  loadSplit( _splitItem-> guid() );

} // endsetSplitItem( GCW::Dbo::Splits::Item::Ptr _splitItem )-> void

auto
GCW::Eng::Transaction::Manager::
loadSplit( const std::string & _splitGuid )-> void
{
  if( _splitGuid == "" )
    return;

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
  return m_transactionItem-> post_date_as_date();

} // endgetDate() const-> Wt::WDateTime &;

auto
GCW::Eng::Transaction::Manager::
getDateAsString() const-> Wt::WString
{
  return getDate().toString( GCW_DATE_FORMAT_DISPLAY );

} // endgetDate() const-> Wt::WDateTime &;

auto
GCW::Eng::Transaction::Manager::
setDate( const Wt::WDateTime & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transactionItem.modify()-> set_post_date( _value );

} // endsetDate( const Wt::WDateTime & _value )-> void

auto
GCW::Eng::Transaction::Manager::
setDate( const Wt::WDate & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transactionItem.modify()-> set_post_date( Wt::WDateTime( _value ) );

} // endsetDate( const Wt::WDateTime & _value )-> void



auto
GCW::Eng::Transaction::Manager::
setAction( const std::string & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transactionItem.modify()-> set_num( _value );

} // endsetAction( const std::string & _value )-> void

auto
GCW::Eng::Transaction::Manager::
getDescription() const-> std::string
{
  return m_transactionItem-> description();

} // endgetDescription() const-> std::string &

auto
GCW::Eng::Transaction::Manager::
setDescription( const std::string & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transactionItem.modify()-> set_description( _value );

} // endsetDescription( const std::string & _value )-> void

auto
GCW::Eng::Transaction::Manager::
setDescription( const Wt::WString & _value )-> void
{
  setDescription( _value.toUTF8() );

} // ensetDescription( const Wt::WString & _value )-> void

auto
GCW::Eng::Transaction::Manager::
getNum() const-> std::string
{
  return m_transactionItem-> num();

} // endgetDescription() const-> std::string &

auto
GCW::Eng::Transaction::Manager::
setNum( const std::string & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_transactionItem.modify()-> set_num( _value );

} // endsetDescription( const std::string & _value )-> void

auto
GCW::Eng::Transaction::Manager::
setNum( const Wt::WString & _value )-> void
{
  setNum( _value.toUTF8() );

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


auto
GCW::Eng::Transaction::Manager::
otherSplits() const-> GCW::Dbo::Splits::Item::Vector
{
  return GCW::Dbo::Splits::bySplitExcept( m_splitGuid );

} // endotherSplits() const-> GCW::Dbo::Splits::Item::Vector

auto
GCW::Eng::Transaction::Manager::
setReadOnly( bool _value )-> void
{

} // endsetReadOnly( bool _value )-> void

auto
GCW::Eng::Transaction::Manager::
createText( const std::string & _text ) const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >( _text );

  retVal-> setStyleClass( "blank" );

  return std::move( retVal );

} // endcreateBlank()  const-> std::unique_ptr< Wt::WStandardItem >

auto
GCW::Eng::Transaction::Manager::
createBlank() const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >();

  retVal-> setStyleClass( "blank" );

  return std::move( retVal );

} // endcreateBlank()  const-> std::unique_ptr< Wt::WStandardItem >

auto
GCW::Eng::Transaction::Manager::
createEmpty() const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >();

  retVal-> setStyleClass( "empty" );

  return std::move( retVal );

} // endcreateEmpty()  const-> std::unique_ptr< Wt::WStandardItem >

auto
GCW::Eng::Transaction::Manager::
createDate( TxItem _txItem ) const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >();

  retVal-> setStyleClass( "date" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  /*!
  ** \note The post_date column (col-0) also carries with it the guid of the split
  **  item itself, so that the originating split can be located from the table
  **  view.  The guid can be accessed by;
  **
  ** \code
  ** Wt::WString splitRowGuid = Wt::asString( standardItem.data( Wt::ItemDataRole::User ) )
  ** \endcode
  **
  ** \sa getSplitGuid
  */
//  auto tip =
//    Wt::WString
//    (
//     "row: {1}\n"
//     "acg: {2}\n"
//     "spg: {3}\n"
//    )
//    .arg( m_model-> rowCount()         )
//    .arg( thisSplit()-> account_guid() )
//    .arg( thisSplit()-> guid()         )
//    ;

  retVal-> setData( transactionItem()-> post_date_as_date(), Wt::ItemDataRole::Edit );
  retVal-> setData( thisSplit()-> guid(), Wt::ItemDataRole::User );
//  retVal-> setToolTip( tip );

  return std::move( retVal );

} // endcreateDate() const-> std::unique_ptr< Wt::WStandardItem > ;

auto
GCW::Eng::Transaction::Manager::
createNum( TxItem _txItem )  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >( _txItem-> num() );

  retVal-> setStyleClass( "txnum" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  return std::move( retVal );

} // endcreateNum()  const-> std::unique_ptr< Wt::WStandardItem >


auto
GCW::Eng::Transaction::Manager::
createNum( SpItem _spItem )  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >( _spItem-> action() );

  retVal-> setStyleClass( "spnum" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  return std::move( retVal );

} // endcreateNum()  const-> std::unique_ptr< Wt::WStandardItem >


auto
GCW::Eng::Transaction::Manager::
createDescription( TxItem _txItem )  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >( _txItem-> description() );

  retVal-> setStyleClass( "txdesc" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  return std::move( retVal );

} // endcreateDescription()  const-> std::unique_ptr< Wt::WStandardItem >


auto
GCW::Eng::Transaction::Manager::
createDescription( SpItem _spItem )  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >( _spItem-> memo() );

  retVal-> setStyleClass( "spdesc" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  return std::move( retVal );

} // endcreateDescription()  const-> std::unique_ptr< Wt::WStandardItem >

#ifdef NEVER
auto
GCW::Eng::Transaction::Manager::
createAccount( SpItem _splitItem )  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >();
  retVal-> setStyleClass( "acct" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  /*!
  ** The 'account' text depends on the
  **  target account defined in the split.  There are three
  **  possibilities here;
  **
  **   -# no splits... this shows up as an <b>'imbalance'</b> (this is an error condition)
  **   -# 1 split...   this just shows the split account on the same single line
  **   -# >1 split...  this is more than one target account, so just indicate 'split'
  */
  switch( otherSplits().size() )
  {
    /*!
    ** \par Imbalance
    ** This is actually a problem... We don't have another split, and
    **  according to 'generally accepted accounting practices' we
    **  should!  So, just  plop an 'imbalance' indicator in the view.
    **  A style-class is also applied to the item to allow the rendering
    **  in the view to highlight this problem.
    */
    case 0:
    {
      retVal-> setText( TR("gcw.AccountRegister.account.imbalanceUSD") ); // account
      retVal-> setStyleClass( retVal-> styleClass() + " errval" );
      retVal-> setToolTip( TR("gcw.AccountRegister.account.imbalanceUSD.toolTip") );
      break;
    }

    /*!
    ** \par Normal Split
    ** This is a straight and simple 1:1 split transaction, so we can pull
    **  the account name from the other side of the split and pop that in
    **  to the model directly.
    */
    case 1:
    {
      auto txSplitItem      = *otherSplits().begin();
      auto splitAccountItem = GCW::Dbo::Accounts::byGuid( txSplitItem-> account_guid() );

      // yes, we have one account item
      if( splitAccountItem )
      {
        retVal-> setText( GCW::Dbo::Accounts::fullName( splitAccountItem-> guid() ) );

        auto tip =
          Wt::WString
          (
           "spa:{1}\n"
           "txi:{2}\n"
          )
          .arg( splitAccountItem-> guid() )
          .arg( txSplitItem-> guid() )
          ;
        retVal-> setToolTip( tip );
      }

      // no, we don't have an account item
      else
      {
        /*!
        ** \par Another Imbalance
        ** This is another problem... We have another split, but the account
        **  we are split-to doesn't exist.  This is a problem and should not
        **  happen and represents an error in the database.  This means the
        **  account containing this guid nolonger exists.  That should never
        **  happen.
        */
        retVal-> setText( TR("gcw.AccountRegister.account.imbalanceUSD") );
        retVal-> setStyleClass( retVal-> styleClass() + " errval" );

        auto toolTip =
          Wt::WString("target guid:{1}\n{2}")
          .arg( txSplitItem-> account_guid() )
          .arg( TR("gcw.AccountRegister.account.invalidTarget.toolTip") )
          .toUTF8()
          ;

        retVal-> setToolTip( toolTip );

      } // endelse no account item

      break;

    } // endcase 1:

    /*!
    ** \par Multi-Split
    ** When we have more than one split then we cannot display
    **  all of the split accounts on just one line, so just pop
    **  a message that indicates that we're in a multisplit
    **  transaction.
    */
    default:
    {
      retVal-> setText( TR("gcw.AccountRegister.account.multisplit") ); // account
    }

  } // endswitch( transMan.otherSplits().size() )


  return std::move( retVal );

} // endcreateAccount()  const-> std::unique_ptr< Wt::WStandardItem >
#endif

auto
GCW::Eng::Transaction::Manager::
createAccount( SpItem _splitItem )  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >();
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  auto splitAccountItem = GCW::Dbo::Accounts::byGuid( _splitItem-> account_guid() );

  // yes, we have one account item
  if( splitAccountItem )
  {
    retVal-> setText( GCW::Dbo::Accounts::fullName( splitAccountItem-> guid() ) );

//    auto tip =
//      Wt::WString
//      (
//       "spa:{1}\n"
//       "txi:{2}\n"
//      )
//      .arg( splitAccountItem-> guid() )
//      .arg( _splitItem-> guid() )
//      ;
//    retVal-> setToolTip( tip );
  }

  // no, we don't have an account item
  else
  {
    /*!
    ** \par Another Imbalance
    ** This is another problem... We have another split, but the account
    **  we are split-to doesn't exist.  This is a problem and should not
    **  happen and represents an error in the database.  This means the
    **  account containing this guid nolonger exists.  That should never
    **  happen.
    */
    retVal-> setText( TR("gcw.AccountRegister.account.imbalanceUSD") );
    retVal-> setStyleClass( retVal-> styleClass() + " errval" );

//    auto toolTip =
//      Wt::WString("target guid:{1}\n{2}")
//      .arg( _splitItem-> account_guid() )
//      .arg( TR("gcw.AccountRegister.account.invalidTarget.toolTip") )
//      .toUTF8()
//      ;
//    retVal-> setToolTip( toolTip );

  } // endelse no account item

  return std::move( retVal );

} // endcreateAccount()  const-> std::unique_ptr< Wt::WStandardItem >

auto
GCW::Eng::Transaction::Manager::
createReconcile( SpItem _splitItem )  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >( _splitItem-> reconcile_state() );

  retVal-> setStyleClass( "rec" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  return std::move( retVal );

} // endcreateReconcile()  const-> std::unique_ptr< Wt::WStandardItem >

auto
GCW::Eng::Transaction::Manager::
createDebit( SpItem _splitItem )  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >(  );

  retVal-> setStyleClass( "dr" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  if( _splitItem-> value() > 0 )
  {
    retVal -> setText( _splitItem-> valueAsString() );
  }

  return std::move( retVal );

} // endcreateDebit()  const-> std::unique_ptr< Wt::WStandardItem >

auto
GCW::Eng::Transaction::Manager::
createCredit( SpItem _splitItem )  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >(  );

  retVal-> setStyleClass( "cr" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  if( _splitItem-> value() < 0 )
  {
    retVal -> setText( _splitItem-> valueAsString( true ) );
  }

  return std::move( retVal );

} // endcreateCredit()  const-> std::unique_ptr< Wt::WStandardItem >

auto
GCW::Eng::Transaction::Manager::
createBalance()  const-> std::unique_ptr< Wt::WStandardItem >
{
  auto retVal = std::make_unique< Wt::WStandardItem >( toString( model()-> m_balance, GCW::Cfg::decimal_format() ) );

  retVal-> setStyleClass( "bal" );
  retVal-> setFlags( Wt::ItemFlag::DeferredToolTip );

  return std::move( retVal );

} // endcreateBalance()  const-> std::unique_ptr< Wt::WStandardItem >

auto
GCW::Eng::Transaction::Manager::
highlightNegativeBalance( RowItem & _row ) const-> void
{
  /*
  ** if the balance is negative, highlight the row
  */
  if( model()-> m_balance < 0 )
  {
    if( prefrenceItem().accountRegisterHighlight( GCW::Dbo::Prefrences::AccountRegisterHighlight::NEGVAL_EXTRA ) )
    {
      for( int col = 0; col< _row.size(); col++ )
        _row.at( col )-> setStyleClass( _row.at( col )-> styleClass() + " negval" );
    }

    if( prefrenceItem().accountRegisterHighlight( GCW::Dbo::Prefrences::AccountRegisterHighlight::NORMAL ) )
    {
      _row.at( _row.size()-1 )-> setStyleClass( _row.at( _row.size()-1 )-> styleClass() + " negval" );
    }

  } // endif( model()-> m_balance < 0 )


} // endhighlightNegativeBalance() const-> void

auto
GCW::Eng::Transaction::Manager::
appendBasicLedger() const-> void
{
  RowItem row ;

  row.push_back( createDate        ( transactionItem() ) );
  row.push_back( createNum         ( transactionItem() ) );
  row.push_back( createDescription ( transactionItem() ) );
  row.push_back( createAccount     ( thatSplit()       ) );
  row.push_back( createReconcile   ( thisSplit()       ) );
  row.push_back( createDebit       ( thisSplit()       ) );
  row.push_back( createCredit      ( thisSplit()       ) );
  row.push_back( createBalance     (                   ) );

  highlightNegativeBalance( row );

  /*
  ** set alternating row colors (row-basic-ledger: rowbl)
  */
  for( int col=0; col< row.size(); col++ )
    row.at(col)-> setStyleClass( row.at(col)-> styleClass() + " rowbl" );

  model()-> appendRow( std::move( row ) );

} // endappendBasicLedger() const-> void

auto
GCW::Eng::Transaction::Manager::
appendAutosplitLedger() const-> void
{
} // endappendAutosplitLedger() const-> void

auto
GCW::Eng::Transaction::Manager::
appendTransactionJournal() const-> void
{
  /*
  ** set the first line
  */
  {
    RowItem row ;

    row.push_back( createDate        ( transactionItem() ) );
    row.push_back( createNum         ( transactionItem() ) );
    row.push_back( createDescription ( transactionItem() ) );
    row.push_back( createEmpty       (                   ) ); // account is empty on this row
    row.push_back( createEmpty       (                   ) ); // reconcile is empty on this row
    row.push_back( createDebit       ( thisSplit()       ) );
    row.push_back( createCredit      ( thisSplit()       ) );
    row.push_back( createBalance     (                   ) );

    highlightNegativeBalance( row );

    /*
    ** set static row color (row-transaction-journal: rowtj)
    */
    for( int col=0; col< row.size(); col++ )
      row.at(col)-> setStyleClass( row.at(col)-> styleClass() + " rowtj" );

    model()-> appendRow( std::move( row ) );
  }

  /*
  ** set another line, one for each split
  */
  for( auto splitItem : splits() )
  {
    RowItem row ;
    row.push_back( createEmpty       (           ) );
    row.push_back( createNum         ( splitItem ) );
    row.push_back( createDescription ( splitItem ) );
    row.push_back( createAccount     ( splitItem ) );
    row.push_back( createReconcile   ( splitItem ) );
    row.push_back( createDebit       ( splitItem ) );
    row.push_back( createCredit      ( splitItem ) );
    row.push_back( createEmpty       (           ) );

    for( int col=1; col< row.size(); col++ )
      row.at(col)-> setStyleClass( row.at(col)-> styleClass() + " rowtd" );

    model()-> appendRow( std::move( row ) );
  }

  if( model()-> doubleLine() )
  {
    RowItem row ;
    row.push_back( createEmpty() );
    row.push_back( createEmpty() );
    row.push_back( createEmpty() );
    row.push_back( createEmpty() );
    row.push_back( createEmpty() );
    row.push_back( createEmpty() );
    row.push_back( createEmpty() );
    row.push_back( createEmpty() );

    model()-> appendRow( std::move( row ) );
  }

} // endappendTransactionJournal() const-> void

auto
GCW::Eng::Transaction::Manager::
appendGeneralJournal() const-> void
{
} // endappendGeneralJournal() const-> void



auto
GCW::Eng::Transaction::Manager::
appendRow()-> void
{
  /*
  ** calculate the running balance
  */
  model()-> m_balance += thisSplit()-> value();

  /*
  ** build a row depending on the view mode
  */
  switch( model()-> viewMode() )
  {
// #warning fix this
#ifndef NEVER
    case GCW::Gui::AccountRegister::Model::ViewMode::BASIC_LEDGER:
    {
      appendBasicLedger();
      break;
    }

    case GCW::Gui::AccountRegister::Model::ViewMode::AUTOSPLIT_LEDGER:
    {
      appendAutosplitLedger();
      break;
    }

    case GCW::Gui::AccountRegister::Model::ViewMode::TRANSACTION_JOURNAL:
    {
      appendTransactionJournal();
      break;
    }

    case GCW::Gui::AccountRegister::Model::ViewMode::GENERAL_JOURNAL:
    {
      appendGeneralJournal();
      break;
    }
#endif

  } // endswitch( model()-> viewMode() )

} // endappendRow()-> void



