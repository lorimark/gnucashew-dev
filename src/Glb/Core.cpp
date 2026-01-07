#line 2 "src/Glb/Core.cpp"

#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <sys/stat.h>
#include <unistd.h>
#include <locale.h>


#include <Wt/WModelIndex.h>
#include <Wt/WDate.h>
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

    snprintf( buffer, sizeof(buffer), "%04x: ", i );
    adrLine = std::string(buffer);

    for( int j=0; j<16; j++ )
    {
      if( i+j < string.length() )
      {
        snprintf( buffer, sizeof(buffer), "%02x ", (string.at(i+j) & 0xff) );
        hexLine += std::string(buffer);

        if( std::isprint( string.at(i+j) ) )
        {
          snprintf( buffer, sizeof(buffer), "%c", string.at(i+j) );
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

auto
dateStorageString( const Wt::WDate * _date )-> std::string
{
  return
    _date-> toString( GCW_DATE_FORMAT_STORAGE ).toUTF8();

}

auto
GCW::Core::
dateTimeStorageString( const Wt::WDateTime & _dateTime )-> std::string
{
  return
    _dateTime.toString( GCW_DATETIME_FORMAT_STORAGE ).toUTF8();

} // enddateTimeStorageString( const Wt::WDateTime & _dateTime )-> std::string

/*
**
*/
auto
GCW::Core::
currentDateTimeStorageString()-> std::string
{
  return
    dateTimeStorageString( currentDateTime() );

} // endcurrentDateTime()-> std::string

auto
GCW::Core::
dateTimeDisplayString( const Wt::WDateTime & _dateTime )-> std::string
{
  return
    _dateTime.toString( GCW_DATE_FORMAT_DISPLAY ).toUTF8();

} // enddateTimeDisplayString( const Wt::WDateTime & _dateTime )-> std::string

/*
**
*/
auto
GCW::Core::
currentDateTimeDisplayString()-> std::string
{
  return
    dateTimeDisplayString( currentDateTime() );

} // endcurrentDateTime()-> std::string


/*!
** \brief Make File Name
**
** This will take an odrinary string and remove anything that is not
**  acceptable in a valid file-name.  The intended use for this function
**  is to take something like a person's name or a company name and remove
**  and replace anything in those strings that might not produce a
**  disk-compatible file-name.  This includes things like ':' colons and
**  '/' forward and back slashes and anything else that looks just
**  plain weird.
**
*/
auto
GCW::Core::
makeFileName( const std::string & value )-> std::string
{
  std::string retVal;

  /*
  ** each character is examined individually
  */
  for( auto ch : value )
  {
    /*!
    ** All non-printable characters are simply discarded
    */
    if( isprint( ch ) )
    {
      /*!
      **  The routine performs simple character-by-character
      **  substitution.  In some cases the substitution is 'nothing',
      **  like in the case of '.' (period) and ',' (comma)
      **  other characters are simply replaced with suitable
      **  replacements that have similar appearance but are
      **  not likely to mess up a file-name on disk.  Odd punctuation
      **  characters are removed since this function is a string-to-filename
      **  conversion, therefore absolute punctuation has less meaning
      **  in a file-name than it does in the database.
      **
      ** \par Examples
      ** \code
      ** std::cout << makeFileName("LORIMARK SOLUTIONS, LLC.") << std::endl;
      ** std::cout << makeFileName("Bridge On The River Kwai") << std::endl;
      ** std::cout << makeFileName("He said \"no\", She said \"yes\"") << std::endl;
      ** std::cout << makeFileName("Chicago <south> Storage_Facility") << std::endl;
      ** std::cout << makeFileName("Boat (float) :/: or Ship Sink") << std::endl;
      **
      ** result:
      **  LORIMARK SOLUTIONS LLC
      **  Bridge On The River Kwai
      **  He said 'no' She said 'yes'
      **  Chicago (south) Storage_Facility
      **  Boat (float) -- or Ship Sink
      ** \endcode
      **
      */
      switch( ch )
      {
        case '.':                   break; /// '.' period               -> nothing
        case ',':                   break; /// ',' comma                -> nothing
        case '<':   retVal += '(';  break; /// '<' less than            -> open paren
        case '>':   retVal += ')';  break; /// '>' greater than         -> close paren
        case ':':   retVal += '-';  break; /// ':' colon                -> dash ~ sometimes works, but is actually NTFS Alternate Data Streams
        case '"':   retVal += '\''; break; /// '"' double quote         -> single quote
        case '/':   retVal += '-';  break; /// '/' forward slash        -> dash
        case '\\':  retVal += '-';  break; /// '\\'backslash            -> dash
        case '|':                   break; /// '|' vertical bar or pipe -> nothing
        case '?':                   break; /// '?' question mark        -> nothing
        case '*':                   break; /// '*' asterisk             -> nothing
        default:    retVal += ch;

      } // endswitch( ch )

    } // endif( isprint( ch ) )

  } // endfor( auto ch : value )

  return retVal;

} // endmakeFileName( const std::string & value )-> std::string


auto
GCW::Core::
system_command( const std::string & cmd, bool show )-> int
{
  int result = system( cmd.c_str() );

  if( show )
    std::cout << __FILE__ << ":" << __LINE__ << " " << cmd << std::endl;



  if( result != 0 )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " "
      << result << " "
      << cmd
      << std::endl
      ;
  }

  return result;

} // endsystem_command( const std::string & cmd, bool show )-> auto

/*
** This function produces a case-insensitive sort of
**  the files and folders in a directory.  The file
**  items are converted to upper-case so that case
**  becomes ignored, and then the function uses the
**  strverscmp function which causes jan-1, jan-2,
**  jan-10 to be sorted in that order, which can
**  make a little more logical sense when looking at
**  folder names.
**
** https://linux.die.net/man/3/scandir
**
*/
static auto
ialphasort( const struct dirent **a, const struct dirent **b )-> int
{
  std::string ua = (*a)-> d_name;
  std::transform( ua.begin(), ua.end(), ua.begin(), ::toupper );

  std::string ub = (*b)-> d_name;
  std::transform( ub.begin(), ub.end(), ub.begin(), ::toupper );

  return strverscmp( ua.c_str(), ub.c_str() );

} // endialphasort( const struct dirent **a, const struct dirent **b )-> int


auto
GCW::Core::
fileList( const std::string & folder )-> std::vector<std::string>
{
  std::vector<std::string> retVal;

  /*
  ** pull up all the items in this folder
  **
  */
  struct dirent ** namelist;
  int n = scandir( folder.c_str(), &namelist, 0, ialphasort );

  if( n > 0 )
  {
    /*
    ** loop through all the items in the folder
    **
    */
    for( int i=0; i< n; i++ )
    {
      /*
      ** pull the folder name from the items list
      **  and free the original source
      **
      */
      std::string fileName( namelist[i]-> d_name );
      free( namelist[i] );

      /*
      ** single '.' dot items are ignored totally
      */
      if( fileName == "." )
        continue;

      /*
      ** make something that represents the full file path
      **
      */
      std::string filePath( folder + "/" + fileName );

      /*
      ** the 'fileStat' value contains the following flags
      **  and status codes.  grab the filestat based on the 'stat'
      **  function call so that the file can be parsed.
      **
      **  st_atime
      **  st_ctime
      **  st_gid
      **  st_ino
      **  st_mtime·
      **  st_nlink·
      **  st_mode·
      **  st_size·
      **  st_uid·
      **
      */
      struct stat fileStat;
      int result = stat( filePath.c_str(), &fileStat );

      /*
      ** there should always be a result on pulling the
      **  file stat.
      */
      if( result == 0 )
      {
        retVal.push_back( fileName );
      }

    } // endfor( int i=0; i< n; i++ )

    free( namelist );

  } // endif( n > 0 )

  return retVal;

} // endfileList( const std::string & folder )-> std::vector<std::string>


auto
GCW::Core::
findFiles( const std::string & folder, const std::string & match )-> std::vector<std::string>
{
  std::vector<std::string> retVal;

  for( auto fileName : fileList( folder ) )
    if( fileName.find(match) != std::string::npos )
      retVal.push_back( fileName );

  return retVal;

} // endfindFiles( const std::string & folder, const std::string & match )-> std::vector<std::string>


auto
GCW::Core::
fileExists( const std::string & fileName )-> bool
{
  std::ifstream f( fileName.c_str() );
  return f.good();

} // endfileExists( const std::string & fileName )-> bool


auto
GCW::Core::
stoi( const std::string & value )-> int
{
  try
  {
    int id = std::stoi(value);
    return id;
  }
  catch(...)
  {
//    std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "::value='" << value << "'" << std::endl;
  }

  return 0;

} // endstoi( const std::string & value )-> int


auto
GCW::Core::
itos( int value )-> std::string
{
  return
    Wt::WString("{1}")
    .arg( value )
    .toUTF8()
    ;

} // enditos( int value )-> std::string


auto
GCW::Core::
stof( const std::string & value )-> double 
{
  try
  {
    std::string v;
    for( auto c : value )
      if( isdigit(c) ||  c == '.' || c == '-' )
        v.push_back(c);

    if( v.length() > 0 )
    {
      double id = std::stod(v);
      return id;
    }

  }
  catch(...)
  {
  }

  return 0;

} // endstof( const std::string & value )-> double 


auto
GCW::Core::
ftos( double value, int decimals )-> std::string
{
  char buffer[256];

  snprintf( buffer, sizeof(buffer), "%.*f", decimals, value );

  return std::string(buffer);

} // endftos( double value, int decimals )-> std::string


auto
GCW::Core::
ftos( double value, const std::string & suffix, int decimals )-> std::string
{
  char buffer[256];

  snprintf( buffer, sizeof(buffer), "%.*f%s", decimals, value, suffix.data() );

  return std::string(buffer);

} // endftos( double value, const std::string & suffix, int decimals )-> std::string


auto
GCW::Core::
ftos( const std::string & prefix, double value, int decimals )-> std::string
{
  char buffer[256];

  snprintf( buffer, sizeof(buffer), "%s%.*f", prefix.data(), decimals, value );

  return std::string(buffer);

} // endftos( const std::string & prefix, double value, int decimals )-> std::string


auto
GCW::Core::
ftom( double value, int decimals )-> std::string
{
  char buffer[256];

  std::setlocale( LC_ALL, "" );
  snprintf( buffer, sizeof(buffer), "%'.*f", decimals, value );

  return std::string(buffer);

} // endftom( double value, int decimals )-> std::string

auto
GCW::Core::
ftom( const std::string & prefix, double value, int decimals )-> std::string
{
  char buffer[256];

  std::setlocale( LC_ALL, "" );
  snprintf( buffer, sizeof(buffer), "%s%'.*f", prefix.data(), decimals, value );

  return std::string(buffer);

} // endftom( const std::string & prefix, double value, int decimals )-> std::string


auto
GCW::Core::
ends_with( const std::string & value, const std::string & ending )-> bool
{
  if( ending.size() > value.size() )
    return false;

  return std::equal( ending.rbegin(), ending.rend(), value.rbegin() );

} // endends_with( const std::string & value, const std::string & ending )-> bool


auto
GCW::Core::
append( const std::string & s, const std::string & append, const std::string & separator )-> std::string
{
  std::string retVal = s;

  /*
  ** only put the separator on if there is already data, and...
  */
  if( retVal != "" )
  {
    /*
    ** ...and if the end of the string doesn't already have
    **  the separator on it
    **
    */
    if( !ends_with( retVal, separator ) )
    {
      retVal += separator;
    }

  } // endif( retVal != "" )

  retVal += append;

  return retVal;

} //endappend( const std::string & s, const std::string & append, const std::string & separator )-> std::string


auto
GCW::Core::
prepend( const std::string & s, int length, char pad )-> std::string
{
  std::string retVal = s;

  while( retVal.length() < length )
    retVal = pad + retVal;

  return retVal;

} // endprepend( const std::string & s, int length, char pad )-> std::string


auto
GCW::Core::
ucase( const std::string & value )-> std::string
{
  std::string retVal = value;
  std::transform( retVal.begin(), retVal.end(), retVal.begin(), ::toupper );
  return retVal;

} // enducase( const std::string & value )-> std::string


auto
GCW::Core::
lcase( const std::string & value )-> std::string
{
  std::string retVal = value;
  std::transform( retVal.begin(), retVal.end(), retVal.begin(), ::tolower );
  return retVal;

} // endlcase( const std::string & value )-> std::string


auto
GCW::Core::
roundUp( float value )-> int
{
  int v = value;
  if( v < value )
      v++;

  return v;

} // endroundUp( float value )-> int


auto
GCW::Core::
roundDown( float value )-> int
{
  return value;

} // endroundDown( float value )-> int


auto
GCW::Core::
roundCurrency( float value )-> float
{
  float retVal = value * 100;

  retVal = round(retVal);

  retVal /= 100;

  return retVal;

} // endroundCurrency( float value )-> float


auto
GCW::Core::
replace( const std::string & string, const std::string & before, const std::string & after )-> std::string
{
  std::string retVal = string;

  size_t start_pos = 0;
  while( (start_pos = retVal.find( before, start_pos )) != std::string::npos )
  {
    retVal.replace( start_pos, before.length(), after );
    start_pos += after.length(); // Handles case where 'to' is a substring of 'from'
  }

  return retVal;

} // endreplace( const std::string & string, const std::string & before, const std::string & after )-> std::string


enum class CSVState
{
  UnquotedField,
  QuotedField,
  QuotedQuote
};


auto
GCW::Core::
readCSVRow( const std::string & row )-> std::vector<std::string>
{
  CSVState state = CSVState::UnquotedField;
  std::vector<std::string> fields {""};
  size_t i = 0; // index of the current field
  for( char c : row )
  {
    switch( state )
    {
      case CSVState::UnquotedField:
      {
        switch( c )
        {
          case ',': // end of field
          {
            fields.push_back("");
            i++;
            break;
          }

          case '"':
          {
            state = CSVState::QuotedField;
            break;
          }

          default:
          {
            fields[i].push_back(c);
            break;
          }

        } // endswitch( c )

        break;

      } // endcase CSVState::UnquotedField:

      case CSVState::QuotedField:
      {
        switch( c )
        {
          case '"':
          {
            state = CSVState::QuotedQuote;
            break;
          }

          default:
          {
            fields[i].push_back(c);
            break;
          }

        } // endswitch( c )

        break;

      } // endcase CSVState::QuotedField:

      case CSVState::QuotedQuote:
      {
        switch( c )
        {
          case ',': // , after closing quote
          {
            fields.push_back("");
            i++;
            state = CSVState::UnquotedField;
            break;
          }

          case '"': // "" -> "
          {
            fields[i].push_back('"');
            state = CSVState::QuotedField;
            break;
          }

          default:  // end of quote
          {
            state = CSVState::UnquotedField;
            break;
          }

        } // endswitch( c )

        break;

      } // endcase CSVState::QuotedQuote:

    } // endswitch( state )

  } // endfor( char c : row )

  return fields;

} // endreadCSVRow( const std::string & row )-> std::vector<std::string>


auto
GCW::Core::
feq( double a, double b, double epsilon, bool trace )-> bool
{
  bool retVal = fabs( a - b ) < epsilon;

  if( trace )
    std::cout << __FILE__ << ":" << __LINE__
      << " retv:" << std::fixed << retVal
      << " eps:"  << std::fixed << epsilon
      << " fabs:" << std::fixed << fabs( a - b )
      << " a:"    << std::fixed << a
      << " b:"    << std::fixed << b
      << std::endl
      ;

  return retVal;

} // endfeq( double a, double b, double epsilon, bool trace )-> bool

/*
** this will strip the leading and trailing <div> from a template html stream.
**
*/
auto
GCW::Core::
to_string( Wt::WTemplate & templt )-> std::string
{
  std::string retVal;

  std::stringstream ss;
  templt.htmlText( ss );

  std::string junk;
  getline( ss, junk );

  while( !ss.eof() )
  {
    std::string line;
    getline( ss, line );

    if( !ss.eof() )
      retVal += line;

  }

  return retVal;

} // endWtx::to_string( Wt::WTemplate & templt )-> std::string


auto
GCW::Core::
to_string( Wt::WTemplate * templt )-> std::string
{
  return to_string( *templt );

} // endto_string( Wt::WTemplate * templt )-> std::string

auto
GCW::Core::
to_htmlfile( Wt::WTemplate & templt, const std::string & folderName, const std::string & fileName )-> bool
{
  std::ofstream ofs( folderName + fileName, std::ofstream::out );
  ofs << to_string( templt );
  return true;

} // endto_htmlfile( Wt::WTemplate & templt, const std::string & folderName, const std::string & fileName )-> bool


auto
GCW::Core::
to_htmlfile( Wt::WTemplate * templt, const std::string & folderName, const std::string & fileName )-> bool
{
  to_htmlfile( *templt, folderName, fileName );
  return true;

} // endto_htmlfile( Wt::WTemplate * templt, const std::string & folderName, const std::string & fileName )-> bool


const GCW::Core::CharConv_t GCW::Core::g_iso8859Conv[256] =
{
//     dec hex   sym      html        utf8            pdf             description
  { /*   0 00 */ "NUL",   nullptr,    nullptr,        nullptr,        "Null char"                                    },
  { /*   1 01 */ "SOH",   nullptr,    nullptr,        nullptr,        "Start of Heading"                             },
  { /*   2 02 */ "STX",   nullptr,    nullptr,        nullptr,        "Start of Text"                                },
  { /*   3 03 */ "ETX",   nullptr,    nullptr,        nullptr,        "End of Text"                                  },
  { /*   4 04 */ "EOT",   nullptr,    nullptr,        nullptr,        "End of Transmission"                          },
  { /*   5 05 */ "ENQ",   nullptr,    nullptr,        nullptr,        "Enquiry"                                      },
  { /*   6 06 */ "ACK",   nullptr,    nullptr,        nullptr,        "Acknowledgment"                               },
  { /*   7 07 */ "BEL",   nullptr,    nullptr,        nullptr,        "Bell"                                         },
  { /*   8 08 */ "BS",    nullptr,    nullptr,        nullptr,        "Back Space"                                   },
  { /*   9 09 */ "HT",    nullptr,    nullptr,        nullptr,        "Horizontal Tab"                               },
  { /*  10 0A */ "LF",    "<br />",   nullptr,        nullptr,        "Line Feed"                                    },
  { /*  11 0B */ "VT",    nullptr,    nullptr,        nullptr,        "Vertical Tab"                                 },
  { /*  12 0C */ "FF",    nullptr,    nullptr,        nullptr,        "Form Feed"                                    },
  { /*  13 0D */ "CR",    nullptr,    nullptr,        nullptr,        "Carriage Return"                              },
  { /*  14 0E */ "SO",    nullptr,    nullptr,        nullptr,        "Shift Out / X-On"                             },
  { /*  15 0F */ "SI",    nullptr,    nullptr,        nullptr,        "Shift In / X-Off"                             },
  { /*  16 10 */ "DLE",   nullptr,    nullptr,        nullptr,        "Data Line Escape"                             },
  { /*  17 11 */ "DC1",   nullptr,    nullptr,        nullptr,        "Device Control 1 (oft. XON)"                  },
  { /*  18 12 */ "DC2",   nullptr,    nullptr,        nullptr,        "Device Control 2"                             },
  { /*  19 13 */ "DC3",   nullptr,    nullptr,        nullptr,        "Device Control 3 (oft. XOFF)"                 },
  { /*  20 14 */ "DC4",   nullptr,    nullptr,        nullptr,        "Device Control 4"                             },
  { /*  21 15 */ "NAK",   nullptr,    nullptr,        nullptr,        "Negative Acknowledgement"                     },
  { /*  22 16 */ "SYN",   nullptr,    nullptr,        nullptr,        "Synchronous Idle"                             },
  { /*  23 17 */ "ETB",   nullptr,    nullptr,        nullptr,        "End of Transmit Block"                        },
  { /*  24 18 */ "CAN",   nullptr,    nullptr,        nullptr,        "Cancel"                                       },
  { /*  25 19 */ "EM",    nullptr,    nullptr,        nullptr,        "End of Medium"                                },
  { /*  26 1A */ "SUB",   nullptr,    nullptr,        nullptr,        "Substitute"                                   },
  { /*  27 1B */ "ESC",   nullptr,    nullptr,        nullptr,        "Escape"                                       },
  { /*  28 1C */ "FS",    nullptr,    nullptr,        nullptr,        "File Separator"                               },
  { /*  29 1D */ "GS",    nullptr,    nullptr,        nullptr,        "Group Separator"                              },
  { /*  30 1E */ "RS",    nullptr,    nullptr,        nullptr,        "Record Separator"                             },
  { /*  31 1F */ "US",    nullptr,    nullptr,        nullptr,        "Unit Separator"                               },
  { /*  32 20 */ " ",     nullptr,    nullptr,        nullptr,        "Space"                                        },
  { /*  33 21 */ "!",     nullptr,    nullptr,        nullptr,        "Exclamation mark"                             },
  { /*  34 22 */ "\"",    "&quot;",   nullptr,        nullptr,        "Double quotes (or speech marks)"              },
  { /*  35 23 */ "#",     nullptr,    nullptr,        nullptr,        "Number"                                       },
  { /*  36 24 */ "$",     nullptr,    nullptr,        nullptr,        "Dollar"                                       },
  { /*  37 25 */ "%",     nullptr,    nullptr,        nullptr,        "Procenttecken"                                },
  { /*  38 26 */ "&",     "&amp;",    nullptr,        nullptr,        "Ampersand"                                    },
  { /*  39 27 */ "'",     nullptr,    nullptr,        nullptr,        "Single quote"                                 },
  { /*  40 28 */ "(",     nullptr,    nullptr,        nullptr,        "Open parenthesis (or open bracket)"           },
  { /*  41 29 */ ")",     nullptr,    nullptr,        nullptr,        "Close parenthesis (or close bracket)"         },
  { /*  42 2A */ "*",     nullptr,    nullptr,        nullptr,        "Asterisk"                                     },
  { /*  43 2B */ "+",     nullptr,    nullptr,        nullptr,        "Plus"                                         },
  { /*  44 2C */ ",",     nullptr,    nullptr,        nullptr,        "Comma"                                        },
  { /*  45 2D */ "-",     nullptr,    nullptr,        nullptr,        "Hyphen"                                       },
  { /*  46 2E */ ".",     nullptr,    nullptr,        nullptr,        "Period, dot or full stop"                     },
  { /*  47 2F */ "/",     nullptr,    nullptr,        nullptr,        "Slash or divide"                              },
  { /*  48 30 */ "0",     nullptr,    nullptr,        nullptr,        "Zero"                                         },
  { /*  49 31 */ "1",     nullptr,    nullptr,        nullptr,        "One"                                          },
  { /*  50 32 */ "2",     nullptr,    nullptr,        nullptr,        "Two"                                          },
  { /*  51 33 */ "3",     nullptr,    nullptr,        nullptr,        "Three"                                        },
  { /*  52 34 */ "4",     nullptr,    nullptr,        nullptr,        "Four"                                         },
  { /*  53 35 */ "5",     nullptr,    nullptr,        nullptr,        "Five"                                         },
  { /*  54 36 */ "6",     nullptr,    nullptr,        nullptr,        "Six"                                          },
  { /*  55 37 */ "7",     nullptr,    nullptr,        nullptr,        "Seven"                                        },
  { /*  56 38 */ "8",     nullptr,    nullptr,        nullptr,        "Eight"                                        },
  { /*  57 39 */ "9",     nullptr,    nullptr,        nullptr,        "Nine"                                         },
  { /*  58 3A */ ":",     nullptr,    nullptr,        nullptr,        "Colon"                                        },
  { /*  59 3B */ ";",     nullptr,    nullptr,        nullptr,        "Semicolon"                                    },
  { /*  60 3C */ "<",     "&lt;",     nullptr,        nullptr,        "Less than (or open angled bracket)"           },
  { /*  61 3D */ "=",     nullptr,    nullptr,        nullptr,        "Equals"                                       },
  { /*  62 3E */ ">",     "&gt;",     nullptr,        nullptr,        "Greater than (or close angled bracket)"       },
  { /*  63 3F */ "?",     nullptr,    nullptr,        nullptr,        "Question mark"                                },
  { /*  64 40 */ "@",     nullptr,    nullptr,        nullptr,        "At symbol"                                    },
  { /*  65 41 */ "A",     nullptr,    nullptr,        nullptr,        "Uppercase A"                                  },
  { /*  66 42 */ "B",     nullptr,    nullptr,        nullptr,        "Uppercase B"                                  },
  { /*  67 43 */ "C",     nullptr,    nullptr,        nullptr,        "Uppercase C"                                  },
  { /*  68 44 */ "D",     nullptr,    nullptr,        nullptr,        "Uppercase D"                                  },
  { /*  69 45 */ "E",     nullptr,    nullptr,        nullptr,        "Uppercase E"                                  },
  { /*  70 46 */ "F",     nullptr,    nullptr,        nullptr,        "Uppercase F"                                  },
  { /*  71 47 */ "G",     nullptr,    nullptr,        nullptr,        "Uppercase G"                                  },
  { /*  72 48 */ "H",     nullptr,    nullptr,        nullptr,        "Uppercase H"                                  },
  { /*  73 49 */ "I",     nullptr,    nullptr,        nullptr,        "Uppercase I"                                  },
  { /*  74 4A */ "J",     nullptr,    nullptr,        nullptr,        "Uppercase J"                                  },
  { /*  75 4B */ "K",     nullptr,    nullptr,        nullptr,        "Uppercase K"                                  },
  { /*  76 4C */ "L",     nullptr,    nullptr,        nullptr,        "Uppercase L"                                  },
  { /*  77 4D */ "M",     nullptr,    nullptr,        nullptr,        "Uppercase M"                                  },
  { /*  78 4E */ "N",     nullptr,    nullptr,        nullptr,        "Uppercase N"                                  },
  { /*  79 4F */ "O",     nullptr,    nullptr,        nullptr,        "Uppercase O"                                  },
  { /*  80 50 */ "P",     nullptr,    nullptr,        nullptr,        "Uppercase P"                                  },
  { /*  81 51 */ "Q",     nullptr,    nullptr,        nullptr,        "Uppercase Q"                                  },
  { /*  82 52 */ "R",     nullptr,    nullptr,        nullptr,        "Uppercase R"                                  },
  { /*  83 53 */ "S",     nullptr,    nullptr,        nullptr,        "Uppercase S"                                  },
  { /*  84 54 */ "T",     nullptr,    nullptr,        nullptr,        "Uppercase T"                                  },
  { /*  85 55 */ "U",     nullptr,    nullptr,        nullptr,        "Uppercase U"                                  },
  { /*  86 56 */ "V",     nullptr,    nullptr,        nullptr,        "Uppercase V"                                  },
  { /*  87 57 */ "W",     nullptr,    nullptr,        nullptr,        "Uppercase W"                                  },
  { /*  88 58 */ "X",     nullptr,    nullptr,        nullptr,        "Uppercase X"                                  },
  { /*  89 59 */ "Y",     nullptr,    nullptr,        nullptr,        "Uppercase Y"                                  },
  { /*  90 5A */ "Z",     nullptr,    nullptr,        nullptr,        "Uppercase Z"                                  },
  { /*  91 5B */ "[",     nullptr,    nullptr,        nullptr,        "Opening bracket"                              },
  { /*  92 5C */ "\\",    nullptr,    nullptr,        nullptr,        "Backslash"                                    },
  { /*  93 5D */ "]",     nullptr,    nullptr,        nullptr,        "Closing bracket"                              },
  { /*  94 5E */ "^",     nullptr,    nullptr,        nullptr,        "Caret - circumflex"                           },
  { /*  95 5F */ "_",     nullptr,    nullptr,        nullptr,        "Underscore"                                   },
  { /*  96 60 */ "`",     nullptr,    nullptr,        nullptr,        "Grave accent"                                 },
  { /*  97 61 */ "a",     nullptr,    nullptr,        nullptr,        "Lowercase a"                                  },
  { /*  98 62 */ "b",     nullptr,    nullptr,        nullptr,        "Lowercase b"                                  },
  { /*  99 63 */ "c",     nullptr,    nullptr,        nullptr,        "Lowercase c"                                  },
  { /* 100 64 */ "d",     nullptr,    nullptr,        nullptr,        "Lowercase d"                                  },
  { /* 101 65 */ "e",     nullptr,    nullptr,        nullptr,        "Lowercase e"                                  },
  { /* 102 66 */ "f",     nullptr,    nullptr,        nullptr,        "Lowercase f"                                  },
  { /* 103 67 */ "g",     nullptr,    nullptr,        nullptr,        "Lowercase g"                                  },
  { /* 104 68 */ "h",     nullptr,    nullptr,        nullptr,        "Lowercase h"                                  },
  { /* 105 69 */ "i",     nullptr,    nullptr,        nullptr,        "Lowercase i"                                  },
  { /* 106 6A */ "j",     nullptr,    nullptr,        nullptr,        "Lowercase j"                                  },
  { /* 107 6B */ "k",     nullptr,    nullptr,        nullptr,        "Lowercase k"                                  },
  { /* 108 6C */ "l",     nullptr,    nullptr,        nullptr,        "Lowercase l"                                  },
  { /* 109 6D */ "m",     nullptr,    nullptr,        nullptr,        "Lowercase m"                                  },
  { /* 110 6E */ "n",     nullptr,    nullptr,        nullptr,        "Lowercase n"                                  },
  { /* 111 6F */ "o",     nullptr,    nullptr,        nullptr,        "Lowercase o"                                  },
  { /* 112 70 */ "p",     nullptr,    nullptr,        nullptr,        "Lowercase p"                                  },
  { /* 113 71 */ "q",     nullptr,    nullptr,        nullptr,        "Lowercase q"                                  },
  { /* 114 72 */ "r",     nullptr,    nullptr,        nullptr,        "Lowercase r"                                  },
  { /* 115 73 */ "s",     nullptr,    nullptr,        nullptr,        "Lowercase s"                                  },
  { /* 116 74 */ "t",     nullptr,    nullptr,        nullptr,        "Lowercase t"                                  },
  { /* 117 75 */ "u",     nullptr,    nullptr,        nullptr,        "Lowercase u"                                  },
  { /* 118 76 */ "v",     nullptr,    nullptr,        nullptr,        "Lowercase v"                                  },
  { /* 119 77 */ "w",     nullptr,    nullptr,        nullptr,        "Lowercase w"                                  },
  { /* 120 78 */ "x",     nullptr,    nullptr,        nullptr,        "Lowercase x"                                  },
  { /* 121 79 */ "y",     nullptr,    nullptr,        nullptr,        "Lowercase y"                                  },
  { /* 122 7A */ "z",     nullptr,    nullptr,        nullptr,        "Lowercase z"                                  },
  { /* 123 7B */ "{",     nullptr,    nullptr,        nullptr,        "Opening brace"                                },
  { /* 124 7C */ "|",     nullptr,    nullptr,        nullptr,        "Vertical bar"                                 },
  { /* 125 7D */ "}",     nullptr,    nullptr,        nullptr,        "Closing brace"                                },
  { /* 126 7E */ "~",     nullptr,    nullptr,        nullptr,        "Equivalency sign - tilde"                     },
  { /* 127 7F */ "DEL",   nullptr,    nullptr,        nullptr,        "Delete"                                       },

//  The table below is according to ISO 8859-1, also called ISO Latin-1. Codes 129-159 contain the Microsoft® Windows Latin-1 extended characters.
//     dec hex   sym      html        utf8            pdf             description
  { /* 128 80 */ "€",     "&euro;",   nullptr,        nullptr,        "Euro sign"                                    },
  { /* 129 81 */ nullptr, nullptr,    nullptr,        nullptr,        nullptr                                        },
  { /* 130 82 */ "‚",     "&sbquo;",  nullptr,        nullptr,        "Single low-9 quotation mark"                  },
  { /* 131 83 */ "ƒ",     "&fnof;",   nullptr,        nullptr,        "Latin small letter f with hook"               },
  { /* 132 84 */ "„",     "&bdquo;",  nullptr,        nullptr,        "Double low-9 quotation mark"                  },
  { /* 133 85 */ "…",     "&hellip;", nullptr,        nullptr,        "Horizontal ellipsis"                          },
  { /* 134 86 */ "†",     "&dagger;", nullptr,        nullptr,        "Dagger"                                       },
  { /* 135 87 */ "‡",     "&Dagger;", nullptr,        nullptr,        "Double dagger"                                },
  { /* 136 88 */ "ˆ",     "&circ;",   nullptr,        nullptr,        "Modifier letter circumflex accent"            },
  { /* 137 89 */ "‰",     "&permil;", nullptr,        nullptr,        "Per mille sign"                               },
  { /* 138 8A */ "Š",     "&Scaron;", nullptr,        nullptr,        "Latin capital letter S with caron"            },
  { /* 139 8B */ "‹",     "&lsaquo;", nullptr,        nullptr,        "Single left-pointing angle quotation"         },
  { /* 140 8C */ "Œ",     "&OElig;",  nullptr,        nullptr,        "Latin capital ligature OE"                    },
  { /* 141 8D */ nullptr, nullptr,    nullptr,        nullptr,        nullptr                                        },
  { /* 142 8E */ "Ž",     nullptr,    nullptr,        nullptr,        "Latin captial letter Z with caron"            },
  { /* 143 8F */ nullptr, nullptr,    nullptr,        nullptr,        nullptr                                        },
  { /* 144 90 */ nullptr, nullptr,    nullptr,        nullptr,        nullptr                                        },
  { /* 145 91 */ "‘",     "&lsquo;",  nullptr,        "'",            "Left single quotation mark"                   },
  { /* 146 92 */ "’",     "&rsquo;",  nullptr,        "'",            "Right single quotation mark"                  },
  { /* 147 93 */ "“",     "&ldquo;",  "\xe2\x80\x9c", "\"",           "Left double quotation mark"                   },
  { /* 148 94 */ "”",     "&rdquo;",  "\xe2\x80\x9d", "\"",           "Right double quotation mark"                  },
  { /* 149 95 */ "•",     "&bull;",   nullptr,        nullptr,        "Bullet"                                       },
  { /* 150 96 */ "–",     "&ndash;",  nullptr,        "-",            "En dash"                                      },
  { /* 151 97 */ "—",     "&mdash;",  nullptr,        "-",            "Em dash"                                      },
  { /* 152 98 */ "˜",     "&tilde;",  nullptr,        "~",            "Small tilde"                                  },
  { /* 153 99 */ "™",     "&trade;",  nullptr,        "tm",           "Trade mark sign"                              },
  { /* 154 9A */ "š",     "&scaron;", nullptr,        nullptr,        "Latin small letter S with caron"              },
  { /* 155 9B */ "›",     "&rsaquo;", nullptr,        nullptr,        "Single right-pointing angle quotation mark"   },
  { /* 156 9C */ "œ",     "&oelig;",  nullptr,        nullptr,        "Latin small ligature oe"                      },
  { /* 157 9D */ nullptr, nullptr,    nullptr,        nullptr,        nullptr                                        },
  { /* 158 9E */ "ž",     nullptr,    nullptr,        nullptr,        "Latin small letter z with caron"              },
  { /* 159 9F */ "Ÿ",     "&yuml;",   nullptr,        nullptr,        "Latin capital letter Y with diaeresis"        },
  { /* 160 A0 */ " ",     "&nbsp;",   nullptr,        nullptr,        "Non-breaking space"                           },
  { /* 161 A1 */ "¡",     "&iexcl;",  nullptr,        nullptr,        "Inverted exclamation mark"                    },
  { /* 162 A2 */ "¢",     "&cent;",   nullptr,        nullptr,        "Cent sign"                                    },
  { /* 163 A3 */ "£",     "&pound;",  nullptr,        "#",            "Pound sign"                                   },
  { /* 164 A4 */ "¤",     "&curren;", nullptr,        nullptr,        "Currency sign"                                },
  { /* 165 A5 */ "¥",     "&yen;",    nullptr,        nullptr,        "Yen sign"                                     },
  { /* 166 A6 */ "¦",     "&brvbar;", nullptr,        nullptr,        "Pipe, Broken vertical bar"                    },
  { /* 167 A7 */ "§",     "&sect;",   nullptr,        nullptr,        "Section sign"                                 },
  { /* 168 A8 */ "¨",     "&uml;",    nullptr,        nullptr,        "Spacing diaeresis - umlaut"                   },
  { /* 169 A9 */ "©",     "&copy;",   nullptr,        nullptr,        "Copyright sign"                               },
  { /* 170 AA */ "ª",     "&ordf;",   nullptr,        nullptr,        "Feminine ordinal indicator"                   },
  { /* 171 AB */ "«",     "&laquo;",  nullptr,        nullptr,        "Left double angle quotes"                     },
  { /* 172 AC */ "¬",     "&not;",    nullptr,        nullptr,        "Not sign"                                     },
  { /* 173 AD */ "­",     "&shy;",    nullptr,        nullptr,        "Soft hyphen"                                  },
  { /* 174 AE */ "®",     "&reg;",    nullptr,        nullptr,        "Registered trade mark sign"                   },
  { /* 175 AF */ "¯",     "&macr;",   nullptr,        nullptr,        "Spacing macron - overline"                    },
  { /* 176 B0 */ "°",     "&deg;",    nullptr,        nullptr,        "Degree sign"                                  },
  { /* 177 B1 */ "±",     "&plusmn;", nullptr,        nullptr,        "Plus-or-minus sign"                           },
  { /* 178 B2 */ "²",     "&sup2;",   nullptr,        nullptr,        "Superscript two - squared"                    },
  { /* 179 B3 */ "³",     "&sup3;",   nullptr,        nullptr,        "Superscript three - cubed"                    },
  { /* 180 B4 */ "´",     "&acute;",  nullptr,        nullptr,        "Acute accent - spacing acute"                 },
  { /* 181 B5 */ "µ",     "&micro;",  nullptr,        nullptr,        "Micro sign"                                   },
  { /* 182 B6 */ "¶",     "&para;",   nullptr,        nullptr,        "Pilcrow sign - paragraph sign"                },
  { /* 183 B7 */ "·",     "&middot;", nullptr,        nullptr,        "Middle dot - Georgian comma"                  },
  { /* 184 B8 */ "¸",     "&cedil;",  nullptr,        nullptr,        "Spacing cedilla"                              },
  { /* 185 B9 */ "¹",     "&sup1;",   nullptr,        nullptr,        "Superscript one"                              },
  { /* 186 BA */ "º",     "&ordm;",   nullptr,        nullptr,        "Masculine ordinal indicator"                  },
  { /* 187 BB */ "»",     "&raquo;",  nullptr,        nullptr,        "Right double angle quotes"                    },
  { /* 188 BC */ "¼",     "&frac14;", nullptr,        nullptr,        "Fraction one quarter"                         },
  { /* 189 BD */ "½",     "&frac12;", nullptr,        nullptr,        "Fraction one half"                            },
  { /* 190 BE */ "¾",     "&frac34;", nullptr,        nullptr,        "Fraction three quarters"                      },
  { /* 191 BF */ "¿",     "&iquest;", nullptr,        nullptr,        "Inverted question mark"                       },
  { /* 192 C0 */ "À",     "&Agrave;", nullptr,        nullptr,        "Latin capital letter A with grave"            },
  { /* 193 C1 */ "Á",     "&Aacute;", nullptr,        nullptr,        "Latin capital letter A with acute"            },
  { /* 194 C2 */ "Â",     "&Acirc;",  nullptr,        nullptr,        "Latin capital letter A with circumflex"       },
  { /* 195 C3 */ "Ã",     "&Atilde;", nullptr,        nullptr,        "Latin capital letter A with tilde"            },
  { /* 196 C4 */ "Ä",     "&Auml;",   nullptr,        nullptr,        "Latin capital letter A with diaeresis"        },
  { /* 197 C5 */ "Å",     "&Aring;",  nullptr,        nullptr,        "Latin capital letter A with ring above"       },
  { /* 198 C6 */ "Æ",     "&AElig;",  nullptr,        nullptr,        "Latin capital letter AE"                      },
  { /* 199 C7 */ "Ç",     "&Ccedil;", nullptr,        nullptr,        "Latin capital letter C with cedilla"          },
  { /* 200 C8 */ "È",     "&Egrave;", nullptr,        nullptr,        "Latin capital letter E with grave"            },
  { /* 201 C9 */ "É",     "&Eacute;", nullptr,        nullptr,        "Latin capital letter E with acute"            },
  { /* 202 CA */ "Ê",     "&Ecirc;",  nullptr,        nullptr,        "Latin capital letter E with circumflex"       },
  { /* 203 CB */ "Ë",     "&Euml;",   nullptr,        nullptr,        "Latin capital letter E with diaeresis"        },
  { /* 204 CC */ "Ì",     "&Igrave;", nullptr,        nullptr,        "Latin capital letter I with grave"            },
  { /* 205 CD */ "Í",     "&Iacute;", nullptr,        nullptr,        "Latin capital letter I with acute"            },
  { /* 206 CE */ "Î",     "&Icirc;",  nullptr,        nullptr,        "Latin capital letter I with circumflex"       },
  { /* 207 CF */ "Ï",     "&Iuml;",   nullptr,        nullptr,        "Latin capital letter I with diaeresis"        },
  { /* 208 D0 */ "Ð",     "&ETH;",    nullptr,        nullptr,        "Latin capital letter ETH"                     },
  { /* 209 D1 */ "Ñ",     "&Ntilde;", nullptr,        nullptr,        "Latin capital letter N with tilde"            },
  { /* 210 D2 */ "Ò",     "&Ograve;", nullptr,        nullptr,        "Latin capital letter O with grave"            },
  { /* 211 D3 */ "Ó",     "&Oacute;", nullptr,        nullptr,        "Latin capital letter O with acute"            },
  { /* 212 D4 */ "Ô",     "&Ocirc;",  nullptr,        nullptr,        "Latin capital letter O with circumflex"       },
  { /* 213 D5 */ "Õ",     "&Otilde;", nullptr,        nullptr,        "Latin capital letter O with tilde"            },
  { /* 214 D6 */ "Ö",     "&Ouml;",   nullptr,        nullptr,        "Latin capital letter O with diaeresis"        },
  { /* 215 D7 */ "×",     "&times;",  nullptr,        nullptr,        "Multiplication sign"                          },
  { /* 216 D8 */ "Ø",     "&Oslash;", nullptr,        nullptr,        "Latin capital letter O with slash"            },
  { /* 217 D9 */ "Ù",     "&Ugrave;", nullptr,        nullptr,        "Latin capital letter U with grave"            },
  { /* 218 DA */ "Ú",     "&Uacute;", nullptr,        nullptr,        "Latin capital letter U with acute"            },
  { /* 219 DB */ "Û",     "&Ucirc;",  nullptr,        nullptr,        "Latin capital letter U with circumflex"       },
  { /* 220 DC */ "Ü",     "&Uuml;",   nullptr,        nullptr,        "Latin capital letter U with diaeresis"        },
  { /* 221 DD */ "Ý",     "&Yacute;", nullptr,        nullptr,        "Latin capital letter Y with acute"            },
  { /* 222 DE */ "Þ",     "&THORN;",  nullptr,        nullptr,        "Latin capital letter THORN"                   },
  { /* 223 DF */ "ß",     "&szlig;",  nullptr,        nullptr,        "Latin small letter sharp s - ess-zed"         },
  { /* 224 E0 */ "à",     "&agrave;", nullptr,        nullptr,        "Latin small letter a with grave"              },
  { /* 225 E1 */ "á",     "&aacute;", nullptr,        nullptr,        "Latin small letter a with acute"              },
  { /* 226 E2 */ "â",     "&acirc;",  nullptr,        nullptr,        "Latin small letter a with circumflex"         },
  { /* 227 E3 */ "ã",     "&atilde;", nullptr,        nullptr,        "Latin small letter a with tilde"              },
  { /* 228 E4 */ "ä",     "&auml;",   nullptr,        nullptr,        "Latin small letter a with diaeresis"          },
  { /* 229 E5 */ "å",     "&aring;",  nullptr,        nullptr,        "Latin small letter a with ring above"         },
  { /* 230 E6 */ "æ",     "&aelig;",  nullptr,        nullptr,        "Latin small letter ae"                        },
  { /* 231 E7 */ "ç",     "&ccedil;", nullptr,        nullptr,        "Latin small letter c with cedilla"            },
  { /* 232 E8 */ "è",     "&egrave;", nullptr,        nullptr,        "Latin small letter e with grave"              },
  { /* 233 E9 */ "é",     "&eacute;", nullptr,        nullptr,        "Latin small letter e with acute"              },
  { /* 234 EA */ "ê",     "&ecirc;",  nullptr,        nullptr,        "Latin small letter e with circumflex"         },
  { /* 235 EB */ "ë",     "&euml;",   nullptr,        nullptr,        "Latin small letter e with diaeresis"          },
  { /* 236 EC */ "ì",     "&igrave;", nullptr,        nullptr,        "Latin small letter i with grave"              },
  { /* 237 ED */ "í",     "&iacute;", nullptr,        nullptr,        "Latin small letter i with acute"              },
  { /* 238 EE */ "î",     "&icirc;",  nullptr,        nullptr,        "Latin small letter i with circumflex"         },
  { /* 239 EF */ "ï",     "&iuml;",   nullptr,        nullptr,        "Latin small letter i with diaeresis"          },
  { /* 240 F0 */ "ð",     "&eth;",    nullptr,        nullptr,        "Latin small letter eth"                       },
  { /* 241 F1 */ "ñ",     "&ntilde;", nullptr,        nullptr,        "Latin small letter n with tilde"              },
  { /* 242 F2 */ "ò",     "&ograve;", nullptr,        nullptr,        "Latin small letter o with grave"              },
  { /* 243 F3 */ "ó",     "&oacute;", nullptr,        nullptr,        "Latin small letter o with acute"              },
  { /* 244 F4 */ "ô",     "&ocirc;",  nullptr,        nullptr,        "Latin small letter o with circumflex"         },
  { /* 245 F5 */ "õ",     "&otilde;", nullptr,        nullptr,        "Latin small letter o with tilde"              },
  { /* 246 F6 */ "ö",     "&ouml;",   nullptr,        nullptr,        "Latin small letter o with diaeresis"          },
  { /* 247 F7 */ "÷",     "&divide;", nullptr,        nullptr,        "Division sign"                                },
  { /* 248 F8 */ "ø",     "&oslash;", nullptr,        nullptr,        "Latin small letter o with slash"              },
  { /* 249 F9 */ "ù",     "&ugrave;", nullptr,        nullptr,        "Latin small letter u with grave"              },
  { /* 250 FA */ "ú",     "&uacute;", nullptr,        nullptr,        "Latin small letter u with acute"              },
  { /* 251 FB */ "û",     "&ucirc;",  nullptr,        nullptr,        "Latin small letter u with circumflex"         },
  { /* 252 FC */ "ü",     "&uuml;",   nullptr,        nullptr,        "Latin small letter u with diaeresis"          },
  { /* 253 FD */ "ý",     "&yacute;", nullptr,        nullptr,        "Latin small letter y with acute"              },
  { /* 254 FE */ "þ",     "&thorn;",  nullptr,        nullptr,        "Latin small letter thorn"                     },
  { /* 255 FF */ "ÿ",     "&yuml;",   nullptr,        nullptr,        "Latin small letter y with diaeresis"          },

};


