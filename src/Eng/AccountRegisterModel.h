#line 2 "src/Eng/AccountRegisterModel.h"

#ifndef __ENG_ACCOUNTREGISTERMODEL_H___
#define __ENG_ACCOUNTREGISTERMODEL_H___

#include <Wt/WStandardItemModel.h>

#include "../GnuCashew.h"

namespace GCW {
  namespace Eng {

/*!
** \brief Account Register Model
**
** This model is used to present account details to the
**  'editor register' (the spreadsheet-looing book-like-looking
**  thing that the user posts transactions through.
**
*/
class AccountRegisterModel
: public Wt::WStandardItemModel
{
  using RowItem = std::vector< std::unique_ptr< Wt::WStandardItem > >;
  using ColItem = Wt::WStandardItem *;

  public:

    enum class ViewMode
    {
      /// basic one-line per transaction
      BASIC_LEDGER,

      /// one-line ledger that auto-opens to multi-line for each selected row
      AUTOSPLIT_LEDGER,

      /// self explanatory
      TRANSACTION_JOURNAL
    };

    /*!
    ** \brief ctor
    **
    ** This opens the model associated with a specific account.
    **
    */
    AccountRegisterModel( const std::string & _accountGuid = "", bool _editable = true );

    auto setAccountGuid( const std::string & _accountGuid )-> void ;
    auto refreshFromDisk()-> void ;
    auto saveToDisk()-> void ;

    auto viewMode() const-> ViewMode { return m_viewMode; }
    auto setViewMode( ViewMode _viewMode )-> void;
    auto doubleLine() const-> bool { return m_doubleLine; }
    auto setDoubleLine( bool _doubleLine )-> void;

    /*!
    ** \brief Get GUID from row
    **
    ** This will retrieve the GUID value from the row.
    **
    */
    auto getSplitGuid( const Wt::WModelIndex & _index )-> std::string ;
    auto getSplitGuid( int _row )-> std::string ;

    /*!
    ** \brief Get Date from the index
    **
    ** This pulls the 'date' column out and returns it as a WDateTime
    **  value.
    **
    ** \note This will 'force' the 'time' component to be equal to
    **        the default time of '10:59:00', since the 'date' column
    **        does not support a time component... this seems to be
    **        consistent with GnuCash.
    **
    */
    auto getDate( const Wt::WModelIndex & _index )-> Wt::WDateTime;

    /*!
    ** \brief Get Action
    **
    */
    auto getAction( const Wt::WModelIndex & _index )-> std::string;

    /*!
    ** \brief Get Description
    **
    */
    auto getDescription( const Wt::WModelIndex & _index )-> std::string;

    /*!
    ** \brief Get Transfer Account Text
    **
    */
    auto getTransferText( const Wt::WModelIndex & _index )-> std::string;

    /*!
    ** \brief Get Transfer Account GUID
    **
    */
    auto getTransferGuid( const Wt::WModelIndex & _index )-> std::string;

    /*!
    ** \brief Get Reconciliation
    **
    */
    auto getReconcile( const Wt::WModelIndex & _index )-> std::string;

    /*!
    ** \brief Get numeric value
    **
    ** This returns the numeric value of the line.  This is suitable
    **  for querying either the debit or credit column values (and is really
    **  intended for internal use).  The 'value' is pulled from the Display
    **  value of the index and converted to a GCW_NUMERIC value.
    **
    */
    auto getNumeric( const Wt::WModelIndex & _index )-> GCW_NUMERIC;

    /*!
    ** \brief Get Debit value
    **
    */
    auto getDebit( const Wt::WModelIndex & _index )-> GCW_NUMERIC;

    /*!
    ** \brief Get Credit value
    **
    */
    auto getCredit( const Wt::WModelIndex & _index )-> GCW_NUMERIC;

    /*!
    ** \brief Get Value (positive or negative)
    **
    ** The value that gets stored in the back-end database is either positive
    **  for debit, and negative for credit.  This function will read-out the
    **  debit and credit columns in the register display and figure out if
    **  the returned value should be returned positive or negative corrected.
    **
    ** This function always positive for debit, and negative for credit values.
    **
    */
    auto getValue( const Wt::WModelIndex & _index )-> GCW_NUMERIC;

    /*!
    ** \brief
    **
    **
    **
    */
    auto getBalance ( const Wt::WModelIndex & _index )-> GCW_NUMERIC ;

    auto present    () const-> GCW_NUMERIC { return m_present;    }
    auto future     () const-> GCW_NUMERIC { return m_future;     }
    auto cleared    () const-> GCW_NUMERIC { return m_cleared;    }
    auto reconciled () const-> GCW_NUMERIC { return m_reconciled; }
    auto projected  () const-> GCW_NUMERIC { return m_projected;  }

    auto makeRow( const std::string & _splitGuid )-> RowItem ;

    /*!
    ** \brief Column Suggestions
    **
    ** This produces a unique-set of items that represent all the text-values
    **  for that particular column.  This is used to produce a suggestion-box
    **  for the register.
    **
    */
    auto suggestionsFromColumn( int _column ) const-> std::set< std::string > ;

    auto setData( const Wt::WModelIndex & _index, const Wt::cpp17::any & _value, Wt::ItemDataRole _role )-> bool ;

/*

   these are additional values that need to be available

balance
  balance limit
  balance (Period)
  balance usd
  cleared
  cleared usd
  fiture minimum
  future minimum usa
  last num
  last reconcile date
  opening balance
  present
  present usd
  reconciled reconciled usd
  total total period
  total usd
*/

  private:

    auto getString( const Wt::WModelIndex & _index, int column )-> std::string;

    auto saveToDisk( const Wt::WModelIndex & _index )-> void ;

#ifdef NEVER
    template <typename T>
    bool matchValue( const Wt::cpp17::any & _any1, const Wt::cpp17::any & _any2 )
    {
      auto v1 = Wt::cpp17::any_cast< T >( _any1 );
      auto v2 = Wt::cpp17::any_cast< T >( _any2 );
      return v1 == v2;
    }
#endif

    /*
    ** Send a signal when a index is being updated
    **  because it was dirty.
    **
    */
    Wt::Signal< Wt::WModelIndex > m_goneDirty;

    /*
    ** keep track of rows as they go dirty.
    **
    */
//    std::set< int > m_dirtyRows;

    /*!
    ** \brief Editable Indicator
    **
    ** The model can be either R/W (read-write) or R/O (read-only).
    **
    */
    bool m_editable = false;

    ViewMode m_viewMode   = ViewMode::BASIC_LEDGER;
    bool     m_doubleLine = false;

    /*!
    ** \brief Account GUID
    **
    ** The model is associated with a single account.
    **
    */
    std::string m_accountGuid;

    /*
    ** Keep track of the last date entered for pre-populating
    **  the next row.
    **
    */
    std::string m_lastDate;

    GCW_NUMERIC m_present    ;
    GCW_NUMERIC m_future     ;
    GCW_NUMERIC m_cleared    ;
    GCW_NUMERIC m_reconciled ;
    GCW_NUMERIC m_projected  ;

}; // endclass AccountRegisterModel

  } //  namespace Eng {
} // endnamespace GCW {

#endif // #ifndef __ENG_ACCOUNTREGISTERMODEL_H___



