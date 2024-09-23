#line 2 "src/Gui/RawTableWidget.h"

#ifndef __GUI_RAWTABLEWIDGET_H___
#define __GUI_RAWTABLEWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/Dbo/QueryModel.h>

//#include "../GnuCashew.h"
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
template <class C>
class RawTableWidget
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
    using Model = Wt::Dbo::QueryModel< typename C::Ptr >;

    /*!
    ** \brief Constructor
    **
    */
    RawTableWidget();

    /*!
    ** \brief Table View
    **
    **
    **
    */
    auto tableView ()-> GCW::Gui::TableView * { return m_tableView; }

    auto model ()-> std::shared_ptr< Model > { return m_model; }

  protected:

    auto load()-> void;

  private:

    auto loadData()-> void;

    std::shared_ptr< Model >   m_model;
    Wt::WContainerWidget     * m_toolBar   = nullptr;
    GCW::Gui::TableView      * m_tableView = nullptr;
    Wt::WContainerWidget     * m_statusBar = nullptr;

};  // endclass RawTableWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#ifndef __GUI_RAWTABLEWIDGETIMPL_H___
#include "RawTableWidget_impl.h"
#endif // __GUI_RAWTABLEWIDGETIMPL_H___

#endif // end __GUI_RAWTABLEWIDGET_H___


