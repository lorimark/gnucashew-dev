#line 2 "src/Gui/BillPay/Status.cpp"

#include "BillPay.h"

auto
GCW::Gui::BillPay::
asString( Status _status )-> std::string
{
  switch( _status )
  {
    case Status::Paid     : return TR8( "gcw.billPay.tableName.Paid"     );
    case Status::Pending  : return TR8( "gcw.billPay.tableName.Pending"  );
    case Status::Unpaid   : return TR8( "gcw.billPay.tableName.Unpaid"   );
    case Status::Inactive : return TR8( "gcw.billPay.tableName.Inactive" );
  }

  return "";

} // endasString( Status _status )-> std::string

auto
GCW::Gui::BillPay::
asStyleClass( Status _status )-> std::string
{
  switch( _status )
  {
    case Status::Paid     : return "billpay paid"     ;
    case Status::Pending  : return "billpay pending"  ;
    case Status::Unpaid   : return "billpay unpaid"   ;
    case Status::Inactive : return "billpay inactive" ;
  }

  return "";

} // endasStyleClass( Status _status )-> std::string

