#line 2 "src/Gui/CentralWidget.h"

#ifndef __GUI_CENTRALWIDGET_H___
#define __GUI_CENTRALWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WGridLayout.h>
#include <Wt/WTabWidget.h>

#include "AccountsTreeView.h"
#include "CustomersWidget.h"
#include "AccountRegister.h"

namespace GCW {
  namespace Gui {
    class AccountsTreeView;

/*!
** \brief Main UI Central Widget
**
** This widget acts as a 'tab widget manager' for controlling
**  what views (widgets) are presented to the user in the main
**  central display widget.  The central widget fills up the
**  lions share of the view window.
**
*/
class CentralWidget
: public Wt::WContainerWidget
{
  public:

    CentralWidget();

    auto tabWidget()        -> Wt::WTabWidget              * { return m_tabWidget;         }
    auto accountsTreeView() -> GCW::Gui::AccountsTreeView  * { return m_accountsTreeView;  }
    auto customersWidget()  -> GCW::Gui::CustomersWidget   * { return m_customersWidget;   }

    auto open_AccountRegister( const std::string & _accountGuid )-> void;
    auto open_CustomersWidget()-> void;
    auto open_CustomerReportWidget( const std::string & _customerGuid )-> void;
    auto open_BillPayWidget()-> void;
    auto open_TablesWidget()-> void;

    /*!
    ** \brief Index of Tab matching 'text'
    **
    ** Return the index of the tab with the
    **  matching text.
    **
    */
    auto tabIndex( const std::string & _text )-> int;

    auto test()-> void ;

  private:

    Wt::WGridLayout             * m_gridLayout       = nullptr ;
    Wt::WTabWidget              * m_tabWidget        = nullptr ;
    GCW::Gui::AccountsTreeView  * m_accountsTreeView = nullptr ;
    GCW::Gui::CustomersWidget   * m_customersWidget  = nullptr ;

}; // endclass CentralWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end#ifndef __CENTRALWIDGET_H___


