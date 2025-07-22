#line 2 "src/Gui/BillPay/EditWidget.cpp"

#include <Wt/WMenuItem.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WMessageBox.h>

#include "../../Eng/AccountComboModel.h"
#include "../../Glb/Core.h"
#include "BillPay.h"

GCW::Gui::BillPay::EditWidget::
EditWidget( const std::string & _bpGuid )
: Wt::WContainerWidget(),
  m_bpGuid( _bpGuid )
{
  addStyleClass( "EditWidget" );

  /*
  ** use a layout.
  */
  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );

  /*
  ** This is a complex widget, with a header area with a
  **  handful of fields, then a tab widget with a couple
  **  pages.
  */
  auto templtMain =
    lw->
    addWidget
    (
     std::make_unique< Wt::WTemplate >( TR("gcw_gui.billpay.editwidget.form.main") )
    );

  /*
  ** add all the widgets
  */
  m_pbSave    = templtMain-> bindNew< Wt::WPushButton           >( "save"      , TR("gcw.billPay.lbl.save")      );
  m_pbCancel  = templtMain-> bindNew< Wt::WPushButton           >( "cancel"    , TR("gcw.billPay.lbl.cancel")    );
  m_pbDelete  = templtMain-> bindNew< Wt::WPushButton           >( "delete"    , TR("gcw.billPay.lbl.delete")    );
  m_pbProcess = templtMain-> bindNew< Wt::WPushButton           >( "process"   , TR("gcw.billPay.lbl.process")   );
  m_account   = templtMain-> bindNew< GCW::Gui::AccountComboBox >( "account"                                     );
  m_dueDay    = templtMain-> bindNew< Wt::WSpinBox              >( "dueDay"                                      );
  m_minimum   = templtMain-> bindNew< Wt::WLineEdit             >( "minimum"                                     );
  m_budget    = templtMain-> bindNew< Wt::WLineEdit             >( "budget"                                      );
  m_nickname  = templtMain-> bindNew< Wt::WLineEdit             >( "nickname"                                    );
  m_group     = templtMain-> bindNew< Wt::WSpinBox              >( "group"                                       );
  m_limit     = templtMain-> bindNew< Wt::WLineEdit             >( "limit"                                       );
  m_actual    = templtMain-> bindNew< Wt::WLineEdit             >( "actual"                                      );
  m_ap        = templtMain-> bindNew< Wt::WCheckBox             >( "ap"        , TR("gcw.billPay.lbl.ap")        );
  m_isActive  = templtMain-> bindNew< Wt::WCheckBox             >( "isActive"  , TR("gcw.billPay.lbl.isActive")  );
  m_isVisible = templtMain-> bindNew< Wt::WCheckBox             >( "isVisible" , TR("gcw.billPay.lbl.isVisible") );
  m_autoPay   = templtMain-> bindNew< Wt::WCheckBox             >( "autoPay"   , TR("gcw.billPay.lbl.autoPay")   );
  m_payNow    = templtMain-> bindNew< Wt::WCheckBox             >( "payNow"    , TR("gcw.billPay.lbl.payNow")    );

  m_pbSave    -> setStyleClass( "btn-xs" );
  m_pbCancel  -> setStyleClass( "btn-xs" );
  m_pbDelete  -> setStyleClass( "btn-xs" );
  m_pbProcess -> setStyleClass( "btn-xs" );

  m_account   -> setToolTip( TR("gcw.billPay.ttp.account"     ) );
  m_dueDay    -> setToolTip( TR("gcw.billPay.ttp.dueDay"      ) );
  m_minimum   -> setToolTip( TR("gcw.billPay.ttp.minimum"     ) );
  m_budget    -> setToolTip( TR("gcw.billPay.ttp.budget"      ) );
  m_nickname  -> setToolTip( TR("gcw.billPay.ttp.nickname"    ) );
  m_group     -> setToolTip( TR("gcw.billPay.ttp.group"       ) );
  m_limit     -> setToolTip( TR("gcw.billPay.ttp.limit"       ) );
  m_actual    -> setToolTip( TR("gcw.billPay.ttp.actual"      ) );
  m_ap        -> setToolTip( TR("gcw.billPay.ttp.ap"          ) );
  m_isActive  -> setToolTip( TR("gcw.billPay.ttp.isActive"    ) );
  m_isVisible -> setToolTip( TR("gcw.billPay.ttp.isVisible"   ) );
  m_autoPay   -> setToolTip( TR("gcw.billPay.ttp.autoPay"     ) );
  m_payNow    -> setToolTip( TR("gcw.billPay.ttp.payNow"      ) );

  m_dueDay -> setRange( 1, 31 );
  m_group  -> setRange( 0, 30 );
  m_group  -> setSingleStep( 5 );

  templtMain-> bindString( "accountLabel"  , TR("gcw.billPay.lbl.account"  ) );
  templtMain-> bindString( "dueDayLabel"   , TR("gcw.billPay.lbl.dueDay"   ) );
  templtMain-> bindString( "minimumLabel"  , TR("gcw.billPay.lbl.minimum"  ) );
  templtMain-> bindString( "budgetLabel"   , TR("gcw.billPay.lbl.budget"   ) );
  templtMain-> bindString( "nicknameLabel" , TR("gcw.billPay.lbl.nickname" ) );
  templtMain-> bindString( "groupLabel"    , TR("gcw.billPay.lbl.group"    ) );
  templtMain-> bindString( "limitLabel"    , TR("gcw.billPay.lbl.limit"    ) );
  templtMain-> bindString( "actualLabel"   , TR("gcw.billPay.lbl.actual"   ) );

  /*
  ** this is the tab widget.  It takes up the remaining bottom space
  **  on the form.
  */
  m_tabWidget = lw-> addWidget( std::make_unique< Wt::WTabWidget >(), 1 );

  /*
  ** This is the payment template.  It will get added to
  **  the first page of the tab widget.
  */
  Wt::WTemplate * templtPayment;
  {
    auto u_ = std::make_unique< Wt::WTemplate >( TR( "gcw_gui.billpayeditor.form.tab1" ) );
    templtPayment = u_.get();
    m_tabWidget-> addTab( std::move( u_ ), TR("gcw.billPay.tabName.payment")  );

    for( int cb = 0; cb < 12; cb++ )
    {
      auto cbx = std::make_unique< Wt::WCheckBox >( toString( cb+1 ) );
      cbx-> setTristate( true );
      cbx-> setPartialStateSelectable( true );

      m_cbx.push_back( cbx.get() );

      templtPayment-> bindWidget( "cb" + toString( cb+1 ), std::move( cbx ) );
    }

    auto pbgo = templtPayment-> bindNew< Wt::WPushButton >( "go", TR("gcw.billPay.lbl.go") );
    pbgo-> setStyleClass( "btn-xs" );

    m_url   = templtPayment-> bindNew< Wt::WLineEdit >( "url"            );
    m_last4 = templtPayment-> bindNew< Wt::WLineEdit >( "last4"          );
    m_note  = templtPayment-> bindNew< Wt::WTextArea >( "note"           );
//    m_note  = templtPayment-> bindNew< Wt::WTextEdit >( "note"           );
    m_label = templtPayment-> bindNew< Wt::WLabel    >( "image", "image" );
    m_label-> setMinimumSize( "160px", "160px" );
    m_label-> resize( "160px", "160px" );

    m_note-> setRows( 10 );
//    m_note-> resize( Wt::WLength::Auto, Wt::WLength( 200 ) );

    auto pbClear = templtPayment-> bindNew< Wt::WPushButton >( "clear", TR("gcw.billPay.lbl.clear") );
    pbClear-> setStyleClass( "btn-xs" );
    pbClear-> setToolTip( TR("gcw.billPay.ttp.clear") );
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
    m_register-> setReadOnly( true );
    auto tab = m_tabWidget-> addTab( std::move( w_ ), TR("gcw.billPay.tabName.history") );
//    tab-> contents()-> setMaximumSize( Wt::WLength::Auto, "300px" );

  } // endWt::WTemplate * templtHistory;

  m_pbSave    -> clicked().connect( [&](){ saveData();        });
  m_pbCancel  -> clicked().connect( [&](){ m_canceled.emit(); });
  m_pbDelete  -> clicked().connect( [&](){ m_deleted.emit();  });
  m_pbProcess -> clicked().connect( [&](){ processPayment();  });

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
  ** beware of safety
  */
  if( m_bpGuid == "" )
    return;

  m_pbProcess -> setDisabled( false );
  m_pbDelete  -> setDisabled( false );

  /*
  ** Get the item that carries the bill-pay info
  */
  auto bpItem = GCW::Gui::BillPay::bpItem( m_bpGuid );

  /*
  ** format the 'name' to be something readable
  */
  auto fullName = GCW::Dbo::Accounts::fullName( bpItem.accountGuid() );

  /*
  ** If the account-name has been assigned, then don't allow it to
  **  be re-assigned.
  */
  if( fullName != "" )
    m_account -> setDisabled( true );

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

  int i = 1;
  for( auto cb : m_cbx )
    cb-> setValueText( bpItem.cb( i++ ) );

  m_register -> setAccountGuid( bpItem.accountGuid() );

} // endloadData()-> void

