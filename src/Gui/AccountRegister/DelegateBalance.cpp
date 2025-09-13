#line 2 "src/Gui/AccountRegister/DelegateBalance.cpp"

#include "Editor.h"
#include "DelegateBalance.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegister::DelegateBalance::
DelegateBalance()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegister::DelegateBalance::
~DelegateBalance()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegister::DelegateBalance::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "(): " << _index.row() << "," << _index.column()
    << " BalanceDelegate::" << __FUNCTION__
    << " '" << Wt::asString( _index.data( Wt::ItemDataRole::Edit ) ) << "'"
    << std::endl;
#endif

#ifdef NEVER
  auto retVal = std::make_unique< Wt::WContainerWidget >();
  retVal-> setSelectable( false );

  /*
  ** Get the data from the string value
  **
  */
  auto balance =  Wt::asString( _index.data( Wt::ItemDataRole::Edit ) );

  /*
  ** Build an editor
  **
  ** This is actually only a WText object, since it's not really an editor,
  **  it is a widget that responds to clicks.  It's not a push-button (doesn't
  **  need to be) it's just text, and upon clicking on the widget it will respond
  **  and change values accordingly.
  **
  */
  auto balanceEdit = std::make_unique< Wt::WText >();
  balanceEdit-> setText( balance );

  /*!
  ** \todo applying styles here; this needs to be moved to the .css files
  */
  balanceEdit-> setAttributeValue( "style", "background-color:yellow;border-radius:4px;border:1px solid rgb(204,204,204)" );

  /*
  ** Stuff it in to the layout
  **
  */
  retVal-> setLayout( std::make_unique< Wt::WHBoxLayout >() );
  retVal-> layout()-> setContentsMargins( 0,0,0,0 );
  retVal-> layout()-> addWidget( std::move( balanceEdit ) );
#endif

#ifndef NEVER
  auto retVal = DelegateBase::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );
  lineEdit-> setReadOnly( true );
  lineEdit-> setAttributeValue( "style", "text-align:right;" );
#endif

  return retVal;

} // endcreateEditor( ... ) const-> std::unique_ptr< Wt::WWidget >



