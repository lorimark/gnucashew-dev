#line 2 "src/Gui/BillPay/SummarytWidget.cpp"

#include <Wt/WMenuItem.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WMessageBox.h>

#include "../../Eng/AccountComboModel.h"
#include "../../Glb/Core.h"
#include "BillPay.h"

GCW::Gui::BillPay::SummaryWidget::
SummaryWidget()
: Wt::WContainerWidget()
{
  addStyleClass( "SummaryWidget" );

  m_text = addWidget( std::make_unique< Wt::WText >() );

} // endSummaryWidget( const std::string & _accountGuid )

auto
GCW::Gui::BillPay::SummaryWidget::
setMonth( int _month )-> void
{

  m_text-> setText( Wt::WString( "Month: {1}" ).arg( _month ) );

} // endloadData()-> void




