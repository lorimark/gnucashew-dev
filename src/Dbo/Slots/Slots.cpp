#line 2 "src/Dbo/Slots.cpp"

#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Serializer.h>

#include "../App.h"
#include "Slots.h"


const char * GCW::Dbo::Slots::s_tableName = "slots";

Wt::WFormModel::Field GCW::Dbo::Slots::Field::id                 = "id"                ; // integer PRIMARY KEY AUTOINCREMENT NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Slots::Field::obj_guid           = "obj_guid"          ; // text(32) NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Slots::Field::name               = "name"              ; // text(4096) NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Slots::Field::slot_type          = "slot_type"         ; // integer NOT NULL,
Wt::WFormModel::Field GCW::Dbo::Slots::Field::int64_val          = "int64_val"         ; // bigint,
Wt::WFormModel::Field GCW::Dbo::Slots::Field::string_val         = "string_val"        ; // text(4096),
Wt::WFormModel::Field GCW::Dbo::Slots::Field::double_val         = "double_val"        ; // float8,
Wt::WFormModel::Field GCW::Dbo::Slots::Field::timespec_val       = "timespec_val"      ; // text(19),
Wt::WFormModel::Field GCW::Dbo::Slots::Field::guid_val           = "guid_val"          ; // text(32),
Wt::WFormModel::Field GCW::Dbo::Slots::Field::numeric_val_num    = "numeric_val_num"   ; // bigint,
Wt::WFormModel::Field GCW::Dbo::Slots::Field::numeric_val_denom  = "numeric_val_denom" ; // bigint,
Wt::WFormModel::Field GCW::Dbo::Slots::Field::gdate_val          = "gdate_val"         ; // text(8)



GCW::Dbo::Slots::Item::Vector
GCW::Dbo::Slots::
get()
{
  GCW::Dbo::Slots::Item::Vector retVal;

  /*
  **
  */
  auto resultList =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Slots::Item >()
      .resultList()
      ;

  for( auto & result : resultList )
    retVal.push_back( result );

  return retVal;

} // endget()


GCW::Dbo::Slots::Item::Ptr
GCW::Dbo::Slots::
get( const std::string & _guid, const std::string & _name )
{
  GCW::Dbo::Slots::Item::Ptr retVal;

  /*
  ** Build a 'where' that has both the key and cfy
  **  fields represented.
  **
  */
  auto where =
    Wt::WString( "\"obj_guid\" = '{1}'" )
    .arg( _guid )
    .toUTF8()
    ;

  if( _name != "*"
   && _name != ""
    )
    where +=
      Wt::WString( " AND \"name\" = '{1}'" )
      .arg( _name )
      .toUTF8()
      ;

  /*
  ** find the item (or try to)
  **
  */
  retVal =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Slots::Item >()
      .where( where )
      .resultValue()
      ;

  return retVal;

} // endget( const std::string & _keyValue, const std::string & _cfyValue )

#ifdef NEVER
std::string
GCW::Dbo::Vars::Item::
getVarString( const std::string & _field ) const
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

} // endgetVarString( const std::string & _field ) const

int
GCW::Dbo::Vars::Item::
getVarInt( const std::string & _field ) const
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

} // endgetVarInt( const std::string & _field ) const

void
GCW::Dbo::Vars::Item::
setVar( const std::string & _field, const char * _value )
{
  setVar( _field, std::string( _value ) );

} // endsetVar( const std::string & _field, const std::string & _value )

void
GCW::Dbo::Vars::Item::
setVar( const std::string & _field, const Wt::WString & _value )
{
  setVar( _field, _value.toUTF8() );

} // endsetVar( const std::string & _field, const std::string & _value )

void
GCW::Dbo::Vars::Item::
setVar( const std::string & _field, const std::string & _value )
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

} // endsetVar( const std::string & _field, const std::string & _value )

void
GCW::Dbo::Vars::Item::
setVar( const std::string & _field, int _value )
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

} // endsetVar( const std::string & _field, int & _value )


#endif

