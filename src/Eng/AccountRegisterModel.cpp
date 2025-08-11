#line 2 "src/Eng/AccountRegisterModel.cpp"

#include "../Glb/gcwglobal.h"
#include "../Dbo/SessionGnuCash.h"
#include "../Dbo/Splits/Splits.h"
#include "../Dbo/Prefrences.h"
#include "../Dbo/Vars/Vars.h"
#include "../Glb/Core.h"
#include "TransactionManager.h"
#include "AccountRegisterModel.h"

/*
** column definitions:
**
** 0,0 - date        : transaction -> post_date
** 0,1 - action      : split       -> action
** 0,2 - description : transaction -> description
** 0,3 - transfer    : split       -> {tx_guid 2nd split}
** 0,4 - reconcile   : split       -> reconcile_state, reconcile_date
** 0,5 - debit       : split       -> value_num, value_denom (+positive value)
** 0,6 - credit      : split       -> value_num, value_denom (-negative value)
** 1,2 - notes       : split       -> memo
*/
#define COL_DATE        (0)
#define COL_ACTION      (1)
#define COL_DESCRIPTION (2)
#define COL_TRANSFER    (3)
#define COL_RECONCILE   (4)
#define COL_DEBIT       (5)
#define COL_CREDIT      (6)
#define COL_BALANCE     (7)
#define COL_NOTES       (2)

GCW::Eng::AccountRegisterModel::
AccountRegisterModel( const std::string & _accountGuid, bool _readOnly )
: Wt::WStandardItemModel( 0, 8 ), // 8-columns
  m_accountGuid( _accountGuid ),
  m_readOnly( _readOnly )
{
  /*
  ** set the lastDate to match the todays date, so when first
  **  opening the register, the date is automatically set.
  */
  m_lastDate = Wt::WDateTime::currentDateTime();

  refreshFromDisk();

#ifdef NEVER
  dataChanged().connect( [=]( Wt::WModelIndex _index1, Wt::WModelIndex _index2 )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " model<signal>.dataChanged()"
      << "\n tst:" << std::string( Wt::asString( _index1.data() ) == Wt::asString( _index2.data() )? "same":"different" )
      << "\n r1:" << _index1.row()
      << "   c1:" << _index1.column()
      << "   v1:" << Wt::asString( _index1.data() )
      << "\n r2:" << _index2.row()
      << "   c2:" << _index2.column()
      << "   v2:" << Wt::asString( _index2.data() )
      << std::endl;

  });
#endif

#ifdef NEVER
  itemChanged().connect( [=]( Wt::WStandardItem * _item )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " model<signal>.itemChanged()"
      << "\n r:" << _item-> row()
      << "   c:" << _item-> column()
      << "\n d:" << Wt::asString( _item-> data( Wt::ItemDataRole::Display ) )
      << "\n t:" << Wt::asString( _item-> text() )
      << std::endl;

  });
#endif

} // endGCW::Eng::AccountRegisterModel::AccountRegisterModel( const std::string & _accountGuid )

auto
GCW::Eng::AccountRegisterModel::
setAccountGuid( const std::string & _accountGuid )-> void
{
  m_accountGuid = _accountGuid;
  refreshFromDisk();

} // endsetAccountGuid( const std::string & _accountGuid )-> void

auto
GCW::Eng::AccountRegisterModel::
setViewMode( ViewMode _viewMode )-> void
{
  m_viewMode = _viewMode;
}

auto
GCW::Eng::AccountRegisterModel::
setDoubleLine( bool _doubleLine )-> void
{
  m_doubleLine = _doubleLine;
}

auto
GCW::Eng::AccountRegisterModel::
isDeletable( const Wt::WModelIndex & _index )-> bool
{
  /*!
  ** If this transaction split has no guid
  **  then it's a new row, and cannot be deleted
  */
  if( getSplitGuid( _index ) == "" )
    return false;

  /*!
  ** If this transaction split is reconciled, then it is
  **  considered not deletable
  */
  GCW::Eng::Transaction::Manager transMan;
  transMan.loadSplit( getSplitGuid( _index ) );
  if( transMan.thisSplit()-> isReconciled() )
    return false;

  /*
  ** deletable
  */
  return true;

} // endisDeletable( const Wt::WModelIndex & _index )-> bool

auto
GCW::Eng::AccountRegisterModel::
isReadOnly()-> bool
{
  return m_readOnly;
}

auto
GCW::Eng::AccountRegisterModel::
isReadOnly( const Wt::WModelIndex & _index )-> bool
{
  if( isReadOnly() )
    return true;

  /*!
  ** If this transaction split has no guid
  **  then it's a new row, and can be edited
  */
  if( getSplitGuid( _index ) == "" )
    return false;

  /*!
  ** If this transaction split is reconciled, then it is
  **  considered not editable
  */
  GCW::Eng::Transaction::Manager transMan;
  transMan.loadSplit( getSplitGuid( _index ) );
  if( transMan.thisSplit()-> isReconciled() )
    return true;

  /*
  ** readOnly == false == editable
  */
  return false;

} // endReadOnly( const Wt::WModelIndex & _index )-> bool

