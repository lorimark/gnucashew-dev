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

    auto buildContent()-> void ;
    auto do_addClicked()-> void ;
    auto do_editClicked()-> void ;
    auto do_disabledClicked()-> void ;
    auto do_summaryClicked()-> void ;
    auto addClicked()-> void ;
    auto editClicked( TableView * _table, Wt::WModelIndex _index )-> void ;
    auto openEditor( const std::string & _bpGuid )-> void ;
    auto buttonChanged( Wt::WRadioButton * _button )-> void ;
    auto setMonth( int _month )-> void ;
    auto refreshViews()-> void ;
    auto importClicked()-> void ;
    auto exportClicked()-> void ;

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
    TableView     * m_disabledView = nullptr ;
    SummaryWidget * m_summaryView  = nullptr ;

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
    int m_selectedMonth = -1;

//    Wt::WGridLayout * m_gridLayout = nullptr ;
    Wt::WHBoxLayout * m_hlw         = nullptr ;

};  // endclass MainWidget

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_MAINWIDGET_H___


