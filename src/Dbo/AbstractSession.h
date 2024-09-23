#line 2 "src/Dbo/AbstractSession.h"

#ifndef __DBO_SESSION_H___
#define __DBO_SESSION_H___

#include <Wt/Dbo/Session.h>

namespace GCW {
  namespace Dbo {

class AbstractSession
: public Wt::Dbo::Session
{
  public:

    AbstractSession() {}

    /*!
    ** \brief Open a database
    **
    */
    auto open( const std::string & _path )-> bool;

    auto path() const-> const std::string & { return m_path; }

    auto isOpen() const-> bool { return m_isOpen; }

//    virtual Wt::Dbo::Transaction startTransaction() const;

  protected:

    std::string m_path;
    bool m_isOpen = false;

  private:

}; // endclass Session

  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __SESSION_H___


