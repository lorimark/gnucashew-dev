#line 2 "src/Gui/BillPay/YearSelector.cpp"

#include "../../Glb/Core.h"
#include "BillPay.h"

GCW::Gui::BillPay::YearSelector::
YearSelector()
: Wt::WComboBox()
{
  /*
  ** preload some useful values
  */
  for( int i=2020; i< 2030; i++ )
    addItem( GCW::Core::itos( i ) );

  /*
  ** set the last used value
  **  (note; the value is stored as an 'integer')
  */
  setValueText( GCW::Core::itos( configItem()-> getVarInt( "selectedYear" ) ) );

  /*
  ** if the user changes the value, record it
  */
  activated()
    .connect( [this]( int _index )
    {
      Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

      configItem().modify()-> setVar( "selectedYear", GCW::Core::stoi( valueText().toUTF8() ) );

    });

} // endYearSelector()


