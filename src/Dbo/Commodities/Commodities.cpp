#line 2 "src/Dbo/Commodities/Commodities.cpp"

#include <fstream>

#include "../Glb/Core.h"
#include "../App.h"
#include "../../3rd/RapidXML/rapidxml.hpp"
#include "Commodities.h"

namespace {

/*
** This is a simple heap dynamic buffer, that deletes when it goes out of scope.
*/
class DynBuf
{
  public:

    char * buffer;

    DynBuf( int size )
    {
      buffer = new char[size];
    }

    ~DynBuf()
    {
      delete buffer;
    }
};

}

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
  return GCW::Dbo::Commodities::load( _guid );

} // endbyGuid( const std::string & _guid )-> GCW::Dbo::Commodities::Item::Ptr



auto
GCW::Dbo::Commodities::
getIso4217Commodities()-> std::vector< Commodity_t >
{
  std::vector< Commodity_t > retVal;

  /*·
  ** Open the file and read it all in to memory
  **
  */
  std::ifstream inFile;
  inFile.open( wApp-> docRoot() + "/iso-4217-currencies.xml" );

  if( inFile.fail() )
    return retVal;

  inFile.seekg( 0, std::ios::end );
  std::streampos length = inFile.tellg();
  inFile.seekg( 0, std::ios::beg );

  /*
  ** make a little empty space in the buffer for adding
  **  zero terminated strings, or whatever it is that the
  **  rapid xml does to the content to manipulate it.  Note
  **  that it's possible to cause rapidxml to not modify
  **  the buffer at all, but then every string that gets pulled
  **  out of the buffer has to be tested for actual length
  **  and any strings derived from that need to include that
  **  length parameter.
  **
  */
  DynBuf db(((int)length)+10000);
  inFile.read( db.buffer, length );
  inFile.close();

  db.buffer[length] = 0;

  /*
  ** Parse-in the XML file
  **
  */
  rapidxml::xml_document<> doc;
  try
  {
    doc.parse<0>( db.buffer );
  }
  catch( std::exception & err )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << err.what() << std::endl;
    return retVal;
  }

  auto _processCurrency = [&]( rapidxml::xml_node<> * topNode )
  {
    for( auto node = topNode-> first_node(); node; node = node-> next_sibling() )
    {
      Commodity_t commodity =
      {
        node-> first_attribute( "isocode"           )-> value(),
        node-> first_attribute( "fullname"          )-> value(),
        node-> first_attribute( "unitname"          )-> value(),
        node-> first_attribute( "partname"          )-> value(),
        node-> first_attribute( "namespace"         )-> value(),
        node-> first_attribute( "exchange-code"     )-> value(),
        node-> first_attribute( "parts-per-unit"    )-> value(),
        node-> first_attribute( "smallest-fraction" )-> value(),
        node-> first_attribute( "local-symbol"      )-> value()
      };

      retVal.push_back( commodity );

    } // endfor( auto node = topNode-> first_node(); node; node = node-> next_sibling() )

  }; // endauto _processObservation = [=]( rapidxml::xml_node<> * topNode )

  for( auto node = doc.first_node(); node; node = node-> next_sibling() )
  {
    if( std::string(node-> name()) == "currencylist" )
      _processCurrency( node );
  }

  return retVal;

} // endgetIso4217Commodities()-> std::vector< Commodity_t >




