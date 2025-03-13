

#include "BillPay.h"
#include "Item.h"

#define FN_ACCOUNTGUID "accountGuid"
#define FN_DUEDAY      "dueDay"
#define FN_MINIMUM     "minimum"
#define FN_BUDGET      "budget"
#define FN_NICKNAME    "nickname"
#define FN_GROUP       "group"
#define FN_LIMIT       "limit"
#define FN_ACTUAL      "actual"
#define FN_URL         "url"
#define FN_AP          "ap"
#define FN_ISACTIVE    "isActive"
#define FN_ISVISIBLE   "isVisible"
#define FN_AUTOPAY     "autoPay"
#define FN_PAYNOW      "payNow"
#define FN_LAST4       "last4"
#define FN_NOTE        "note"
#define FN_CB          "cb"

GCW::Gui::BillPay::Item::
Item( GCW::Dbo::Vars::Item::Ptr _varItem )
: m_varItem( _varItem )
{

} // endBillPayItem( GCW::Dbo::Vars::Item::Ptr _varItem )

auto
GCW::Gui::BillPay::Item::
sortValue() const -> float
{
  std::string sortvalue = "0";

  if( group() != "" )
    sortvalue += group();

  if( dueDay() != "" )
    sortvalue += "." + dueDay();

  return std::stof( sortvalue );

} // endsortValue() const -> float

auto
GCW::Gui::BillPay::Item::
guid () const-> std::string
{
  return
    m_varItem-> keyField();

} // endguid () const-> std::string

auto
GCW::Gui::BillPay::Item::
accountGuid () const-> std::string
{
  return
    m_varItem-> getVarString( FN_ACCOUNTGUID );

} // endaccountGuid () const-> std::string

auto
GCW::Gui::BillPay::Item::
accountFullName () const-> std::string
{
  return
    GCW::Dbo::Accounts::fullName( accountGuid() );

} // endaccountGuid () const-> std::string

auto
GCW::Gui::BillPay::Item::
dueDay () const-> std::string
{
  return
    m_varItem-> getVarString( FN_DUEDAY );

} // enddueDay () const-> std::string

auto
GCW::Gui::BillPay::Item::
minimum () const-> std::string
{
  return
    m_varItem-> getVarString( FN_MINIMUM );

} // endminimum () const-> std::string

auto
GCW::Gui::BillPay::Item::
budget () const-> std::string
{
  return
    m_varItem-> getVarString( FN_BUDGET );

} // endbudget () const-> std::string

auto
GCW::Gui::BillPay::Item::
nickname () const-> std::string
{
  return
    m_varItem-> getVarString( FN_NICKNAME );

} // endnickname () const-> std::string

auto
GCW::Gui::BillPay::Item::
group () const-> std::string
{
  return
    m_varItem-> getVarString( FN_GROUP );

} // endgroup () const-> std::string

auto
GCW::Gui::BillPay::Item::
limit () const-> std::string
{
  return
    m_varItem-> getVarString( FN_LIMIT );

} // endlimit () const-> std::string

auto
GCW::Gui::BillPay::Item::
actual () const-> std::string
{
  return
    m_varItem-> getVarString( FN_ACTUAL );

} // endactual () const-> std::string

auto
GCW::Gui::BillPay::Item::
url () const-> std::string
{
  return
    m_varItem-> getVarString( FN_URL );

} // endurl () const-> std::string

auto
GCW::Gui::BillPay::Item::
ap () const-> std::string
{
  return
    m_varItem-> getVarString( FN_AP );

} // endap () const-> std::string

auto
GCW::Gui::BillPay::Item::
isActive () const-> std::string
{
  return
    m_varItem-> getVarString( FN_ISACTIVE );

} // endisActive () const-> std::string

auto
GCW::Gui::BillPay::Item::
isVisible () const-> std::string
{
  return
    m_varItem-> getVarString( FN_ISVISIBLE );

} // endisVisible () const-> std::string

auto
GCW::Gui::BillPay::Item::
autoPay () const-> std::string
{
  return
    m_varItem-> getVarString( FN_AUTOPAY );

} // endautoPay () const-> std::string

auto
GCW::Gui::BillPay::Item::
payNow () const-> std::string
{
  return
    m_varItem-> getVarString( FN_PAYNOW );

} // endpayNow () const-> std::string

auto
GCW::Gui::BillPay::Item::
last4 () const-> std::string
{
  return
    m_varItem-> getVarString( FN_LAST4 );

} // endlast4 () const-> std::string

auto
GCW::Gui::BillPay::Item::
note () const-> std::string
{
  return
    m_varItem-> getVarString( FN_NOTE );

} // endnote () const-> std::string


auto
GCW::Gui::BillPay::Item::
cb( int _index ) const-> std::string
{
  return
    m_varItem-> getVarString( FN_CB + toString( _index ) );

} // endcb(int _index) const-> std::string

auto
GCW::Gui::BillPay::Item::
setVar( const std::string & _key, const Wt::WString & _value )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_varItem.modify()-> setVar( _key, _value );

} // endset_var( const std::string & _key, const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_accountGuid( const Wt::WString & _value )-> void
{
  setVar( FN_ACCOUNTGUID, _value );

} // endset_accountGuid( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_dueDay( const Wt::WString & _value )-> void
{
  setVar( FN_DUEDAY, _value );

} // endset_dueDay( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_minimum( const Wt::WString & _value )-> void
{
  setVar( FN_MINIMUM, _value );

} // endset_minimum( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_budget( const Wt::WString & _value )-> void
{
  setVar( FN_BUDGET, _value );

} // endset_budget( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_nickname( const Wt::WString & _value )-> void
{
  setVar( FN_NICKNAME, _value );

} // endset_nickname( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_group( const Wt::WString & _value )-> void
{
  setVar( FN_GROUP, _value );

} // endset_group( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_limit( const Wt::WString & _value )-> void
{
  setVar( FN_LIMIT, _value );

} // endset_limit( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_actual( const Wt::WString & _value )-> void
{
  setVar( FN_ACTUAL, _value );

} // endset_actual( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_url( const Wt::WString & _value )-> void
{
  setVar( FN_URL, _value );

} // endset_url( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_ap( const Wt::WString & _value )-> void
{
  setVar( FN_AP, _value );

} // endset_ap( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_isActive( const Wt::WString & _value )-> void
{
  setVar( FN_ISACTIVE, _value );

} // endset_isActive( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_isVisible( const Wt::WString & _value )-> void
{
  setVar( FN_ISVISIBLE, _value );

} // endset_isVisible( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_autoPay( const Wt::WString & _value )-> void
{
  setVar( FN_AUTOPAY, _value );

} // endset_autoPay( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_payNow( const Wt::WString & _value )-> void
{
  setVar( FN_PAYNOW, _value );

} // endset_payNow( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_last4( const Wt::WString & _value )-> void
{
  setVar( FN_LAST4, _value );

} // endset_last4( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_note( const Wt::WString & _value )-> void
{
  setVar( FN_NOTE, _value );

} // endset_note( const Wt::WString & _value )-> void

auto
GCW::Gui::BillPay::Item::
set_cb(int _index, const Wt::WString & _value)-> void
{
  setVar( FN_CB + toString( _index ), _value );

} // endset_cb(int _index, const Wt::WString & _value)-> void





