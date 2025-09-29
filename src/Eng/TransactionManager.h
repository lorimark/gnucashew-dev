#line 2 "src/Eng/TransactionManager.h"

#ifndef __ENG_TRANSACTIONMANAGER_H___
#define __ENG_TRANSACTIONMANAGER_H___

#include "../Dbo/Accounts/Accounts.h"
#include "../Dbo/Prefrences.h"
#include "../Dbo/Splits/Splits.h"
#include "../Dbo/Transactions/Transactions.h"

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Gui {
    namespace AccountRegister {
    class Model ;
    }
  }
  namespace Eng {
    namespace Transaction {

/*!
** \brief Transaction Manager
**
** This is a convenience class for grouping all the transaction manipulation tasks in to one place.
**  It allows new transactions to be created, and takes care of insuring that the transaction is
**  always in balance, and always contains the requisite debits and credits to insure a properly
**  balanced transaction.
**
** The Transaction Manager is a 'friend' class to the AccountRegisterModel.  This allows the manager
**  to poke directly in to the model and manipulate it.
**
*/
class Manager
{
  public:

    using RowItem = std::vector< std::unique_ptr< Wt::WStandardItem > > ;
    using TxItem  = GCW::Dbo::Transactions::Item::Ptr ;
    using SpItem  = GCW::Dbo::Splits::Item::Ptr ;

    Manager();
    Manager( Gui::AccountRegister::Model * _model );

    auto model() const-> Gui::AccountRegister::Model * { return m_model ; }

    /*!
    ** \brief Set Transaction
    **
    ** Set transaction based on the transaction Guid.  This will load
    **  the transaction as well as all the splits associated with it.
    */
    auto loadTransaction( const std::string & _transactionGuid )-> void ;

    /*!
    ** \brief Delete Transaction
    **
    ** This insures all splits and any other data associated with the
    **  transaction is properly removed.
    */
    auto deleteTransaction()-> void ;

    auto setSplitItem( GCW::Dbo::Splits::Item::Ptr _splitItem )-> void ;

    /*!
    ** \brief Set Split
    **
    ** Set transaction based on any one of the splits.
    **
    ** This will load the split, then load the transaction for that split,
    **  causing all the other splits to load.
    */
    auto loadSplit( const std::string & _splitGuid )-> void ;

    /*!
    ** \brief Sort Splits
    **
    ** Sorts first Debits, then Credits
    */
    auto sortSplits()-> void ;

    /*!
    ** \brief Is Transaction Balanced
    **
    ** This checks the transaction and indicates if it is in
    **  balance or not.
    **
    ** \ref see; gnucash/libgnucash/engine/Transaction.cpp:1030
    */
    auto isBalanced()-> bool ;

    /*!
    ** \brief Balance Value
    **
    ** This checks the splits on the transaction and returns
    **  the 'balance value' which should be zero when the
    **  transaction is in balance.
    **
    ** \ref see; gnucash/libgnucash/engine/Transaction.cpp:1030
    */
    auto balanceValue()-> GCW_NUMERIC ;

    /*!
    ** \brief New Transaction
    **
    ** This will create a new Transaction for an account within the
    **  system fully populated with at least two splits.
    */
    auto newTransaction( const std::string & _accountGuid1, const std::string & _accountGuid2, const Wt::WDate & _date = Wt::WDate::currentDate(), GCW_NUMERIC _value = GCW_NUMERIC(0), const std::string & _description = "" )-> void ;

    /*!
    ** \brief Transaction Item
    **
    ** This returns the transaction pointer object
    */
    auto transactionItem() const-> GCW::Dbo::Transactions::Item::Ptr { return m_transactionItem; }
    auto prefrenceItem() const-> const GCW::Dbo::Prefrences::Item & { return m_prefrenceItem; }

    /*!
    ** \brief Splits Vector
    **
    ** This returns the splits vector
    */
    auto splits() const-> GCW::Dbo::Splits::Item::Vector { return m_splits; }

    auto otherSplits() const-> GCW::Dbo::Splits::Item::Vector ;

    /*!
    ** \brief Other GUID
    **
    ** When there are only two splits, this will return the guid of the
    **  split item that _does not_ match the guid provided.
    */
    auto otherGuid() const-> std::string ;

    /*!
    ** \brief Set Date
    **
    ** This sets the date on the Transaction of the element.
    */
    auto getDate() const-> Wt::WDateTime ;
    auto getDateAsString() const-> Wt::WString ;
    auto setDate( const Wt::WDateTime & _value )-> void ;
    auto setDate( const Wt::WDate & _value )-> void ;

    /*!
    ** \brief Set Action
    **
    ** This sets the Action on the split.  The 'action' is stored in
    **  the Split item and this function will apply the value to
    **  both sides of the split.
    */
    auto setAction( const std::string & _value )-> void ;

    /*!
    ** \brief Set Description
    **
    ** This sets the description on the Transaction of the element.
    */
    auto getDescription() const-> std::string ;
    auto setDescription( const std::string & _value )-> void ;
    auto setDescription( const Wt::WString & _value )-> void ;

    /*!
    ** \brief Set Num
    **
    ** On the Transaction, the 'num' is the action field, on the splits
    **  it is the action value.  So, in transaction it's called 'num' and
    **  in the splits it's called 'action'.
    */
    auto getNum() const-> std::string ;
    auto setNum( const std::string & _value )-> void ;
    auto setNum( const Wt::WString & _value )-> void ;

    /*!
    ** \brief Set Transfer GUID
    **
    ** This sets the (other) split (identified by guid) to the account
    **  given.
    */
    auto setTransferGuid( const std::string & _value  )-> void ;

    /*!
    ** \brief 
    **
    **
    */
    auto setReconcile( const std::string & _value  )-> void ;

    /*!
    ** \brief 
    **
    **
    */
    auto getValue() const-> GCW_NUMERIC ;
    auto getValueAsString() const-> std::string ;
    auto setValue( GCW_NUMERIC _value )-> void ;
    auto setValue( const std::string & _acctGuid, GCW_NUMERIC _value )-> void ;

    /*!
    ** \brief 
    **
    **
    */
    auto setNotes( const std::string & _acctGuid, const std::string & _value )-> void ;

    auto split( const std::string & _splitGuid ) const-> GCW::Dbo::Splits::Item::Ptr ;

    /*!
    ** \brief Load Split for Account
    **
    ** When we know the account guid, this will fetch the associated split
    **
    ** \note this assumes an account only has a single split
    */
    auto forAccountSplit( const std::string & _accountGuid ) const-> GCW::Dbo::Splits::Item::Ptr ;

    auto thisSplit() const-> GCW::Dbo::Splits::Item::Ptr ;
    auto thatSplit() const-> GCW::Dbo::Splits::Item::Ptr ;

    auto fromSplit() const-> GCW::Dbo::Splits::Item::Ptr ;
    auto toSplit()   const-> GCW::Dbo::Splits::Item::Ptr ;

    auto getFromAccount() const-> std::string ;
    auto getToAccount()   const-> std::string ;

    auto setReadOnly( bool _value )-> void ;

    /*
    ** append the row to the model
    */
    auto appendRow( bool _editable )-> void ;
    auto appendEmptyRow( bool _editable )-> void ;
    auto insertDoubleLine( int _row )-> void ;

  private:

    auto highlightNegativeBalance( RowItem & _row ) const-> void ;

    auto flags( bool _editable ) const-> Wt::WFlags< Wt::ItemFlag > ;

    auto createText        ( const std::string & _text                   ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createBlank       (                                             ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createEmpty       (                                             ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createDate        ( const TxItem      & _txItem, bool _editable ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createNum         ( const TxItem      & _txItem, bool _editable ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createNum         ( const SpItem      & _spItem, bool _editable ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createDescription ( const TxItem      & _txItem, bool _editable ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createDescription ( const SpItem      & _spItem, bool _editable ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createAccount     ( const SpItem      & _spItem, bool _editable ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createReconcile   ( const SpItem      & _spItem, bool _editable ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createDebit       ( const SpItem      & _spItem, bool _editable ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createCredit      ( const SpItem      & _spItem, bool _editable ) const-> std::unique_ptr< Wt::WStandardItem > ;
    auto createBalance     (                                             ) const-> std::unique_ptr< Wt::WStandardItem > ;

    auto appendBasicLedger        ( bool _editable ) const-> void ;
    auto appendAutosplitLedger    ( bool _editable ) const-> void ;
    auto appendTransactionJournal ( bool _editable ) const-> void ;
    auto appendGeneralJournal     ( bool _editable ) const-> void ;

    Gui::AccountRegister::Model             * m_model           = nullptr ;
    Wt::WModelIndex                           m_index           ;
    std::string                               m_splitGuid       ;
    GCW::Dbo:: Transactions ::Item::Ptr       m_transactionItem ;
    GCW::Dbo:: Prefrences   ::Item            m_prefrenceItem   ;
    GCW::Dbo:: Splits       ::Item::Vector    m_splits          ;

}; // endclass Manager

    } // namespace Transaction {
  } // namespace Eng {
} // namespace GCW {

#endif // #ifndef __ENG_TRANSACTIONMANAGER_H___


