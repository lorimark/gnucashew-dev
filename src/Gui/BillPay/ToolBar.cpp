#line 2 "src/Gui/BillPay/ToolBar.cpp"

#include <Wt/WHBoxLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

#include "BillPay.h"

GCW::Gui::BillPay::ToolBar::
ToolBar()
{
  addStyleClass( "ToolBar" );

  /*
  ** Always use a layout
  **
  */
  auto lw = setLayout( std::make_unique< Wt::WHBoxLayout >() );

  /*
  ** click to add
  **
  */
  auto pbAdd  = lw-> addWidget( std::make_unique< Wt::WPushButton >( "add"  ) );
       pbAdd-> clicked().connect( [=](){ m_addClicked.emit(); } );

  /*
  ** click to edit
  **
  */
  auto pbEdit = lw-> addWidget( std::make_unique< Wt::WPushButton >( "edit" ) );

  /*
  ** hide and show disabled items
  **
  */
  m_disabled = lw-> addWidget( std::make_unique< Wt::WCheckBox >( "disabled" ) );
  m_disabled-> setValueText( configItem()-> getVarString( "showDisabled" ) );
  m_disabled->
    clicked().connect( [&]( Wt::WMouseEvent _event )
    {
      auto item = configItem();
      Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
      item.modify()-> setVar( "showDisabled", m_disabled-> valueText() );
      item.flush();

    });

  /*
  ** hide and show the summary view
  **
  */
  m_summary = lw-> addWidget( std::make_unique< Wt::WCheckBox >( "summary" ), 1 );
  m_summary-> setValueText( configItem()-> getVarString( "showSummary" ) );
  m_summary->
    clicked().connect( [&]( Wt::WMouseEvent _event )
    {
      auto item = configItem();
      Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
      item.modify()-> setVar( "showSummary", m_summary-> valueText() );
      item.flush();

    });

} // endToolBar()

bool
GCW::Gui::BillPay::ToolBar::
showDisabled() const
{
  return disabledButton()-> checkState() == Wt::CheckState::Checked? true:false;
}

