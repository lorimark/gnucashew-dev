#line 2 "src/Gui/SlotsWidget.cpp"

#include <Wt/WDateEdit.h>
#include <Wt/WItemDelegate.h>
#include <Wt/WSuggestionPopup.h>
#include <Wt/WText.h>
#include <Wt/WTableView.h>
#include <Wt/WTheme.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>

#include "../define.h"
#include "../App.h"
#include "SlotsWidget.h"


GCW::Gui::SlotsWidget::
SlotsWidget()
{
  /*
  ** Look in gcw.css for styling.
  **
  */
  addStyleClass( "SlotsWidget" );

  /*
  ** use a layout manager to install the table view into, so
  **  that the widget will fit and scroll properly.
  **
  */
  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );
  m_tableView = lw-> addWidget( std::make_unique< GCW::Gui::TableView >(), 1 );
//  tableView()-> setRowHeight( "20px" );

  /*
  ** Configure the table view.
  **
  */
  tableView()-> setSortingEnabled       ( true                                                          );
  tableView()-> setAlternatingRowColors ( true                                                          );
  tableView()-> setSelectionBehavior    ( Wt::SelectionBehavior::Rows                                   );
  tableView()-> setSelectionMode        ( Wt::SelectionMode::Single                                     );
//  tableView()-> setEditTriggers         ( Wt::EditTrigger::SingleClicked                                );
//  tableView()-> setEditOptions          ( Wt::EditOption::SingleEditor | Wt::EditOption::SaveWhenClosed ); // FIXME: this should probably be: MultipleEditor | LeaveEditorsOpen so we can open all editors on a single entry

  loadData();

} // endSlotsWidget()

void
GCW::Gui::SlotsWidget::
loadData()
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  auto query =
   GCW::app()-> gnucashew_session().find< GCW::Dbo::Slots::Item >()
   .orderBy( "id" )
   ;

  m_model = std::make_shared< Model >();
  m_model-> setQuery( query );
  m_model-> reload();
  m_model-> addAllFieldsAsColumns();

  tableView()-> setModel( m_model );

#ifdef NEVER
  // 0 = Date
  tableView()-> setColumnWidth    ( 0, "150px"                   );
  tableView()-> setHeaderAlignment( 0, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 0, Wt::AlignmentFlag::Right  );

  // 1 = Action/Num
  tableView()-> setColumnWidth    ( 1,  "50px"                   );
  tableView()-> setHeaderAlignment( 1, Wt::AlignmentFlag::Center );
  tableView()-> setColumnAlignment( 1, Wt::AlignmentFlag::Center );

  // 2 = Memo/Description
  tableView()-> setColumnWidth    ( 2,   "99%"                   );
  tableView()-> setHeaderAlignment( 2, Wt::AlignmentFlag::Left   );
  tableView()-> setColumnAlignment( 2, Wt::AlignmentFlag::Left   );

  // 3 = Account/Transfer
  tableView()-> setColumnWidth    ( 3, "200px"                   );
  tableView()-> setHeaderAlignment( 3, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 3, Wt::AlignmentFlag::Right  );

  // 4 = Reconciliation
  tableView()-> setColumnWidth    ( 4,  "25px"                   );
  tableView()-> setHeaderAlignment( 4, Wt::AlignmentFlag::Center );
  tableView()-> setColumnAlignment( 4, Wt::AlignmentFlag::Center );

  // 5 = Debit
  tableView()-> setColumnWidth    ( 5, "100px"                   );
  tableView()-> setHeaderAlignment( 5, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 5, Wt::AlignmentFlag::Right  );

  // 6 = Credit
  tableView()-> setColumnWidth    ( 6, "100px"                   );
  tableView()-> setHeaderAlignment( 6, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 6, Wt::AlignmentFlag::Right  );

  // 7 = Balance
  tableView()-> setColumnWidth    ( 7, "100px"                   );
  tableView()-> setHeaderAlignment( 7, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 7, Wt::AlignmentFlag::Right  );

  auto lastIndex = model()-> index( model()-> rowCount() -1, 0 );
  tableView()-> scrollTo( lastIndex );
  tableView()-> edit( lastIndex );
#endif

} // endvoid GCW::Gui::SlotsWidget::loadData()



