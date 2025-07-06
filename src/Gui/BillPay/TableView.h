#line 2 "src/Gui/BillPay/TableView.h"

#ifndef __GUI_BILLPAY_TABLEVIEW_H___
#define __GUI_BILLPAY_TABLEVIEW_H___

#include <Wt/WTableView.h>

#include "TableModel.h"
#include "Status.h"

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \brief Table View
**
** A view to the data model
**
*/
class TableView
: public Wt::WTableView
{
  public:

    TableView( int _selectedMonth, const Status _status );

    auto setMonth( int _month )-> void ;

    auto rowCount()-> int ;

    auto model() const-> std::shared_ptr< TableModel >
    {
      return m_model;
    }

  private:

    std::shared_ptr< TableModel > m_model;

}; // endclass TableView

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_TABLEVIEW_H___