auto
GCW::Eng::AccountRegisterModel::
isReadOnly( int _row )-> bool
{
  if( isReadOnly() )
    return true;

  return isReadOnly( index( _row, 0 ) );
}

auto
GCW::Eng::AccountRegisterModel::
saveToDisk()-> void
{
  std::cout << FUNCTION_HEADER << std::endl;

} // endsaveToDisk()

auto
GCW::Eng::AccountRegisterModel::
getString( const Wt::WModelIndex & _index, int column )-> std::string
{
  return
    Wt::asString                            // convert the index.data() to a WString
    (
     index( _index.row(), column )          // get the index of the ACTION column
     .data( Wt::ItemDataRole::Display )     // get the (string/display) data from it
    )
    .toUTF8();                              // convert the WString to a std::string
                                            //
} // endgetString( const Wt::WModelIndex & _index, int column )-> std::string

auto
GCW::Eng::AccountRegisterModel::
getDate( const Wt::WModelIndex & _index )-> Wt::WDateTime
{
  auto retVal =
    Wt::WDateTime::fromString             // convert the WString to a WDateTime
    (
      getString( _index, COL_DATE ),
      GCW_DATE_FORMAT_DISPLAY             // use this DATE format for the conversion
    );

  /*
  ** set the default time-component
  */
  retVal.setTime( GCW_DATE_DEFAULT_TIME );

  return retVal;

} // endgetDate( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Eng::AccountRegisterModel::
getAction( const Wt::WModelIndex & _index )-> std::string
{
  return getString( _index, COL_ACTION );

} // endgetDescription( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Eng::AccountRegisterModel::
getDescription( const Wt::WModelIndex & _index )-> std::string
{
  return getString( _index, COL_DESCRIPTION );

} // endgetDescription( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Eng::AccountRegisterModel::
getTransferText( const Wt::WModelIndex & _index )-> std::string
{
  return getString( _index, COL_TRANSFER );

} // endgetDescription( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Eng::AccountRegisterModel::
getTransferGuid( const Wt::WModelIndex & _index )-> std::string
{
  return
    GCW::Dbo::Accounts::byFullName( getTransferText( _index ) )-> guid();

} // endgetDescription( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Eng::AccountRegisterModel::
getReconcile( const Wt::WModelIndex & _index )-> std::string
{
  return getString( _index, COL_RECONCILE );

} // endgetDescription( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Eng::AccountRegisterModel::
getNumeric( const Wt::WModelIndex & _index )-> GCW_NUMERIC
{
  GCW_NUMERIC retVal( 0 );

  if( !_index.data( Wt::ItemDataRole::Display ).empty() )
    retVal = GCW_NUMERIC( Wt::asString( _index.data( Wt::ItemDataRole::Display ) ).toUTF8() );

  return retVal;

} // endgetNumeric( const Wt::WModelIndex & _index )-> GCW_NUMERIC

auto
GCW::Eng::AccountRegisterModel::
getDebit( const Wt::WModelIndex & _index )-> GCW_NUMERIC
{
  return
    getNumeric( index( _index.row(), COL_DEBIT ) );

} // endgetDebit( const Wt::WModelIndex & _index )-> GCW_NUMERIC

auto
GCW::Eng::AccountRegisterModel::
getCredit( const Wt::WModelIndex & _index )-> GCW_NUMERIC
{
  return
    getNumeric( index( _index.row(), COL_CREDIT ) );

} // endgetCredit( const Wt::WModelIndex & _index )-> GCW_NUMERIC

auto
GCW::Eng::AccountRegisterModel::
getValue( const Wt::WModelIndex & _index )-> GCW_NUMERIC
{
  GCW_NUMERIC retVal( 0 );

  // get both values so we can determine (+) or (-)
  auto debit  = getDebit(  _index );
  auto credit = getCredit( _index );
       retVal = debit - credit;

  return retVal;

} // endgetValue( const Wt::WModelIndex & _index )-> GCW_NUMERIC

auto
GCW::Eng::AccountRegisterModel::
getSplitGuid( const Wt::WModelIndex & _index )-> std::string
{
  return
    Wt::asString                           // convert the index.data() to a WString
    (
     index( _index.row(), COL_DATE )       // get the index of the DATE column
     .data( Wt::ItemDataRole::User )       // get the (string/User) data from it
    )
    .toUTF8();                             // convert the WString to a std::string

} // endgetSplitGuid( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Eng::AccountRegisterModel::
getSplitGuid( int _row )-> std::string
{
  return getSplitGuid( index( _row, COL_DATE ) );

} // endgetSplitGuid( int _row )-> std::string

auto
GCW::Eng::AccountRegisterModel::
saveToDisk( const Wt::WModelIndex & _index )-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): "
    << "\n row:" << _index.row()
    << "\n col:" << _index.column()
    << "\n gui:" << getSplitGuid( _index )
    << std::endl;
