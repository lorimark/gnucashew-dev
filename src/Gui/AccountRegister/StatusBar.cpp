#line 2 "src/Gui/AccountRegister/StatusBar.cpp"

#include <Wt/WHBoxLayout.h>

#include "../App.h"
#include "StatusBar.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegister::StatusBar::
StatusBar()
{
  addStyleClass( "StatusBar" );

  auto lw = setLayout( std::make_unique< Wt::WHBoxLayout >() );

  lw-> setSpacing( 0 );

  auto _addWidget = [&]( const std::string & _key, int _spacing = 0 )
  {
    lw-> addWidget( std::make_unique< Wt::WText >( TR("gcw.AccountRegister.StatusBar." + _key ) + ":" ) );
    auto retVal = lw-> addWidget( std::make_unique< Wt::WText >(), _spacing );
    retVal-> setAttributeValue( "style", "margin-right:10px" );
    return retVal;
  };

  m_present    = _addWidget( "present"      );
  m_future     = _addWidget( "future"       );
  m_cleared    = _addWidget( "cleared"      );
  m_reconciled = _addWidget( "reconciled"   );
  m_projected  = _addWidget( "projected", 1 );
  m_rowCount   = _addWidget( "rowCount"     );

  setPresent    ();
  setFuture     ();
  setCleared    ();
  setReconciled ();
  setProjected  ();
  setRowCount   ();

} // endStatusBar()

auto
GCW::Gui::AccountRegister::StatusBar::
setText( Wt::WText * _widget, GCW_NUMERIC _value )-> void
{
  _widget-> setText( "$" + toString( _value, GCW::Cfg::decimal_format() ) );
}

auto
GCW::Gui::AccountRegister::StatusBar::
setText( Wt::WText * _widget, int _value )-> void
{
  _widget-> setText( std::to_string( _value ) );
}

auto GCW::Gui::AccountRegister::StatusBar:: setPresent    ( GCW_NUMERIC _value )-> void  { setText( m_present    , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setFuture     ( GCW_NUMERIC _value )-> void  { setText( m_future     , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setCleared    ( GCW_NUMERIC _value )-> void  { setText( m_cleared    , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setReconciled ( GCW_NUMERIC _value )-> void  { setText( m_reconciled , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setProjected  ( GCW_NUMERIC _value )-> void  { setText( m_projected  , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setRowCount   ( int         _value )-> void  { setText( m_rowCount   , _value ); }



