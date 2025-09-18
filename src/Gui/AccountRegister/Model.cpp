#line 2 "src/Gui/AccountRegister/Model.cpp"

#include <chrono>

#include "../Glb/gcwglobal.h"
#include "../Dbo/SessionGnuCash.h"
#include "../Dbo/Splits/Splits.h"
#include "../Dbo/Prefrences.h"
#include "../Dbo/Vars/Vars.h"
#include "../Glb/Core.h"
#include "../Eng/TransactionManager.h"
#include "Model.h"

GCW::Gui::AccountRegister::Model::
Model()
: Wt::WStandardItemModel( 0, 8 ) // 8-columns
{
  /*
  ** these are here for testing, so we can quickly enable the view and putz around on it
  */
//  m_viewMode = ViewMode::BASIC_LEDGER        ; // (default)
//  m_viewMode = ViewMode::AUTOSPLIT_LEDGER    ;
//  m_viewMode = ViewMode::TRANSACTION_JOURNAL ;
//  m_viewMode = ViewMode::GENERAL_JOURNAL     ;
//  m_doubleLine = true ;

  /*
  ** set the lastDate to match the todays date, so when first
  **  opening the register, the date is automatically set.
  */
  m_lastDate = Wt::WDateTime::currentDateTime();
  m_lastDate.setTime( GCW_DATE_DEFAULT_TIME );

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

} // endGCW::Gui::AccountRegisterModel::AccountRegisterModel( const std::string & _accountGuid )

auto
GCW::Gui::AccountRegister::Model::
setAccountGuid( const std::string & _accountGuid )-> void
{
  m_accountGuid = _accountGuid;
  refreshFromDisk();

} // endsetAccountGuid( const std::string & _accountGuid )-> void

auto
GCW::Gui::AccountRegister::Model::
setViewMode( ViewMode _viewMode )-> void
{
  m_viewMode = _viewMode;
  refreshFromDisk();

} // endsetViewMode( ViewMode _viewMode )-> void

auto
GCW::Gui::AccountRegister::Model::
setDoubleLine( bool _doubleLine )-> void
{
  m_doubleLine = _doubleLine;
  refreshFromDisk();

} // endsetDoubleLine( bool _doubleLine )-> void

auto
GCW::Gui::AccountRegister::Model::
splitCount()-> int
{
  return m_splitCount;

} // endsplitCount()-> int

auto
GCW::Gui::AccountRegister::Model::
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
  auto split = Dbo::Splits::byGuid( getSplitGuid( _index ) );
  if( split-> isReconciled() )
    return false;

  /*
  ** deletable
  */
  return true;

} // endisDeletable( const Wt::WModelIndex & _index )-> bool

auto
GCW::Gui::AccountRegister::Model::
isJumpable( const Wt::WModelIndex & _index )-> bool
{
  /*!
  ** If this transaction split has no guid
  **  then it's a new row, and cannot be jumped
  */
  if( getSplitGuid( _index ) == "" )
    return false;

  // BUGBUG: use transman here to get the other split
  /*!
  ** Need to have another split to be jumpable
  */
//  auto splits = Dbo::Splits::bySplitExcept( getSplitGuid( _index ) );
//  if( 
//  if( !split || split-> guid() == "" )
//    return false;

  /*
  ** jumpable
  */
  return true;

} // endisJumpable( const Wt::WModelIndex & _index )-> bool

auto
GCW::Gui::AccountRegister::Model::
isReadOnly()-> bool
{
  return m_readOnly;
}

auto
GCW::Gui::AccountRegister::Model::
isReadOnly( const Wt::WModelIndex & _index )-> bool
{
  /*
  ** if the whole model is read/only, return it
  */
  if( isReadOnly() )
    return true;

  /*
  ** if the index isn't valid, we are read/only
  */
  if( !_index.isValid() )
    return true;

  /*!
  ** If this transaction split has no guid
  **  then it's a new row, and can be edited
  */
  if( getSplitGuid( _index ) == "" )
    return false;

  /*!
  ** If this transaction split is reconciled, then it is
  **  considered not editable.
  **
  ** We have to convert this _index in to the proper split
  **  that represents it, and then query that split to see
  **  if it is reconciled or not.  We use the transaction
  **  manager to get this done, as it encapsulates a bunch
  **  of different tools for manipulating the data.
  */
//  GCW::Gui::Transaction::Manager transMan( Dbo::Splits::byGuid( getSplitGuid( _index ) ) );
//  if( transMan.thisSplit()-> isReconciled() )
//    return true;

  /*
  ** readOnly == false == editable
  */
  return false;

} // endReadOnly( const Wt::WModelIndex & _index )-> bool

