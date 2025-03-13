#line 2 "src/Gui/AccountComboBox.h"

#ifndef __GUI_ACCOUNTCOMBOBOX_H___
#define __GUI_ACCOUNTCOMBOBOX_H___

#include <Wt/WComboBox.h>

namespace GCW {
  namespace Gui {

class AccountComboBox
: public Wt::WComboBox
{
  public:
    AccountComboBox();

    auto valueGuid()-> std::string ;
};

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTCOMBOBOX_H___


