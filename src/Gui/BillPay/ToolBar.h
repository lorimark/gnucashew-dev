#line 2 "src/Gui/BillPay/ToolBar.h"


#ifndef __GUI_BILLPAY_TOOLBAR_H___
#define __GUI_BILLPAY_TOOLBAR_H___

#include <Wt/WTableView.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>

#include "Status.h"

namespace GCW {
  namespace Gui {
    namespace BillPay {

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

    Wt::Signal<> & editClicked() { return m_editClicked; }
    Wt::Signal<> m_editClicked;

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

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_TOOLBAR_H___


