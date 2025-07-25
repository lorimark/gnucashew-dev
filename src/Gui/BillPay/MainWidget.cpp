#line 2 "src/Gui/BillPay/MainWidget.cpp"

#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>

#include "BillPay.h"

GCW::Gui::BillPay::MainWidget::
MainWidget()
{
  // identify
  addStyleClass( "BillPay"    );
  addStyleClass( "MainWidget" );

  buildContent();

} // endMainWidget()

auto
GCW::Gui::BillPay::MainWidget::
buildContent()-> void
{
  clear();

  // layout
  m_hlw = setLayout( std::make_unique< Wt::WHBoxLayout >() );

  m_summaryView = m_hlw-> addWidget( std::make_unique< SummaryWidget >() );
  m_hlw-> setResizable( 0, true, Wt::WLength( 20, Wt::LengthUnit::Percentage ) );

  auto cw  = m_hlw-> addWidget( std::make_unique< Wt::WContainerWidget >() );

  // toolbar
  {
    auto u_ = std::make_unique< ToolBar >();
    m_toolBar = u_.get();
    cw-> addWidget( std::move( u_ ) );

    m_toolBar                    -> addClicked()  .connect( this, &GCW::Gui::BillPay::MainWidget::do_addClicked  );
    m_toolBar                    -> editClicked() .connect( this, &GCW::Gui::BillPay::MainWidget::do_editClicked );
    m_toolBar-> inactiveButton() -> clicked()     .connect( this, &MainWidget::do_inactiveClicked                );
    m_toolBar-> summaryButton()  -> clicked()     .connect( this, &MainWidget::do_summaryClicked                 );
    m_toolBar-> importClicked()                   .connect( this, &MainWidget::importClicked                     );
    m_toolBar-> exportClicked()                   .connect( this, &MainWidget::exportClicked                     );

  } // toolbar

  // recall selected month
  m_selectedMonth = configItem()-> getVarInt( "selectedMonth" );
  if( m_selectedMonth < 1
   || m_selectedMonth > 12 )
      m_selectedMonth = 1;

  // unpaid items
  {
    auto u_ = std::make_unique< TableView >( m_selectedMonth, Status::Unpaid );
    m_unpaidView = u_.get();
    cw-> addWidget( std::move( u_ ) );
    m_unpaidView->
      clicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        /*
        ** remember the clicked index
        */
        m_selectedIndex = _index;
        clearSelectionExcept( m_unpaidView );
      });
    m_unpaidView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        clearSelectionExcept( m_unpaidView );
        editClicked( m_unpaidView, _index );
      });

    /*
    ** unpaid items has a header, whereas the other two item-tables do not have a
    **  header and clicking on the header changes the selected month
    */
    m_unpaidView->
      headerClicked().connect( this, &MainWidget::on_headerClicked );

  } // endunpaid items

  // pending items
  {
    auto u_ = std::make_unique< TableView >( m_selectedMonth, Status::Pending );
    m_pendingView = u_.get();
    cw-> addWidget( std::move( u_ ) );
    m_pendingView->
      clicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        /*
        ** remember the clicked index
        */
        m_selectedIndex = _index;
        clearSelectionExcept( m_pendingView );
      });
    m_pendingView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        clearSelectionExcept( m_pendingView );
        editClicked( m_pendingView, _index );
      });

  } // endpending items

  // paid items
  {
    auto u_ = std::make_unique< TableView >( m_selectedMonth, Status::Paid );
    m_paidView = u_.get();
    cw-> addWidget( std::move( u_ ) );
    m_paidView->
      clicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        /*
        ** remember the clicked index
        */
        m_selectedIndex = _index;
        clearSelectionExcept( m_paidView );
      });
    m_paidView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        clearSelectionExcept( m_paidView );
        editClicked( m_paidView, _index );
      });

  } // endpaid items

  // inactive items
  {
    auto u_ = std::make_unique< TableView >( m_selectedMonth, Status::Inactive );
    m_inactiveView = u_.get();
    cw-> addWidget( std::move( u_ ) );
    m_inactiveView->
      clicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        /*
        ** remember the clicked index
        */
        m_selectedIndex = _index;
        clearSelectionExcept( m_inactiveView );
      });
    m_inactiveView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        clearSelectionExcept( m_inactiveView );
        editClicked( m_inactiveView, _index );
      });

  } // endinactive items

  do_summaryClicked();

  refreshViews();

} // endbuildContent()-> void


auto
GCW::Gui::BillPay::MainWidget::
clearSelectionExcept( TableView * _view )-> void
{
  if( _view != m_unpaidView   ) m_unpaidView   -> clearSelection();
  if( _view != m_pendingView  ) m_pendingView  -> clearSelection();
  if( _view != m_paidView     ) m_paidView     -> clearSelection();
  if( _view != m_inactiveView ) m_inactiveView -> clearSelection();

  wApp-> processEvents();

} // endclearSelectionExcept( TableView * )-> void


