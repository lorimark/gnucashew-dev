#line 2 "src/Gui/BillPay/MainWidget.cpp"

//#define EDIT_FORM_AS_POPUP_DIALOG
#define EDIT_FORM_AS_SPLIT_PAGE

#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>

#include "BillPay.h"

GCW::Gui::BillPay::MainWidget::
MainWidget()
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

  buildContent();

  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endMainWidget()

void
GCW::Gui::BillPay::MainWidget::
buildContent()
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  clear();

  addStyleClass( "MainWidget" );

  m_gridLayout = setLayout( std::make_unique< Wt::WGridLayout >() );

  // toolbar
  {
    auto u_ = std::make_unique< ToolBar >();
    m_toolBar = u_.get();
    m_gridLayout-> addWidget( std::move( u_ ), 0, 0 );

    m_toolBar-> addClicked().connect( this, &GCW::Gui::BillPay::MainWidget::addClicked );
//    m_toolBar-> buttonGroup()-> checkedChanged().connect( this, &MainWidget::buttonChanged );
    m_toolBar-> disabledButton()-> clicked().connect( this, &MainWidget::disabledClicked );

  } // toolbar

  /*
  ** recall
  **
  */
  m_selectedMonth = configItem()-> getVarInt( "selectedMonth" );
  if( m_selectedMonth < 1 )
      m_selectedMonth = 1;

  Wt::WVBoxLayout      * lw2;
  Wt::WContainerWidget * cw;
  {
    auto u_ = std::make_unique< Wt::WContainerWidget >();
    cw = u_.get();
    m_gridLayout-> addWidget( std::move( u_ ), 1, 0 );
    m_gridLayout-> setRowStretch( 1, 1 );

    lw2 = cw-> setLayout( std::make_unique< Wt::WVBoxLayout >() );
    lw2-> setSpacing( 0 );
  }

  // unpaid items
  {
    auto u_ = std::make_unique< Table >( m_selectedMonth, Status::Unpaid );
    m_unpaidView = u_.get();
    lw2-> addWidget( std::move( u_ ) );
    m_unpaidView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        editClicked( m_unpaidView, _index );
      });

    /*
    ** clicking on the header changes the selected month
    */
    m_unpaidView->
      headerClicked().connect( this, &MainWidget::on_headerClicked );
  }

  // paid items
  {
    auto u_ = std::make_unique< Table >( m_selectedMonth, Status::Paid );
    m_paidView = u_.get();
    lw2-> addWidget( std::move( u_ ), m_toolBar-> showDisabled()? 0:1 );
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
    lw2-> addWidget( std::move( u_ ), 1 );
    m_disabledView->
      doubleClicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        editClicked( m_disabledView, _index );
      });
  }

} // endbuildContent()

void
GCW::Gui::BillPay::MainWidget::
openEditor( const std::string & _accountGuid )
{

#ifdef EDIT_FORM_AS_POPUP_DIALOG

  std::cout << __FILE__ << ":" << __LINE__ << " opening popup" << std::endl;

  /*
  ** Add a dialog to open/edit this item
  **
  */
  m_dialog = std::make_unique< GCW::Gui::BillPay::EditWidgetDialog >( _accountGuid );
  m_dialog-> show();
  m_dialog->
    finished().connect( [&]()
    {
      refreshViews();
      m_dialog.release();
    });

#endif

#ifdef EDIT_FORM_AS_SPLIT_PAGE

  std::cout << __FILE__ << ":" << __LINE__ << " opening split" << std::endl;

  /*
  **
  **
  */
  if( m_editWidget )
  {
//    m_gridLayout-> removeWidget( m_editWidget );
//    m_editWidget = nullptr;
    return;
  }

  /*
  ** Split the page to open/edit this item
  **
  */
  auto u_ = std::make_unique< GCW::Gui::BillPay::EditWidget >( _accountGuid );
  m_editWidget = u_.get();
  m_gridLayout-> addWidget( std::move( u_), 1, 1 );
  m_gridLayout-> setColumnResizable( 0, true, "30%" );

  m_editWidget->
    save().connect( [=]()
    {
      refreshViews();
      m_gridLayout-> removeWidget( m_editWidget );
      m_editWidget = nullptr;
    });

  m_editWidget->
    cancel().connect( [=]()
    {
      refreshViews();
      m_gridLayout-> removeWidget( m_editWidget );
      m_editWidget = nullptr;
    });
#endif

} // endopenEditor( const std::string & _accountGuid )


void
GCW::Gui::BillPay::MainWidget::
addClicked()
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  openEditor( "" );

} // endaddClicked()

void
GCW::Gui::BillPay::MainWidget::
editClicked( Table * _table, Wt::WModelIndex _index )
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  /*
  ** Get the 0-col index and use that to get the guid of this
  **  row, and use that to get the Edit dialog open on that
  **  guid.
  **
  */
  auto zcolIndex = _index.model()-> index( _index.row(), 0 );
  auto accountGuid = Wt::asString( _table-> model()-> itemFromIndex( zcolIndex )-> data() ).toUTF8();
  openEditor( accountGuid );

} // endeditClicked( Wt::WModelIndex _index, Wt::WMouseEvent _event )

void
GCW::Gui::BillPay::MainWidget::
buttonChanged( Wt::WRadioButton * _button )
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

} // endbuttonChanged( Wt::WRadioButton * _button )

void
GCW::Gui::BillPay::MainWidget::
disabledClicked()
{
  buildContent();
}

void
GCW::Gui::BillPay::MainWidget::
setMonth( int _month )
{
  if( m_paidView     ) m_paidView     -> setMonth( _month );
  if( m_unpaidView   ) m_unpaidView   -> setMonth( _month );
  if( m_disabledView ) m_disabledView -> setMonth( _month );

  m_selectedMonth = _month;

  configItem().modify()-> setVar( "selectedMonth", m_selectedMonth );

} // endsetMonth( int _month )

void
GCW::Gui::BillPay::MainWidget::
refreshViews()
{
  setMonth( m_selectedMonth );
}

void
GCW::Gui::BillPay::MainWidget::
on_headerClicked( int _col, const Wt::WMouseEvent _me )
{
  if( _col >= 9 )
    setMonth( _col - 8 );

} // endon_headerClicked( int _col, const Wt::WMouseEvent _me )


