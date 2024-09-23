#line 2 "src/Eng/AccountSuggestionModel.cpp"

#include "AccountSuggestionModel.h"

GCW::Eng::AccountSuggestionModel::
AccountSuggestionModel( const std::string & _accountGuid )
: Wt::WStandardItemModel( 0, 1 ),
  m_accountGuid( _accountGuid )
{

} // endAccountSuggestionModel( const std::string & _accountGuid )


