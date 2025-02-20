#line 2 "src/Gui/BillPay/MainWidget.cpp"

#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>

#include "BillPay.h"

GCW::Gui::BillPay::MainWidget::
MainWidget()
{
  buildContent();

} // endMainWidget()

auto
GCW::Gui::BillPay::MainWidget::
buildContent()-> void
{
  clear();

  // identify
  addStyleClass( "BillPay" );

  // layout
  m_hlw = setLayout( std::make_unique< Wt::WHBoxLayout >() );
  auto cw  = m_hlw-> addWidget( std::make_unique< Wt::WContainerWidget >() );
//  auto vlw = m_hlw-> addLayout( std::make_unique< Wt::WVBoxLayout      >() );

  // toolbar
  {
    auto u_ = std::make_unique< ToolBar >();
    m_toolBar = u_.get();
    cw-> addWidget( std::move( u_ ) );

    m_toolBar-> addClicked().connect( this, &GCW::Gui::BillPay::MainWidget::addClicked );
//    m_toolBar-> buttonGroup()-> checkedChanged().connect( this, &MainWidget::buttonChanged );
    m_toolBar-> disabledButton()-> clicked().connect( this, &MainWidget::disabledClicked );

    m_toolBar-> importClicked().connect( this, &MainWidget::importClicked );
    m_toolBar-> exportClicked().connect( this, &MainWidget::exportClicked );

  } // toolbar

  // recall
  m_selectedMonth = configItem()-> getVarInt( "selectedMonth" );
  if( m_selectedMonth < 1 )
      m_selectedMonth = 1;

//  Wt::WVBoxLayout      * lw2;
//  Wt::WContainerWidget * cw;
//  {
//    auto u_ = std::make_unique< Wt::WContainerWidget >();
//    cw = u_.get();
//    m_gridLayout-> addWidget( std::move( u_ ), 1, 0 );
//    m_gridLayout-> setRowStretch( 1, 1 );
//
//    lw2 = cw-> setLayout( std::make_unique< Wt::WVBoxLayout >() );
//    lw2-> setSpacing( 0 );
//  }

  // unpaid items
  {
    auto u_ = std::make_unique< Table >( m_selectedMonth, Status::Unpaid );
    m_unpaidView = u_.get();
    cw-> addWidget( std::move( u_ ) );
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
  }

  // paid items
  {
    auto u_ = std::make_unique< Table >( m_selectedMonth, Status::Paid );
    m_paidView = u_.get();
    cw-> addWidget( std::move( u_ ) );
    m_paidView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        editClicked( m_paidView, _index );
      });
  }

  // disabled items
  if( m_toolBar-> showDisabled() )
  {
    auto u_ = std::make_unique< Table >( m_selectedMonth, Status::Disabled );
    m_disabledView = u_.get();
    cw-> addWidget( std::move( u_ ) );
    m_disabledView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        editClicked( m_disabledView, _index );
      });

  }

  // fill-up remaining space
//  vlw-> addWidget( std::make_unique< Wt::WContainerWidget >(), 1 );

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

  /*
  ** This splits the page, and sets the first side to 25% width, and the second
  **  side to 75%.  The edit form occupies the 75% width side.  The split also
  **  has a slider, so if the user wants to temporarily slide the detail form
  **  out of the way, he can do that.
  **
  */
  m_hlw-> addWidget( std::move( u_ ) );
  m_hlw-> setResizable( 0, true, Wt::WLength(40,Wt::LengthUnit::Percentage) );

  m_editWidget->
    save().connect( [=]()
    {
      refreshViews();
      m_hlw-> removeWidget( m_editWidget.get() );
    });

  m_editWidget->
    cancel().connect( [=]()
    {
      refreshViews();
      m_hlw-> removeWidget( m_editWidget.get() );
    });

} // endopenEditor( const std::string & _nickname )-> void

auto
GCW::Gui::BillPay::MainWidget::
addClicked()-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  openEditor( "" );

} // endaddClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
editClicked( Table * _table, Wt::WModelIndex _index )-> void
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

} // endeditClicked( Table * _table, Wt::WModelIndex _index )-> void

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
disabledClicked()-> void
{
  buildContent();

} // enddisabledClicked()-> void

auto
GCW::Gui::BillPay::MainWidget::
setMonth( int _month )-> void
{
  if( m_unpaidView   ) m_unpaidView   -> setMonth( _month );
  if( m_paidView     ) m_paidView     -> setMonth( _month );
  if( m_disabledView ) m_disabledView -> setMonth( _month );

  m_selectedMonth = _month;

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


