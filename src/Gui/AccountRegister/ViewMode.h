#line 2 "src/Gui/AccountRegister/ViewMode.h"

#ifndef __ENG_ACCOUNTREGISTER_VIEWMODE_H___
#define __ENG_ACCOUNTREGISTER_VIEWMODE_H___

#include <Wt/WDateTime.h>
#include <Wt/WStandardItemModel.h>

namespace GCW {
  namespace Gui {
    namespace AccountRegister {

/*!
** \brief View Mode
**
** The View Mode defines how the data in the model is assembled.  The simplest form is the
**  one-line register, which is also the most compact.  The next mode is the Auto-Split
**  ledger.  The auto-split ledger looks just like the one-line register except for the
**  line that is currently selected, which is formatted as a transaction-journal, but just for
**  that one selected line.  The final format is the transaction-journal, which is like the
**  auto-split register but every row is already split out.  The General Journal is the same
**  as the Transaction Journal but it shows every account, and does not compute balances.
**
*/
enum class ViewMode
{
  /// basic one-line per transaction
  BASIC_LEDGER,

  /// one-line ledger that auto-opens to multi-line for each selected row
  AUTOSPLIT_LEDGER,

  /// multi-line ledger for every row
  TRANSACTION_JOURNAL,

  /// multi-line ledger that shows all accounts and no balances
  GENERAL_JOURNAL

}; // endenum class ViewMode

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
enum class ColDefs : int
{
  DATE        = 0,
  ACTION      = 1,
  DESCRIPTION = 2,
  TRANSFER    = 3,
  RECONCILE   = 4,
  DEBIT       = 5,
  CREDIT      = 6,
  BALANCE     = 7,
  NOTES       = 2

};

constexpr int asInt( ColDefs col ) noexcept
{
  return static_cast< int >( col );
}

    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // #ifndef __ENG_ACCOUNTREGISTER_VIEWMODE_H___


