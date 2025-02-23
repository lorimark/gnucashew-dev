#line 2 "src/Gui/Customer/Invoices.cpp"

#include <Wt/WHBoxLayout.h>

#include "Invoices.h"

GCW::Gui::Customer::Invoices::
Invoices()
{
  // identify
  addStyleClass( "Invoices" );

  // layout
  auto m_hlw = setLayout( std::make_unique< Wt::WHBoxLayout >() );

  m_tableView = m_hlw-> addWidget( std::make_unique< Wt::WTableView >(), 1 );

  m_model = std::make_shared< GCW::Eng::InvoicesModel >();

  m_tableView-> setModel( m_model );

  m_model-> setCustomerGuid( "x" );

  m_tableView->
    clicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
    {

    });

} // endInvoices()

auto
GCW::Gui::Customer::Invoices::
setCustomerGuid( const std::string & _guid )-> void
{
  m_model-> setCustomerGuid( _guid );

  std::cout << __FILE__ << ":" << __LINE__ << " " << m_model-> rowCount() << std::endl;

  m_tableView-> setModel( m_model );

} // endsetCustomerGuid( const std::string & _guid )-> void



