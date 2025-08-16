#line 2 "src/Gui/AccountRegister/AccountSuggestionEdit.cpp"

#include "AccountSuggestionEdit.h"
#include "AccountSuggestionPopup.h"

GCW::Gui::AccountSuggestionEdit::
AccountSuggestionEdit()
{
  auto popup = addChild( std::make_unique< GCW::Gui::AccountSuggestionPopup >() );
  popup-> forEdit( this, Wt::PopupTrigger::Editing /* | Wt::PopupTrigger::DropDownIcon */ );

} // endAccountSuggestionEdit()



