#line 2 "src/main.cpp"

#include <dirent.h>
#include <fstream>
#include <grp.h>
#include <langinfo.h>
#include <locale.h>
#include <pwd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include <Wt/Http/Request.h>
#include <Wt/Http/Response.h>
#include <Wt/WDateTime.h>
#include <Wt/WLayout.h>
#include <Wt/WResource.h>
#include <Wt/WServer.h>

#include "GnuCashew.h"

std::string g_dbName;

#define VAULT_ROOT std::string("/")
#define CLIENT_FOLDERS "/"

void show_program_version( const std::string & message )
{
#ifdef __GRAB_DATE_STRING_FROM_PROGRAM_DATE__
  struct stat attr;
  stat( argv[0], &attr );

  auto tm = localtime( &attr.st_mtime );
  char datestring[256];

  /* Get localized date string. */
  strftime( datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm );
#endif

#ifdef NEVER
  std::string datestring = __GNUCASHEW_VERSION__ + " " + __GNUCASHEW_BUILD__;

  std::cout << __DATETIMEPIDFILELINE__
    << " " << argv[0]
    << " " << datestring
    << " -> " << message
    << std::endl;
#endif

}

class Redirector
: public Wt::WApplication
{
  public:
    Redirector( const Wt::WEnvironment & env )
    : Wt::WApplication(env)
    {
      redirect( "/demo" );
    }
};


/*
** This is a simple static html file server.  It is designed to serve up files
**  in the approot/html folder.  This resource employs a little bit of access
**  control by way of 'valid-ip' address handling.
**
*/
class HtmlResource
: public Wt::WResource
{
  public:

    void handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response );

};

void HtmlResource::handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response )
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "\n headers:" << request.headers().size()
    << "\n path:" << request.path()
    << "\n queryString:" << request.queryString()
    << "\n urlParams:" << request.urlParams().size()
    << "\n pathInfo:" << request.pathInfo()
    << "\n clientAddress:" << request.clientAddress()
    << std::endl;

  for( auto header : request.headers() )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << header.name() << " " << header.value() << std::endl;

  }
#endif

  auto _blocked = [&]()
  {
    std::vector< std::string > allowed =
    {
    };

    return
      std::find
      (
       allowed.begin(),
       allowed.end(),
       request.headerValue( "X-Forwarded-For" )
      ) == allowed.end();
  };

  /*
  ** this checks if the IP address is blocked.
  **  if it is blocked, it will insert an entry
  **  in to a local log file so we can back-trace
  **  attempted hacks.
  **
  */
  if( _blocked() )
  {
    std::cout << __FILE__ << ":" << __LINE__
      << " HtmlResource::ipblocked: [" << request.headerValue( "X-Forwarded-For" ) << "]"
      << " '" << request.path() << "'"
      << std::endl;

    response.out() << "<html><body>oh oh, something went wrong.<br />Please contact the site administrator</body></html>";

    std::ofstream file;
    file.open( "HtmlResource.log", std::ios_base::app );
    if( file.is_open() )
    {
      file
        << "["  << Wt::WDateTime::currentDateTime().toString().toUTF8() << "]"
        << " [" << request.headerValue( "x-Forwarded-For" ) << "]"
        << " "  << request.path()
        << std::endl;
    }

    return;
  }

  /*
  ** The user is allowed to view these documents.
  **
  */
  auto fileName = "approot/html" + request.pathInfo();
  std::ifstream file;
  file.open( fileName );

  if( !file.is_open() )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " NO FILE:" << fileName << std::endl;
    response.out() << "no file!";
  }

  std::cout << __FILE__ << ":" << __LINE__
    << " [" << request.headerValue( "X-Forwarded-For" ) << "]"
    << " HtmlResource:" << fileName
    << std::endl;

  response.out() << file.rdbuf();

} // endvoid HtmlResource::handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response )


class MonitResource
: public Wt::WResource
{
  public:

    void handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response );

};

void MonitResource::handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response )
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "\n headers:"       << request. headers       ().size()
    << "\n path:"          << request. path          ()
    << "\n queryString:"   << request. queryString   ()
    << "\n urlParams:"     << request. urlParams     ().size()
    << "\n pathInfo:"      << request. pathInfo      ()
    << "\n clientAddress:" << request. clientAddress ()
    << std::endl;

  for( auto header : request.headers() )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << header.name() << " " << header.value() << std::endl;

  }
#endif

#ifdef NEVER
  auto _blocked = [&]()
  {
    std::vector< std::string > allowed =
    {
    };

    return
      std::find
      (
       allowed.begin(),
       allowed.end(),
       request.headerValue( "X-Forwarded-For" )
      )
      == allowed.end();
  };

  /*
  ** this checks if the IP address is blocked.
  **  if it is blocked, it will insert an entry
  **  in to a local log file so we can back-trace
  **  attempted hacks.
  **
  */
  if( _blocked() )
  {
    std::cout << __FILE__ << ":" << __LINE__
      << " HtmlResource::ipblocked: [" << request.headerValue( "X-Forwarded-For" ) << "]"
      << " '" << request.path() << "'"
      << std::endl;

    response.out() << "<html><body>oh oh, something went wrong.<br />Please contact the site administrator</body></html>";

    std::ofstream file;
    file.open( "HtmlResource.log", std::ios_base::app );
    if( file.is_open() )
    {
      file
        << "["  << Wt::WDateTime::currentDateTime().toString().toUTF8() << "]"
        << " [" << request.headerValue( "x-Forwarded-For" ) << "]"
        << " "  << request.path()
        << std::endl;
    }

    return;
  }
