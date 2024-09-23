#line 2 "src/Eng/Engine.h"

#ifndef __ENG_ENGINE_H___
#define __ENG_ENGINE_H___

#include <string>

#include "Accounts.h"

namespace GCW {
  namespace Eng {

class Engine
{
  public:

    Engine();

    /*!
    ** \brief Open the Database
    **
    */
    bool open( const std::string & _filePath );

    /*!
    ** \brief Is Database Open
    **
    */
    bool isOpen();

    /*!
    ** \brief Database has Gnucashew Extensions
    **
    */
    bool hasGnucashewExtensions();

    GCW::Eng::Accounts & accounts() { return m_accounts; }

  private:

    GCW::Eng::Accounts m_accounts;

}; // endclass Engine

  } //  namespace Eng {
} // endnamespace GCW {


#endif // #ifndef __ENG_ENGINE_H___