#endif

  /*
  ** Prepare to update everything
  */
  GCW::Eng::Transaction::Manager transMan;

  /*
  ** If we don't have a split guid, then this is a new row.  It also
  **  means we don't have a transaction, either.  So, build up a whole
  **  set of transaction-items that we'll be needing to set in these
  **  new values.
  */
  auto splitGuid = getSplitGuid( _index );
  if( splitGuid == "" )
  {
    /*
    ** Create a new transaction
    **
    */
    transMan.newTransaction( m_accountGuid, getTransferGuid( _index ) );

  } // endif( ..no split.. )

  /*
  ** We have a split item, so load up the transaction associated with it as
  **  well as the split-pair item, we will poke changes in to it accordingly below.
  */
  else
  {
    transMan.loadSplit( splitGuid );
  }

  /*
  ** write out the data that changed
  */
  switch( _index.column() )
  {
    case COL_DATE:
    {
      transMan.setDate( getDate( _index ) );
      break;
    }

    case COL_ACTION:
    {
      transMan.setAction( getAction( _index ) );
      break;
    }

    case COL_DESCRIPTION:
    {
      transMan.setDescription( getDescription( _index ) );
      break;
    }

    case COL_TRANSFER:
    {
      transMan.setTransferGuid( getTransferGuid( _index ) );
      break;
    }

    case COL_RECONCILE:
    {
      transMan.setReconcile( getReconcile( _index ) );
      break;
    }

    case COL_DEBIT:
    {
      transMan.setValue( getValue( _index ) );
      break;
    }

    case COL_CREDIT:
    {
      transMan.setValue( getValue( _index ) );
      break;
    }

#ifdef NEVER
    case COL_NOTES:
    {
      transMan.setNotes( getNotes( _index ) );
      break;
    }
#endif

  } // endswitch( index.column() )

} // endsaveToDisk( const Wt::WModelIndex & _index )-> void

auto
GCW::Eng::AccountRegisterModel::
setData( const Wt::WModelIndex & _index, const Wt::cpp17::any & _value, Wt::ItemDataRole _role )-> bool
{
  /*
  ** This is not an edit role - fast quit!
  */
  if( _role != Wt::ItemDataRole::Edit )
    return false;

  /*
  ** Nothing happening constitutes a success
  */
  bool retVal = true;

  /*
  ** This compare function compares two _any_ values
  */
  auto _valuesMatch = []( const Wt::cpp17::any & _any1, const Wt::cpp17::any & _any2 )
  {
    /*
    ** In any case, the two values must be of the same type.
    */
    if( _any1.type() == _any2.type() )
    {
#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
        << "\n " << typeid(Wt::WString).name()
        << "\n " << typeid(Wt::WString).hash_code()
        << "\n " << _any1.type().name()
        << "\n " << _any1.type().hash_code()
        << std::endl;
#endif

      if( typeid(std::string) == _any1.type() )
      {
        auto v1 = Wt::cpp17::any_cast< std::string >( _any1 );
        auto v2 = Wt::cpp17::any_cast< std::string >( _any2 );
        return v1 == v2;
      }

      else
      if( typeid(Wt::WString) == _any1.type() )
      {
        auto v1 = Wt::cpp17::any_cast< Wt::WString >( _any1 );
        auto v2 = Wt::cpp17::any_cast< Wt::WString >( _any2 );
        return v1 == v2;
      }

      else
      if( typeid(int) == _any1.type() )
      {
        auto v1 = Wt::cpp17::any_cast< int >( _any1 );
        auto v2 = Wt::cpp17::any_cast< int >( _any2 );
        return v1 == v2;
      }

      else
      if( typeid(Wt::WDate) == _any1.type() )
      {
        auto v1 = Wt::cpp17::any_cast< Wt::WDate >( _any1 );
        auto v2 = Wt::cpp17::any_cast< Wt::WDate >( _any2 );
        return v1 == v2;
      }

      else
      if( typeid(Wt::WDateTime) == _any1.type() )
      {
        auto v1 = Wt::cpp17::any_cast< Wt::WDateTime >( _any1 );
        auto v2 = Wt::cpp17::any_cast< Wt::WDateTime >( _any2 );
        return v1 == v2;
      }

      else
      {
        std::cout << __FILE__ << ":" << __LINE__
          << " unhandled type " << _any1.type().name()
          << std::endl;
      }

    } // endif( _any1.type() == _any2.type() )

    /*
    ** not a match!
    */
    return false;

  }; // endauto _valuesMatch = []( const Wt::cpp17::any & _any1, const Wt::cpp17::any & _any2 )

  /*
  ** Only updating if the data actually changed
  */
  if( !_valuesMatch( _index.data( _role ), _value ) )
  {
#ifdef NEVER
    std::cout << BREAKHEADER
      << "\n row:" << _index.row()
      << "\n col:" << _index.column()
      << "\n cur:" << Wt::asString( _index.data( _role ) )
      << "\n new:" << Wt::asString( _value )
      << std::endl;
#endif

    /*
    ** saving to the model causes _index to be updated with the new value
    */
    retVal = Wt::WStandardItemModel::setData( _index, _value, _role );

//    saveToDisk( _index );

//    m_dirtyRows.insert( _index.row() );

//    m_goneDirty.emit( _index );

//    dataChanged().emit( index( _index.row(), COL_DATE ), index( _index.row(), COL_BALANCE ) );

#ifdef NEVER
    std::cout << BREAKFOOTER
      << std::endl;
#endif

  } // endif( !_valuesMatch( _index.data( _role ), _value ) )

  /*
  ** Return success fail
  */
  return retVal;

} // endsetData( const Wt::WModelIndex & _index, const Wt::cpp17::any & _value, Wt::ItemDataRole _role )-> bool

