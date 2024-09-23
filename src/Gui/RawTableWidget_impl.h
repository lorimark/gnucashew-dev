#line 2 "src/Gui/RawTableWidget_impl.h"

#ifndef __GUI_RAWTABLEWIDGETIMPL_H___
#define __GUI_RAWTABLEWIDGETIMPL_H___

#include <Wt/WVBoxLayout.h>

template <class C>
GCW::Gui::RawTableWidget<C>::
RawTableWidget()
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
  auto w = std::make_unique< GCW::Gui::TableView >();
  m_tableView = w.get();
  lw-> addWidget( std::move( w ), 1 );
//  tableView()-> setRowHeight( "20px" );

  /*
  ** Configure the table view.
  **
  */
  tableView()-> setSortingEnabled       ( true                                                          );
  tableView()-> setAlternatingRowColors ( true                                                          );
  tableView()-> setSelectionBehavior    ( Wt::SelectionBehavior::Rows                                   );
  tableView()-> setSelectionMode        ( Wt::SelectionMode::Single                                     );
  tableView()-> setEditTriggers         ( Wt::EditTrigger::None /* SingleClicked */                     );
//  tableView()-> setEditOptions          ( Wt::EditOption::SingleEditor | Wt::EditOption::SaveWhenClosed ); // FIXME: this should probably be: MultipleEditor | LeaveEditorsOpen so we can open all editors on a single entry

} // endSlotsWidget()

template <class C>
auto
GCW::Gui::RawTableWidget<C>::
load()-> void
{
  Wt::WContainerWidget::load();

  loadData();

} // endload()-> void

template <class C>
auto
GCW::Gui::RawTableWidget<C>::
loadData()-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  auto query =
   GCW::app()-> gnucashew_session().find< typename C::Item >()
//   .orderBy( "id" )
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

} // endloadData()-> void


#endif // __GUI_RAWTABLEWIDGETIMPL_H___


