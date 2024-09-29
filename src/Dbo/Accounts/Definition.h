#line 2 "src/Dbo/Accounts/Definition.h"

#ifndef __DBO_ACCOUNTS_DEFINITION_H___
#define __DBO_ACCOUNTS_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace Accounts {

extern const char * s_tableName;

/*!
** \brief Account Debit/Credit Enum
**
** This indicates if this account is a 'debit' type account or
**  a 'credit' type account.
*
** \sa GCW::Dbo::Accounts::Item
**
*/
enum class DrCr
{
  /// 0x00 ~ invalid - should not happen
  NONE   = 0x00,

  /// 0x01 ~ DEBIT type account
  DEBIT  = 0x01,

  /// 0x02 ~ CREDIT type account
  CREDIT = 0x02
};

/*!
** \brief Account Type
**
** These are used internally to switch the views depending on the account type.
**  While these codes exactly match the codes in the native gnucash proper, they
**  should not be relied on to match the native gnucash account type codes
**  (those are textual, see; GCW::Dbo::Accounts::Item::accountTypeName).  But,
**  these are internal anyhow, and they don't get stored.  They're just used to
**  steer the application, especially as it pertains to debit/credit calculations.
**
** The definition-table can be found here: \ref s_accountDefs
**
** \note gnucash source reference: ..src/libgnucash/engine/Account.h
**
*/
enum class Type
{
  /// -1 ~ not a type
  INVALID    = -1,

  /// -1 ~ not a type
  NONE       = -1,

  /// 00 ~ bank institutionally held monies, can be interest bearing
  BANK       = 0,

  /// 01 ~ pure cash (shoebox)
  CASH       = 1,

  /// 03 ~ AMEX / VISA / DISCOVER type of credit cards
  CREDIT     = 3,

  /// 02 ~ generic generalized asset account
  ASSET      = 2,

  /// 04 ~ generic generalized liability account
  LIABILITY  = 4,

  /// 05 ~ stock account show as three-column registers: price, # shares, value
  STOCK      = 5,

  /// 06 ~ similar to stock, shows: price, # shares, value
  MUTUAL     = 6,

  /// 07 ~ currency trading account (DEPRECATED)
  CURRENCY   = 7,

  /// 08 ~ income tracking account
  INCOME     = 8,

  /// 09 ~ expense tracking account
  EXPENSE    = 9,

  /// 10 ~ used to balance the balance sheet
  EQUITY     = 10,

  /// 11 ~ A/R receivable account
  RECEIVABLE = 11,

  /// 12 ~ A/R payable account
  PAYABLE    = 12,

  /// 13 ~ hidden root account for the account tree
  ROOT       = 13,

  /// 14 ~ used to record multiple commodify transactions
  TRADING    = 14,

  /// 15 ~ end of account types
  NUM_ACCOUNT_TYPES    = 15,

  /// 15 ~ do not use
  CHECKING   = 15,

  /// 16 ~ do not use
  SAVINGS    = 16,

  /// 17 ~ do not use
  MONEYMRKT  = 17,

  /// 18 ~ do not use
  CREDITLINE = 18,

  /// end of list
  LAST

};

/*!
** \brief Account Definition
**
** This structure provides a set of account-definitions that are used in the
**  various views and balance calculations.
**
*/
typedef struct ACCOUNTDEF_S
{
  /// Account Type as per gnucash
  Type        type;

  /// indicate if the account is Debit or Credit
  DrCr        drcr;

  /// a printable 'name' for the account
  std::string name;

  /// a printable 'label' for the 'account' column in the registers
  std::string colAccount;

  /// a printable 'label' for the 'debit' column in the registers
  std::string colDr;

  /// a printable 'label' for the 'credit' column in the registers
  std::string colCr;

} AccountDef_t;

extern const std::vector< AccountDef_t > s_accountDefs;

      namespace Field {

extern const Wt::WFormModel::Field guid             ; // text(32) PRIMARY KEY NOT NULL
extern const Wt::WFormModel::Field name             ; // text(2048) NOT NULL
extern const Wt::WFormModel::Field account_typeName ; // text(2048) NOT NULL
extern const Wt::WFormModel::Field commodity_guid   ; // text(32)
extern const Wt::WFormModel::Field commodity_scu    ; // integer NOT NULL (special currency unit)
extern const Wt::WFormModel::Field non_std_scu      ; // integer NOT NULL (1=special currency unit in use)
extern const Wt::WFormModel::Field parent_guid      ; // text(32)
extern const Wt::WFormModel::Field code             ; // text(2048)
extern const Wt::WFormModel::Field description      ; // text(2048)
extern const Wt::WFormModel::Field hidden           ; // integer
extern const Wt::WFormModel::Field placeHolder      ; // integer

      } // endnamespace Field {
    } // endnamespace Accounts {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_ACCOUNTS_DEFINITION_H___



