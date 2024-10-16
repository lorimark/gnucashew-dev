#line 2 "src/Gui/BillPay/EditWidget.cpp"

#include <Wt/WMenuItem.h>
#include <Wt/WVBoxLayout.h>

#include "../../Eng/AccountComboModel.h"
#include "../../Glb/Core.h"
#include "BillPay.h"

GCW::Gui::BillPay::EditWidget::ComboBox::
ComboBox()
{
  setModel( std::make_shared< GCW::Eng::AccountComboModel >() );
  setModelColumn( 1 );

} // endComboBox()

auto
GCW::Gui::BillPay::EditWidget::ComboBox::
valueGuid()-> std::string
{
  return
    Wt::asString( model()-> data( currentIndex(), 0 ) ).toUTF8() ;

} // endselectedGuid()-> std::string


GCW::Gui::BillPay::EditWidget::
EditWidget( const std::string & _bpGuid )
: Wt::WContainerWidget(),
  m_bpGuid( _bpGuid )
{
  addStyleClass( "BillPay_EditWidget" );

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
     std::make_unique< Wt::WTemplate >( TR("gcw_gui.billpay.editwidget.form.main") )
    );

  /*
  ** add all the widgets
  **
  */
  m_pbSave    = templtMain-> bindNew< Wt::WPushButton >( "save"      , TR("gcw.billPay.pb.save")      );
  m_pbCancel  = templtMain-> bindNew< Wt::WPushButton >( "cancel"    , TR("gcw.billPay.pb.cancel")    );
  m_pbDelete  = templtMain-> bindNew< Wt::WPushButton >( "delete"    , TR("gcw.billPay.pb.delete")    );
  m_account   = templtMain-> bindNew< ComboBox        >( "account"                                    );
  m_dueDay    = templtMain-> bindNew< Wt::WLineEdit   >( "dueDay"                                     );
  m_minimum   = templtMain-> bindNew< Wt::WLineEdit   >( "minimum"                                    );
  m_budget    = templtMain-> bindNew< Wt::WLineEdit   >( "budget"                                     );
  m_nickname  = templtMain-> bindNew< Wt::WLineEdit   >( "nickname"                                   );
  m_group     = templtMain-> bindNew< Wt::WLineEdit   >( "group"                                      );
  m_limit     = templtMain-> bindNew< Wt::WLineEdit   >( "limit"                                      );
  m_actual    = templtMain-> bindNew< Wt::WLineEdit   >( "actual"                                     );
  m_ap        = templtMain-> bindNew< Wt::WCheckBox   >( "ap"        , TR("gcw.billPay.pb.ap")        );
  m_isActive  = templtMain-> bindNew< Wt::WCheckBox   >( "isActive"  , TR("gcw.billPay.pb.isActive")  );
  m_isVisible = templtMain-> bindNew< Wt::WCheckBox   >( "isVisible" , TR("gcw.billPay.pb.isVisible") );
  m_autoPay   = templtMain-> bindNew< Wt::WCheckBox   >( "autoPay"   , TR("gcw.billPay.pb.autoPay")   );
  m_payNow    = templtMain-> bindNew< Wt::WCheckBox   >( "payNow"    , TR("gcw.billPay.pb.payNow")    );

  templtMain-> bindString( "accountLabel"  , TR("gcw.billPay.accountLabel"  ) );
  templtMain-> bindString( "dueDayLabel"   , TR("gcw.billPay.dueDayLabel"   ) );
  templtMain-> bindString( "minimumLabel"  , TR("gcw.billPay.minimumLabel"  ) );
  templtMain-> bindString( "budgetLabel"   , TR("gcw.billPay.budgetLabel"   ) );
  templtMain-> bindString( "nicknameLabel" , TR("gcw.billPay.nicknameLabel" ) );
  templtMain-> bindString( "groupLabel"    , TR("gcw.billPay.groupLabel"    ) );
  templtMain-> bindString( "limitLabel"    , TR("gcw.billPay.limitLabel"    ) );
  templtMain-> bindString( "actualLabel"   , TR("gcw.billPay.actualLabel"   ) );

  /*
  ** this is the tab widget.  It takes up the remaining bottom space
  **  on the form.
  */
  m_tabWidget = lw-> addWidget( std::make_unique< Wt::WTabWidget >(), 1 );

  /*
  ** This is the payment template.  It will get added to
  **  the first page of the tab widget.
  **
  */
  Wt::WTemplate * templtPayment;
  {
    auto u_ = std::make_unique< Wt::WTemplate >( TR( "gcw_gui.billpayeditor.form.tab1" ) );
    templtPayment = u_.get();
    m_tabWidget-> addTab( std::move( u_ ), TR("gcw.billPay.tabName.payment")  );

    for( int cb = 0; cb < 12; cb++ )
      m_cbx.push_back( templtPayment-> bindNew< Wt::WCheckBox >( "cb" + toString( cb+1 ), toString( cb+1 ) ) );

    auto pbgo = templtPayment-> bindNew< Wt::WPushButton >( "go", TR("gcw.billPay.pb.go") );
//    pbgo-> setStyleClass( "btn-xs" );

    m_url   = templtPayment-> bindNew< Wt::WLineEdit >( "url"            );
    m_last4 = templtPayment-> bindNew< Wt::WLineEdit >( "last4"          );
    m_note  = templtPayment-> bindNew< Wt::WTextArea >( "note"           );
    m_label = templtPayment-> bindNew< Wt::WLabel    >( "image", "image" );
    m_label-> setMinimumSize( "160px", "160px" );
    m_label-> resize( "160px", "160px" );

    auto pbClear = templtPayment-> bindNew< Wt::WPushButton >( "clear", TR("gcw.billPay.pb.clear") );
    pbClear-> setToolTip( TR("gcw.billPay.pb.clear.toolTip") );
    pbClear->
      clicked().connect( [&]()
      {
        for( auto cb : m_cbx )
          cb-> setValueText( "no" );
      });

  } // endWt::WTemplate * templtPayment;

  /*
  ** This is the history widget.  It contains
  **  a registry table for this widget.  It gets added to
  **  the second page of the tab widget.
  **
  */
  Wt::WTemplate * templtHistory;
  {
    /*
    ** This does a better job of honoring the layout, but we still have
    **  to set the widget height.
    **
    */
    auto w_ = std::make_unique< GCW::Gui::AccountRegister >();
    m_register = w_.get();
    auto tab = m_tabWidget-> addTab( std::move( w_ ), TR("gcw.billPay.tabName.history") );
//    tab-> contents()-> setMaximumSize( Wt::WLength::Auto, "300px" );

  } // endWt::WTemplate * templtHistory;

  m_pbSave  -> clicked().connect( [&](){ saveData();      });
  m_pbCancel-> clicked().connect( [&](){ m_cancel.emit(); });
  m_pbDelete-> clicked().connect( [&](){ m_delete.emit(); });

  /*
  ** get all the data loaded
  */
  loadData();

} // endEditWidget( const std::string & _accountGuid )

