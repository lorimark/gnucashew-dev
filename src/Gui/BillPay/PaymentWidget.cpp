#line 2 "src/Gui/BillPay/PaymentWidget.cpp"

#include <Wt/WVBoxLayout.h>

#include "../../Dbo/Transactions/Manager.h"
#include "../../Glb/Core.h"
#include "../AccountSuggestionEdit.h"
#include "BillPay.h"

GCW::Gui::BillPay::PaymentWidget::
PaymentWidget( const std::string & _bpGuid )
: Wt::WContainerWidget(),
  m_bpGuid( _bpGuid )
{
  addStyleClass( "PaymentWidget" );

  /*
  ** use a layout.
  */
  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );

  /*
  ** This is a complex widget, with a header area with a
  **  handful of fields, and some controls and whatnot.
  */
  auto templtMain =
    lw->
      addWidget( std::make_unique< Wt::WTemplate >( TR("gcw_gui.billpay.paymentwidget.form.main") ) );

  /*
  ** insert the table
  */
  m_table = templtMain-> bindNew< Wt::WTable >( "table" );
  m_table-> addStyleClass( "MakePaymentTable" );

  /*
  ** add the first row of widgets
  */
  m_date       = table()-> elementAt( 0, 0 )-> addNew< Wt::WDateEdit         >( );
  m_num        = table()-> elementAt( 0, 1 )-> addNew< Wt::WLineEdit         >( );
  m_desc       = table()-> elementAt( 0, 2 )-> addNew< Wt::WLineEdit         >( );
  auto acct    = table()-> elementAt( 0, 3 )-> addNew< AccountSuggestionEdit >( );
  m_recon      = table()-> elementAt( 0, 4 )-> addNew< Wt::WLineEdit         >( );
  m_debit      = table()-> elementAt( 0, 5 )-> addNew< Wt::WLineEdit         >( );
  m_credit     = table()-> elementAt( 0, 6 )-> addNew< Wt::WLineEdit         >( );

#ifdef INCLUDE_TABLE_WITH_MULTIPLE_INPUT_ROWS
  /*
  ** add the edit widget to the tableWidgets vector set
  */
  auto _addElement = [&]( size_t _row, size_t _col, const char * styleClass, Wt::WFormWidget * _element )
  {
    _element-> addStyleClass( styleClass );

    if( m_tableWidgets.size() <= _row )
        m_tableWidgets.resize( _row + 1 );

    if( m_tableWidgets[_row].size() <= _col )
        m_tableWidgets[_row].resize( _col + 1 );

    m_tableWidgets[_row][_col] = _element;
  };

  /*
  ** add a LineEdit to the table
  */
  auto _addLineEdit = [&]( size_t _row, size_t _col, const char * _styleClass )
  {
    auto element = table()-> elementAt( _row, _col )-> addNew< Wt::WLineEdit >();
    _addElement( _row, _col, _styleClass, element );
  };

  /*
  ** add the AccountSeggestionEdit to the table
  */
  auto _addAcctEdit = [&]( size_t _row, size_t _col, const char * _styleClass )
  {
    auto element = table()-> elementAt( _row, _col )-> addNew< AccountSuggestionEdit >();
    _addElement( _row, _col, _styleClass, element );
  };

  /*
  ** build the table
  */
  for( int row=1; row<= 3; row++ )
  {
    _addLineEdit( row, 1, "num"    );
    _addLineEdit( row, 2, "desc"   );
    _addAcctEdit( row, 3, "acct"   );
    _addLineEdit( row, 4, "recon"  );
    _addLineEdit( row, 5, "debit"  );
    _addLineEdit( row, 6, "credit" );
  }
#endif

  /*
  ** apply styling
  */
  m_date   -> addStyleClass      ( "date"        );
  m_num    -> addStyleClass      ( "num"         );
  m_desc   -> addStyleClass      ( "desc"        );
    acct   -> addStyleClass      ( "acct"        );
  m_recon  -> addStyleClass      ( "recon"       );
  m_debit  -> addStyleClass      ( "debit"       );
  m_credit -> addStyleClass      ( "credit"      );

  m_date   -> setPlaceholderText ( "Date"        );
  m_num    -> setPlaceholderText ( "Num"         );
  m_desc   -> setPlaceholderText ( "Description" );
  m_recon  -> setPlaceholderText ( "R"           );
  m_debit  -> setPlaceholderText ( "Debit"       );
  m_credit -> setPlaceholderText ( "Credit"      );

