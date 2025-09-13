#line 2 "src/Gui/AccountRegister/DelegateDate.cpp"

#include <Wt/WDateEdit.h>
#include <Wt/WHBoxLayout.h>

#include "Editor.h"
#include "DelegateDate.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegister::DelegateDate::
DelegateDate()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;

  /*
  ** setting the text format here can work, except
  **  it requires that _every_ row have the WDateTime value
  **  set as its value, otherwise the display-conversion
  **  will throw.
  */
  setTextFormat( GCW_DATE_FORMAT_DISPLAY ); // use this DATE format for the conversion

} // endDateDelegate()

GCW::Gui::AccountRegister::DelegateDate::
~DelegateDate()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegister::DelegateDate::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
 std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
   << " ("   << _index.row() << "," << _index.column() << ")"
   << std::endl;
#endif

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "(): " << _index.row() << "," << _index.column()
    << " DateDelegate::" << __FUNCTION__
    << " "  << _index.data( Wt::ItemDataRole::Edit ).type().name()
    << " '" << Wt::asString( _index.data( Wt::ItemDataRole::Edit ) ) << "'"
    << std::endl;
#endif

  /*
  ** The editor is placed in to a container for layout
  **  management
  */
  auto retVal = std::make_unique< Wt::WContainerWidget >();
  retVal-> setSelectable( true );

  /*
  ** Build an editor
  **
  ** Hitting the 'enter' key or the 'esc' key closes the editor
  */
  auto dateEdit = std::make_unique< Wt::WDateEdit >();
  dateEdit-> setFormat( GCW::Cfg::date_format() );
//  m_dateEdit-> enterPressed  ().connect( [&](){ doCloseEditor( dateEdit.get(), true  ); });
//  m_dateEdit-> escapePressed ().connect( [&](){ doCloseEditor( dateEdit.get(), false ); });
//  m_dateEdit-> keyWentDown   ().connect( [&]( Wt::WKeyEvent _keyEvent ){ doTabAction( _keyEvent ); });

  setDate( dateEdit.get(), _index.data( Wt::ItemDataRole::Edit ) );

  /*
  ** Stuff it in to the layout
  */
  retVal-> setLayout( std::make_unique< Wt::WHBoxLayout >() );
  retVal-> layout()-> setContentsMargins( 1,1,1,1 );
  retVal-> layout()-> addWidget( std::move( dateEdit ) );

  return std::move( retVal );

} // endcreateEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >

auto
GCW::Gui::AccountRegister::DelegateDate::
setDate( Wt::WDateEdit * _dateEdit, Wt::cpp17::any _value ) const-> void
{
  /*
  ** this just verifies we have the right type
  */
  if( _value.type() == typeid( Wt::WDateTime ) )
  {
#ifdef NEVER
    std::cout << __FILE__ << ":" << __LINE__
      << " " << GCW::Cfg::date_format()
      << " " << Wt::asString( _value )
      << std::endl;
#endif

    /*
    ** Get the date from the value
    */
    auto dateTime = Wt::cpp17::any_cast< Wt::WDateTime >( _value );

    _dateEdit-> setDate( dateTime.date() );

  } // endif( _value.type() == typeid( Wt::WDateTime ) )

} // endsetDate( Wt::cpp17::any & _value )-> void

auto
GCW::Gui::AccountRegister::DelegateDate::
doCloseEditor( Wt::WDateEdit * _dateEdit, bool _save ) const-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " DateDelegate::doCloseEditor()" << std::endl;
#endif

  closeEditor().emit( _dateEdit, _save );

} // enddoCloseEditor( Wt::WDateEdit * _dateEdit, bool save ) const-> void

auto
GCW::Gui::AccountRegister::DelegateDate::
doTabAction( Wt::WKeyEvent _keyEvent ) const-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " DateDelegate::doTabAction()" << std::endl;
#endif

} // enddoTabAction( Wt::WKeyEvent _keyEvent ) const-> void

auto
GCW::Gui::AccountRegister::DelegateDate::
editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any
{
  Wt::WDateTime retVal;

  auto cw = dynamic_cast< Wt::WContainerWidget* >( _editor );
  if(  cw && cw-> layout()-> count() > 0 )
  {
    auto de = dynamic_cast< Wt::WDateEdit* >( cw-> layout()-> itemAt(0)-> widget() );
    if(  de )
    {
      /*
      ** the date editor only returns a 'date' component
      **  so in order to return the correct data type
      **  the date component must be upgraded to a datetime
      **  element for return.  Set the default time upon
      **  doing so.
      */
      retVal.setDate( de-> date()           );
      retVal.setTime( GCW_DATE_DEFAULT_TIME );

    }

  }

  return retVal ;

} // endeditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any

auto
GCW::Gui::AccountRegister::DelegateDate::
setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << "(): " << _editor
    << " "    << _index.row() << "," << _index.column()
    << " "    << _value.type().name()
    << " '"   << Wt::asString( _value ) << "'"
    << std::endl;
#endif

  auto cw = dynamic_cast< Wt::WContainerWidget* >( _editor );
  if(  cw && cw-> layout()-> count() > 0 )
  {
    auto de = dynamic_cast< Wt::WDateEdit* >( cw-> layout()-> itemAt(0)-> widget() );
    if(  de )
    {
      setDate( de, _value );
    }
  }

} // endsetEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void

auto
GCW::Gui::AccountRegister::DelegateDate::
setModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " setModelData()"
    << " " << _index.row()
    << " " << _index.column()
    << " " << _editState.type().name()
    << " " << Wt::asString( _editState )
    << " " << _model
    << std::endl;
#endif

  DelegateBase::setModelData( _editState, _model, _index );

} // endsetModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void



