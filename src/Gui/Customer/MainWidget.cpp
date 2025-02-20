#line 2 "src/Gui/Customer/MainWidget.cpp"

#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>

#include "../../define.h"
#include "../../GnuCashew.h"
#include "MainWidget.h"

GCW::Gui::Customer::MainWidget::
MainWidget()
{
  addStyleClass( "CustomerWidget" );

  /*
  ** Apply a layout so everything will fit in the window
  **
  */
  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );
  lw-> setSpacing( 0 );

  /*
  ** Standard TableView for now
  **
  */
  auto w = std::make_unique< Wt::WTableView >();
  m_view = w.get();
  lw-> addWidget( std::move( w ), 1 );

  /*
  ** Setup standard control
  **
  */
  view()-> setSelectionBehavior( Wt::SelectionBehavior::Rows );
  view()-> setSelectionMode(     Wt::SelectionMode::Single   );
  view()-> setAlternatingRowColors( true );
  view()-> doubleClicked().connect( this, &MainWidget::doubleClicked );

  /*
  ** Prepare a column list
  **
  */
  std::vector< Wt::WFormModel::Field > fields =
  {
    GCW::Dbo::Customers::Field::id,
    GCW::Dbo::Customers::Field::name,
    GCW::Dbo::Customers::Field::addr_phone,
    GCW::Dbo::Customers::Field::addr_email
  };

  /*
  ** Create the model and apply it to the view
  **
  */
  m_model = std::make_shared< GCW::Eng::CustomersModel >( fields );
  model()-> sort( 0 );
  view()-> setModel( model() );

} // endGCW::Gui::CustomersWidget::CustomersWidget()

void GCW::Gui::Customer::MainWidget::
doubleClicked( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )
{
  /*
  ** get to the customerItem that was clicked on
  */
//  auto customerItem = model()-> resultRow( _index.row() );

  /*
  ** emit the guid of the item
  */
//  doubleClicked().emit( customerItem-> guid() );

} // endvoid GCW::Gui::CustomersWidget::doubleClicked( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )



