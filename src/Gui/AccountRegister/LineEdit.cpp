#line 2 "src/Gui/AccountRegister/LineEdit.cpp"

#include "LineEdit.h"

GCW::Gui::AccountRegister::SuggestionEdit::
SuggestionEdit()
{
  auto popup = addChild( std::make_unique< GCW::Gui::AccountRegister::SuggestionPopup >() );
  popup-> forEdit( this, Wt::PopupTrigger::Editing /* | Wt::PopupTrigger::DropDownIcon */ );

} // endSuggestionEdit()



