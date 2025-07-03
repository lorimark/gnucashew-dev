#line 2 "src/Dbo/Vars.cpp"

#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Serializer.h>

#include "../App.h"
#include "Vars.h"


const char * GCW::Dbo::Vars::s_tableName = "gcw_vars";


auto
GCW::Dbo::Vars::
get( const std::string & _keyValue, const std::string & _cfyValue, bool _add )-> GCW::Dbo::Vars::Item::Ptr
{
  GCW::Dbo::Vars::Item::Ptr retVal;

  /*
  ** Build a 'where' that has both the key and cfy
  **  fields represented.
  **
  */
  auto where =
    Wt::WString( "\"keyField\" = '{1}'" )
    .arg( _keyValue )
    .toUTF8()
    ;

  if( _cfyValue != "*" )
    where +=
      Wt::WString( " AND \"cfyField\" = '{1}'" )
      .arg( _cfyValue )
      .toUTF8()
      ;

  /*
  ** find the item (or try to)
  **
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  retVal =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Vars::Item >()
      .where( where )
      .resultValue()
      ;

  /*
  ** if an item could not be found then create one, setting in
  **  the key and cfy if available.
  **
  */
  if( !retVal && _add )
  {
    retVal =
      GCW::app()-> gnucashew_session().addNew< GCW::Dbo::Vars::Item >()
        ;

    retVal.modify()-> setKeyField( _keyValue );

    if( _cfyValue != "*" )
      retVal.modify()-> setCfyField( _cfyValue );

    retVal.flush();

  } // endif( !retVal )

  return retVal;

} // endget( const std::string & _keyValue, const std::string & _cfyValue )-> GCW::Dbo::Vars::Item::Ptr

auto
GCW::Dbo::Vars::
getByCfy( const std::string & _cfyValue )-> GCW::Dbo::Vars::Item::Vector
{
  GCW::Dbo::Vars::Item::Vector retVal;

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  auto items =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Vars::Item >()
      .where( "\"cfyField\" = '" + _cfyValue + "'" )
      .resultList()
      ;

  for( auto item : items )
    retVal.push_back( item );

  return retVal;

} // endget( const std::string & _keyValue, const std::string & _cfyValue )-> GCW::Dbo::Vars::Item::Ptr

auto
GCW::Dbo::Vars::Item::
getVarString( const std::string & _field ) const-> std::string
{
  std::string retVal;

  if( _field != "" )
  {
    Wt::Json::Object jobj;
    try {
       Wt::Json::parse( varField(), jobj );
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " id:" << this-> id() << " " << e.what() << std::endl;
    }

    retVal = jobj.get( _field ).orIfNull("");

  }

  return retVal;

} // endgetVarString( const std::string & _field ) const-> std::string

auto
GCW::Dbo::Vars::Item::
getVarInt( const std::string & _field ) const-> int
{
  int retVal = 0;

  if( _field != "" )
  {
    Wt::Json::Object jobj;
    try {
       Wt::Json::parse( varField(), jobj );
    }
    catch( std::exception & e )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " id:" << this-> id() << " " << e.what() << std::endl;
    }

    retVal = jobj.get( _field ).orIfNull( 0 );

  }

  return retVal;

} // endgetVarInt( const std::string & _field ) const-> int

auto
GCW::Dbo::Vars::Item::
setVar( const std::string & _field, const char * _value )-> void
{
  setVar( _field, std::string( _value ) );

} // endsetVar( const std::string & _field, const char * _value )-> void

auto
GCW::Dbo::Vars::Item::
setVar( const std::string & _field, const Wt::WString & _value )-> void
{
  setVar( _field, _value.toUTF8() );

} // endsetVar( const std::string & _field, const Wt::WString & _value )-> void

auto
GCW::Dbo::Vars::Item::
setVar( const std::string & _field, const std::string & _value )-> void
{
  /*
  ** If there is no field specified, then there's nothing
  **  to do.
  **
  */
  if( _field == "" )
    return;

  Wt::Json::Object jobj;
  try {
    Wt::Json::parse( varField(), jobj );

  }
  catch( std::exception & e )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " id:" << this-> id() << " " << e.what() << std::endl;
  }

  jobj[_field] = Wt::WString( _value );

  setVarField( Wt::Json::serialize( jobj ) );

} // endsetVar( const std::string & _field, const std::string & _value )-> void

auto
GCW::Dbo::Vars::Item::
setVar( const std::string & _field, int _value )-> void
{
  /*
  ** If there is no field specified, then there's nothing
  **  to do.
  **
  */
  if( _field == "" )
    return;

  Wt::Json::Object jobj;
  try {
    Wt::Json::parse( varField(), jobj );
  }
  catch( std::exception & e )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " id:" << this-> id() << " " << e.what() << std::endl;
  }

  jobj[_field] = _value;

  setVarField( Wt::Json::serialize( jobj ) );

} // endsetVar( const std::string & _field, int _value )-> void



