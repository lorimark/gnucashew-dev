#line 2 "src/Dbo/Versions/Versions.cpp"

#include <gnucash/gnc-session.h>

#include "../App.h"
#include "../Glb/Core.h"

#include "Versions.h"

const char * GCW::Dbo::Versions::s_tableName = "versions";

const Wt::WFormModel::Field GCW::Dbo::Versions::Field::table_name       = "table_name"       ; // text(50) PRIMARY KEY NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Versions::Field::table_version    = "table_version"    ; // integer NOT NULL

auto
GCW::Dbo::Versions::
load( const std::string & _table_name )-> GCW::Dbo::Versions::Item::Ptr
{
  GCW::Dbo::Versions::Item::Ptr retVal;

  if( _table_name != "" )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    try
    {
      retVal =
        GCW::app()-> gnucashew_session().find< GCW::Dbo::Versions::Item >()
        .where( "table_name = ?" )
        .bind( _table_name )
        .resultValue()
        ;
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }
  }

  return retVal;

} // endload( const std::string & _guid )-> GCW::Dbo::Versions::Item::Ptr



