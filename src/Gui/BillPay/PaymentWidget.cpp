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
  **
  */
  auto templtMain =
    lw->
    addWidget
    (
     std::make_unique< Wt::WTemplate >( TR("gcw_gui.billpay.paymentwidget.form.main") )
    );

  /*
  ** add all the widgets
  **
  */
  m_table = templtMain-> bindNew< Wt::WTable >( "table" );
  m_table-> addStyleClass( "MakePaymentTable" );

  m_date       = table()-> elementAt( 0, 0 )-> addNew< Wt::WDateEdit >( );
  m_num        = table()-> elementAt( 0, 1 )-> addNew< Wt::WLineEdit >( );
  m_desc       = table()-> elementAt( 0, 2 )-> addNew< Wt::WLineEdit >( );
  auto acct    = table()-> elementAt( 0, 3 )-> addNew< Wt::WLineEdit >( );
  m_recon      = table()-> elementAt( 0, 4 )-> addNew< Wt::WLineEdit >( );
  m_debit      = table()-> elementAt( 0, 5 )-> addNew< Wt::WLineEdit >( );
  m_credit     = table()-> elementAt( 0, 6 )-> addNew< Wt::WLineEdit >( );

  table()-> elementAt( 1, 1 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "num"    );
  table()-> elementAt( 1, 2 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "desc"   );
  table()-> elementAt( 1, 3 )-> addNew< AccountSuggestionEdit >( )-> addStyleClass( "acct"   );
  table()-> elementAt( 1, 4 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "recon"  );
  table()-> elementAt( 1, 5 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "debit"  );
  table()-> elementAt( 1, 6 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "credit" );

  table()-> elementAt( 2, 1 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "num"    );
  table()-> elementAt( 2, 2 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "desc"   );
  table()-> elementAt( 2, 3 )-> addNew< AccountSuggestionEdit >( )-> addStyleClass( "acct"   );
  table()-> elementAt( 2, 4 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "recon"  );
  table()-> elementAt( 2, 5 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "debit"  );
  table()-> elementAt( 2, 6 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "credit" );

  table()-> elementAt( 3, 1 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "num"    );
  table()-> elementAt( 3, 2 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "desc"   );
  table()-> elementAt( 3, 3 )-> addNew< AccountSuggestionEdit >( )-> addStyleClass( "acct"   );
  table()-> elementAt( 3, 4 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "recon"  );
  table()-> elementAt( 3, 5 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "debit"  );
  table()-> elementAt( 3, 6 )-> addNew< Wt::WLineEdit         >( )-> addStyleClass( "credit" );

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

  std::cout << __FILE__ << ":" << __LINE__ << " bpItem:"  << bpItem.guid()        << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << " account:" << bpItem.accountGuid() << std::endl;

  GCW::Dbo::Transactions::Manager transactionManager;

  m_date-> setValueText( GCW::Core::currentDateTimeDisplayString() );

#ifdef NEVER
  /*
  ** format the 'name' to be something readable
  */
  auto fullName = bpItem.accountFullName();

  /*
  ** populate the form
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_account   -> setValueText( fullName            );
  m_dueDay    -> setValueText( bpItem.dueDay    () );
  m_minimum   -> setValueText( bpItem.minimum   () );
  m_budget    -> setValueText( bpItem.budget    () );
  m_nickname  -> setValueText( bpItem.nickname  () );
  m_group     -> setValueText( bpItem.group     () );
  m_limit     -> setValueText( bpItem.limit     () );
  m_actual    -> setValueText( bpItem.actual    () );
  m_url       -> setValueText( bpItem.url       () );
  m_ap        -> setValueText( bpItem.ap        () );
  m_isActive  -> setValueText( bpItem.isActive  () );
  m_isVisible -> setValueText( bpItem.isVisible () );
  m_autoPay   -> setValueText( bpItem.autoPay   () );
  m_payNow    -> setValueText( bpItem.payNow    () );
  m_last4     -> setValueText( bpItem.last4     () );
  m_note      -> setValueText( bpItem.note      () );

  /*
  ** If the account-name has been assigned, then don't allow it to
  **  be re-assigned.
  */
  if( fullName != "" )
    m_account-> setDisabled( true );


  int i = 1;
  for( auto cb : m_cbx )
    cb-> setValueText( bpItem.cb( i++ ) );

  m_register-> setAccountGuid( bpItem.accountGuid() );
#endif

} // endloadData()-> void

auto
GCW::Gui::BillPay::PaymentWidget::
saveData()-> void
{
  /*
  ** load the bpItem
  **
  */
  auto bpItem = GCW::Gui::BillPay::bpItem( m_bpGuid );

#ifdef NEVER
  /*
  ** save everything
  */
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

  auto pbSave   = titleBar()-> addNew< Wt::WPushButton >( TR("gcw.billPay.label.save")   );
  auto pbCancel = titleBar()-> addNew< Wt::WPushButton >( TR("gcw.billPay.label.cancel") );

  pbSave    -> setStyleClass( "btn-xs" );
  pbCancel  -> setStyleClass( "btn-xs" );

  pbSave   -> clicked().connect( [this,editWidget](){ editWidget-> saveData(); accept(); } );
  pbCancel -> clicked().connect( this, &Wt::WDialog::reject );

} // endPaymentWidgetDialog( const std::string & _bpGuid )



