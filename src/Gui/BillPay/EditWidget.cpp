#line 2 "src/Gui/BillPay/EditWidget.cpp"

#include <Wt/WMenuItem.h>
#include <Wt/WVBoxLayout.h>

#include "BillPay.h"

#define FN_DUEDAY    "dueDay"
#define FN_MINIMUM   "minimum"
#define FN_BUDGET    "budget"
#define FN_NICKNAME  "nickname"
#define FN_GROUP     "group"
#define FN_LIMIT     "limit"
#define FN_ACTUAL    "actual"
#define FN_AP        "ap"
#define FN_ISACTIVE  "isActive"
#define FN_ISVISIBLE "isVisible"
#define FN_AUTOPAY   "autoPay"
#define FN_PAYNOW    "payNow"
#define FN_LAST4     "last4"
#define FN_NOTE      "note"

namespace {

auto
toString( int _value )-> std::string
{
  std::string retVal = std::to_string( _value );

  if( retVal.length() == 1 )
    retVal = "0" + retVal;

  return retVal;

} // endtoString( int _value )-> std::string

} // endnamespace {

GCW::Gui::BillPay::EditWidget::ComboBox::
ComboBox()
{

  /*
  ** Populate the fullName of the account in to the combo box
  **  selection items.
  **
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  for( auto accountItem : GCW::Dbo::Accounts::allAccounts() )
  {
    /*
    ** Placehold accounts are not available here
    **
    */
    if( accountItem-> placeHolder() != 0 )
      continue;

    addItem( GCW::Dbo::Accounts::fullName( accountItem-> guid() ) );

  } // endfor( auto accountItem : GCW::Dbo::Accounts::allAccounts() )

} // endComboBox()


GCW::Gui::BillPay::EditWidget::
EditWidget( const std::string & _nickname )
: Wt::WContainerWidget(),
  m_nick( _nickname )
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
  m_key       = templtMain-> bindNew< ComboBox        >( "key"                                        );
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

  /*
  ** Once an account is assigned we can't change it.  This is
  **  somewhat of a technical reason due to the setup of this item.
  **  We don't want to start with one account on this billPay item
  **  and then switch it to a different account.
  ** (move to the load function)
  */
//  if( _nickname != "" )
//    m_key-> setDisabled( true );

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
//    auto tab = m_tabWidget-> addTab( std::make_unique< GCW::Gui::AccountRegister >( _accountGuid ), TR("gcw.billPay.tabName.history") );
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
  if( m_nick == "" )
    return;

  /*
  ** Get the item that carries the bill-pay info
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  auto bpItem = GCW::Gui::BillPay::bpItem( m_nick );

  /*
  ** format the 'name' to be something readable
  */
  auto fullName = GCW::Dbo::Accounts::fullName( bpItem-> getVarString( FN_NICKNAME ) );

  /*
  ** populate the form
  */
  m_key       -> setValueText( fullName );
  m_dueDay    -> setValueText( bpItem-> getVarString( FN_DUEDAY    ) );
  m_minimum   -> setValueText( bpItem-> getVarString( FN_MINIMUM   ) );
  m_budget    -> setValueText( bpItem-> getVarString( FN_BUDGET    ) );
  m_nickname  -> setValueText( bpItem-> getVarString( FN_NICKNAME  ) );
  m_group     -> setValueText( bpItem-> getVarString( FN_GROUP     ) );
  m_limit     -> setValueText( bpItem-> getVarString( FN_LIMIT     ) );
  m_actual    -> setValueText( bpItem-> getVarString( FN_ACTUAL    ) );
  m_ap        -> setValueText( bpItem-> getVarString( FN_AP        ) );
  m_isActive  -> setValueText( bpItem-> getVarString( FN_ISACTIVE  ) );
  m_isVisible -> setValueText( bpItem-> getVarString( FN_ISVISIBLE ) );
  m_autoPay   -> setValueText( bpItem-> getVarString( FN_AUTOPAY   ) );
  m_payNow    -> setValueText( bpItem-> getVarString( FN_PAYNOW    ) );
  m_last4     -> setValueText( bpItem-> getVarString( FN_LAST4     ) );
  m_note      -> setValueText( bpItem-> getVarString( FN_NOTE      ) );

  int i = 1;
  for( auto cb : m_cbx )
    cb-> setValueText( bpItem-> getVarString( "cb" + toString( i++ ) ) );

} // endloadData()-> void

auto
GCW::Gui::BillPay::EditWidget::
saveData()-> void
{
  GCW::Dbo::Accounts::Item::Ptr accountItem;

  auto nickname = m_nickname-> valueText().toUTF8();

#ifdef NEVER
  /*
  ** If the nickname is not set, then this is a '(new)'
  **  entry.  We have to generate a new item for storage
  **
  */
  if( m_nick == "" )
  {

  } // endif( m_nick == "" )

  /*
  ** We have an nick, so just fetch the account
  **
  */
  else
  {
    std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

    accountItem = GCW::Dbo::Accounts::byGuid( m_accountGuid );
  }

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );


  auto varItem = GCW::Gui::BillPay::bpItem( m_accountGuid );

  varItem.modify()-> setVar( FN_DUEDAY    , m_dueDay    -> valueText() );
  varItem.modify()-> setVar( FN_MINIMUM   , m_minimum   -> valueText() );
  varItem.modify()-> setVar( FN_BUDGET    , m_budget    -> valueText() );
  varItem.modify()-> setVar( FN_NICKNAME  , m_nickname  -> valueText() );
  varItem.modify()-> setVar( FN_GROUP     , m_group     -> valueText() );
  varItem.modify()-> setVar( FN_LIMIT     , m_limit     -> valueText() );
  varItem.modify()-> setVar( FN_ACTUAL    , m_actual    -> valueText() );
  varItem.modify()-> setVar( FN_AP        , m_ap        -> valueText() );
  varItem.modify()-> setVar( FN_ISACTIVE  , m_isActive  -> valueText() );
  varItem.modify()-> setVar( FN_ISVISIBLE , m_isVisible -> valueText() );
  varItem.modify()-> setVar( FN_AUTOPAY   , m_autoPay   -> valueText() );
  varItem.modify()-> setVar( FN_PAYNOW    , m_payNow    -> valueText() );
  varItem.modify()-> setVar( FN_LAST4     , m_last4     -> valueText() );
  varItem.modify()-> setVar( FN_NOTE      , m_note      -> valueText() );

  int i = 1;
  for( auto cb : m_cbx )
    varItem.modify()-> setVar( "cb" + toString( i++ ), cb-> valueText() );

#endif
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



