#line 2 "src/Gui/EmployeesWidget.cpp"

#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>

#include "../define.h"
#include "../GnuCashew.h"
#include "EmployeesWidget.h"

GCW::Gui::EmployeesWidget::
EmployeesWidget()
{
  addStyleClass( "EmployeesWidget" );

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
  view()-> doubleClicked().connect( this, &EmployeesWidget::doubleClicked );

  /*
  ** Prepare a column list
  **
  */
  std::vector< Wt::WFormModel::Field > fields =
  {
    GCW::Dbo::Employees::Field::id,
    GCW::Dbo::Employees::Field::username,
    GCW::Dbo::Employees::Field::addr_phone,
    GCW::Dbo::Employees::Field::addr_email
  };

  /*
  ** Create the model and apply it to the view
  **
  */
  m_model = std::make_shared< GCW::Eng::EmployeesModel >( fields );
  view()-> setModel( model() );

} // endGCW::Gui::EmployeesWidget::EmployeesWidget()

void GCW::Gui::EmployeesWidget::
doubleClicked( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )
{

} // endvoid GCW::Gui::CustomersWidget::doubleClicked( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )



