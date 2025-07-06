#line 2 "src/Gui/AccountSuggestionPopup.cpp"

#include "../App.h"
#include "AccountSuggestionPopup.h"

GCW::Gui::AccountSuggestionPopup::
AccountSuggestionPopup()
: Wt::WSuggestionPopup
  (
    Wt::WSuggestionPopup::Options
    {
      "<b>",                 // highlightBeginTag
      "</b>",                // highlightEndTag
      ',',                   // listSeparator      ()
      " \n",                 // whitespace
      "()[]{}-., \"@\n;:",   // wordSeparators     ()
      ""                     // appendReplacedText ()
   }
  )
{
  setAttributeValue( "style", "height:250px;overflow:scroll" );

  /*
  ** load all active accounts
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  for( auto accountItem : GCW::Dbo::Accounts::activeAccounts() )
    addSuggestion( GCW::Dbo::Accounts::fullName( accountItem-> guid() ) );

} // endAccountSuggestionPopup()