auto
GCW::Gui::AccountRegister::Model::
isReadOnly( int _row )-> bool
{
  return
    isReadOnly( index( _row, 0 ) );
}

auto
GCW::Gui::AccountRegister::Model::
saveToDisk()-> void
{
  std::cout << FUNCTION_HEADER << " ~not implemented~ " << std::endl;

} // endsaveToDisk()

auto
GCW::Gui::AccountRegister::Model::
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
GCW::Gui::AccountRegister::Model::
getDate( const Wt::WModelIndex & _index )-> Wt::WDateTime
{
  auto retVal =
    Wt::WDateTime::fromString             // convert the WString to a WDateTime
    (
      getString( _index, asInt( Col::DATE ) ),
      GCW_DATE_FORMAT_DISPLAY             // use this DATE format for the conversion
    );

  /*
  ** set the default time-component
  */
  retVal.setTime( GCW_DATE_DEFAULT_TIME );

  return retVal;

} // endgetDate( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Gui::AccountRegister::Model::
getAction( const Wt::WModelIndex & _index )-> std::string
{
  return getString( _index, asInt( Col::ACTION ) );

} // endgetAction( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Gui::AccountRegister::Model::
getDescription( const Wt::WModelIndex & _index )-> std::string
{
  return getString( _index, asInt( Col::DESCRIPTION ) );

} // endgetDescription( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Gui::AccountRegister::Model::
getTransferText( const Wt::WModelIndex & _index )-> std::string
{
  return getString( _index, asInt( Col::TRANSFER ) );

} // endgetTransferText( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Gui::AccountRegister::Model::
getTransferGuid( const Wt::WModelIndex & _index )-> std::string
{
  return
    GCW::Dbo::Accounts::byFullName( getTransferText( _index ) )-> guid();

} // endgetTransferGuid( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Gui::AccountRegister::Model::
getReconcile( const Wt::WModelIndex & _index )-> std::string
{
  return getString( _index, asInt( Col::RECONCILE ) );

} // endgetReconcile( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Gui::AccountRegister::Model::
getNumeric( const Wt::WModelIndex & _index )-> GCW_NUMERIC
{
  GCW_NUMERIC retVal( 0 );

  if( !_index.data( Wt::ItemDataRole::Display ).empty() )
    retVal = GCW_NUMERIC( Wt::asString( _index.data( Wt::ItemDataRole::Display ) ).toUTF8() );

  return retVal;

} // endgetNumeric( const Wt::WModelIndex & _index )-> GCW_NUMERIC

auto
GCW::Gui::AccountRegister::Model::
getDebit( const Wt::WModelIndex & _index )-> GCW_NUMERIC
{
  return
    getNumeric( index( _index.row(), asInt( Col::DEBIT ) ) );

} // endgetDebit( const Wt::WModelIndex & _index )-> GCW_NUMERIC

auto
GCW::Gui::AccountRegister::Model::
getCredit( const Wt::WModelIndex & _index )-> GCW_NUMERIC
{
  return
    getNumeric( index( _index.row(), asInt( Col::CREDIT ) ) );

} // endgetCredit( const Wt::WModelIndex & _index )-> GCW_NUMERIC

auto
GCW::Gui::AccountRegister::Model::
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
GCW::Gui::AccountRegister::Model::
getSplitGuid( const Wt::WModelIndex & _index )-> std::string
{
  return
    Wt::asString                           // convert the index.data() to a WString
    (
     index( _index.row(), asInt( Col::DATE ) )       // get the index of the DATE column
     .data( Wt::ItemDataRole::User )       // get the (string/User) data from it
    )
    .toUTF8();                             // convert the WString to a std::string

} // endgetSplitGuid( const Wt::WModelIndex & _index )-> std::string

auto
GCW::Gui::AccountRegister::Model::
getSplitGuid( int _row )-> std::string
{
  return getSplitGuid( index( _row, asInt( Col::DATE ) ) );

} // endgetSplitGuid( int _row )-> std::string


auto
GCW::Gui::AccountRegister::Model::
getSplitRow( const std::string & _guid )-> int
{
  for( int row = 0; row< rowCount(); row++ )
    if( getSplitGuid( row ) == _guid )
      return row;

  return -1;

} // endgetSplitRow( const std::string & _guid )-> int


