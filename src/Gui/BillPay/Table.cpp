#line 2 "src/Gui/BillPay/Table.cpp"

#include <Wt/WModelIndex.h>
#include <Wt/WStandardItem.h>

#include "../../Dbo/Accounts/Accounts.h"
#include "BillPay.h"

GCW::Gui::BillPay::Table::
Table( int _selectedMonth, const Status _status )
{
  /*
  ** Add 'Unpaid', 'Paid', 'Disabled' to the style class of this
  **  table for styling and such as.
  **
  */
  addStyleClass( asStyleClass( _status ) );

  /*
  ** Set up some controls
  **
  */
  setSortingEnabled       ( false                       );
  setSelectionBehavior    ( Wt::SelectionBehavior::Rows );
  setSelectionMode        ( Wt::SelectionMode::Single   );
  setColumnResizeEnabled  ( false                       );
  setAlternatingRowColors ( true                        );

  /*
  ** Make a data model
  **
  */
  m_model = std::make_shared< Model >( _selectedMonth, _status );

  /*
  ** Set the model in to the table
  **
  */
  setModel( m_model );

  /*
  ** Apply the column widths and alignments
  **
  */
  for( int col=0; col< m_model-> columnCount(); col++ )
  {
    setColumnWidth    ( col, m_model-> columnDef(col).width     );
    setColumnAlignment( col, m_model-> columnDef(col).alignment );
  }

} // endTable()


void
GCW::Gui::BillPay::Table::
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


