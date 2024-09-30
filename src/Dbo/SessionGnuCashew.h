#line 2 "src/Dbo/SessionGnuCashew.h"

#ifndef __DBO_SESSIONGNUCASHEW_H___
#define __DBO_SESSIONGNUCASHEW_H___

#include "Users/Auth.h"
#include "AbstractSession.h"

namespace GCW {
  namespace Dbo {
    namespace GnuCashew {

/*!
** \brief GnuCash Native Session
**
** This session controller is designed to interface to a back-end
**  gnucash data structure, without modification.
**
*/
class Session
: public GCW::Dbo::AbstractSession
{
  public:

    Session() {}

    /*!
    ** \brief Open a database
    **
    */
    bool open( const std::string & _path );

    /*!
    ** \brief Check GnuCashew Extensions
    **
    ** This examines the database tables to determine if the necessary
    **  modifications have been made to the database to support the
    **  GnuCashew Extensions.
    **
    */
    bool hasGnuCashewExtensions();

    /*!
    ** \brief Add GnuCashew Extensions
    **
    ** This makes the necessary modifications to the database to include
    **  the extensions necessary to support the GnuCashew attributes.
    **
    ** This function can be called repeatedly, as it will check for the
    **  presense of each attribute before it is added.
    **
    */
    bool addGnuCashewExtensions();

    bool gnucashIsOpen() const;
    void openGnucash();
    void closeGnucash();

    auto users()-> Wt::Auth::AbstractUserDatabase & { return *m_users; }
    auto login()-> Wt::Auth::Login                & { return  m_login; }

  private:

    std::unique_ptr< GCW::Dbo::Users::UserDatabase > m_users;
    Wt::Auth::Login m_login;

}; // endclass Session

    } // endnamespace GnuCashew {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __SESSIONGNUCASHEW_H___


