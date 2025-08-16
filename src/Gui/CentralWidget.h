#line 2 "src/Gui/CentralWidget.h"

#ifndef __GUI_CENTRALWIDGET_H___
#define __GUI_CENTRALWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WGridLayout.h>
#include <Wt/WTabWidget.h>

#include "AccountsTreeView.h"
#include "AccountRegister/AccountRegister.h"
#include "Customer/MainWidget.h"

namespace GCW {
  namespace Gui {
    class AccountsTreeView;

/*!
** \brief Main GnuCashew Central Widget
**
** This widget acts as a 'tab widget manager' for controlling
**  what views (widgets) are presented to the user in the main
**  central display widget.  The central widget fills up the
**  lion's share of the MainWidget area.
**
** \ref see also; MainWidget
**
*/
class CentralWidget
: public Wt::WContainerWidget
{
  public:

    CentralWidget();

    auto tabWidget()        -> Wt::WTabWidget                 * { return m_tabWidget;         }
    auto accountsTreeView() -> GCW::Gui::AccountsTreeView     * { return m_accountsTreeView;  }
    auto customersWidget()  -> GCW::Gui::Customer::MainWidget * { return m_customersWidget;   }
    auto activateAccountsTreeView()-> void ;

    auto open_AccountRegister      ( const std::string & _accountGuid  )-> void;
    auto open_CustomersWidget      (                                   )-> void;
    auto open_EmployeesWidget      (                                   )-> void;
    auto open_CustomerReportWidget ( const std::string & _customerGuid )-> void;
    auto open_TablesWidget         (                                   )-> void;

#ifdef ENABLE_BILLPAY
    auto open_BillPayWidget        (                                   )-> void;
#endif

    /*!
    ** \brief Index of Tab matching 'text'
    **
    ** Return the index of the tab with the
    **  matching text.
    **
    ** This is used when opening new windows.  When opening a new window, the
    **  system will first check if the window is already open.  For instance,
    **  if the "Customers Widget" is requested, the system will first check, by
    **  way of "tab-name" if there is a tab that is already open.  If so, the
    **  user is switched to the open tab, rather than creating a new tab.
    **
    */
    auto tabIndex( const std::string & _text )-> int ;

    auto test()-> void ;

  private:

    Wt::WGridLayout                * m_gridLayout       = nullptr ;
    Wt::WTabWidget                 * m_tabWidget        = nullptr ;
    GCW::Gui::AccountsTreeView     * m_accountsTreeView = nullptr ;
    GCW::Gui::Customer::MainWidget * m_customersWidget  = nullptr ;

}; // endclass CentralWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end#ifndef __CENTRALWIDGET_H___


