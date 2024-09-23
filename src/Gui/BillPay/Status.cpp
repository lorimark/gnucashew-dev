#line 2 "src/Gui/BillPay/Status.cpp"

#include "BillPay.h"

std::string
GCW::Gui::BillPay::
asString( Status _status )
{
  std::string values[] =
  {
    TR8( "gcw.billPay.tableName.Paid"     ),
    TR8( "gcw.billPay.tableName.Unpaid"   ),
    TR8( "gcw.billPay.tableName.Disabled" )
  };

  return values[ static_cast<int>( _status ) ];
}

std::string
GCW::Gui::BillPay::
asStyleClass( Status _status )
{
  std::string values[] =
  {
    "billpay paid"     ,
    "billpay unpaid"   ,
    "billpay disabled"
  };

  return values[ static_cast<int>( _status ) ];
}

