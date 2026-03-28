#line 2 "src/Glb/Core.h"

#ifndef __GCW_CORE_H___
#define __GCW_CORE_H___

#include <string>
#include <vector>

#include <Wt/Json/Object.h>
#include <Wt/WTemplate.h>

#include "Numeric.h"

//#define COUT_FLF  __FILE__, __LINE__, __FUNCTION__
//#define COUT_BEG  std::cout << __FILE__ << ":" << __LINE__ << "(" << __PRETTY_FUNCTION__ << ") "
//#define COUT_END  std::endl
//#define COUT_LINE std::cout << __FILE__ << ":" << __LINE__ << "(" << __PRETTY_FUNCTION__ << ")" << COUT_END
//#define COUT_(x)  COUT_BEG << x << COUT_END


namespace GCW {

  /*!
  ** \brief helper functions and features
  **
  */
  namespace Core {


std::vector<std::string> split( const std::string & value, char delim );

extern const char* trim_ws;
std::string & rtrim( std::string & s, const char* t = trim_ws );
std::string & ltrim( std::string & s, const char* t = trim_ws );
std::string & trim( std::string & s, const char* t = trim_ws );
std::string toupper( const std::string & s );
std::string tolower( const std::string & s );

Wt::Json::Object toJson( Wt::WTreeView * _view );

std::string hexDump( const std::string & data, int start = -1, int end = -1 );

/*!
** \brief Generate new GUID string value
**
** This GUID is suitable for use as the primary-guid-key value for the
**  data tables.
**
*/
auto newGuid()-> std::string ;

/*!
** \brief Current Date/Time
**
** This will return the current date/time suitable for back-end storage
**
*/
auto currentDateTime()-> Wt::WDateTime ;

auto dateStorageString( const Wt::WDate * _date )-> std::string ;
auto dateStorageString( const Wt::WDate & _date )-> std::string ;
auto dateTimeStorageString( const Wt::WDateTime & _dateTime )-> std::string ;
auto dateTimeDisplayString( const Wt::WDateTime & _dateTime )-> std::string ;
auto currentDateTimeStorageString()-> std::string ;
auto currentDateTimeDisplayString()-> std::string ;

/* * * * * * * * * * * * * * * * * * * * */

std::string makeFileName( const std::string & value );

/*!
** \brief Check if a File or Folder exists
**
**
*/
bool fileExists( const std::string & fileName );

/*!
** \brief Execute a system command
**
** This runs a command in the console and returns the result code.
**
*/
int system_command( const std::string & cmd, bool show = false );

/*!
** \brief File Listing
**
** This procedure will scan a folder and return a list of all the files
**  in it.
*/
std::vector<std::string> fileList( const std::string & folder );

/*!
** \brief Find File
**
** This scans a directory folder and returns a list containing
**  the full file-name of all the files that matche the value.
**
*/
std::vector<std::string> findFiles( const std::string & folder, const std::string & match );

/*!
** \brief Convert a String to an Integer
**
*/
int stoi( const std::string & value );

/*!
** \brief Convert an Integer to a String
**
*/
std::string itos( int value );

/*!
** \brief Convert a String to Float
**
*/
double stof( const std::string & value );

/*!
** \brief Convert a Float to String with decimal precision
**
*/
std::string ftos( double value, int decimals = 2 );
std::string ftos( double value, const std::string & suffix, int decimals = 2 );
std::string ftos( const std::string & prefix, double value, int decimals = 2 );
std::string ftom( double value, int decimals = 2 );
std::string ftom( const std::string & prefix, double value, int decimals = 2 );

/*!
** \brief Check if a string ends with another string
**
*/
bool ends_with( const std::string & value, const std::string & ending );

/*!
** \brief Append a string to string
**
** This will append a string to another string and place
**  a separator if there is already data in the lead string
**
*/
std::string append( const std::string & s, const std::string & append, const std::string & separator );

/*!
** \brief Prepend some number of characters in front of another string
**
** This procedure is often used to zero-pad a number, such that numbers
**  like 23 and 2005 and 10553 will always appear as 00023 and 02005
**  and 10553 respectively.
**
*/
std::string prepend( const std::string & s, int length = 0, char pad = '0' );

/*!
** \brief Upper Case a string
**
** this procedure converts a string to all upper case
*/
std::string ucase( const std::string & value );

/*!
** \brief Lower Case a string
**
** this procedure converts a string to all lower case
*/
std::string lcase( const std::string & value );

/*!
** \brief Round a number up
**
** This will round a number up
**
*/
int roundUp( float value );

/*!
** \brief Round a number down
**
** This will round a number down
**
*/
int roundDown( float value );

/*!
** \brief Round a number for Currency
**
** This will round a number up or down depending on the value
**  of the currency.  1.3999999 becomes 1.4
**
*/
float roundCurrency( float value );

/*!
** \brief Replace a String
**
** This will replace all occurrences of a substring within another string with some other string;
**
*/
std::string replace( const std::string & string, const std::string & before, const std::string & after );

std::vector<std::string> readCSVRow( const std::string & row );

/*!
** This compares two floating point numbers if they are equal
**
*/
bool feq( double a, double b, double epsilon = 0.005f, bool trace = false );

std::string to_string( Wt::WTemplate & templt );
std::string to_string( Wt::WTemplate * templt );

bool to_htmlfile( Wt::WTemplate & templt, const std::string & folderName, const std::string & fileName );
bool to_htmlfile( Wt::WTemplate * templt, const std::string & folderName, const std::string & fileName );

typedef struct CharConv
{
  const char * symbol;
  const char * html;
  const char * utf8;
  const char * pdf;
  const char * description;

} CharConv_t;

extern const CharConv_t g_iso8859Conv[256];

  } // endnamespace Core
} // endnamespace GCW

#endif

