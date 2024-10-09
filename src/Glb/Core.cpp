#line 2 "src/Glb/Core.cpp"

#include <sstream>
#include <algorithm>

#include <Wt/WModelIndex.h>
#include <Wt/WDateTime.h>
#include <Wt/WLocalDateTime.h>

#include "../3rd/guid.hpp"
#include "gcwglobal.h"
#include "Core.h"

static
std::vector<std::string> &
split( const std::string & s, char delim, std::vector<std::string> & elems )
{
  std::stringstream ss( s );
  std::string item;
  while( std::getline( ss, item, delim ) )
  {
    elems.push_back( item );
  }
  return elems;
}


std::vector<std::string>
GCW::Core::
split( const std::string & s, char delim )
{
  std::vector<std::string> elems;
  ::split( s, delim, elems );
  return elems;
}

const char* GCW::Core::trim_ws = " \t\n\r\f\v";

// trim from end of string (right)
std::string &
GCW::Core::
rtrim( std::string & s, const char* t )
{
  s.erase( s.find_last_not_of(t) + 1 );
  return s;
}

// trim from beginning of string (left)
std::string &
GCW::Core::
ltrim( std::string & s, const char* t )
{
  s.erase( 0, s.find_first_not_of(t) );
  return s;
}

// trim from both ends of string (left & right)
std::string &
GCW::Core::
trim( std::string & s, const char* t )
{
  return ltrim( rtrim(s, t), t );
}

std::string
GCW::Core::
toupper( const std::string & s )
{
  std::string retVal = s;

  std::transform( retVal.begin(), retVal.end(), retVal.begin(), ::toupper );

  return retVal;
}

std::string
GCW::Core::
tolower( const std::string & s )
{
  std::string retVal = s;

  std::transform( retVal.begin(), retVal.end(), retVal.begin(), ::tolower );

  return retVal;
}

/*
** This will iterate a single a WTreeView and fill
**  a vector of every node which is the .last-expanded.
**  node of every branch.
**
*/
static
bool
iterate( Wt::Json::Array & _jary, Wt::WModelIndex _parent )
{
#ifdef NEVER
  /*
  ** If this _parent node is not expanded, then we're basically done.
  **
  */
  if( !view()-> isExpanded( _parent ) )
    return false;

  /*
  ** This _parent node is expanded, so loop through all the
  **  child nodes checking if any of them are expanded.
  **
  */
  bool expanded = false;
  for( int row=0; row< view()-> model()-> rowCount( _parent ); row++ )
    expanded |= iterate( _jary, view()-> model()-> index( row, 0, _parent ) );

  /*
  ** None of the child nodes are expanded, so record this _parent
  **  node as the 'last' node in the tree
  **
  */
  if( !expanded )
  {
    /*
    ** The true root node is not associated with an actual account,
    **  it is simply the invisibleRoot of the tree itself, and only
    **  contains the set of first-root nodes that actually get
    **  displayed.  So, there is no User data in this one, don't record it.
    **
    */
    auto accountGuid = Wt::asString( _parent.data( Wt::ItemDataRole::User ) );
    if( accountGuid != "" )
      _jary.push_back( accountGuid );

  } // endif( !expanded )

  /*
  ** Something is expanded.  Either we are expanded, or
  **  one of the sub-nodes are expanded, so return that 'someone' is
  **  expanded.
  **
  */
#endif

  return true;

} // endvoid iterate( Wt::WModelIndex _index ) const

Wt::Json::Object
GCW::Core::
toJson( Wt::WTreeView * _view )
{
  Wt::Json::Object jobj;

#ifdef NEVER
  jobj["selected"] = Wt::WString( selectedAccount() );

  for( int col=0; col< 7; col++ )
    jobj[ Wt::WString("cw{1}").arg( col ).toUTF8() ] = Wt::WString( view()-> columnWidth( col ).cssText() );

  Wt::Json::Array jary;
  iterate( jary );
  jobj["expanded"] = jary;

#endif

  return jobj;

}

auto
GCW::Core::
hexDump( const std::string & string, int start, int end )-> std::string
{
  std::stringstream rv;

  char buffer[100];
  for( unsigned int i=0; i<string.length(); i += 16 )
  {
    std::string adrLine;
    std::string hexLine;
    std::string ascLine;

    sprintf( buffer, "%04x: ", i );
    adrLine = std::string(buffer);

    for( int j=0; j<16; j++ )
    {
      if( i+j < string.length() )
      {
        sprintf( buffer, "%02x ", (string.at(i+j) & 0xff) );
        hexLine += std::string(buffer);

        if( std::isprint( string.at(i+j) ) )
        {
          sprintf( buffer, "%c", string.at(i+j) );
          ascLine += std::string(buffer);
        }
        else
        {
          ascLine += ".";
        }
      }
      else
      {
        hexLine += "xx ";
        ascLine += ".";
      }

    } // endfor( int j=0; j<16; j++ )

    bool showline = false;
    if( start == -1 && end == -1 )
      showline = true;

    else
      if( (start > -1 && i >= start)
      &&  (end   > -1 && i <= end)
        )
        showline = true;

    if( showline )
      rv
        << adrLine
        << hexLine
        << ascLine
        << std::endl
        ;

  } // endfor( int i=0; i<string.length(); i += 16 )

  return rv.str();

} // endstd::string GCW::hexDump( const std::string & string )

auto
GCW::Core::
newGuid()-> std::string
{
  std::string g = xg::newGuid();

  std::string retVal;
  for( auto c : g )
    if( c != '-' )
      retVal.push_back( c );

  return retVal;

} // endnewGuid()-> std::string


/*
** note about this date time:
**  WLocalDateTime will produce the local-time
**  WDateTime will product a GMT time
**
** This was tested, and gnucash seems to want the GMT time-stamp
**  rather than the local time (makes sense really)
**
*/
auto
GCW::Core::
currentDateTime()-> Wt::WDateTime
{
  return
//    Wt::WLocalDateTime::currentDateTime().toString( GCW_DATE_FORMAT ).toUTF8();
    Wt::WDateTime::currentDateTime();

} // endcurrentDateTime()-> std::string


/*
** note about this date time:
**  WLocalDateTime will produce the local-time
**  WDateTime will product a GMT time
**
** This was tested, and gnucash seems to want the GMT time-stamp
**  rather than the local time (makes sense really)
**
*/
auto
GCW::Core::
currentDateTimeStorageString()-> std::string
{
  return
    currentDateTime().toString( GCW_DATE_FORMAT_STORAGE ).toUTF8();

} // endcurrentDateTime()-> std::string



