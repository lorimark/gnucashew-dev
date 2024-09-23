#line 2 "src/Eng/AccountSuggestionModel.h"

#ifndef __ENG_ACCOUNTSUGGESTIONMODEL_H___
#define __ENG_ACCOUNTSUGGESTIONMODEL_H___

#include <Wt/WStandardItemModel.h>

namespace GCW {
  namespace Eng {



class AccountSuggestionModel
: public Wt::WStandardItemModel
{
  public:

    AccountSuggestionModel( const std::string & _accountGuid );


    std::string m_accountGuid;

};

  } // end namespace Eng {
} // endnamespace GCW {


#endif // #ifndef __ENG_ACCOUNTSUGGESTIONMODEL_H___