//  m_trans1    -> setToolTip( TR("gcw.billPay.toolTip.trans"       ) );
//  m_date1     -> setToolTip( TR("gcw.billPay.toolTip.date"        ) );
//  m_memo1     -> setToolTip( TR("gcw.billPay.toolTip.memo"        ) );
//  m_confirm   -> setToolTip( TR("gcw.billPay.toolTip.confirm"     ) );

  m_confirm = templtMain-> bindNew< Wt::WTextArea >( "confirm" );
  m_confirm-> setPlaceholderText( "Confirmation" );

  /*
  ** get all the data loaded
  */
  loadData();

} // endPaymentWidget( const std::string & _bpGuid )

auto
GCW::Gui::BillPay::PaymentWidget::
loadData()-> void
{
  /*
  ** be safe
  */
  if( m_bpGuid == "" )
    return;

  auto bpItem = GCW::Gui::BillPay::bpItem( bpGuid() );

  GCW::Dbo::Transactions::Manager transactionManager;

  m_date-> setValueText( GCW::Core::currentDateTimeDisplayString() );

} // endloadData()-> void

auto
GCW::Gui::BillPay::PaymentWidget::
saveData()-> void
{
  /*
  ** load the bpItem
  */
  auto bpItem = GCW::Gui::BillPay::bpItem( m_bpGuid );

  std::cout << __FILE__ << ":" << __LINE__
    << " " << bpItem.accountFullName()
    << " " << bpItem.nickname()
    << std::endl;

#ifdef NEVER
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  bpItem.set_accountGuid ( m_account   -> valueGuid() );
  bpItem.set_dueDay      ( m_dueDay    -> valueText() );
  bpItem.set_minimum     ( m_minimum   -> valueText() );
  bpItem.set_budget      ( m_budget    -> valueText() );
  bpItem.set_nickname    ( m_nickname  -> valueText() );
  bpItem.set_group       ( m_group     -> valueText() );
  bpItem.set_limit       ( m_limit     -> valueText() );
  bpItem.set_actual      ( m_actual    -> valueText() );
  bpItem.set_url         ( m_url       -> valueText() );
  bpItem.set_ap          ( m_ap        -> valueText() );
  bpItem.set_isActive    ( m_isActive  -> valueText() );
  bpItem.set_isVisible   ( m_isVisible -> valueText() );
  bpItem.set_autoPay     ( m_autoPay   -> valueText() );
  bpItem.set_payNow      ( m_payNow    -> valueText() );
  bpItem.set_last4       ( m_last4     -> valueText() );
  bpItem.set_note        ( m_note      -> valueText() );

  int i = 1;
  for( auto cb : m_cbx )
    bpItem.set_cb( i++, cb-> valueText() );

#endif

} // endsaveData()-> void

GCW::Gui::BillPay::PaymentWidgetDialog::
PaymentWidgetDialog( const std::string & _bpGuid )
{
  rejectWhenEscapePressed( true );
  setClosable( true );

  addStyleClass( "PaymentWidgetDialog" );
  setWindowTitle( TR( "gcw.billPay.dialog.title" ) );

  auto editWidget = contents()-> addNew< PaymentWidget >( _bpGuid );

  auto pbSave   = titleBar()-> addNew< Wt::WPushButton >( TR( "gcw.billPay.label.save"   ) );
  auto pbCancel = titleBar()-> addNew< Wt::WPushButton >( TR( "gcw.billPay.label.cancel" ) );

  pbSave   -> setStyleClass( "btn-xs" );
  pbCancel -> setStyleClass( "btn-xs" );

  pbSave   -> clicked().connect( [this,editWidget](){ editWidget-> saveData(); accept(); } );
  pbCancel -> clicked().connect( this, &Wt::WDialog::reject );

} // endPaymentWidgetDialog( const std::string & _bpGuid )