#endif

  response.out() << "ok\n";

} // endvoid ApiResource::handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response )











/*
** This is a simple static html file server.  It is designed to serve up files
**  in the approot/html folder.  This resource employs a little bit of access
**  control by way of 'valid-ip' address handling.
**
*/
class ApiResource
: public Wt::WResource
{
  public:

    void handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response );

};

void ApiResource::handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response )
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "\n headers:"       << request. headers       ().size()
    << "\n path:"          << request. path          ()
    << "\n queryString:"   << request. queryString   ()
    << "\n urlParams:"     << request. urlParams     ().size()
    << "\n pathInfo:"      << request. pathInfo      ()
    << "\n clientAddress:" << request. clientAddress ()
    << std::endl;

  for( auto header : request.headers() )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << header.name() << " " << header.value() << std::endl;

  }
#endif

  auto _blocked = [&]()
  {
    std::vector< std::string > allowed =
    {
    };

    return
      std::find
      (
       allowed.begin(),
       allowed.end(),
       request.headerValue( "X-Forwarded-For" )
      )
      == allowed.end();
  };

  /*
  ** this checks if the IP address is blocked.
  **  if it is blocked, it will insert an entry
  **  in to a local log file so we can back-trace
  **  attempted hacks.
  **
  */
  if( _blocked() )
  {
    std::cout << __FILE__ << ":" << __LINE__
      << " HtmlResource::ipblocked: [" << request.headerValue( "X-Forwarded-For" ) << "]"
      << " '" << request.path() << "'"
      << std::endl;

    response.out() << "<html><body>oh oh, something went wrong.<br />Please contact the site administrator</body></html>";

    std::ofstream file;
    file.open( "HtmlResource.log", std::ios_base::app );
    if( file.is_open() )
    {
      file
        << "["  << Wt::WDateTime::currentDateTime().toString().toUTF8() << "]"
        << " [" << request.headerValue( "x-Forwarded-For" ) << "]"
        << " "  << request.path()
        << std::endl;
    }

    return;
  }

  if( request.queryString() == "c=jobphotos" )
  {
    for( int i = 100000; i < 115000; i++ )
    {
      auto _path =
        Wt::WString( VAULT_ROOT + "/jobs/" )
        .arg( i )
        .toUTF8()
        ;

      std::cout << __FILE__ << ":" << __LINE__ << " " << _path << std::endl;



    }
  }

  response.out() << "ok";

} // endvoid ApiResource::handleRequest( const Wt::Http::Request & request, Wt::Http::Response & response )







template <class C>
void addEntryPoint( const std::string & url, Wt::WServer & server )
{
  server.addEntryPoint
  (
   Wt::EntryPointType::Application,
   [](const Wt::WEnvironment &env)
   {
     return std::make_unique<C>(env);
   },
   url
  );
}

int main( int argc, char ** argv )
{
  show_program_version( "start-up" );

  /*
  ** Right now we're putting the 'database to open' on the command
  **  line.  We can then run a 'demo' version connected to the 'demo'
  **  database easily.  Later we'll replace this with a proper 'open'
  **  tool.
  **
  */
  g_dbName = argv[1];

  /*
  ** Set the layout to employ the services that
  **  are compatible with embedded table views.  Right now, only
  **  JavaScript layout implementation works properly.
  **
  */
  Wt::WLayout::setDefaultImplementation( Wt::LayoutImplementation::JavaScript );
//  Wt::WLayout::setDefaultImplementation( Wt::LayoutImplementation::Flex );

  /*
  ** Fire up the Wt web server.  If anything throws we'll catch it.
  **
  */
  try
  {
    Wt::WServer server( argc, argv );

    /*
    ** These resources provide access to things in a static manner
    **  (not used yet)
    **
    */
//    server.addResource( std::make_shared< HtmlResource  >(), "/html"       );
//    server.addResource( std::make_shared< MonitResource >(), "/monittoken" );

    /*
    ** These resources provide an external API interface to the project
    **  (not used yet)
    **
    */
//    auto apiResource = std::make_shared<ApiResource>();
//    server.addResource( apiResource, "/api"  );
//    server.addResource( apiResource, "/api2" );

    /*
    ** These are the site entry-points.  There are two URL for this, but
    **  they yeild the same 'site' service.  The 'demo' is there just for
    **  giving quick demos so the url reads gnucashew.websiteserver.demo
    **  rather than gnucashew.websiteserver.gnucashew.
    **
    */
    addEntryPoint< Redirector >( "/"          , server );
    addEntryPoint< GCW::App   >( "/demo"      , server );
    addEntryPoint< GCW::App   >( "/gnucashew" , server );

    server.run();

  } // endtry

  catch( Wt::WServer::Exception & e )
  {
    std::cerr << e.what() << " TERMINATING TERMINATING TERMINATING" << std::endl;
    return -1;
  }

  return 0;

} // endint main( int argc, char ** argv )


