#line 2 "src/Gui/TableView.h"

#ifndef __GUI_TABLEVIEW_H___
#define __GUI_TABLEVIEW_H___

#include <Wt/WTableView.h>

namespace GCW {
  namespace Gui {

/*!
** \brief Custom Table View Class
**
** Implementing our own table view class derived from the Wt one.  This
** implementation is designed to be layout aware.  Key features include
** auto-resizing columns.
**
** Code Credit:
**   https://redmine.webtoolkit.eu/boards/1/topics/11110?r=18058#message-18058
**   Matt Russell (mrussell@neptec.com)
**
**/
class TableView
: public Wt::WTableView
{
public:

    /*! Default table header height */
    const static int kTableHeaderRowHeight;

    /*! Default table row height */
    const static int kTableBodyRowHeight;

    /*! Assumed table cell padding */
    const static int kTableCellPadding;

    /*! Width that a scroll bar adds to a table */
    const static int kScrollBarWidth;

    /*! Default fixed width a date/time column takes up (without wrapping) */
    const static int kDefaultDateTimeWidth;

    /*!
    ** \brief ctor
    */
    TableView() ;

    /*!
    ** Upon a table resize, size the columns appropriately.
    **
    ** @param int width Full table width
    ** @param int height Full table height
    */
    auto layoutSizeChanged( int _width, int _height )-> void override ;

    /*!
    ** Overload setColumnWidth so we can save what the user specifies into our
    ** map.  This implementation can take both absolute and relative
    ** (percentage) widths. Percentages are interpretted as the percentage of
    ** non-allocated width remaining.  i.e. if a table is 100px, and one column
    ** has an absolute width of 20px, then the two following relative columns
    ** should both use 50%, which would yeild 40px each (minus padding.)
    */
    auto setColumnWidth( int _column, const Wt::WLength & _width )-> void override ;

    /*!
    ** Set the number of visible rows before a scroll bar appears
    */
    auto setVisibleRows( int _rows )-> void { m_visible_rows = _rows; }

protected:

    auto handleClick       ( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void;
//    auto handleDoubleClick ( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void;
    auto handleMouseDown   ( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void;
//    auto handleMouseUp     ( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void;

    Wt::WModelIndex m_lastIndexClick;

    /*
    ** Map table columns to width
    */
    std::map< int, Wt::WLength > m_widths;

    /*
    ** Rows visible before scroll bar
    */
    int m_visible_rows = -1;

    /*
    ** Indicates which row is being edited
    */
    int m_editingRow = -1;

}; // endclass TableView :

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end#ifndef __TABLEVIEW_H___


