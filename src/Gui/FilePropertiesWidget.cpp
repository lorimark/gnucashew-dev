#line 2 "src/Gui/FilePropertiesWidget.cpp"

#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>

#include "../define.h"
#include "../GnuCashew.h"
#include "FilePropertiesWidget.h"

GCW::Gui::FilePropertiesWidget::
FilePropertiesWidget()
{
  addStyleClass( "FilePropertiesWidget" );

  /*
  ** Apply a layout so everything will fit in the window
  **
  */
  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );
  lw-> setSpacing( 0 );

  if( GCW::app()-> gnucashew_session().hasGnuCashewExtensions() )
  {
    lw-> addWidget( std::make_unique< Wt::WText >( "has gnucashew extensions" ) );
  }
  else
  {
    auto pb = lw-> addWidget( std::make_unique< Wt::WPushButton >( "apply gnucashew extensions" ) );

    pb-> clicked().connect( this, &FilePropertiesWidget::do_applyGnuCashewExtensions );
  }


} // endGCW::Gui::FilePropertisWidget::FilePropertiesWidget()


void
GCW::Gui::FilePropertiesWidget::
do_applyGnuCashewExtensions()
{
  GCW::app()-> gnucashew_session().addGnuCashewExtensions();

} // enddo_applyGnuCashewExtensions()

