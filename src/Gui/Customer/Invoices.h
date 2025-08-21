#line 2 "src/Gui/Customer/Invoices.h"

#ifndef __GUI_CUSTOMER_INVOICES_H___
#define __GUI_CUSTOMER_INVOICES_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WTableView.h>

#include "../../Eng/InvoicesModel.h"

namespace GCW {
  namespace Gui {
    namespace Customer {

/*!
** \brief Control Bar
**
** Control Bar with buttons
**
*/
class Invoices
: public Wt::WContainerWidget
{
  public:

    Invoices();

    auto setCustomerGuid( const std::string & _guid )-> void ;

  private:

    Wt::WTableView * m_tableView = nullptr;
    std::shared_ptr< GCW::Eng::InvoicesModel > m_model ;

}; // endclass Invoices

    } // endnamespace Customer {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_CUSTOMER_INVOICES_H___


