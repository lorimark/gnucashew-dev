#line 2 "src/Gui/AccountRegister/DelegateHeader.cpp"

#include <Wt/WDateEdit.h>

#include "DelegateHeader.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegister::DelegateHeader::
DelegateHeader( Editor * _editor )
: DelegateBase( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegister::DelegateHeader::
~DelegateHeader()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegister::DelegateHeader::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " HeaderDelegate::" << __FUNCTION__
    << " ("   << _index.row() << "," << _index.column() << ")"
    << std::endl;
#endif

  auto retVal = std::make_unique< Wt::WDateEdit >();

  return std::move( retVal );

} // endcreateEditor

auto
GCW::Gui::AccountRegister::DelegateHeader::
editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any
{
  auto dateEdit = dynamic_cast< Wt::WDateEdit* >( _editor );

//  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

  return dateEdit-> text();

}


