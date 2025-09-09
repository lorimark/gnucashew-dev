#line 2 "src/Gui/AccountRegister/DelegateValue.cpp"

#include "Editor.h"
#include "DelegateValue.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegister::DelegateValue::
DelegateValue( Editor * _editor )
: DelegateBase( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegister::DelegateValue::
~DelegateValue()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegister::DelegateValue::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "(): " << _index.row() << "," << _index.column()
    << " ValueDelegate::" << __FUNCTION__
    << " '" << Wt::asString( _index.data( Wt::ItemDataRole::Edit ) ) << "'"
    << std::endl;
#endif

  auto retVal = DelegateBase::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );

  return retVal;

} // endcreateEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >



