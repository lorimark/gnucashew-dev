#line 2 "src/Gui/BillPay/Model.h"

#ifndef __GUI_BILLPAY_MODEL_H___
#define __GUI_BILLPAY_MODEL_H___

#include <Wt/WLength.h>
#include <Wt/WStandardItemModel.h>

#include "Item.h"
#include "Status.h"

namespace GCW {
  namespace Gui {
    namespace BillPay {

/*!
** \Brief Model Column Definitions
**
** This holds the column definitions for the Model and Table.  It
**  includes the field name, field width (for the table), alignment
**  (also for the table), and toolTip (which is applied to the model
**  but gets displayed in the table).
**
*/
typedef struct COLUMNDEF
{
  /// field name
  const char * name;

  /// column width for the table view
  Wt::WLength width;

  /// alignment flag for the table view
  Wt::AlignmentFlag alignment;

  /// tool tip for the table view
  const char * toolTip;

} ColumnDef_t;

/*!
** \brief Data Model
**
** Contains paid, unpaid and disabled accounts.
**
** When constructing the Model, the parameters control the subset
**  of items that will appear in the model.  Therefore, the final
**  model contains only 'paid', 'unpaid' or 'disabled' items for
**  the month selected.
**
*/
class Model
: public Wt::WStandardItemModel
{
  public:

    /*!
    ** \brief ctor
    **
    ** During construction, the model examines all the billpay-items
    **  to detemine if the item meets the parameter criteria.  This
    **  allows a TableView to be constructed to present the items
    **  that meet this criteria as a grouped set of items.
    **
    ** To return all the items in the month of February that are
    **  'paid', the constructor would appear as follows;
    **
    ** \code
    ** auto model = std::make_shared< Model >( 2, BillPay::Status::Paid );
    ** \endcode
    **
    */
    Model
    (
      /// Select a 'calendar month' to compare status
      int _selectedMonth,

      /// Select a BillPay::Status to evaluate to
      Status _status
    );

    /*!
    ** \brief Column Definition
    **
    ** Return the column definition for the selected column.
    **
    */
    auto columnDef( int _col )-> ColumnDef_t ;

    /*!
    ** \brief Reload the data based on the selected month.
    **
    ** This will drop all the data in the model and reload it with
    **  the month selected.
    **
    */
    auto loadData( int _selectedMonth )-> void ;

  private:

    /*!
    ** \brief Sorter
    **
    ** This sorter produces a sorted list of bills-to-pay sorted
    **  by first 'group' then 'dueDay'.  This produces a number
    **  that might be like 20.22, meaning group=20, day=22.  The
    **  result in the view is all the "due next" items at the top
    **  of the list, and so on.  The group-value is to just help
    **  clean the display.  The result makes it very clear what bills
    **  are due next in line.
    **
    */
    auto sort( std::vector< GCW::Gui::BillPay::Item > & _bpItems )-> void ;

    /*!
    ** \brief Model Status
    **
    ** Each model represents items of a partcular status.  The model set
    **  contains, therefore, only items that match the selected status
    **  and the selected month.
    **
    */
    Status m_status;

}; // endclass Model

    } // endnamespace BillPay {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_BILLPAY_MODEL_H___


