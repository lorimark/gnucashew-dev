#line 2 "src/Gui/BillPay/BillPay.h"

#ifndef __GUI_BILLPAY_H___
#define __GUI_BILLPAY_H___

#include "../../GnuCashew.h"
#include "../../Dbo/Vars/Vars.h"

#include "EditWidget.h"
#include "MainWidget.h"
#include "Item.h"
#include "Model.h"
#include "Status.h"
#include "Table.h"
#include "ToolBar.h"

namespace GCW {
  namespace Gui {

    /*!
    ** \brief Bill Pay
    **
    ** This tool provides an interface for paying bills.  The intent of the interface
    **  is to present bills that are due within a specific period of time, with thier
    **  due dates shown, and organized in to sets of "paid" and "not paid".
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
** \brief Bill Pay Item
**
** This returns a bill-pay item based on the NICKNAME of the relative account.
**
*/
auto bpItem( const std::string & _nickname )-> GCW::Gui::BillPay::Item ;

/*!
** \brief Convert Integer to String
**
** This converts an integer in to a 2-character string.  So, numbers less
**  that 10 return "09", "08", "07"... as a string.
**
*/
auto toString( int _value )-> std::string ;

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_H___




