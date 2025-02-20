#line 2 "src/Gui/CustomerReportWidget.cpp"

#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>

#include "../define.h"
#include "../GnuCashew.h"
#include "CustomerReportWidget.h"

GCW::Gui::CustomerReportWidget::
CustomerReportWidget( const std::string & _customerGuid )
: m_customerGuid( _customerGuid )
{
  addStyleClass( "CustomerReportWidget" );

  /*
  ** Apply a layout so everything will fit in the window
  **
  */
  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );
  lw-> setSpacing( 0 );

} // endGCW::Gui::CustomerReportWidget::CustomerReportWidget()



