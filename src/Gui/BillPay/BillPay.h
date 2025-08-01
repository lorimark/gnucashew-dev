#line 2 "src/Gui/BillPay/BillPay.h"

#ifndef __GUI_BILLPAY_H___
#define __GUI_BILLPAY_H___

#include "../../GnuCashew.h"
#include "../../Dbo/Vars/Vars.h"

#include "EditWidget.h"
#include "PaymentWidget.h"
#include "MainWidget.h"
#include "Item.h"
#include "TableModel.h"
#include "Status.h"
#include "TableView.h"
#include "ToolBar.h"

namespace GCW {
  namespace Gui {

    /*!
    ** \brief Bill Pay
    **
    ** This tool provides an interface for paying bills.  The intent of the interface
    **  is to present bills that are due within a specific period of time, with thier
    **  due dates shown, and organized in to sets of "not paid", "pending" and "paid".
    **
    ** \image html BillPayDetailForm.png
    **
    */
    namespace BillPay {

/*
** Use these to identify the cfyField type
**  for the varItems for the various functions
**  within this application.
**
*/
#define GCW_GUI_BILLPAY_CONFIG_CFY "mpbc"
#define GCW_GUI_BILLPAY_ITEM_CFY   "mbpi"

/*!
** \brief Config Item
**
** This returns the single 'config item' that contains the properties of the
**  bill pay sub-system.
**
*/
auto configItem()-> GCW::Dbo::Vars::Item::Ptr ;

/*!
** \brief Bill Pay Items
**
** This returns all bill pay items in a vector
**
*/
auto bpItems()-> std::vector< GCW::Gui::BillPay::Item > ;

/*!
** \brief Bill Pay Item
**
** This returns a bill-pay item based on the GUID of the relative account.
**
*/
auto bpItem( const std::string & _guid )-> GCW::Gui::BillPay::Item ;

/*!
** \brief Convert Integer to String
**
** This converts an integer in to a 2-character string.  So, numbers less
**  that 10 return "09", "08", "07"... as a string.
**
*/
auto toString( int _value )-> std::string ;

auto exportAll()-> void;
auto importAll()-> void;

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_H___




