#line 2 "src/Dbo/Books/Books.cpp"

#include "../App.h"
#include "../Glb/Core.h"

#include "Books.h"

const char * GCW::Dbo::Books::s_tableName = "books";

const Wt::WFormModel::Field GCW::Dbo::Books::Field::guid               = "guid"               ; // text(32) PRIMARY KEY NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Books::Field::root_account_guid  = "root_account_guid"  ; // text(32) NOT NULL,
const Wt::WFormModel::Field GCW::Dbo::Books::Field::root_template_guid = "root_template_guid" ; // text(32) NOT NULL

auto
GCW::Dbo::Books::
load( const std::string & _guid )-> GCW::Dbo::Books::Item::Ptr
{
  GCW::Dbo::Books::Item::Ptr retVal;

  if( _guid != "" )
  {

    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    try
    {
      retVal =
        GCW::app()-> gnucashew_session().load< GCW::Dbo::Books::Item >( _guid )
        ;
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
    }
  }

  return retVal;

} // endload( const std::string & _guid )-> GCW::Dbo::Books::Item::Ptr

auto
GCW::Dbo::Books::
byGuid( const std::string & _guid )-> GCW::Dbo::Books::Item::Ptr
{
  return load( _guid );

} // endbyGuid( const std::string & _guid )-> GCW::Dbo::Books::Item::Ptr


