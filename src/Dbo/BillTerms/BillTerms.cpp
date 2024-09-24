#line 2 "src/Dbo/BillTerms/BillTerms.cpp"

#include <gnucash/gnc-session.h>

#include "../App.h"
#include "../Glb/Core.h"

#include "BillTerms.h"

const char * GCW::Dbo::BillTerms::s_tableName = "billterms";

const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::guid           = "guid"           ; // text(32) PRIMARY KEY NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::name           = "name"           ; // text(2048) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::description    = "description"    ; // text(2048) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::refcount       = "refcount"       ; // integer NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::invisible      = "invisible"      ; // integer NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::parent         = "parent"         ; // text(32),
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::type           = "type"           ; // text(2048) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::duedays        = "duedays"        ; // integer,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::discountdays   = "discountdays"   ; // integer,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::discount_num   = "discount_num"   ; //  bigint,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::discount_denom = "discount_denom" ; // bigint,
const Wt::WFormModel::Field GCW::Dbo::BillTerms::Field::cutoff         = "cutoff"         ; // integer

auto
GCW::Dbo::BillTerms::
load( const std::string & _guid )-> GCW::Dbo::BillTerms::Item::Ptr
{
  GCW::Dbo::BillTerms::Item::Ptr retVal;

  if( _guid != "" )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    try
    {
      retVal =
        GCW::app()-> gnucashew_session().load< GCW::Dbo::BillTerms::Item >( _guid )
        ;
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }
  }

  return retVal;

} // endload( const std::string & _guid )-> GCW::Dbo::BillTerms::Item::Ptr

auto
GCW::Dbo::BillTerms::
byGuid( const std::string & _guid )-> GCW::Dbo::BillTerms::Item::Ptr
{
  return load( _guid );

} // endbyGuid( const std::string & _guid )-> GCW::Dbo::BillTerms::Item::Ptr


