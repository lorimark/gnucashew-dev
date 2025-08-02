#line 2 "src/Gui/BillPay/TableView.cpp"

#include <Wt/WModelIndex.h>
#include <Wt/WStandardItem.h>

#include "../../Dbo/Accounts/Accounts.h"
#include "BillPay.h"

GCW::Gui::BillPay::TableView::
TableView( int _selectedMonth, const Status _status )
{
  /*
  ** Add 'Unpaid', 'Paid', 'Disabled' to the style class of this
  **  table for styling and such as.
  */
  addStyleClass( asStyleClass( _status ) );

  /*
  ** Set up some controls
  */
  setSortingEnabled       ( false                       );
  setSelectionBehavior    ( Wt::SelectionBehavior::Rows );
  setSelectionMode        ( Wt::SelectionMode::Single   );
  setColumnResizeEnabled  ( false                       );
  setAlternatingRowColors ( true                        );

  /*
  ** Make a data model
  */
  m_model = std::make_shared< TableModel >( _selectedMonth, _status );

  /*
  ** Set the model in to the table
  */
  setModel( m_model );

  /*
  ** Apply the column widths and alignments
  */
  for( int col=0; col< m_model-> columnCount(); col++ )
  {
    setColumnWidth    ( col, m_model-> columnDef(col).width     );
    setColumnAlignment( col, m_model-> columnDef(col).alignment );
  }

} // endTableView()


void
GCW::Gui::BillPay::TableView::
setMonth( int _month )
{
  int selected_row = -1;

  if( selectedIndexes().size() > 0 )
  {
    selected_row = selectedIndexes().begin()-> row();
  }

  m_model-> loadData( _month );

  if( selected_row > -1 )
  {
    select( m_model-> index( selected_row, 0 ) );
  }

} // endsetMonth( int _month )


auto
GCW::Gui::BillPay::TableView::
rowCount()-> int
{
  return m_model-> rowCount();

} // endrowCount()-> int


#define SEPARATOR " ("
auto
GCW::Gui::BillPay::TableView::
selectItem( const std::string _itemIdent )-> void
{
  clearSelection();

  /*
  ** strip off anything with the () SEPARATOR parenthesis
  **  (ugly but functional)
  */
  auto id = _itemIdent;
  if( id.find(SEPARATOR) != std::string::npos )
      id = id.substr( 0, id.find(SEPARATOR) );

  for( int row = 0; row< m_model-> rowCount(); row++ )
  {
    if( m_model-> item( row, 2 )-> text() == id )
    {
      select( m_model-> index( row, 2 ) );
    }
  }

} // endselectItem( const std::string _itemIdent )-> void

