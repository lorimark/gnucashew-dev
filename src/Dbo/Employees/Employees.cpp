#line 2 "src/Dbo/Employees/Employees.cpp"

#include "../Glb/Core.h"
#include "../App.h"
#include "Employees.h"

const char * GCW::Dbo::Employees::s_tableName = "employees";

const Wt::WFormModel::Field GCW::Dbo::Employees::Field::guid            = "guid"          ; // text(32) PRIMARY KEY NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::username        = "username"      ; // text(2048) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::id              = "id"            ; // text(2048) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::language        = "language"      ; // text(2048) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::acl             = "acl"           ; // text(2048) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::active          = "active"        ; // integer NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::currency        = "currency"      ; // text(32) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::ccard_guid      = "ccard_guid"    ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::workday_num     = "workday_num"   ; // bigint NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::workday_denom   = "workday_denom" ; // bigint NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::rate_num        = "rate_num"      ; // bigint NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::rate_denom      = "rate_denom"    ; // bigint NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::addr_name       = "addr_name"     ; // text(1024),
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::addr_addr1      = "addr_addr1"    ; // text(1024),
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::addr_addr2      = "addr_addr2"    ; // text(1024),
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::addr_addr3      = "addr_addr3"    ; // text(1024),
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::addr_addr4      = "addr_addr4"    ; // text(1024),
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::addr_phone      = "addr_phone"    ; // text(128),
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::addr_fax        = "addr_fax"      ; // text(128),
const Wt::WFormModel::Field GCW::Dbo::Employees::Field::addr_email      = "addr_email"    ; // text(256)


auto
GCW::Dbo::Employees::
load( const std::string & _guid )-> GCW::Dbo::Employees::Item::Ptr
{
  GCW::Dbo::Employees::Item::Ptr retVal;

  if( _guid != "" )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    try
    {
      retVal =
        GCW::app()-> gnucashew_session().load< GCW::Dbo::Employees::Item >( _guid )
        ;
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }
  }

  return retVal;

} // endload( const std::string & _guid )-> GCW::Dbo::Employees::Item::Ptr

auto
GCW::Dbo::Employees::
byGuid( const std::string & _guid )-> GCW::Dbo::Employees::Item::Ptr
{
  return load( _guid );

} // endbyGuid( const std::string & _guid )-> GCW::Dbo::Employees::Item::Ptr