auto
GCW::Gui::AccountRegister::Model::
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
  GCW::Eng::Transaction::Manager transMan( this );

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
    case asInt( Col::DATE ):
    {
      transMan.setDate( getDate( _index ) );
      break;
    }

    case asInt( Col::ACTION ):
    {
      transMan.setAction( getAction( _index ) );
      break;
    }

    case asInt( Col::DESCRIPTION ):
    {
      transMan.setDescription( getDescription( _index ) );
      break;
    }

    case asInt( Col::TRANSFER ):
    {
      transMan.setTransferGuid( getTransferGuid( _index ) );
      break;
    }

    case asInt( Col::RECONCILE ):
    {
      transMan.setReconcile( getReconcile( _index ) );
      break;
    }

    case asInt( Col::DEBIT ):
    {
      transMan.setValue( getValue( _index ) );
      break;
    }

    case asInt( Col::CREDIT ):
    {
      transMan.setValue( getValue( _index ) );
      break;
    }

#ifdef NEVER
    case asInt( Col::NOTES ):
    {
      transMan.setNotes( getNotes( _index ) );
      break;
    }
#endif

  } // endswitch( index.column() )

} // endsaveToDisk( const Wt::WModelIndex & _index )-> void

auto
GCW::Gui::AccountRegister::Model::
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
#ifdef NO_NOISE
        std::cout << __FILE__ << ":" << __LINE__ << " setData:_valuesMatch"
          << " unhandled type " << _any1.type().name()
          << std::endl;
#endif
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
** This procedure reads from the gnucash storage source (either postgres or sqlite) and loads all of the
**  transactions and their associated splits in to the model suitable for editing within an automatic
**  table view.
*/
auto
GCW::Gui::AccountRegister::Model::
refreshFromDisk()-> void
{
  const auto start = std::chrono::system_clock::now();

  /*
  ** this gets recomputed below
  */
  m_splitCount = 0;

  /*
  ** can't without an account
  */
  if( m_accountGuid == "" )
    return;

  /*
  ** Signal the model is about to be reset.
  */
  layoutAboutToBeChanged().emit();

  /*!
  ** Before refreshing from disk, the entire contents of the
  **  model are cleared, so it is important to make sure anything
  **  to be saved from the model is done first.
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

  /*
  ** use a transaction manager for accessing everything
  */
  GCW::Eng::Transaction::Manager transMan( this );

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

  /*
  ** remember the split count
  */
  m_splitCount = splitItems.size();

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
  m_balance = GCW_NUMERIC( 0 );
  for( auto splitItem : splitItems )
  {
    transMan.setSplitItem( splitItem );

    /*
    ** BUGBUG: Depending on the condition of the database, in the odd chance that something
    **  has gone corrupted, this will more-or-less mask the issue, by simply
    **  stepping over this split that appears to be in bad shape.  Ideally we need
    **  to generate some sort of report at this point, but for now we'll just step
    **  over it.
    */
    if( !transMan.transactionItem() )
      continue;

    transMan.appendRow( true );

  } // endfor( auto splitItem : splitItems )

  /*!
  ** After all the split items are loaded, an additional ~blank~ item
  **  is included at the end of the vector, for coding new entries.
  */
  if( !isReadOnly() )
  {
    transMan.appendEmptyRow( true );

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

  /*
  ** load time
  */
  std::cout << __FILE__ << ":" << __LINE__
    << " " << std::chrono::duration_cast< std::chrono::milliseconds >
            ( std::chrono::system_clock::now() - start ).count()
    << "mS load time for"
    << " " << splitCount() << " items"
    << std::endl;

} // endrefreshFromDisk()-> void

auto
GCW::Gui::AccountRegister::Model::
makeRow( const std::string & _splitGuid )-> GCW::Gui::AccountRegister::Model::RowItem
{
  RowItem rowItem;

  return rowItem;

} // endmakeRow( const std::string & _splitGuid )-> GCW::Gui::AccountRegisterModel::RowItem

auto
GCW::Gui::AccountRegister::Model::
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

auto
GCW::Gui::AccountRegister::Model::
setStyleClass( int _row, const std::string & _class )-> void
{
  

} // endsetStyleClass( int _row, const std::string & _class )-> void

auto
GCW::Gui::AccountRegister::Model::
removeStyleClass( int _row, const std::string & _class )-> void
{

} // endremoveStyleClass( int _row, const std::string & _class )-> void


