#line 2 "src/Gui/BillPay/TableView.cpp"

#include <Wt/WModelIndex.h>
#include <Wt/WStandardItem.h>

#include "../../Dbo/Accounts/Accounts.h"
#include "BillPay.h"

GCW::Gui::BillPay::TableView::
TableView( int _selectedMonth, int _selectedYear, const Status _status )
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
  m_model = std::make_shared< TableModel >( _selectedMonth, _selectedYear, _status );

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
setDate( int _month, int _year )
{
  int selected_row = -1;

  if( selectedIndexes().size() > 0 )
  {
    selected_row = selectedIndexes().begin()-> row();
  }

  m_model-> loadData( _month, _year );

  if( selected_row > -1 )
  {
    select( m_model-> index( selected_row, 0 ) );
  }

} // endsetMonth( int _month )


auto
GCW::Gui::BillPay::TableView::
setFilter( const std::string & _filter )-> void
{
  m_model-> setFilter( _filter );

} // endsetFilter( const std::string & _filter )-> void


auto
GCW::Gui::BillPay::TableView::
rowCount()-> int
{
  return m_model-> rowCount();

} // endrowCount()-> int

/*!
** BUGBUG: this is really crappy
**
** \todo fix this
** This function is here to capture the SummaryReport
**  clicked() txItem-> description() value.  This value
**  is a simple text-value from the description of the
**  transaction as it was entered in the bill pay
**  sub system.  Basically, there is no 'hard' connection
**  between the bill pay event and the transaction item
**  that gets entered.  This needs to be fixed, as keying
**  these two widgets together like this is sloppy.
**
*/
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
      /*
      ** this selects the item in the view and also
      **  emits a 'clicked' signal so any other entity
      **  interested in this selection can respond
      **  accordinly.
      */
      auto index = m_model-> index( row, 2 );
      select( index );
      clicked().emit( index, Wt::WMouseEvent() );
      return;
    }
  }

} // endselectItem( const std::string _itemIdent )-> void

