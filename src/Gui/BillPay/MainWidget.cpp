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
    m_toolBar-> disabledButton() -> clicked()     .connect( this, &MainWidget::do_disabledClicked                );
    m_toolBar-> summaryButton()  -> clicked()     .connect( this, &MainWidget::do_summaryClicked                 );
    m_toolBar-> importClicked()                   .connect( this, &MainWidget::importClicked                     );
    m_toolBar-> exportClicked()                   .connect( this, &MainWidget::exportClicked                     );

  } // toolbar

  // recall selected month
  m_selectedMonth = configItem()-> getVarInt( "selectedMonth" );
  if( m_selectedMonth < 1 )
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
      });
    m_unpaidView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
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
      });
    m_pendingView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
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
      });
    m_paidView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        editClicked( m_paidView, _index );
      });

  } // endpaid items

  // disabled items
  if( m_toolBar-> showDisabled() )
  {
    auto u_ = std::make_unique< TableView >( m_selectedMonth, Status::Disabled );
    m_disabledView = u_.get();
    cw-> addWidget( std::move( u_ ) );
    m_disabledView->
      clicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        /*
        ** remember the clicked index
        */
        m_selectedIndex = _index;
      });
    m_disabledView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        editClicked( m_disabledView, _index );
      });

  } // enddisabled items

  /*
  ** This activates the summary widget and causes it to show
  **   or not show depending on the chosen option.
  */
  do_summaryClicked();

} // endbuildContent()-> void

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
  ** Get the 0-col index and use that to get the guid of this
  **  row, and use that to get the Edit dialog open on that
  **  guid.
  **
  */
  auto zcolIndex = _index.model()-> index( _index.row(), 0 );
  auto bpGuid = Wt::asString( zcolIndex.data( Wt::ItemDataRole::User ) ).toUTF8();
  openEditor( bpGuid );

} // endeditClicked( TableView * _table, Wt::WModelIndex _index )-> void

auto
GCW::Gui::BillPay::MainWidget::
buttonChanged( Wt::WRadioButton * _button )-> void
{
  /*
  ** If there is a button (sometimes there is not), then there's
  **  nothing to do.
  **
  ** This function can get called from a selection of one of the
  **  monthly buttons in the tool bar, or it can get called from a
  **  detailForm .save. event.  It shouldn't happen, but it's possible
  **  to add an item without having a month selected.  The button
  **  is going to get defaulted to 1, to help mitigate the issue, but
  **  it's still a problem if we pass a nullptr for the button.  So,
  **  to be safe, just deal with it.
  **
  */
  if( !_button )
    return;

  setMonth( std::stoi( _button-> text().toUTF8() ) );

} // endbuttonChanged( Wt::WRadioButton * _button )-> void

auto
GCW::Gui::BillPay::MainWidget::
do_disabledClicked()-> void
{
  buildContent();

} // enddisabledClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
do_summaryClicked()-> void
{
  if( m_toolBar-> showSummary() )
    m_summaryView-> setHidden( false );
  else
    m_summaryView-> setHidden( true );

  m_summaryView-> setMonth( m_selectedMonth );

} // enddisabledClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
setMonth( int _month )-> void
{
  m_selectedMonth = _month;

  if( m_unpaidView   ) m_unpaidView   -> setMonth( _month );
  if( m_pendingView  ) m_pendingView  -> setMonth( _month );
  if( m_paidView     ) m_paidView     -> setMonth( _month );
  if( m_disabledView ) m_disabledView -> setMonth( _month );
  if( m_summaryView  ) m_summaryView  -> setMonth( _month );

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


