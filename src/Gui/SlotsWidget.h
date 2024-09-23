#line 2 "src/Gui/SlotsWidget.h"

#ifndef __GUI_SLOTSWIDGET_H___
#define __GUI_SLOTSWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/Dbo/QueryModel.h>

#include "../GnuCashew.h"
#include "../Dbo/Slots.h"
#include "TableView.h"


namespace GCW {
  namespace Gui {

/*!
** \brief SlotsWidget
**
** The 'slots' table is used to 'extend' data in the various areas, such as notes on
**  transactions and so forth.
**
*/
class SlotsWidget
: public Wt::WContainerWidget
{
  private:

  public:

    /*!
    ** \brief Model
    **
    ** An alias for the Model in case this interface changes.
    **
    */
    using Model = Wt::Dbo::QueryModel< GCW::Dbo::Slots::Item::Ptr >;

    /*!
    ** \brief Constructor
    **
    */
    SlotsWidget();

    /*!
    ** \brief Table View
    **
    **
    **
    */
    GCW::Gui::TableView * tableView () { return m_tableView; }

    std::shared_ptr< Model > model () { return m_model; }

  private:

    void loadData();

    std::shared_ptr< Model >   m_model;
    GCW::Gui::TableView      * m_tableView = nullptr;

};  // endclass SlotsWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_SLOTSWIDGET_H___


