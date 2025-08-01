#line 2 "src/Gui/BillPay/ToolBar.cpp"

#include <Wt/WHBoxLayout.h>
#include <Wt/WTable.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

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

  /*
  ** click to add
  */
  auto pbAdd  = table-> elementAt( 0, 0 )-> addWidget( std::make_unique< Wt::WPushButton >( TR("gcw.billPay.lbl.add") ) );
  pbAdd-> setStyleClass( "btn-xs" );
  pbAdd-> clicked().connect( [=](){ m_addClicked.emit(); } );

  /*
  ** click to edit
  */
  auto pbEdit = table-> elementAt( 0, 1 )-> addWidget( std::make_unique< Wt::WPushButton >( TR("gcw.billPay.lbl.edit") ) );
  pbEdit-> setStyleClass( "btn-xs" );
  pbEdit-> clicked().connect( [=](){ m_editClicked.emit(); } );

  /*
  ** hide and show disabled items
  */
  m_inactive = table-> elementAt( 0, 2 )-> addWidget( std::make_unique< Wt::WCheckBox >( TR("gcw.billPay.lbl.inactive") ) );
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
  m_summary = table-> elementAt( 0, 3 )-> addWidget( std::make_unique< Wt::WCheckBox >( TR("gcw.billPay.lbl.summary") ) );
  m_summary-> setValueText( configItem()-> getVarString( "showSummary" ) );
  m_summary->
    clicked().connect( [&]( Wt::WMouseEvent _event )
    {
      auto item = configItem();
      Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
      item.modify()-> setVar( "showSummary", m_summary-> valueText() );
      item.flush();

    });

#ifdef NEVER
  /*
  ** import export buttons
  */
  {
    auto pbImport = table-> elementAt( 0, 4 )-> addWidget( std::make_unique< Wt::WPushButton >( "import" ) );
    auto pbExport = table-> elementAt( 0, 5 )-> addWidget( std::make_unique< Wt::WPushButton >( "export" ) );

    pbImport-> setStyleClass( "btn-xs" );
    pbExport-> setStyleClass( "btn-xs" );

    pbImport-> clicked().connect( [=]{ m_importClicked.emit(); } );
    pbExport-> clicked().connect( [=]{ m_exportClicked.emit(); } );

  }
#endif

} // endToolBar()

bool
GCW::Gui::BillPay::ToolBar::
showInactive() const
{
  return inactiveButton()-> checkState() == Wt::CheckState::Checked? true:false;
}

bool
GCW::Gui::BillPay::ToolBar::
showSummary() const
{
  return summaryButton()-> checkState() == Wt::CheckState::Checked? true:false;
}

