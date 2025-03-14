

#include "../Eng/AccountComboModel.h"

#include "AccountComboBox.h"

GCW::Gui::AccountComboBox::
AccountComboBox()
{
  setModel( std::make_shared< GCW::Eng::AccountComboModel >() );
  setModelColumn( 1 );

} // endAccountComboBox()

auto
GCW::Gui::AccountComboBox::
valueGuid()-> std::string
{
  return
    Wt::asString( model()-> data( currentIndex(), 0 ) ).toUTF8() ;

} // endvalueGuid()-> std::string



