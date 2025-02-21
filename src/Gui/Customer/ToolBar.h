#line 2 "src/Gui/Customer/ToolBar.h"


#ifndef __GUI_CUSTOMER_TOOLBAR_H___
#define __GUI_CUSTOMER_TOOLBAR_H___

#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>
#include <Wt/WCheckBox.h>

namespace GCW {
  namespace Gui {
    namespace Customer {

/*!
** \brief Control Bar
**
** Control Bar with buttons
**
*/
class ToolBar
: public Wt::WContainerWidget
{
  public:

    ToolBar();

    Wt::Signal<> & addClicked() { return m_addClicked; }
    Wt::Signal<> m_addClicked;

//    int selectedMonth() const;

//    std::shared_ptr< Wt::WButtonGroup > buttonGroup    () const { return m_group;    }
    auto disabledButton () const-> Wt::WCheckBox * { return m_disabled; }
    auto showDisabled   () const-> bool            ;

    auto importClicked()-> Wt::Signal<> & { return m_importClicked; }
    auto exportClicked()-> Wt::Signal<> & { return m_exportClicked; }

  private:

//    std::shared_ptr< Wt::WButtonGroup > m_group;
    Wt::WCheckBox * m_disabled = nullptr;
    Wt::WCheckBox * m_summary  = nullptr;

    Wt::Signal<> m_importClicked;
    Wt::Signal<> m_exportClicked;

}; // endclass ToolBar

    } // endnamespace Customer {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_CUSTOMER_TOOLBAR_H___


