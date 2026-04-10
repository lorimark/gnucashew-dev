#line 2 "src/Gui/BillPay/MainWidget.h"

#ifndef __GUI_BILLPAY_MAINWIDGET_H___
#define __GUI_BILLPAY_MAINWIDGET_H___

#include <Wt/WGridLayout.h>
#include <Wt/WContainerWidget.h>

#include "EditWidget.h"
#include "SummaryWidget.h"
#include "TableView.h"
#include "ToolBar.h"

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \brief Bill Pay Widget
**
**
*/
class MainWidget
: public Wt::WContainerWidget
{
  public:

    MainWidget();

  private:

    /*!
    ** Build Content
    */
    auto buildContent()-> void ;

    /*!
    ** Do refresh clicked
    */
    auto do_refreshClicked()-> void ;

    /*!
    ** Do add clicked
    */
    auto do_addClicked()-> void ;

    /*!
    ** Do edit clicked
    */
    auto do_editClicked()-> void ;

    /*!
    ** Do inactive clicked
    */
    auto do_inactiveClicked()-> void ;

    /*!
    ** Do summary clicked
    */
    auto do_summaryClicked()-> void ;

    /*!
    ** Do year changed
    */
    auto do_yearChanged()-> void ;

    /*!
    ** Refresh Clicked Handler
    */
    auto refreshClicked()-> void ;

    /*!
    ** Add Clicked Handler
    */
    auto addClicked()-> void ;

    /*!
    ** Edit Clicked Handler
    */
    auto editClicked( TableView * _table, Wt::WModelIndex _index )-> void ;

    /*!
    ** Open the Editor
    */
    auto openEditor( const std::string & _bpGuid )-> void ;

    /*!
    ** Set the current Month
    */
    auto setMonth( int _month )-> void ;

    /*!
    ** Refresh the views
    */
    auto refreshViews()-> void ;

    /*!
    ** Import Handler
    */
    auto importClicked()-> void ;

    /*!
    ** Export Handler
    */
    auto exportClicked()-> void ;

    /*!
    ** Clear table selections except for the indicated table
    */
    auto clearSelectionExcept( TableView * = nullptr )-> void ;

    /*!
    ** Summary Clicked Handler
    */
    auto summaryClicked( const std::string & _txGuid )-> void ;

    /*!
    ** Finder Input Handler
    */
    auto finderInput()-> void ;

    /*!
    ** Recall selected month from config.
    */
    auto recallSelectedMonth() const-> int ;

    auto toolBar      () const-> ToolBar       * { return m_toolBar;      }
    auto pendingView  () const-> TableView     * { return m_pendingView;  }
    auto paidView     () const-> TableView     * { return m_paidView;     }
    auto unpaidView   () const-> TableView     * { return m_unpaidView;   }
    auto inactiveView () const-> TableView     * { return m_inactiveView; }
    auto summaryView  () const-> SummaryWidget * { return m_summaryView;  }

    auto selectedMonth()-> int { return m_selectedMonth ; }
    auto selectedYear()-> int ;

    std::unique_ptr< EditWidgetDialog > m_dialog ;

    /*
    ** The edit widget gets loaded and unloaded for the
    **  editing functions.  Using an observing pointer
    **  let's us know automatically when the editor is
    **  open and when it's not.
    **
    */
    Wt::Core::observing_ptr< EditWidget > m_editWidget ;

    ToolBar       * m_toolBar      = nullptr ;
    TableView     * m_pendingView  = nullptr ;
    TableView     * m_paidView     = nullptr ;
    TableView     * m_unpaidView   = nullptr ;
    TableView     * m_inactiveView = nullptr ;
    SummaryWidget * m_summaryView  = nullptr ;

    /*!
    ** \brief Header Clicked
    **
    ** This responds to the header/columns being clicked on.  It
    **  selects the current month to be worked on for bill pay.
    **
    ** /ref see; m_selectedMonth;
    **
    */
    auto on_headerClicked( int _col, const Wt::WMouseEvent _me )-> void ;

    /*!
    ** \brief Selected Index
    **
    ** When single-clicking through the interface, the currently selected
    **  (clicked) item, so that if the 'edit' button is hit, we'll know
    **  which was the last item clicked.  This is important because there
    **  are three possible table-views containing items, and we're never
    **  sure which was the last table clicked in.  So, on-click, in any of
    **  the three tables, the clicked-item index will be stored here.
    **
    */
    Wt::WModelIndex m_selectedIndex;

    /*!
    ** \brief Selected Month
    **
    ** Bill Pay works on one month at a time.  The month is chosen
    **  by clicking on one of the month columns.
    **
    */
    int m_selectedMonth = -1;

//    Wt::WGridLayout * m_gridLayout = nullptr ;
    Wt::WHBoxLayout * m_hlw         = nullptr ;

    /*
    ** \brief Encryption Password
    **
    ** This is a very simple (and dumb) password tool for the bill-pay data.
    **  Since it is possible (to unwisely) code user names and passwords
    **  in to the notes field (yes we do) it is a good idea to offer
    **  encryption.
    **
    ** When BillPay is opened, this password is empty by default, so the user
    **  will be required to enter the password to access the notes field.
    **
    */
    std::string _password ;

};  // endclass MainWidget

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_MAINWIDGET_H___


