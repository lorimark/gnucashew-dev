#line 2 "src/Dbo/Commodities/Commodities.cpp"

#include "../Glb/Core.h"
#include "../App.h"
#include "Commodities.h"

const char * GCW::Dbo::Commodities::s_tableName = "commodities";

const Wt::WFormModel::Field GCW::Dbo::Commodities::Field::guid          = "guid"         ; // text(32) PRIMARY KEY NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Commodities::Field::nameSpace     = "namespace"    ; // text(2048) NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Commodities::Field::mnemonic      = "mnemonic"     ; // text(2048) NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Commodities::Field::fullname      = "fullname"     ; // text(2048)
const Wt::WFormModel::Field GCW::Dbo::Commodities::Field::cusip         = "cusip"        ; // text(2048)
const Wt::WFormModel::Field GCW::Dbo::Commodities::Field::fraction      = "fraction"     ; // integer NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Commodities::Field::quote_flag    = "quote_flag"   ; // integer NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Commodities::Field::quote_source  = "quote_source" ; // text(2048)
const Wt::WFormModel::Field GCW::Dbo::Commodities::Field::quote_tz      = "quote_tz"     ; // text(2048)

auto
GCW::Dbo::Commodities::
load( const std::string & _guid )-> GCW::Dbo::Commodities::Item::Ptr
{
  GCW::Dbo::Commodities::Item::Ptr retVal;

  if( _guid != "" )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    try
    {
      retVal =
        GCW::app()-> gnucashew_session().load< GCW::Dbo::Commodities::Item >( _guid )
        ;
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }
  }

  return retVal;

} // endload( const std::string & _guid )-> GCW::Dbo::Commodities::Item::Ptr

auto
GCW::Dbo::Commodities::
byGuid( const std::string & _guid )-> GCW::Dbo::Commodities::Item::Ptr
{
  return load( _guid );

} // endbyGuid( const std::string & _guid )-> GCW::Dbo::Commodities::Item::Ptr