auto
GCW::Gui::BillPay::EditWidget::
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

  /*
  ** format the 'name' to be something readable
  */
  auto fullName = GCW::Dbo::Accounts::fullName( bpItem.accountGuid() );

  /*
  ** populate the form
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  m_account   -> setValueText( fullName );
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

  int i = 1;
  for( auto cb : m_cbx )
    cb-> setValueText( bpItem.cb( i++ ) );

} // endloadData()-> void

auto
GCW::Gui::BillPay::EditWidget::
saveData()-> void
{
  /*
  ** little bit of housekeeping before we begin
  */
  if( m_bpGuid == "" )
      m_bpGuid = GCW::Core::newGuid();

  /*
  ** load the bpItem, if we had to create a new guid above,
  **  then we'll end up with a 'new' bpItem.
  **
  */
  auto bpItem = GCW::Gui::BillPay::bpItem( m_bpGuid );

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

  m_save.emit();

} // endsaveData()-> void


GCW::Gui::BillPay::EditWidgetDialog::
EditWidgetDialog( const std::string & _accountGuid )
{
  addStyleClass( "EditWidgetDialog" );
  setWindowTitle( "Bill Pay Account" );

  setClosable( true );
  rejectWhenEscapePressed( true );

  auto editWidget = contents()-> addNew< EditWidget >( _accountGuid );

  editWidget-> save   ().connect( [&](){ accept(); });
  editWidget-> cancel ().connect( [&](){ reject(); });

} // endEditWidgetDialog( const std::string & _accountGuid )



