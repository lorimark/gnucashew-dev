#line 2 "src/Gui/RawTableWidget_impl.h"

#ifndef __GUI_RAWTABLEWIDGETIMPL_H___
#define __GUI_RAWTABLEWIDGETIMPL_H___

#include <Wt/WVBoxLayout.h>

template <class C>
GCW::Gui::RawTableWidget<C>::
RawTableWidget( const std::string & _viewName )
{
  /*
  ** Look in gcw.css for styling.
  */
  addStyleClass( "RawTableWidget_" + _viewName );

  /*
  ** use a layout manager to install the table view into, so
  **  that the widget will fit and scroll properly.
  */
  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );

  auto tb = std::make_unique< Wt::WToolBar >();
  m_toolBar = tb.get();

  auto w_ = std::make_unique< Wt::WLineEdit   >();
  m_search = w_.get();
  m_toolBar-> addWidget( std::move( w_ ), Wt::AlignmentFlag::Right );
  m_toolBar-> addWidget( std::make_unique< Wt::WText >( "<span style=\"color:red;\">these tables have been designed to facilitate the complete destruction of your database.  clicking can ruin your day!  use caution!</span>" ) );
  m_search -> setPlaceholderText( "Search" );
  m_search -> textInput().connect( this, &RawTableWidget<C>::on_search );

  /*
  ** Configure the table view.
  */
  auto tv = std::make_unique< GCW::Gui::TableView >();
  m_tableView = tv.get();
  tableView()-> setSortingEnabled       ( true                                                          );
  tableView()-> setAlternatingRowColors ( true                                                          );
  tableView()-> setSelectionBehavior    ( Wt::SelectionBehavior::Items                                  );
  tableView()-> setSelectionMode        ( Wt::SelectionMode::Single                                     );
  tableView()-> setEditTriggers         ( Wt::EditTrigger::SingleClicked                                );
  tableView()-> setEditOptions          ( Wt::EditOption::SingleEditor | Wt::EditOption::SaveWhenClosed );

  auto sb = std::make_unique< Wt::WContainerWidget >();
  m_statusBar = sb.get();

  lw-> addWidget( std::move( tb )    );
  lw-> addWidget( std::move( tv ), 1 );
  lw-> addWidget( std::move( sb )    );

} // endSlotsWidget()

template <class C>
auto
GCW::Gui::RawTableWidget<C>::
load()-> void
{
  Wt::WContainerWidget::load();

  loadData();

  m_statusBar-> addNew< Wt::WText >( Wt::WString( "{1} Rows" ).arg( tableView()-> model()-> rowCount() ) );

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

  m_proxy = std::make_shared< Wt::WSortFilterProxyModel >();
  m_proxy-> setSourceModel( m_model );
  m_proxy-> setDynamicSortFilter( true );
  m_proxy-> setFilterKeyColumn( 0 );

  tableView()-> setModel( m_proxy );

} // endloadData()-> void

template <class C>
auto
GCW::Gui::RawTableWidget<C>::
on_search()-> void
{
  auto regex = std::make_unique< std::regex >( Wt::WString(".*{1}.*").arg( m_search-> valueText() ).toUTF8() );
  m_proxy-> invalidate();
  m_proxy-> setFilterRegExp( std::move( regex ) );

} // endon_search()-> void

#endif // __GUI_RAWTABLEWIDGETIMPL_H___


