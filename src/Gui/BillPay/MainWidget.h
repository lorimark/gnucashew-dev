#line 2 "src/Gui/BillPay/MainWidget.h"

#ifndef __GUI_BILLPAY_MAINWIDGET_H___
#define __GUI_BILLPAY_MAINWIDGET_H___

#include <Wt/WGridLayout.h>
#include <Wt/WContainerWidget.h>

#include "EditWidget.h"
#include "Table.h"
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
    auto addClicked()-> void ;
    auto editClicked( Table * _table, Wt::WModelIndex _index )-> void ;
    auto openEditor( const std::string & _accountGuid )-> void ;
    auto buttonChanged( Wt::WRadioButton * _button )-> void ;
    auto setMonth( int _month )-> void ;
    auto disabledClicked()-> void ;
    auto refreshViews()-> void ;
    auto importClicked()-> void ;
    auto exportClicked()-> void ;

    std::unique_ptr< EditWidgetDialog > m_dialog;

    /*
    ** The edit widget gets loaded and unloaded for the
    **  editing functions.  Using an observing pointer
    **  let's us know automatically when the editor is
    **  open and when it's not.
    **
    */
    Wt::Core::observing_ptr< EditWidget > m_editWidget;

    ToolBar          * m_toolBar      = nullptr;
    Table            * m_paidView     = nullptr;
    Table            * m_unpaidView   = nullptr;
    Table            * m_disabledView = nullptr;

    auto on_headerClicked( int _col, const Wt::WMouseEvent _me )-> void ;

    int m_selectedMonth = -1;

//    Wt::WGridLayout * m_gridLayout = nullptr;
    Wt::WHBoxLayout * m_hlw = nullptr;

};  // endclass MainWidget

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_MAINWIDGET_H___