auto
GCW::Gui::BillPay::MainWidget::
openEditor( const std::string & _bpGuid )-> void
{

  /*
  ** if the edit widget is open, then we can't do anything.
  */
  if( m_editWidget )
    return;

  /*
  ** Split the page to open/edit this item
  **
  */
  auto u_ = std::make_unique< GCW::Gui::BillPay::EditWidget >( _bpGuid );
  m_editWidget = u_.get();
//  m_gridLayout-> addWidget( std::move( u_), 1, 1 );
//  m_gridLayout-> setColumnResizable( 0, true, "30%" );

  m_hlw-> addWidget( std::move( u_ ) );
  m_hlw-> setResizable( 1, true, Wt::WLength( 20, Wt::LengthUnit::Percentage ) );

  m_editWidget->
    deleted().connect( [=]()
    {
      Wt::WMessageBox::show( "Bill Pay", TR("gcw.not-yet-implemented"), Wt::StandardButton::Ok );
    });

  m_editWidget->
    saved().connect( [=]()
    {
      refreshViews();
      m_hlw-> removeWidget( m_editWidget.get() );
      m_hlw-> setResizable( 1, true, Wt::WLength::Auto );
    });

  m_editWidget->
    canceled().connect( [=]()
    {
      m_hlw-> removeWidget( m_editWidget.get() );
      m_hlw-> setResizable( 1, true, Wt::WLength::Auto );
    });

} // endopenEditor( const std::string & _nickname )-> void

auto
GCW::Gui::BillPay::MainWidget::
do_addClicked()-> void
{
  addClicked();

} // enddo_addClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
do_editClicked()-> void
{
  if( !m_selectedIndex.isValid() )
    return;

  auto zcolIndex = m_selectedIndex.model()-> index( m_selectedIndex.row(), 0 );
  auto bpGuid = Wt::asString( zcolIndex.data( Wt::ItemDataRole::User ) ).toUTF8();
  openEditor( bpGuid );

} // enddo_editClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
addClicked()-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  openEditor( "" );

} // endaddClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
editClicked( TableView * _table, Wt::WModelIndex _index )-> void
{
  /*
  ** remember the index
  */
  m_selectedIndex = _index;

  /*
  ** Get the 0-col index and use that to get the guid of this
  **  row, and use that to get the Edit dialog open on that
  **  guid.
  */
  if( _index.isValid() )
  {
    auto zcolIndex = _index.model()-> index( _index.row(), 0 );
    auto bpGuid = Wt::asString( zcolIndex.data( Wt::ItemDataRole::User ) ).toUTF8();
    openEditor( bpGuid );
  }

} // endeditClicked( TableView * _table, Wt::WModelIndex _index )-> void

auto
GCW::Gui::BillPay::MainWidget::
do_inactiveClicked()-> void
{
  if( m_toolBar-> showInactive() )
      m_inactiveView-> setHidden( false );
  else
      m_inactiveView-> setHidden( true );

} // endinactiveClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
do_summaryClicked()-> void
{
  if( m_toolBar-> showSummary() )
    m_summaryView-> setHidden( false );
  else
    m_summaryView-> setHidden( true );

//  m_summaryView-> setMonth( m_selectedMonth );

} // enddo_summaryClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
setMonth( int _month )-> void
{
  m_selectedMonth = _month;

  if( m_unpaidView   ) m_unpaidView   -> setMonth( _month );
  if( m_pendingView  ) m_pendingView  -> setMonth( _month );
  if( m_paidView     ) m_paidView     -> setMonth( _month );
  if( m_inactiveView ) m_inactiveView -> setMonth( _month );
  if( m_summaryView  ) m_summaryView  -> setMonth( _month );

  if( m_pendingView-> rowCount() > 0 )
      m_pendingView-> setHidden( false );
  else
      m_pendingView-> setHidden( true );

  if( m_paidView-> rowCount() > 0 )
      m_paidView-> setHidden( false );
  else
      m_paidView-> setHidden( true );

  /*
  ** BUGBUG: not sure why i tested all of this just to make the same call... weird!
  */
//  if( m_inactiveView-> rowCount() > 0 )
//      do_inactiveClicked();
//  else
      do_inactiveClicked();

  /*
  ** in the words of Spock; "remember"
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  configItem().modify()-> setVar( "selectedMonth", m_selectedMonth );

} // endsetMonth( int _month )-> void

auto
GCW::Gui::BillPay::MainWidget::
refreshViews()-> void
{
  setMonth( m_selectedMonth );

} // endrefreshViews()-> void

auto
GCW::Gui::BillPay::MainWidget::
importClicked()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endimportClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
exportClicked()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endexportClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
on_headerClicked( int _col, const Wt::WMouseEvent _me )-> void
{
  if( _col >= 9 )
    setMonth( _col - 8 );

} // endon_headerClicked( int _col, const Wt::WMouseEvent _me )-> void


