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

    void buildContent();
    void addClicked();
    void editClicked( Table * _table, Wt::WModelIndex _index );
    void openEditor( const std::string & _accountGuid );
    void buttonChanged( Wt::WRadioButton * _button );
    void setMonth( int _month );
    void disabledClicked();
    void refreshViews();

    std::unique_ptr< EditWidgetDialog > m_dialog;
    EditWidget       * m_editWidget   = nullptr;
    ToolBar          * m_toolBar      = nullptr;
    Table            * m_paidView     = nullptr;
    Table            * m_unpaidView   = nullptr;
    Table            * m_disabledView = nullptr;

    void on_headerClicked( int _col, const Wt::WMouseEvent _me );

    int m_selectedMonth = -1;

    Wt::WGridLayout * m_gridLayout = nullptr;

};  // endclass MainWidget

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_MAINWIDGET_H___


