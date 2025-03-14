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

  std::set< std::string > items;
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  for( auto accountItem : GCW::Dbo::Accounts::activeAccounts() )
    items.insert( GCW::Dbo::Accounts::fullName( accountItem-> guid() ) );

  for( auto item : items )
    addSuggestion( item );

} // endAccountSuggestionPopup()



