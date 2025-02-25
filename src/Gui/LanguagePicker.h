#line 2 "src/Gui/LanguagePicker.h"

#ifndef __GUI_LANGUAGEPICKER_H___
#define __GUI_LANGUAGEPICKER_H___

#include <Wt/WComboBox.h>

namespace GCW {
  namespace Gui {

/*!
** \brief Language Picker
**
** The language picker is a combo-box placed at the top of the
**  website that allows the user to change the selected language
**  for the website.
**
**
*/
class LanguagePicker
: public Wt::WComboBox
{
  public:

    LanguagePicker();

  private:

}; // endclass LanguagePicker

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // #ifndef __GUI_LANGUAGEPICKER_H___


