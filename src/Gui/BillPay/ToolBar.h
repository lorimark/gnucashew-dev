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

    /*!
    ** return the selected year
    */
    auto selectedYear() const-> int ;

    /*!
    ** return the text in the finder field
    */
    auto finderText() const-> std::string ;

    /*!
    ** Year Selector
    */
    auto yearSelector() const-> Wt::WComboBox *
    {
      return m_year;
    }

    /*!
    ** Add Button
    */
    auto addButton() const-> Wt::WPushButton *
    {
      return m_add;
    }

    /*!
    ** Edit Button
    */
    auto editButton() const-> Wt::WPushButton *
    {
      return m_edit;
    }

    /*!
    ** Import Button
    */
    auto importButton() const-> Wt::WPushButton *
    {
      return m_import;
    }

    /*!
    ** Export Button
    */
    auto exportButton() const-> Wt::WPushButton *
    {
      return m_export;
    }

    /*!
    ** Inactive Button
    */
    auto inactiveButton() const-> Wt::WCheckBox *
    {
      return m_inactive;
    }

    /*!
    ** Show Inactive
    */
    auto showInactive() const-> bool ;

    /*!
    ** Summary Button
    */
    auto summaryButton() const-> Wt::WCheckBox *
    {
      return m_summary;
    }

    /*!
    ** Show Summary
    */
    auto showSummary() const-> bool ;

    /*!
    ** Finder Input
    */
    auto finderInput() const-> Wt::WLineEdit *
    {
      return m_finder;
    }

  private:

    Wt::WPushButton * m_add      = nullptr ;
    Wt::WPushButton * m_edit     = nullptr ;
    Wt::WPushButton * m_import   = nullptr ;
    Wt::WPushButton * m_export   = nullptr ;
    Wt::WComboBox   * m_year     = nullptr ;
    Wt::WCheckBox   * m_inactive = nullptr ;
    Wt::WCheckBox   * m_summary  = nullptr ;
    Wt::WLineEdit   * m_finder   = nullptr ;

}; // endclass ToolBar

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_TOOLBAR_H___