auto
GCW::Gui::BillPay::EditWidget::
accountIsDuplicated()-> bool
{
  auto accountGuid = m_account-> valueGuid();

  auto items = GCW::Dbo::Vars::getByCfy( GCW_GUI_BILLPAY_ITEM_CFY );

  for( auto & itm : items )
  {
    Item item(itm);

    /*
    ** if the account is the same but the bpItem is different
    **  then this must be a duplicate.  The accountGuid and
    **  bpItemGuid must match in order for this to not be a
    **  duplicate.  When they match, it means we're saving
    **  the same (correct) bp item.
    */
    if( item.accountGuid() == accountGuid
     && item.guid()        != m_bpGuid
      )
      return true;
  }

  return false;

} // endduplicateAccount()-> bool

auto
GCW::Gui::BillPay::EditWidget::
saveData()-> void
{
  /*
  ** This needs to be set before we can save
  */
  if( m_account-> valueText() == "" )
  {
    Wt::WMessageBox::show( TR("gcw.billPay.lbl.billPay"), TR("gcw.billPay.save.needaccount"), Wt::StandardButton::Ok );
    return;
  }

#ifdef DUPLICATES_ARE_ALLOWED_SINCE_INTERNET_EXPENSES_ARE_PAID_TO_FRONTIER_AND_HOSTGATOR_AND_SO_ON_SO_THERE_CAN_BE_MULTIPLE_INTERNET_BILLS
  /*
  ** If the account is already in a bill-pay, then disallow
  **  another duplicate
  */
  if( accountIsDuplicated() )
  {
    Wt::WMessageBox::show( TR("gcw.billPay.lbl.billPay"), TR("gcw.billPay.save.duplicate"), Wt::StandardButton::Ok );
    return;
  }
#endif

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
  Wt::Dbo::Transaction t ( GCW::app()  -> gnucashew_session() );
  bpItem.set_accountGuid ( m_account   -> valueGuid()         );
  bpItem.set_dueDay      ( m_dueDay    -> valueText()         );
  bpItem.set_minimum     ( m_minimum   -> valueText()         );
  bpItem.set_budget      ( m_budget    -> valueText()         );
  bpItem.set_nickname    ( m_nickname  -> valueText()         );
  bpItem.set_group       ( m_group     -> valueText()         );
  bpItem.set_limit       ( m_limit     -> valueText()         );
  bpItem.set_actual      ( m_actual    -> valueText()         );
  bpItem.set_url         ( m_url       -> valueText()         );
  bpItem.set_ap          ( m_ap        -> valueText()         );
  bpItem.set_isActive    ( m_isActive  -> valueText()         );
  bpItem.set_isVisible   ( m_isVisible -> valueText()         );
  bpItem.set_autoPay     ( m_autoPay   -> valueText()         );
  bpItem.set_payNow      ( m_payNow    -> valueText()         );
  bpItem.set_last4       ( m_last4     -> valueText()         );
  bpItem.set_note        ( m_note      -> valueText()         );

  int i = 1;
  for( auto cb : m_cbx )
    bpItem.set_cb( i++, cb-> valueText() );

  m_saved.emit();

} // endsaveData()-> void



static std::unique_ptr< GCW::Gui::BillPay::PaymentWidgetDialog > dialog;
auto
GCW::Gui::BillPay::EditWidget::
processPayment()-> void
{
  dialog = std::make_unique< GCW::Gui::BillPay::PaymentWidgetDialog >( m_bpGuid );
  dialog-> show();
  dialog->
    finished().connect( []()
    {
      dialog.reset( nullptr );
    });

} // endprocessPayment()-> void



GCW::Gui::BillPay::EditWidgetDialog::
EditWidgetDialog( const std::string & _bpGuid )
{
  addStyleClass( "EditWidgetDialog" );
  setWindowTitle( "Bill Pay Account" );

  setClosable( true );
  rejectWhenEscapePressed( true );

  auto editWidget = contents()-> addNew< EditWidget >( _bpGuid );

  editWidget-> saved    ().connect( [&](){ accept(); });
  editWidget-> canceled ().connect( [&](){ reject(); });

} // endEditWidgetDialog( const std::string & _accountGuid )


