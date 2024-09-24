
#include <gnucash/gnc-session.h>
#include <gnucash/Account.h>

#include "../App.h"
#include "../Glb/Core.h"

#include "Entries.h"

const char * GCW::Dbo::Entries::s_tableName = "entries";

const Wt::WFormModel::Field GCW::Dbo::Entries::Field::guid             = "guid"             ; // text(32) PRIMARY KEY NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::date             = "date"             ; //  text(19) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::date_entered     = "date_entered"     ; //  text(19),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::description      = "description"      ; //  text(2048),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::action           = "action"           ; //  text(2048),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::notes            = "notes"            ; // text(2048),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::quantity_num     = "quantity_num"     ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::quantity_denom   = "quantity_denom"   ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_acct           = "i_acct"           ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_price_num      = "i_price_num"      ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_price_denom    = "i_price_denom"    ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_discount_num   = "i_discount_num"   ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_discount_denom = "i_discount_denom" ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::invoice          = "invoice"          ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_disc_type      = "i_disc_type"      ; // text(2048),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_disc_how       = "i_disc_how"       ; // text(2048),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_taxable        = "i_taxable"        ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_taxincluded    = "i_taxincluded"    ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::i_taxtable       = "i_taxtable"       ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::b_acct           = "b_acct"           ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::b_price_num      = "b_price_num"      ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::b_price_denom    = "b_price_denom"    ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::bill             = "bill"             ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::b_taxable        = "b_taxable"        ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::b_taxincluded    = "b_taxincluded"    ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::b_taxtable       = "b_taxtable"       ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::b_paytype        = "b_paytype"        ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::billable         = "billable"         ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::billto_type      = "billto_type"      ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::billto_guid      = "billto_guid"      ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::Entries::Field::order_guid       = "order_guid"       ; // text(32)

auto
GCW::Dbo::Entries::
load( const std::string & _guid )-> GCW::Dbo::Entries::Item::Ptr
{
  GCW::Dbo::Entries::Item::Ptr retVal;

  if( _guid != "" )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    try
    {
      retVal =
        GCW::app()-> gnucashew_session().load< GCW::Dbo::Entries::Item >( _guid )
        ;
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }
  }

  return retVal;

} // endload( const std::string & _guid )-> GCW::Dbo::Entries::Item::Ptr

auto
GCW::Dbo::Entries::
byGuid( const std::string & _guid )-> GCW::Dbo::Entries::Item::Ptr
{
  return load( _guid );

} // endbyGuid( const std::string & _guid )-> GCW::Dbo::Accounts::Item::Ptr


