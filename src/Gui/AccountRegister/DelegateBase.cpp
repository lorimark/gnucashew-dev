#line 2 "src/Gui/AccountRegister/DelegateBase.cpp"

#include <Wt/WDateTime.h>

#include "DelegateBase.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

/*!
** \brief Base Delegate
**
** This class is strictly for debugging and tracing purposes.  It
**  facilitates the hooking of the various calls in to the delegate
**  classes so that their behaviour and interaction with the view
**  can be studied, understood (and perhaps documented).
**
*/
GCW::Gui::AccountRegister::DelegateBase::
DelegateBase()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegister::DelegateBase::
~DelegateBase()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegister::DelegateBase::
createEditor( const Wt::WModelIndex &_index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
 std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
   << " ("   << _index.row() << "," << _index.column() << ")"
   << std::endl;
#endif

  return Wt::WItemDelegate::createEditor( _index, _flags );

} // endcreateEditor( ... ) const-> std::unique_ptr< WWidget >

auto
GCW::Gui::AccountRegister::DelegateBase::
update( Wt::WWidget * _widget, const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags )-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
 std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
   << "(): " << widget
   << " ("   << _index.row() << "," << _index.column() << ")"
   << std::endl;
#endif

  return Wt::WItemDelegate::update( _widget, _index, _flags );

} //endupdate( Wt::WWidget * _widget, const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags )-> std::unique_ptr< Wt::WWidget >

auto
GCW::Gui::AccountRegister::DelegateBase::
updateModelIndex( Wt::WWidget * _widget, const Wt::WModelIndex & _index )-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << "(): " << _widget
   << " ("   << _index.row() << "," << _index.column() << ")"
    << std::endl;
#endif

  Wt::WItemDelegate::updateModelIndex( _widget, _index );

} // endupdateModelIndex( Wt::WWidget * _widget, const Wt::WModelIndex & _index )-> void

auto
GCW::Gui::AccountRegister::DelegateBase::
validate( const Wt::WModelIndex & _index, const Wt::cpp17::any & _editState ) const-> Wt::ValidationState
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << " ("   << _index.row() << "," << _index.column() << ")"
    << std::endl;
#endif

  return Wt::WItemDelegate::validate( _index, _editState );

} // endvalidate( const Wt::WModelIndex & _index, const Wt::cpp17::any & _editState ) const-> Wt::ValidationState

auto
GCW::Gui::AccountRegister::DelegateBase::
editState( Wt::WWidget * _widget, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any
{
  auto retVal = Wt::WItemDelegate::editState( _widget, _index );

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << " ("   << _index.row() << "," << _index.column() << ")"
    << "(): " << typeid(  _widget ).name()
    << "(): " << typeid( *_widget ).name()
    << " '"   << Wt::asString( retVal ) << "'"
    << std::endl;
#endif

  return retVal;

} // endeditState( Wt::WWidget * _widget, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any

auto
GCW::Gui::AccountRegister::DelegateBase::
setEditState( Wt::WWidget * _widget, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << "(): " << _widget
    << " ("   << _index.row() << "," << _index.column() << ")"
    << " "    << _value.type().name()
    << " '"   << Wt::asString( _value ) << "'"
    << std::endl;
#endif

//  Wt::WItemDelegate::setEditState( widget, index, value );

} // endsetEditState( Wt::WWidget * _widget, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void

auto
GCW::Gui::AccountRegister::DelegateBase::
setModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << " ("   << _index.row() << "," << _index.column() << ")"
    << std::endl;
#endif

  /*
  ** in order to compare .any. type, check the types,
  **  and then ultimately cast the type correctly and
  **  then compare the actual values.
  */
  auto _equal = []( Wt::cpp17::any _a, Wt::cpp17::any _b )
  {
    if( !_a.has_value() && !_b.has_value() )
      return true; // both empty

    if( _a.type() != _b.type() )
      return false; // different types

    // compare based on type
    if( _a.type() == typeid(int) )
      return Wt::cpp17::any_cast<int>(_a)
          == Wt::cpp17::any_cast<int>(_b);

    if( _a.type() == typeid(std::string) )
      return Wt::cpp17::any_cast<std::string>(_a)
          == Wt::cpp17::any_cast<std::string>(_b);

    if( _a.type() == typeid(double) )
      return Wt::cpp17::any_cast<double>(_a)
          == Wt::cpp17::any_cast<double>(_b);

    if( _a.type() == typeid(Wt::WString) )
      return Wt::cpp17::any_cast<Wt::WString>(_a)
          == Wt::cpp17::any_cast<Wt::WString>(_b);

    if( _a.type() == typeid(Wt::WDateTime) )
      return Wt::cpp17::any_cast<Wt::WDateTime>(_a)
          == Wt::cpp17::any_cast<Wt::WDateTime>(_b);

    std::cout << __FILE__ << ":" << __LINE__ << " unhandled type: " << _a.type().name() << std::endl;

    return false;

  }; // endauto _equal = []( Wt::cpp17::any _a, Wt::cpp17::any _b )

  auto modelData = _index.data( Wt::ItemDataRole::Edit );

  Wt::WItemDelegate::setModelData( _editState, _model, _index );

  /*
  ** if the data changed then signal the editor
  */
  if( !_equal( modelData, _editState ) )
  {
#ifdef NEVER
    std::cout << __FILE__ << ":" << __LINE__ << " data changed"
      << " " << Wt::asString( modelData  )
      << " " << Wt::asString( _editState )
      << std::endl;
#endif

//    editor()-> setDirty( _index );

  } // endif( !_equal( modelData, _editState ) )

} // endsetModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void