/*!
** \brief Refresh From Disk
**
** This procedure reads from the gnucash storage source
**  (either postgres or sqlite) and loads all of the
**  transactions and their associated splits in to the
**  model suitable for editing within an automatic
**  table view.
*/
auto
GCW::Eng::AccountRegisterModel::
refreshFromDisk()-> void
{
  if( m_accountGuid == "" )
    return;

  /*
  ** Signal the model is about to be reset.
  */
  layoutAboutToBeChanged().emit();

  /*!
  ** \par Model Columns
  ** \code
  **   col  name                  notes
  **  -----+---------------------+----------------------
  **    0   date
  **    1   num (check number)
  **    2   description
  **    3   account / transfer
  **    4   reconciliation
  **    5   debit
  **    6   credit
  **    7   balance r/o (computed)
  ** \endcode
  */
  auto _addColumn = [&]( RowItem & columns, auto _value )
  {
    auto item = std::make_unique< Wt::WStandardItem >( _value );

    item-> setToolTip( _value );

    auto retVal = item.get();
    columns.push_back( std::move( item ) );
    return retVal;
  };

  /*!
  ** Before refreshing from disk, the entire contents of the
  **  model are cleared, so it is important to make sure anything
  **  to be saved from the model should be done first.
  */
  clear();

  /*
  ** Get the prefrence item that can inform us about prefrences
  **  to be applied to this model.
  */
  auto prefrenceItem = GCW::Dbo::Prefrences::get();

  /*
  ** Get an account item loaded.  This is the account that _is_ this
  **  register.
  */
  auto registerAccountItem = GCW::Dbo::Accounts::byGuid( m_accountGuid );

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " guid:" << registerAccountItem-> guid()
    << " name:" << registerAccountItem-> name()
    << " dbcr:" << static_cast<int>( registerAccountItem-> accountDrCr() )
    << " type:" << static_cast<int>( registerAccountItem-> accountType() )
    << " typn:" << registerAccountItem-> accountTypeName()
    << std::endl;
#endif

  /*!
  ** In order to produce a proper 'register' of items, it is important
  **  to load the data from the 'splits' side of the transaction rather
  **  than the transaction itself.
  **
  ** Note that when the splits are loaded based on the account ID, they
  **  are returned in a std::vector(sorted_by_date) that is sorted based on
  **  the transction date.  This chosen sort method insures that the
  **  running balance can be accurately calculated on the fly, since each
  **  item is pulled from the vector in a sorted order, and the running
  **  balance is included in the model row.  The user can sort the user
  **  interface later and still have the line-item-balance remain accurate.
  */
  auto splitItems = GCW::Dbo::Splits::byAccount( m_accountGuid );

  /*!
  ** Each item is processed from the vector in sequential order.
  **  In this process we grab the contents of the split, and
  **  generate a model item row containing all of the column values.
  **  Maintain a running balance as we go along to keep the balance
  **  reflected within the view.  The result is a multi-column row
  **  item that is added to the model.  This allows the model to be
  **  subsequently re-sorted or subset-extracted without affecting
  **  the running balances and so forth.
  */
  GCW_NUMERIC runningBalance( 0 );
  for( auto splitItem : splitItems )
  {
    /*
    ** Start out read-only == true.  We want to default read-only
    **  and upgrade to read-write if the dataset calls for it.
    **
    */
    bool readOnly = true;

    /*!
    ** From the initial split item, we get a handle on the transaction,
    **  and then load all of the other splits associated with this
    **  transaction.
    */
    auto transactionItem   = GCW::Dbo::Transactions ::byGuid        ( splitItem-> tx_guid () );
    auto transactionSplits = GCW::Dbo::Splits       ::bySplitExcept ( splitItem-> guid    () );

    /*
    ** BUGBUG: Depending on the condition of the database, in the odd chance that something
    **  has gone corrupted, this will more-or-less mask the issue, by simply
    **  stepping over this split that appears to be in bad shape.  Ideally we need
    **  to generate some sort of report at this point, but for now we'll just step
    **  over it.
    */
    if( !transactionItem )
      continue;

    /*
    ** The first row comprises all of the basic account register information, such
    **  as the transaction date, and target account and amounts and so forth.  It is
    **  the first line in the basic one-line ledger.
    */
    auto _append1stRow = [&]()
    {
      /*
      ** Prepare a row of columns.
      **
      ** Values of the transaction appear either in the Debit column (positive-Left)
      **  or in the Credit column (negative-Right) depending on if they are positive
      **  or negative.  The 'decimal.h' library is used to perform the
      **  arithmetic to prevent the floating point math problems.
      **
      ** The balance on the transaction is computed on-the-fly, which
      **  makes clear the importance of having the initial vector of splits
      **  to appear in the correct chronological order.  It also makes clear that
      **  if the 'view' is re-sorted on anything other than the date column, the
      **  balance column will ~not~ be recomputed.
      */
      RowItem columns;
      ColItem post_date   = nullptr;
      ColItem num         = nullptr;
      ColItem description = nullptr;
      ColItem account     = nullptr;
      ColItem reconcile   = nullptr;
      ColItem debit       = nullptr;
      ColItem credit      = nullptr;
      ColItem balance     = nullptr; // (computed on-the-fly)

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
      auto tip =
        Wt::WString
        (
         "row: {1}\n"
         "acg: {2}\n"
         "spg: {3}\n"
        )
        .arg( rowCount()         )
        .arg( m_accountGuid      )
        .arg( splitItem-> guid() )
        ;

      post_date = _addColumn( columns, "" );
      post_date-> setData( transactionItem-> post_date_as_date(), Wt::ItemDataRole::Edit );
      post_date-> setData( splitItem-> guid(), Wt::ItemDataRole::User );
      post_date-> setData( splitItem , Wt::ItemDataRole::User + 1 );
      post_date-> setToolTip( tip );

      /*!
      ** The 'num' column is a simple text-column.
      */
      num = _addColumn( columns, transactionItem-> num() );

      /*!
      ** The 'description' column is a simple text-column.
      */
      description = _addColumn( columns, transactionItem-> description() );

      /*!
      ** The 'account' text depends on the
      **  target account defined in the split.  There are three
      **  possibilities here;
      **
      **   -# no splits... this shows up as an <b>'imbalance'</b> (this is an error condition)
      **   -# 1 split...   this just shows the split account on the same single line
      **   -# >1 split...  this is more than one target account, so just indicate 'split'
      */
      switch( transactionSplits.size() )
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
          account = _addColumn( columns, TR("gcw.AccountRegister.account.imbalanceUSD") ); // account
          account-> setStyleClass( "errval" );
          account-> setToolTip( TR("gcw.AccountRegister.account.imbalanceUSD.toolTip") );
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
          auto txSplitItem      = *transactionSplits.begin();
          auto splitAccountItem = GCW::Dbo::Accounts::byGuid( txSplitItem-> account_guid() );

          // yes, we have one account item
          if( splitAccountItem )
          {
            account = _addColumn( columns, GCW::Dbo::Accounts::fullName( splitAccountItem-> guid() ) );

            auto tip =
              Wt::WString
              (
               "spa:{1}\n"
               "txi:{2}\n"
              )
              .arg( splitAccountItem-> guid() )
              .arg( txSplitItem-> guid() )
              ;
            account-> setToolTip( tip );
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
            account = _addColumn( columns, TR("gcw.AccountRegister.account.imbalanceUSD") );
            account-> setStyleClass( "errval" );

            auto toolTip =
              Wt::WString("target guid:{1}\n{2}")
              .arg( txSplitItem-> account_guid() )
              .arg( TR("gcw.AccountRegister.account.invalidTarget.toolTip") )
              .toUTF8()
              ;

            account-> setToolTip( toolTip );

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
          account = _addColumn( columns, TR("gcw.AccountRegister.account.multisplit") ); // account
        }

      } // endswitch( transactionSplits.size() )

      /*!
      ** The reconcile column is a simple text-column.
      */
      reconcile = _addColumn( columns, splitItem-> reconcile_state() ); // Reconciled

      /*!
      ** \par Balance Computation Notes
      **
      **  There are two 'types' of accounts; Debit/Credit.  Gnucash
      **   stores split information as a single value that is positive
      **   or negative.  If the value is positive, then it is posted
      **   to the debit (left) column.  If the value is negative, it
      **   is posted to credit (right) column.
      **
      **  Depending on the account type (debit/credit), that value is
      **   then either 'added' or 'subtracted' from the account balance.
      **   If this is a 'credit' account, then the value is subtracted,
      **   and if it is a debit account, the value is added.
      **
      **  Therefore, if this is a credit account, such as a credit card,
      **   then a 'positive' value, posted to the debit column, would
      **   'decrease' the balance in that account.  Therefore, the value,
      **   being positive, is 'subtracted' from the running balance.  If
      **   the value were negative, it would be posted to the credit
      **   column, and again would be 'subtracted' from the running
      **   balance, and a negative value being subtracted from a value
      **   causes the result to 'increase'.
      **
      **  If this is a debit account, such as a bank checking account, a
      **   'positive' value, posted to the debit column (again), would
      **   'increase' the balance in that account.
      **
      **  So, that's the funky GAAP math done here.
      **
      ** What follows is a pretty good explanation of the debit/credit
      **  stuff;
      **
      **  >>>>>>>>>>>>>>>
      **  Debit/Credit is just Left/Right.
      **  Maybe this will help
      **
      ** \par The Accounting Equation:
      ** \code
      **  Assets - Liabilities = Equity
      ** \endcode
      **
      ** \par let's make all terms 'positive'
      ** \code
      **  Assets = Liabilities + Equity
      ** \endcode
      **
      ** \par now, we'll split off a subset of Equity
      ** \code
      **  Assets = Liabilities + Equity + Retained Earnings
      ** \endcode
      **
      ** \par now, we'll substitute temporary accounts for Retained Earnings)
      ** \code
      **  Assets = Liabilities + Equity + (Income - Expenses)
      ** \endcode
      **
      **      (now, we'll once again, make all terms 'positive')
      **  Assets + Expenses = Liabilities + Equity + Income
      **
      **  And there, you have the full Accounting Equation with the five major account types that GnuCash uses.
      **
      **  In double-entry accounting, ALL transactions are in the form of:
      **  Debit = Credit
      **  Left = Right
      **
      **  The 'Debit' accounts (those that are normally (positive) a Debit balance, and increase with a Debit, decrease with a Credit) are on the left of the equation:
      **  Assets
      **  Expenses
      **
      **  The 'Credit' accounts (those that are normally (positive) a Credit balance, and increase with a Credit, decrease with a Debit) are those on the right of the equation:
      **  Liabilities
      **  Equity
      **  Income
      **
      **  A negative balance in any account would indicate either an entry error or a contra-balance situation. (rare for individuals)
      **
      **  You can move funds from the left to the right, or vice versa, or between any accounts or types on the same side of the equation. (I will use the abbreviations Dr. and Cr. here)
      **  Most texts will write transactions Debit first, then Credit as shown below. The amounts are not shown, because they *must* be equal.
      **
      ** \par Example Left to Right - Asset to Liability (paying down a debt)
      ** \code
      **  Dr. Liabilities:Loan
      **    Cr. Assets:Cash
      **  result: decreased Loan owed, decreased Cash on hand, Assets decreased, Liabilities decreased - equation still in balance
      ** \endcode
      **
      ** \par Example Right to Left - Income to Asset (receipt of income)
      ** \code
      **  Dr. Assets:Cash
      **    Cr. Income:Salary
      **  result: increased Cash on hand, increased Salary earned, Assets increased, Income increased - equation still in balance
      ** \endcode
      **
      ** \par  Example Left to Left(same type) - Asset to Asset (buying land outright)
      ** \code
      **  Dr. Assets:Land
      **    Cr. Assets:Cash
      **  result: increased Land owned, decreased Cash on hand, Assets shifted - equation still in balance
      ** \endcode
      **
      ** \par  Example Left to Left(different type) - Asset to Expense (buying groceries)
      ** \code
      **  Dr. Expenses:Food
      **    Cr. Assets:Cash
      **  result: increased Food expense, decreased Cash on hand, Expenses increased, Assets decreased - equation still in balance
      ** \endcode
      **
      ** \par  Example Right to Right(same type) - Liability to Liability (paying down a loan with a credit card)
      ** \code
      **  Dr. Liabilities:Loan
      **    Cr. Liabilities:Credit Card
      **  result: decreased Loan owed, increased Credit Card owed, Liabilities shifted - equation still in balance
      ** \endcode
      **
      ** \par  Example Right to Right(different type) - Equity to Liability (recognition of dividends to be paid - business transaction)
      ** \code
      **  Dr. Equity:Retained Earnings
      **    Cr. Liabilities:Dividends Payable
      **  result: decreased Retained Earnings, increased Dividends owed to shareholders, Equity decreased, Liability increased - equation remains in balance.
      ** \endcode
      **
      **  *it is rare and unusual for an individual to shift Equity to Liabilities and vice versa. Forgiveness of Debt may in some jurisdictions be a transfer from Liabilities to Income.
      **
      ** \par Original Post
      ** \ref https://lists.gnucash.org/pipermail/gnucash-user/2023-October/109219.html
      ** \par Accounting Basics
      ** \ref https://www.gnucash.org/docs/v5/C/gnucash-guide/basics-accounting1.html
      **  >>>>>>>>>>>>>>>
      */
      bool invert = false;
      switch( prefrenceItem.reverseBalanceAccounts() )
      {
        case GCW::Dbo::Prefrences::ReverseBalanceAccounts::INCOME_EXPENSE:
        {
#ifdef NO_DRCR_YET
          if( registerAccountItem-> accountType() == GCW::Dbo::Account::Type::INCOME
           || registerAccountItem-> accountType() == GCW::Dbo::Account::Type::EXPENSE
            )
          {
            invert = true; // math inverted
          }
#endif
          break;
        }

        case GCW::Dbo::Prefrences::ReverseBalanceAccounts::CREDIT:
        {
#ifdef NO_DRCR_YET
          if( registerAccountItem-> accountDrCr() == GCW::Dbo::Account::DrCr::CREDIT )
          {
            invert = true; // math inverted
          }
#endif
          break;
        }

      } // endswitch( prefrenceItem.reverseBalanceAccounts() )

      /*
      ** Compute the running balance.
      */
      runningBalance += splitItem-> value( invert );

      /*!
      ** \todo Add up the static running accumulators
      **
      */
      m_present += splitItem-> value( invert );
      //    m_future     ;
      //    m_cleared    ;
      //    m_reconciled ;
      //    m_projected  ;

      /*
      ** if the value is positive, we post it to the debit (left) column.
      */
      if( splitItem-> value() > 0 )
      {
        debit  = _addColumn( columns, splitItem-> valueAsString() );
        credit = _addColumn( columns, "" );

        /// \bug may not need to store GCW_NUMERIC on the AccountRegisterModel items.  it is redundant and we're not using the values and updates from the delegates don't update these values.
        debit -> setData( splitItem-> value(), Wt::ItemDataRole::User );
        credit-> setData( GCW_NUMERIC(0)     , Wt::ItemDataRole::User );
      }

      /*
      ** if the value is negative, we post it to the credit (right) column.
      **  however, we invert the value in this column, so that it does not
      **  carry the (-) leading minus sign... all the numbers we enter are
      **  positive... only the 'balance' column can show negative numbers.
      */
      else
      if( splitItem-> value() < 0 )
      {
        debit  = _addColumn( columns, "" );
        credit = _addColumn( columns, splitItem-> valueAsString(true) );

        debit -> setData( GCW_NUMERIC(0)     , Wt::ItemDataRole::User );
        credit-> setData( splitItem-> value(), Wt::ItemDataRole::User );
      }

      /*
      ** if the value is zero, we make sure both columns are blank.
      */
      else
      if( splitItem-> value() == 0 )
      {
        debit  = _addColumn( columns, "" );
        credit = _addColumn( columns, "" );

        debit -> setData( GCW_NUMERIC(0), Wt::ItemDataRole::User );
        credit-> setData( GCW_NUMERIC(0), Wt::ItemDataRole::User );
      }

      /*
      ** Poke the balance in
      */
      balance =
        _addColumn
        (
         columns,
         Wt::WString( "{1}" )
         .arg( toString( runningBalance, GCW::Cfg::decimal_format() ) )
        );
      balance-> setData( runningBalance, Wt::ItemDataRole::User );

      /*
      ** If the balance hit negative, highlight the number with a bit
      **  of bad-news-red.
      */
      if( runningBalance < 0 )
      {
        if( prefrenceItem.accountRegisterHighlight( GCW::Dbo::Prefrences::AccountRegisterHighlight::NEGVAL_EXTRA ) )
        {
          post_date   -> setStyleClass( "negval" );
          num         -> setStyleClass( "negval" );
          description -> setStyleClass( "negval" );
          account     -> setStyleClass( "negval" );
          reconcile   -> setStyleClass( "negval" );
          debit       -> setStyleClass( "negval" );
          credit      -> setStyleClass( "negval" );
        }

        if( prefrenceItem.accountRegisterHighlight( GCW::Dbo::Prefrences::AccountRegisterHighlight::NORMAL ) )
        {
          balance     -> setStyleClass( "negval" );
        }
      }

      /*
      ** If this model is editable, then check the reconciliation
      **  state.  If the split has already been reconciled then
      **  we really don't want the user messing around with it.
      */
      if( !m_readOnly )
      {
        if( splitItem-> reconcile_state() == GCW_RECONCILE_YES )
        {
          readOnly = true;
        }
        else
        {
          readOnly = false;
        }
      }

      /*
      ** If this item can be edited then unlock everything.
      **
      ** TODO: note, it would be possible here to do things
      **        like, if the transaction has been reconciled,
      **        allow for the description to be edited, but
      **        perhaps not the date or amounts... that could
      **        be handy.
      */
      post_date   -> setFlags( readOnly? Wt::ItemFlag::Selectable : Wt::ItemFlag::Editable );
      num         -> setFlags( readOnly? Wt::ItemFlag::Selectable : Wt::ItemFlag::Editable );
      description -> setFlags( readOnly? Wt::ItemFlag::Selectable : Wt::ItemFlag::Editable );
      account     -> setFlags( readOnly? Wt::ItemFlag::Selectable : Wt::ItemFlag::Editable );
      reconcile   -> setFlags( readOnly? Wt::ItemFlag::Selectable : Wt::ItemFlag::Editable );
      debit       -> setFlags( readOnly? Wt::ItemFlag::Selectable : Wt::ItemFlag::Editable );
      credit      -> setFlags( readOnly? Wt::ItemFlag::Selectable : Wt::ItemFlag::Editable );
      balance     -> setFlags( readOnly? Wt::ItemFlag::Selectable : Wt::ItemFlag::Editable );

      /*
      ** Add the row to the model
      */
      appendRow( std::move( columns ) );

    }; // endauto _append1stRow = [&]()

    /*
    ** The second row represents the second line in a "double-line" view
    **  of the ledger.
    */
    auto _append2ndRow = [&]()
    {
      /*
      ** Prepare a row of columns.
      */
      RowItem columns;

      /*!
      ** Load everything blank (except for the memo)
      */
                  _addColumn( columns, ""                 ); // date
                  _addColumn( columns, ""                 ); // action
      auto memo = _addColumn( columns, splitItem-> memo() );
                  _addColumn( columns, ""                 ); // account
                  _addColumn( columns, ""                 ); // reconcile
                  _addColumn( columns, ""                 ); // debit
                  _addColumn( columns, ""                 ); // credit
                  _addColumn( columns, ""                 ); // balance

      /*
      ** If this item can be edited then unlock everything.
      */
      if( readOnly )
      {
        memo -> setFlags( Wt::ItemFlag::Editable );
      }

      /*
      ** Add the row to the model
      */
      appendRow( std::move( columns ) );

    }; // endauto _append2ndRow = [&]()

    _append1stRow();

    if( doubleLine() )
      _append2ndRow();

  } // endfor( auto splitItem : splitItems )

  /*!
  ** After all the split items are loaded, an additional ~blank~ item
  **  is included at the end of the vector, for coding new entries.
  */
  if( !isReadOnly() )
  {
    /*
    ** Create a row with blank values
    */
    RowItem columns;
    auto post_date = _addColumn( columns, "" );                             // Date
         post_date-> setData( m_lastDate, Wt::ItemDataRole::Edit );
         post_date-> setFlags( Wt::ItemFlag::Editable );

    _addColumn( columns, ""         )-> setFlags( Wt::ItemFlag::Editable ); // Num
    _addColumn( columns, ""         )-> setFlags( Wt::ItemFlag::Editable ); // Memo
    _addColumn( columns, ""         )-> setFlags( Wt::ItemFlag::Editable ); // Account
    _addColumn( columns, "n"        )-> setFlags( Wt::ItemFlag::Editable ); // R
    _addColumn( columns, ""         )-> setFlags( Wt::ItemFlag::Editable ); // Deposit
    _addColumn( columns, ""         )-> setFlags( Wt::ItemFlag::Editable ); // Withdrawal
    _addColumn( columns, ""         )-> setFlags( Wt::ItemFlag::Editable ); // Balance
    appendRow( std::move( columns ) )                                     ;

  } // endif( m_editable )

  /*!
  ** poke all the header labels in.  Note that some of the labels change
  **  depending on the account debit/credit type.  We get those from the
  **  accountDef.
  **
  ** \bug Needs work
  **   this is modified a bit to allow for a default account def.
  **    this is necessary since it is possible to ask for an account
  **    register that is not (yet) associated to an account... this
  **    can happen in the BillPay module when setting up a new
  **    account for bill-pay functions. (kind of sloppy doing it here)
  **    The first item at(0) represents the default-register settings,
  **    suitable for any register view.
  */
  GCW::Dbo::Accounts::AccountDef_t accountDef = GCW::Dbo::Accounts::s_accountDefs.at(0);
