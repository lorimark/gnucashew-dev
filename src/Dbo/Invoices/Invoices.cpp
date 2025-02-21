#line 2 "src/Dbo/Invoices/Invoices.cpp"

#include "../App.h"
#include "../Glb/Core.h"

#include "Invoices.h"

const char * GCW::Dbo::Invoices::s_tableName = "invoices";

const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::guid             = "guid"             ; // text(32) PRIMARY KEY NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::id               = "id"               ; // text(2048) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::date_opened      = "date_opened"      ; // text(19),
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::date_posted      = "date_posted"      ; // text(19),
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::notes            = "notes"            ; // text(2048) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::active           = "active"           ; // integer NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::currency         = "currency"         ; // text(32) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::owner_type       = "owner_type"       ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::owner_guid       = "owner_guid"       ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::terms            = "terms"            ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::billing_id       = "billing_id"       ; // text(2048),
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::post_txn         = "post_txn"         ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::post_lot         = "post_lot"         ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::post_acc         = "post_acc"         ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::billto_type      = "billto_type"      ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::billto_guid      = "billto_guid"      ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::charge_amt_num   = "charge_amt_num"   ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::Invoices::Field::charge_amt_denom = "charge_amt_denom" ; // bigint

auto
GCW::Dbo::Invoices::
load( const std::string & _guid )-> GCW::Dbo::Invoices::Item::Ptr
{
  GCW::Dbo::Invoices::Item::Ptr retVal;

  if( _guid != "" )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    try
    {
      retVal =
        GCW::app()-> gnucashew_session().load< GCW::Dbo::Invoices::Item >( _guid )
        ;
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }
  }

  return retVal;

} // endload( const std::string & _guid )-> GCW::Dbo::Invoices::Item::Ptr

auto
GCW::Dbo::Invoices::
byGuid( const std::string & _guid )-> GCW::Dbo::Invoices::Item::Ptr
{
  return GCW::Dbo::Invoices::load( _guid );

} // endbyGuid( const std::string & _guid )-> GCW::Dbo::Invoices::Item::Ptr


