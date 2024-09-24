#line 2 "src/Dbo/Customers.cpp"

#include "../App.h"
#include "Customers.h"

const char * GCW::Dbo::Customers::s_tableName = "customers";

Wt::WFormModel::Field GCW::Dbo::Customers::Field::guid           = "guid"           ; // text(32) PRIMARY KEY NOT NULL
Wt::WFormModel::Field GCW::Dbo::Customers::Field::name           = "name"           ; // text(2048) NOT NULL
Wt::WFormModel::Field GCW::Dbo::Customers::Field::id             = "id"             ; // text(2048) NOT NULL
Wt::WFormModel::Field GCW::Dbo::Customers::Field::notes          = "notes"          ; // text(2048) NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Customers::Field::active         = "active"         ; // integer NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Customers::Field::discount_num   = "discount_num"   ; // bigint NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Customers::Field::discount_denom = "discount_denom" ; // bigint NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Customers::Field::credit_num     = "credit_num"     ; // bigint NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Customers::Field::credit_denom   = "credit_denom"   ; // bigint NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Customers::Field::currency       = "currency"       ; // text(32) NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Customers::Field::tax_override   = "tax_override"   ; // integer NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Customers::Field::addr_name      = "addr_name"      ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::addr_addr1     = "addr_addr1"     ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::addr_addr2     = "addr_addr2"     ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::addr_addr3     = "addr_addr3"     ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::addr_addr4     = "addr_addr4"     ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::addr_phone     = "addr_phone"     ; // text(128),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::addr_fax       = "addr_fax"       ; // text(128),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::addr_email     = "addr_email"     ; // text(256),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::shipaddr_name  = "shipaddr_name"  ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::shipaddr_addr1 = "shipaddr_addr1" ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::shipaddr_addr2 = "shipaddr_addr2" ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::shipaddr_addr3 = "shipaddr_addr3" ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::shipaddr_addr4 = "shipaddr_addr4" ; // text(1024),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::shipaddr_phone = "shipaddr_phone" ; // text(128),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::shipaddr_fax   = "shipaddr_fax"   ; // text(128),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::shipaddr_email = "shipaddr_email" ; // text(256),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::terms          = "terms"          ; // text(32),
Wt::WFormModel::Field GCW::Dbo::Customers::Field::tax_included   = "tax_included"   ; // integer,
Wt::WFormModel::Field GCW::Dbo::Customers::Field::taxtable       = "taxtable"       ; // text(32)

GCW::Dbo::Customers::Item::Ptr
GCW::Dbo::Customers::
byGuid( const std::string & _guid )
{
  GCW::Dbo::Customers::Item::Ptr retVal;

  retVal =
    GCW::app()-> gnucashew_session().load< GCW::Dbo::Customers::Item >( _guid )
    ;

  return retVal;

} // endbyGuid( const std::string & _guid )



