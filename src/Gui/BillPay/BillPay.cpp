#line 2 "src/Gui/BillPay/BillPay.cpp"

#include "BillPay.h"

auto
GCW::Gui::BillPay::
configItem()-> GCW::Dbo::Vars::Item::Ptr
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  auto retVal = GCW::Dbo::Vars::get( "config", GCW_GUI_BILLPAY_CONFIG_CFY );

  return retVal;

} // endconfigItem()-> GCW::Dbo::Vars::Item::Ptr

auto
GCW::Gui::BillPay::
bpItem( const std::string & _nickname )-> GCW::Gui::BillPay::Item
{
  return
    GCW::Gui::BillPay::Item
    (
     GCW::Dbo::Vars::get
     (
      _nickname,
      GCW_GUI_BILLPAY_ITEM_CFY,
      true
     )
    );

} // endbpItem( const std::string & _nickname )-> GCW::Dbo::Vars::Item::Ptr

auto
GCW::Gui::BillPay::
toString( int _value )-> std::string
{
  std::string retVal = std::to_string( _value );

  if( retVal.length() == 1 )
    retVal = "0" + retVal;

  return retVal;

} // endtoString( int _value )-> std::string


