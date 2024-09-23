#line 2 "src/Dbo/SessionGnuCashew.h"

#ifndef __DBO_SESSIONGNUCASHEW_H___
#define __DBO_SESSIONGNUCASHEW_H___

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

  private:

}; // endclass Session

    } // endnamespace GnuCashew {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // end#ifndef __SESSIONGNUCASHEW_H___


