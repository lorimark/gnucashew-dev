
#include <Wt/WApplication.h>

#include "LanguagePicker.h"

namespace {

/*
** These are language-picker items used in the combo-box
**  language selector in the top of the site menu bar.
**  Each 'lauguage' requires a corresponding gcw_lang.xml
**  file that contains all of the translated strings.
**
*/
std::vector< std::vector< std::string > > langItems =
{
  { "en"    , "English"     },
  { "en_cb" , "Cowboy"      },
  { "nl"    , "Netherlands" },
};

} // endnamespace {

GCW::Gui::LanguagePicker::
LanguagePicker()
{
  /*
  ** Load the language choices in the combo box
  **
  */
  for( auto & item : langItems )
    addItem( item.at(1) );

  /*
  ** when activated, change the language
  **
  */
  activated().connect( [&]( int _selection )
  {
    wApp-> setLocale( langItems.at( _selection ).at(0) );
  });

} // endLanguagePicker()



