#line 2 "src/Gui/Customer/MainWidget.cpp"

#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>

#include "../../define.h"
#include "../../GnuCashew.h"
#include "MainWidget.h"
#include "ToolBar.h"

GCW::Gui::Customer::MainWidget::
MainWidget()
{
  addStyleClass( "CustomerWidget" );

  /*
  ** Apply a layout so everything will fit in the window
  **
  */
  auto vlw = setLayout( std::make_unique< Wt::WVBoxLayout >() );
  vlw-> setSpacing( 0 );

  /*
  ** Install the tool bar
  **
  */
  auto tb_ = std::make_unique< ToolBar >();
  vlw-> addWidget( std::move( tb_ ) );

  auto hlw = vlw-> addLayout( std::make_unique< Wt::WHBoxLayout >(), 1 );

  {
    /*
    ** Standard TableView for now
    **
    */
    auto w_ = std::make_unique< Wt::WTableView >();
    m_view = w_.get();
    hlw-> addWidget( std::move( w_ ), 1 );
  }

  /*
  ** Setup standard control
  **
  */
  view()-> setSelectionBehavior    ( Wt::SelectionBehavior::Rows      );
  view()-> setSelectionMode        ( Wt::SelectionMode::Single        );
  view()-> setAlternatingRowColors ( true                             );
  view()-> doubleClicked().connect ( this, &MainWidget::doubleClicked );

  /*
  ** Prepare a column list
  **
  */
  std::vector< Wt::WFormModel::Field > fields =
  {
    Dbo::Customers::Field::id,
    Dbo::Customers::Field::name,
    Dbo::Customers::Field::addr_phone,
    Dbo::Customers::Field::addr_email
  };

  /*
  ** Create the model and apply it to the view
  **
  */
  m_model = std::make_shared< Eng::CustomersModel >( fields );
  model()-> sort( 0 );
  view()-> setModel( model() );

  auto tabWidget_ = std::make_unique< Wt::WTabWidget >();
  auto m_tabWidget = tabWidget_.get();
  hlw-> addWidget( std::move( tabWidget_ ), 1 );

  {
    auto w_ = std::make_unique< Invoices >();
    m_invoicesView = w_.get();
    m_tabWidget-> addTab( std::move( w_ ), "Invoices" );

    hlw-> setResizable( 0, true, "25%" );

    view()->
      clicked().connect( [&]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
      {
        m_invoicesView-> setCustomerGuid( m_model-> guid( _index.row() ) );

      });
  }

} // endMainWidget()

auto
GCW::Gui::Customer::MainWidget::
doubleClicked( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void
{
  /*
  ** get to the customerItem that was clicked on
  */
//  auto customerItem = model()-> resultRow( _index.row() );

  /*
  ** emit the guid of the item
  */
//  doubleClicked().emit( customerItem-> guid() );

} // enddoubleClicked( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void



