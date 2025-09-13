#line 2 "src/Gui/AccountRegister/ToolBar.cpp"

#include <Wt/WHBoxLayout.h>

#include "../App.h"
#include "ToolBar.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegister::ToolBar::
ToolBar()
{
  addStyleClass( "ToolBar" );

  auto lw = setLayout( std::make_unique< Wt::WHBoxLayout >() );

  lw-> setSpacing( 0 );

} // endToolBar()



