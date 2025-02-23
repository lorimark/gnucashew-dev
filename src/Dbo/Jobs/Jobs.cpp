#line 2 "src/Dbo/Jobs/Jobs.cpp"

#include "../App.h"
#include "../Glb/Core.h"

#include "Jobs.h"

const char * GCW::Dbo::Jobs::s_tableName = "jobs";

const Wt::WFormModel::Field GCW::Dbo::Jobs::Field::guid             = "guid"       ; // text(32) PRIMARY KEY NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Jobs::Field::id               = "id"         ; // text(2048)           NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Jobs::Field::name             = "name"       ; // text(2048)           NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Jobs::Field::reference        = "reference"  ; // text(2048)           NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Jobs::Field::active           = "active"     ; // integer              NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Jobs::Field::owner_type       = "owner_type" ; // integer,
const Wt::WFormModel::Field GCW::Dbo::Jobs::Field::owner_guid       = "owner_guid" ; // text(32),

auto
GCW::Dbo::Jobs::
load( const std::string & _guid )-> GCW::Dbo::Jobs::Item::Ptr
{
  GCW::Dbo::Jobs::Item::Ptr retVal;

  if( _guid != "" )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    try
    {
      retVal =
        GCW::app()-> gnucashew_session().load< GCW::Dbo::Jobs::Item >( _guid )
        ;
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }
  }

  return retVal;

} // endload( const std::string & _guid )-> GCW::Dbo::Jobs::Item::Ptr

auto
GCW::Dbo::Jobs::
byGuid( const std::string & _guid )-> GCW::Dbo::Jobs::Item::Ptr
{
  return GCW::Dbo::Jobs::load( _guid );

} // endbyGuid( const std::string & _guid )-> GCW::Dbo::Jobs::Item::Ptr


