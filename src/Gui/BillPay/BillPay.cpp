#line 2 "src/Gui/BillPay/BillPay.cpp"

#include "BillPay.h"

GCW::Dbo::Vars::Item::Ptr
GCW::Gui::BillPay::
configItem()
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  auto retVal = GCW::Dbo::Vars::get( "config", GCW_GUI_BILLPAY_CONFIG_CFY );

  return retVal;

} // endconfigItem()

GCW::Dbo::Vars::Item::Ptr
GCW::Gui::BillPay::
bpItem( const std::string & _nickname )
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  return GCW::Dbo::Vars::get( _nickname, GCW_GUI_BILLPAY_ITEM_CFY );
}

std::string
GCW::Gui::BillPay::
toString( int _value )
{
  std::string retVal = std::to_string( _value );

  if( retVal.length() == 1 )
    retVal = "0" + retVal;

  return retVal;

} // endstd::string toString( int _value )


