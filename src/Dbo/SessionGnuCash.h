#line 2 "src/Dbo/SessionGnucash.h"

#ifdef NEVER
#ifndef __DBO_SESSIONGNUCASH_H___
#define __DBO_SESSIONGNUCASH_H___

#include <gnucash/gnc-session.h>
#include <gnucash/Account.h>
#include <gnucash/Transaction.h>
#include <gnucash/qofsession.h>

#include "AbstractSession.h"

namespace GCW {
  namespace Dbo {
    namespace GnuCash {

class Session;
class Account;
class Book;

class Account
{
  public:

    /*
    ** standard constructor
    **
    */
    Account(){}
    Account( ::Account * _gncAccount, Book * _book );

    /*
    ** copy constructor
    **
    */
    Account( const Account & );

    std::string guid();
    std::string name();
    std::string code();
    std::string description();
    std::string notes();

    std::vector< Account > children();

    Book * book();
    ::Account * gncAccount();

#ifdef ALL_THESE_FUNCTIONS_NEED_TO_BE_PACKED_INTO_THIS_OBJECT

// Set the account's notes.
void xaccAccountSetNotes (Account *account, const char *notes);

// Set the account's type.
void xaccAccountSetType (Account *account, GNCAccountType)

// Set the account's name.
void xaccAccountSetName (Account *account, const char *name)

// Set the account's accounting code.
void xaccAccountSetCode (Account *account, const char *code)

// Set the account's description.
void xaccAccountSetDescription (Account *account, const char *desc)

// Set the account's Color.
void xaccAccountSetColor (Account *account, const char *color)

// Set the account's Filter.
void xaccAccountSetFilter (Account *account, const char *filter)

// Set the account's Sort Order.
void xaccAccountSetSortOrder (Account *account, const char *sortorder)

// Set the account's Sort Order direction.
void xaccAccountSetSortReversed (Account *account, gboolean sortreversed)

// Set the account's associated account e.g. More...
void xaccAccountSetAssociatedAccount (Account *acc, const char *tag, const Account *assoc_acct)

// Set the last num field of an Account.
void xaccAccountSetLastNum (Account *account, const char *num)

// Set the account's lot order policy.
void gnc_account_set_policy (Account *account, GNCPolicy *policy)

// Returns the account's account type. More...
GNCAccountType xaccAccountGetType (const Account *account)

// Returns true if the account is a stock, mutual fund or currency, otherwise false. More...
gboolean xaccAccountIsPriced (const Account *acc)

// This function will set the starting commodity balance for this account. More...
void gnc_account_set_start_balance (Account *acc, const gnc_numeric start_baln)

// This function will set the starting cleared commodity balance for this account. More...
void gnc_account_set_start_cleared_balance (Account *acc, const gnc_numeric start_baln)

// This function will set the starting reconciled commodity balance for this account. More...
void gnc_account_set_start_reconciled_balance (Account *acc, const gnc_numeric start_baln)

// Tell the account that the running balances may be incorrect and need to be recomputed. More...
void gnc_account_set_balance_dirty (Account *acc)

// Tell the account believes that the splits may be incorrectly sorted and need to be resorted. More...
void gnc_account_set_sort_dirty (Account *acc)

// Set the defer balance flag. More...
void gnc_account_set_defer_bal_computation (Account *acc, gboolean defer)

// Insert the given split from an account. More...
gboolean gnc_account_insert_split (Account *acc, Split *s)

// Remove the given split from an account. More...
gboolean gnc_account_remove_split (Account *acc, Split *s)

// Get the account's name.
const char * xaccAccountGetName (const Account *account);

// Get the account's accounting code.
const char * xaccAccountGetCode (const Account *account)

// Get the account's description.
const char * xaccAccountGetDescription (const Account *account)

// Get the account's color.
const char * xaccAccountGetColor (const Account *account)

// Get the account's filter.
const char * xaccAccountGetFilter (const Account *account)

// Get the account's Sort Order.
const char * xaccAccountGetSortOrder (const Account *account)

// Get the account's Sort Order direction.
gboolean xaccAccountGetSortReversed (const Account *account)

// Get the account's associated account e.g. More...
Account * xaccAccountGetAssociatedAccount (const Account *acc, const char *tag)

// Get the last num field of an Account.
const char * xaccAccountGetLastNum (const Account *account)

// Get the account's lot order policy.
GNCPolicy * gnc_account_get_policy (Account *account)

// Get the account's flag for deferred balance computation.
gboolean gnc_account_get_defer_bal_computation (Account *acc)

// The following recompute the partial balances (stored with the transaction) and the total balance, for this account.
void xaccAccountRecomputeBalance (Account *)

// The xaccAccountSortSplits() routine will resort the account's splits if the sort is dirty. More...
void xaccAccountSortSplits (Account *acc, gboolean force)

// The gnc_account_get_full_name routine returns the fully qualified name of the account using the given separator char. More...
gchar * gnc_account_get_full_name (const Account *account)

// Retrieve the gains account used by this account for the indicated currency, creating and recording a new one if necessary. More...
Account * xaccAccountGainsAccount (Account *acc, gnc_commodity *curr)

// Set a string that identifies the Finance::Quote backend that should be used to retrieve online prices. More...
void dxaccAccountSetPriceSrc (Account *account, const char *src)

// Get a string that identifies the Finance::Quote backend that should be used to retrieve online prices. More...
const char * dxaccAccountGetPriceSrc (const Account *account)

#endif

  private:

    Book * m_book = nullptr;

    ::Account * m_gncAccount = nullptr;

}; // endclass Account

class Book
{
  public:

    Book( Session * _session );

    Account rootAccount();
    Account accountByGuid( const std::string _guid );

    guint count_transactions();

  private:

    QofBook * m_book    = nullptr;
    Session * m_session = nullptr;

}; // endclass Book

/*!
** \brief GnuCash Native Session
**
** This session controller is designed to work through the
**  libgnucash back-end library.
**
*/
class Session
: public GCW::Dbo::AbstractSession
{
  public:

    Session() {}
    ~Session();

    QofSession * qofSession();

    /*!
    ** \brief Open a database
    **
    */
    bool open( const std::string & _path );

    Book book();

  private:

    void closeGnuCash();

    void init();

    QofSession * m_session = nullptr;

}; // endclass Session

} // endnamespace GnuCash {


  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __SESSIONGNUCASH_H___
#endif

