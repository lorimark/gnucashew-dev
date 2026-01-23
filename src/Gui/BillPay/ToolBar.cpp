#line 2 "src/Gui/BillPay/ToolBar.cpp"

#include <Wt/WHBoxLayout.h>
#include <Wt/WTable.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>

#include "../../Glb/Core.h"
#include "BillPay.h"

GCW::Gui::BillPay::ToolBar::
ToolBar()
{
  addStyleClass( "ToolBar" );

  /*
  ** Always use a layout
  */
  auto lw = setLayout( std::make_unique< Wt::WHBoxLayout >() );
  auto table = lw-> addWidget( std::make_unique< Wt::WTable >() );
  table-> setAttributeValue( "style", "border-spacing:10px;border-collapse:separate;" );
  lw-> addWidget( std::make_unique< Wt::WContainerWidget >(), 1 );

  int col = 0;

  /*
  ** operating year selector
  */
  m_year = table-> elementAt( 0, col++ )-> addWidget( std::make_unique< YearSelector >() );

  /*
  ** finder input
  */
  m_finder = table-> elementAt( 0, col++ )-> addWidget( std::make_unique< Wt::WLineEdit >() );
  m_finder-> setPlaceholderText( TR("gcw.billPay.pht.finder") );

  /*
  ** click to add
  */
  m_add  = table-> elementAt( 0, col++ )-> addWidget( std::make_unique< Wt::WPushButton >( TR("gcw.billPay.lbl.add") ) );
  m_add-> setStyleClass( "btn-xs" );

  /*
  ** click to edit
  */
  m_edit = table-> elementAt( 0, col++ )-> addWidget( std::make_unique< Wt::WPushButton >( TR("gcw.billPay.lbl.edit") ) );
  m_edit-> setStyleClass( "btn-xs" );

  /*
  ** hide and show disabled items
  */
  m_inactive = table-> elementAt( 0, col++ )-> addWidget( std::make_unique< Wt::WCheckBox >( TR("gcw.billPay.lbl.inactive") ) );
  m_inactive-> setValueText( configItem()-> getVarString( "showInactive" ) );
  m_inactive->
    clicked().connect( [&]( Wt::WMouseEvent _event )
    {
      auto item = configItem();
      Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
      item.modify()-> setVar( "showInactive", m_inactive-> valueText() );
      item.flush();

    });

  /*
  ** hide and show the summary view
  */
  m_summary = table-> elementAt( 0, col++ )-> addWidget( std::make_unique< Wt::WCheckBox >( TR("gcw.billPay.lbl.summary") ) );
  m_summary-> setValueText( configItem()-> getVarString( "showSummary" ) );
  m_summary->
    clicked().connect( [&]( Wt::WMouseEvent _event )
    {
      auto item = configItem();
      Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
      item.modify()-> setVar( "showSummary", m_summary-> valueText() );
      item.flush();

    });

#ifdef BILL_PAY_IMPORT_EXPORT
  /*
  ** import export buttons
  */
  {
    auto pbImport = table-> elementAt( 0, col++ )-> addWidget( std::make_unique< Wt::WPushButton >( "import" ) );
    auto pbExport = table-> elementAt( 0, col++ )-> addWidget( std::make_unique< Wt::WPushButton >( "export" ) );

    pbImport-> setStyleClass( "btn-xs" );
    pbExport-> setStyleClass( "btn-xs" );

    pbImport-> clicked().connect( [=]{ m_importClicked.emit(); } );
    pbExport-> clicked().connect( [=]{ m_exportClicked.emit(); } );

  }
#endif

} // endToolBar()

auto
GCW::Gui::BillPay::ToolBar::
showInactive() const-> bool
{
  /*
  ** default false
  */
  bool retVal = false;

  if( inactiveButton() )
    retVal = inactiveButton()-> checkState() == Wt::CheckState::Checked? true:false;

  return retVal;

} // endshowInactive() const-> bool

auto
GCW::Gui::BillPay::ToolBar::
showSummary() const-> bool
{
  /*
  ** default false
  */
  bool retVal = false;

  if( summaryButton() )
    retVal = summaryButton()-> checkState() == Wt::CheckState::Checked? true:false;

  return retVal;

} // endshowSummary() const-> bool

auto
GCW::Gui::BillPay::ToolBar::
selectedYear() const-> int
{
  /*!
  ** default 0
  */
  int retVal = 0;

  if( yearSelector() )
    retVal = GCW::Core::stoi( yearSelector()-> valueText().toUTF8() );

  return retVal;

} // endselectedYear() const-> int

auto
GCW::Gui::BillPay::ToolBar::
finderText() const-> std::string
{
  /*
  ** default empty
  */
  std::string retVal;

  if( finderInput() )
    retVal = finderInput()-> valueText().toUTF8();

  return retVal;

} // endfinderText() const-> std::string


