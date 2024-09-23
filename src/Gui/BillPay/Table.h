#line 2 "src/Gui/BillPay/Table.h"

#ifndef __GUI_BILLPAY_TABLE_H___
#define __GUI_BILLPAY_TABLE_H___

#include <Wt/WTableView.h>

#include "Model.h"
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
class Table
: public Wt::WTableView
{
  public:

    Table( int _selectedMonth, const Status _status );

    void setMonth( int _month );

    std::shared_ptr< Model > model() const
    {
      return m_model;
    }

  private:

    std::shared_ptr< Model > m_model;
};

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_TABLE_H___


