#line 2 "src/Gui/BillPay/PaymentWidget.cpp"

#include <Wt/WVBoxLayout.h>

#include "../../Eng/TransactionManager.h"
#include "../../Glb/Core.h"
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
  m_date   = table()-> elementAt( 0, 0 )-> addNew< Wt::WDateEdit         >( );
  m_num    = table()-> elementAt( 0, 1 )-> addNew< Wt::WLineEdit         >( );
  m_desc   = table()-> elementAt( 0, 2 )-> addNew< Wt::WLineEdit         >( );
  m_acct   = table()-> elementAt( 0, 3 )-> addNew< AccountSuggestionEdit >( );
  m_recon  = table()-> elementAt( 0, 4 )-> addNew< Wt::WLineEdit         >( );
  m_debit  = table()-> elementAt( 0, 5 )-> addNew< Wt::WLineEdit         >( );
//  m_credit = table()-> elementAt( 0, 6 )-> addNew< Wt::WLineEdit         >( );

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
  m_date   -> addStyleClass( "date"   );
  m_num    -> addStyleClass( "num"    );
  m_desc   -> addStyleClass( "desc"   );
  m_acct   -> addStyleClass( "acct"   );
  m_recon  -> addStyleClass( "recon"  );
  m_debit  -> addStyleClass( "debit"  );
//  m_credit -> addStyleClass( "credit" );

  m_date   -> setPlaceholderText( TR("gcw.billPay.pht.date"  ) );
  m_num    -> setPlaceholderText( TR("gcw.billPay.pht.num"   ) );
  m_desc   -> setPlaceholderText( TR("gcw.billPay.pht.desc"  ) );
  m_acct   -> setPlaceholderText( TR("gcw.billPay.pht.acct"  ) );
  m_recon  -> setPlaceholderText( TR("gcw.billPay.pht.recon" ) );
  m_debit  -> setPlaceholderText( TR("gcw.billPay.pht.debit" ) );
//  m_credit -> setPlaceholderText( TR("gcw.billPay.pht.credit") );

//  m_trans1    -> setToolTip( TR("gcw.billPay.toolTip.trans"       ) );
//  m_date1     -> setToolTip( TR("gcw.billPay.toolTip.date"        ) );
//  m_memo1     -> setToolTip( TR("gcw.billPay.toolTip.memo"        ) );
//  m_confirm   -> setToolTip( TR("gcw.billPay.toolTip.confirm"     ) );

  m_confirm = templtMain-> bindNew< Wt::WTextArea >( "confirm" );
  m_confirm-> setPlaceholderText( TR("gcw.billPay.pht.confirm") );

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

  GCW::Eng::Transaction::Manager transactionManager;

  m_date  -> setValueText( GCW::Core::currentDateTimeDisplayString() );
  m_recon -> setValueText( "n" );
  m_num   -> setValueText( "bp" );
  m_desc  -> setValueText( bpItem.nickname() );

} // endloadData()-> void

auto
GCW::Gui::BillPay::PaymentWidget::
saveData()-> void
{
  /*
  ** make sure the account is assigned
  */
  if( m_acct-> valueText() == "" )
  {
    Wt::WMessageBox::show( TR("gcw.billPay.lbl.billPay"), TR("gcw.billPay.save.needaccount"), Wt::StandardButton::Ok );
    return;
  }

  /*
  ** load up some stuff so we can work
  */
  auto bpItem   = GCW::Gui::BillPay::bpItem( m_bpGuid );
  auto acctItem = GCW::Dbo::Accounts::byFullName( m_acct-> valueText() );

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " " << bpItem.accountFullName()
    << " " << bpItem.accountGuid()
    << " " << bpItem.nickname()
    << std::endl;

  std::cout << __FILE__ << ":" << __LINE__
    << " vt:" << m_acct-> valueText()
    << " id:" << acctItem-> guid()
    << " ds:" << acctItem-> description()
    << std::endl;
#endif

  /*
  ** now build up a new transaction
  **
  ** BUGBUG: note, this procedure will save 'confirm' which is the confirmation notes
  **          to the split item memo field.  This can cause gnucash to improperly display
  **          the value of that memo field if that value that was set there is multi-line.
  **          If the value is multi-line, it is able to store properly in the sql database,
  **          but the display in gnucash does not expand to show the multiple lines, instead
  **          it shows everything on one line with 'line-return' indicators in it.  It is
  **          editable, but I don't know the long-term impact of storing data like this
  **          that gnucash might have to deal with.
  */
  GCW::Eng::Transaction::Manager transMan;
  transMan.newTransaction( bpItem.accountGuid(), acctItem-> guid() );
  transMan.setDescription( m_desc-> valueText() );
  transMan.setDate       ( Wt::WDateTime::fromString( m_date-> valueText(), GCW_DATE_FORMAT_DISPLAY ) );
  transMan.setValue      ( acctItem-> guid()   ,  value() );
  transMan.setValue      ( bpItem.accountGuid(), -value() );
  transMan.setNotes      ( bpItem.accountGuid(), m_confirm-> valueText().toUTF8() );

} // endsaveData()-> void

GCW::Gui::BillPay::PaymentWidgetDialog::
PaymentWidgetDialog( const std::string & _bpGuid )
{
  rejectWhenEscapePressed( true );
  setClosable( true );

  addStyleClass( "PaymentWidgetDialog" );
  setWindowTitle( TR( "gcw.billPay.dialog.title" ) );

  auto editWidget = contents()-> addNew< PaymentWidget >( _bpGuid );

  auto pbSave   = titleBar()-> addNew< Wt::WPushButton >( TR( "gcw.billPay.lbl.save"   ) );
  auto pbCancel = titleBar()-> addNew< Wt::WPushButton >( TR( "gcw.billPay.lbl.cancel" ) );

  pbSave   -> setStyleClass( "btn-xs" );
  pbCancel -> setStyleClass( "btn-xs" );

  pbSave   -> clicked().connect( [this,editWidget](){ editWidget-> saveData(); accept(); } );
  pbCancel -> clicked().connect( this, &Wt::WDialog::reject );

} // endPaymentWidgetDialog( const std::string & _bpGuid )


auto
GCW::Gui::BillPay::PaymentWidget::
value()-> GCW_NUMERIC
{
  GCW_NUMERIC retVal(0);

  /*
  ** this adds the two values together using GAAP...
  **  the debit is 'added' and the credit is 'subtracted'
  **  from the value
  **
  */
  GCW_NUMERIC dVal( m_debit -> valueText().toUTF8() );
//  GCW_NUMERIC cVal( m_credit-> valueText().toUTF8() );

  retVal = dVal; // - cVal;

  return retVal;

} // endvalue()-> GCW_NUMERIC



