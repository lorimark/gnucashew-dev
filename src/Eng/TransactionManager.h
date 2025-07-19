#line 2 "src/Eng/TransactionManager.h"

#ifndef __ENG_TRANSACTIONMANAGER_H___
#define __ENG_TRANSACTIONMANAGER_H___

#include "../Dbo/Accounts/Accounts.h"
#include "../Dbo/Splits/Splits.h"
#include "../Dbo/Transactions/Transactions.h"

/*
** Now we can start building our class!
**
*/
namespace GCW {
  namespace Eng {
    namespace Transaction {

/*!
** \brief Transaction Manager
**
** This is a convenience class for grouping all the
**  transaction manipulation tasks in to one place.  It allows
**  new transactions to be created, and takes care of insuring that
**  the transaction is always in balance, and always contains the
**  requisite debits and credits to insure a properly balanced
**  transaction.
**
*/
class Manager
{
  public:

    Manager();
    Manager( GCW::Dbo::Splits::Item::Ptr _splitItem );

    /*!
    ** \brief Set Transaction
    **
    ** Set transaction based on the transaction Guid.  This will load
    **  the transaction as well as all the splits associated with it.
    **
    */
    auto loadTransaction( const std::string & _transactionGuid )-> void ;

    auto deleteTransaction()-> void ;

    /*!
    ** \brief Set Split
    **
    ** Set transaction based on any one of the splits.
    **
    ** This will load the split, then load the transaction for that split,
    **  causing all the other splits to load.
    **
    */
    auto loadSplit( const std::string & _splitGuid )-> void ;

    /*!
    ** \brief Sort Splits
    **
    ** Sorts first Debits, then Credits
    **
    */
    auto sortSplits()-> void ;

    /*!
    ** \brief Is Transaction Balanced
    **
    ** This checks the transaction and indicates if it is in
    **  balance or not.
    **
    ** \ref see; gnucash/libgnucash/engine/Transaction.cpp:1030
    **
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
    **
    */
    auto balanceValue()-> GCW_NUMERIC ;

    /*!
    ** \brief New Transaction
    **
    ** This will create a new Transaction for an account within the
    **  system fully populated with at least two splits.
    **
    */
    auto newTransaction( const std::string & _accountGuid1, const std::string & _accountGuid2 )-> void ;

    /*!
    ** \brief Transaction Item
    **
    ** This returns the transaction pointer object
    **
    */
    auto transaction() const-> GCW::Dbo::Transactions::Item::Ptr { return m_transaction; }

    /*!
    ** \brief Splits Vector
    **
    ** This returns the splits vector
    **
    */
    auto splits() const-> GCW::Dbo::Splits::Item::Vector { return m_splitItems; }

    /*!
    ** \brief Other GUID
    **
    ** When there are only two splits, this will return the guid of the
    **  split item that _does not_ match the guid provided.
    **
    */
    auto otherGuid() const-> std::string ;

    /*!
    ** \brief Set Date
    **
    ** This sets the date on the Transaction of the element.
    **
    */
    auto getDate() const-> Wt::WDateTime ;
    auto setDate( const Wt::WDateTime & _value )-> void ;

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
    **
    */
    auto getDescription() const-> std::string ;
    auto setDescription( const std::string & _value )-> void ;

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

    /*!
    ** \brief 
    **
    **
    */
    auto setNotes( const std::string & _value )-> void ;

    auto split( const std::string & _splitGuid ) const-> GCW::Dbo::Splits::Item::Ptr ;

    auto thisSplit() const-> GCW::Dbo::Splits::Item::Ptr ;
    auto thatSplit() const-> GCW::Dbo::Splits::Item::Ptr ;

  private:

    std::string                            m_splitGuid   ;
    GCW::Dbo:: Transactions ::Item::Ptr    m_transaction ;
    GCW::Dbo:: Splits       ::Item::Vector m_splitItems  ;

}; // endclass Manager

    } // namespace Transaction {
  } // namespace Eng {
} // namespace GCW {

#endif // #ifndef __ENG_TRANSACTIONMANAGER_H___