#ifdef NO_DRCR_YET
  if( registerAccountItem )
    accountDef = registerAccountItem-> accountDef();
#endif

  /*!
  ** \anchor account_type_labels
  */
  int col = 0;
  setHeaderData( col++, TR( "gcw.AccountRegister.column.date"                     ) );
  setHeaderData( col++, TR( "gcw.AccountRegister.column.num"                      ) );
  setHeaderData( col++, TR( "gcw.AccountRegister.column.memo"                     ) );
  setHeaderData( col++, TR( "gcw.AccountRegister.column." + accountDef.colAccount ) );
  setHeaderData( col++, TR( "gcw.AccountRegister.column.reconcile"                ) );
  setHeaderData( col++, TR( "gcw.AccountRegister.column." + accountDef.colDr      ) );
  setHeaderData( col++, TR( "gcw.AccountRegister.column." + accountDef.colCr      ) );
  setHeaderData( col++, TR( "gcw.AccountRegister.column.balance"                  ) );

  /*
  ** Let the rest of the world know the model changed.
  */
  layoutChanged().emit();

} // endrefreshFromDisk()-> void

auto
GCW::Eng::AccountRegisterModel::
makeRow( const std::string & _splitGuid )-> GCW::Eng::AccountRegisterModel::RowItem
{
  RowItem rowItem;

  return rowItem;

} // endmakeRow( const std::string & _splitGuid )-> GCW::Eng::AccountRegisterModel::RowItem

auto
GCW::Eng::AccountRegisterModel::
suggestionsFromColumn( int _column ) const-> std::set< std::string >
{
  /*
  ** First, make a set of unique values.
  */
  std::set< std::string > retVal;
  for( int row=0; row< rowCount(); row++ )
    retVal.insert( Wt::asString( item( row, _column )-> text() ).toUTF8() );

  return retVal;

} // endsuggestionsFromColumn( int _column ) const-> std::set< std::string >


