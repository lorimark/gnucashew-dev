#line 2 "src/Gui/BillPay/PaymentWidget.cpp"

#include <Wt/WVBoxLayout.h>

#include "../../Eng/AccountComboModel.h"
#include "../../Glb/Core.h"
#include "BillPay.h"

GCW::Gui::BillPay::PaymentWidget::PaymentTable::
PaymentTable()
: Wt::WContainerWidget()
{
  m_table = addNew< Wt::WTable >();
  m_table-> setWidth( "100%" );
  int col = 0;
  m_table-> elementAt( 0, col++ )-> addNew< Wt::WText >( TR( "gcw.billPay.label.account" ) );
  m_table-> elementAt( 0, col++ )-> addNew< Wt::WText >( TR( "gcw.billPay.label.debit"   ) );
  m_table-> elementAt( 0, col++ )-> addNew< Wt::WText >( TR( "gcw.billPay.label.credit"  ) );

  for( int row=1; row< 3; row++ )
  {
    int col = 0;
    m_table-> elementAt( row, col++ )-> addNew< Wt::WLineEdit >( );
    m_table-> elementAt( row, col++ )-> addNew< Wt::WLineEdit >( );
    m_table-> elementAt( row, col++ )-> addNew< Wt::WLineEdit >( );

  }


} // endPaymentTable()

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
  **  handful of fields, then a tab widget with a couple
  **  pages.
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
//  m_pbSave     = templtMain-> bindNew< Wt::WPushButton >( "save"      , TR("gcw.billPay.label.save")   );
//  m_pbCancel   = templtMain-> bindNew< Wt::WPushButton >( "cancel"    , TR("gcw.billPay.label.cancel") );
  m_payTable   = templtMain-> bindNew< PaymentTable    >( "paymentTable"                               );
  m_trans      = templtMain-> bindNew< Wt::WLineEdit   >( "trans"                                      );
  m_date       = templtMain-> bindNew< Wt::WLineEdit   >( "date"                                       );
  m_memo       = templtMain-> bindNew< Wt::WLineEdit   >( "memo"                                       );
  m_confirm    = templtMain-> bindNew< Wt::WTextArea   >( "confirm"                                    );

//  m_pbSave    -> setStyleClass( "btn-xs" );
//  m_pbCancel  -> setStyleClass( "btn-xs" );

  m_trans     -> setToolTip( TR("gcw.billPay.toolTip.trans"       ) );
  m_date      -> setToolTip( TR("gcw.billPay.toolTip.date"        ) );
  m_memo      -> setToolTip( TR("gcw.billPay.toolTip.memo"        ) );
  m_confirm   -> setToolTip( TR("gcw.billPay.toolTip.confirm"     ) );

  templtMain-> bindString( "transLabel"    , TR("gcw.billPay.label.trans"    ) );
  templtMain-> bindString( "dateLabel"     , TR("gcw.billPay.label.date"     ) );
  templtMain-> bindString( "memoLabel"     , TR("gcw.billPay.label.memo"     ) );

//  m_pbSave   -> clicked().connect( [&](){ saveData();       });
//  m_pbCancel -> clicked().connect( [&](){ m_cancel.emit();  });

  /*
  ** get all the data loaded
  */
  loadData();

} // endEditWidget( const std::string & _accountGuid )

auto
GCW::Gui::BillPay::PaymentWidget::
loadData()-> void
{
  /*
  ** be safe
  */
  if( m_bpGuid == "" )
    return;

  /*
  ** Get the item that carries the bill-pay info
  */
  auto bpItem = GCW::Gui::BillPay::bpItem( m_bpGuid );

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



