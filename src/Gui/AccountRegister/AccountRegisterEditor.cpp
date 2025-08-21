#line 2 "src/Gui/AccountRegister/AccountRegisterEditor.cpp"

#include <Wt/WDateEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WSuggestionPopup.h>
#include <Wt/WText.h>
#include <Wt/WTableView.h>
#include <Wt/WTheme.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WMessageBox.h>

#include "../define.h"
#include "../App.h"
#include "../Dbo/Accounts/Accounts.h"
#include "../Dbo/Prefrences.h"
#include "../Dbo/Splits/Splits.h"
#include "../Eng/TransactionManager.h"
#include "AccountSuggestionPopup.h"
#include "AccountRegister.h"

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
GCW::Gui::AccountRegisterEditor::BaseDelegate::
BaseDelegate( AccountRegisterEditor * _editor )
{
  // std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegisterEditor::BaseDelegate::
~BaseDelegate()
{
  // std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegisterEditor::BaseDelegate::
createEditor( const Wt::WModelIndex &_index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifndef NEVER
 std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
   << " ("   << _index.row() << "," << _index.column() << ")"
   << std::endl;
#endif

  return Wt::WItemDelegate::createEditor( _index, _flags );

} // endcreateEditor( ... ) const-> std::unique_ptr< WWidget >

auto
GCW::Gui::AccountRegisterEditor::BaseDelegate::
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
GCW::Gui::AccountRegisterEditor::BaseDelegate::
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
GCW::Gui::AccountRegisterEditor::BaseDelegate::
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
GCW::Gui::AccountRegisterEditor::BaseDelegate::
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
GCW::Gui::AccountRegisterEditor::BaseDelegate::
setEditState( Wt::WWidget * _widget, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void
{
#ifndef NEVER
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
GCW::Gui::AccountRegisterEditor::BaseDelegate::
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

    editor()-> setDirty( _index );

  } // endif( !_equal( modelData, _editState ) )

} // endsetModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegisterEditor::HeaderDelegate::
HeaderDelegate( AccountRegisterEditor * _editor )
: BaseDelegate( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegisterEditor::HeaderDelegate::
~HeaderDelegate()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegisterEditor::HeaderDelegate::
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
GCW::Gui::AccountRegisterEditor::HeaderDelegate::
editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any
{
  auto dateEdit = dynamic_cast< Wt::WDateEdit* >( _editor );

//  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

  return dateEdit-> text();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegisterEditor::DateDelegate::
DateDelegate( AccountRegisterEditor * _editor )
: BaseDelegate( _editor )
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

GCW::Gui::AccountRegisterEditor::DateDelegate::
~DateDelegate()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegisterEditor::DateDelegate::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
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
GCW::Gui::AccountRegisterEditor::DateDelegate::
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
GCW::Gui::AccountRegisterEditor::DateDelegate::
doCloseEditor( Wt::WDateEdit * _dateEdit, bool _save ) const-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " DateDelegate::doCloseEditor()" << std::endl;
#endif

  closeEditor().emit( _dateEdit, _save );

} // enddoCloseEditor( Wt::WDateEdit * _dateEdit, bool save ) const-> void

auto
GCW::Gui::AccountRegisterEditor::DateDelegate::
doTabAction( Wt::WKeyEvent _keyEvent ) const-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " DateDelegate::doTabAction()" << std::endl;
#endif

} // enddoTabAction( Wt::WKeyEvent _keyEvent ) const-> void

auto
GCW::Gui::AccountRegisterEditor::DateDelegate::
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
GCW::Gui::AccountRegisterEditor::DateDelegate::
setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void
{
#ifndef NEVER
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
GCW::Gui::AccountRegisterEditor::DateDelegate::
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

  BaseDelegate::setModelData( _editState, _model, _index );

} // endsetModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void


/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegisterEditor::ReconcileDelegate::
ReconcileDelegate( AccountRegisterEditor * _editor )
: BaseDelegate( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegisterEditor::ReconcileDelegate::
~ReconcileDelegate()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegisterEditor::ReconcileDelegate::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "(): " << _index.row() << "," << _index.column()
    << " ReconcileDelegate::" << __FUNCTION__
    << " '" << Wt::asString( _index.data( Wt::ItemDataRole::Edit ) ) << "'"
    << std::endl;
#endif

  /*
  ** The editor is placed in to a container for layout
  **  management
  **
  */
  auto retVal = std::make_unique< Wt::WContainerWidget >();
  retVal-> setSelectable( true );

  /*
  ** Get the data from the string value
  **
  */
  auto reconciled =  Wt::asString( _index.data( Wt::ItemDataRole::Edit ) );

  /*
  ** Build an editor
  **
  ** This is actually only a WText object, since it's not really an editor,
  **  it is a widget that responds to clicks.  It's not a push-button (doesn't
  **  need to be) it's just text, and upon clicking on the widget it will respond
  **  and change values accordingly.
  **
  */
  auto reconciledEdit = std::make_unique< Wt::WText >();
//  reconciledEdit-> setReadOnly( true );
  reconciledEdit-> setText( reconciled );

  /*!
  ** \todo applying styles here; this needs to be moved to the .css files
  */
  reconciledEdit-> setAttributeValue( "style", "background-color:yellow;border-radius:4px;border:1px solid rgb(204,204,204)" );

//  reconciledEdit-> enterPressed  ().connect( [&]()
//    {
//      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;
//
//      doCloseEditor( reconciledEdit.get(), true  ); 
//    });
//  reconciledEdit-> escapePressed ().connect( [&](){ doCloseEditor( reconciledEdit.get(), false ); });
//  reconciledEdit-> keyWentDown   ().connect( [&]( Wt::WKeyEvent _keyEvent ){ doTabAction( _keyEvent ); });

  /*
  ** Stuff it in to the layout
  **
  */
  retVal-> setLayout( std::make_unique< Wt::WHBoxLayout >() );
  retVal-> layout()-> setContentsMargins( 0,0,0,0 );
  retVal-> layout()-> addWidget( std::move( reconciledEdit ) );

  return retVal;

} // endcreateEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >

auto
GCW::Gui::AccountRegisterEditor::ReconcileDelegate::
doCloseEditor( Wt::WLineEdit * _editor, bool _save ) const-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " ReconciledDelegate::doCloseEditor()" << std::endl;
#endif

  closeEditor().emit( _editor, _save );

#ifdef NEVER
  m_editorClosed.emit( m_row, m_col );
  m_row = -1;
  m_col = -1;
#endif

} // enddoCloseEditor( Wt::WLineEdit * _editor, bool save ) const-> void

auto
GCW::Gui::AccountRegisterEditor::ReconcileDelegate::
doTabAction( Wt::WKeyEvent _keyEvent ) const-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " ReconciledDelegate::doTabAction()" << std::endl;
#endif

} // enddoTabAction( Wt::WKeyEvent _keyEvent ) const-> void

auto
GCW::Gui::AccountRegisterEditor::ReconcileDelegate::
editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any
{
  auto cw = dynamic_cast< Wt::WContainerWidget* >( _editor );

  auto ed = dynamic_cast< Wt::WText* >( cw-> children().at(0) );

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " Wt::cpp17::any ReconcileDelegate::editState()"
    << " r:" << _index.row()
    << " c:" << _index.column()
    << " i:" << cw-> id()
    << " n:" << cw-> objectName()
    << " s:" << cw-> children().size()
    << " t:" << typeid( cw-> children().at(0) ).name()
    << " d:" << ed
    << std::endl
    ;
#endif

  return ed-> text();

} // endeditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any

auto
GCW::Gui::AccountRegisterEditor::ReconcileDelegate::
setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << "(): " << _editor
    << " "    << _index.row() << "," << _index.column()
    << " "    << _value.type().name()
    << " '"   << Wt::asString( _value ) << "'"
    << std::endl;
#endif

//  the '_editor' and 'm_dateEdit' are not the same widget
//  std::cout << __FILE__ << ":" << __LINE__ << " " << _editor    << " " << typeid( _editor ).name()    << std::endl;
//  std::cout << __FILE__ << ":" << __LINE__ << " " << m_dateEdit << " " << typeid( m_dateEdit ).name() << std::endl;


} // endsetEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void

auto
GCW::Gui::AccountRegisterEditor::ReconcileDelegate::
setModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " ReconciledDelegate::setModelData()"
    << " " << _index.row()
    << " " << _index.column()
    << " " << Wt::asString( _editState )
    << " " << _model
    << std::endl;
#endif

  BaseDelegate::setModelData( _editState, _model, _index );

} // endsetModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void


/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegisterEditor::ValueDelegate::
ValueDelegate( AccountRegisterEditor * _editor )
: BaseDelegate( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegisterEditor::ValueDelegate::
~ValueDelegate()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegisterEditor::ValueDelegate::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "(): " << _index.row() << "," << _index.column()
    << " ValueDelegate::" << __FUNCTION__
    << " '" << Wt::asString( _index.data( Wt::ItemDataRole::Edit ) ) << "'"
    << std::endl;
#endif

  auto retVal = BaseDelegate::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );

  return retVal;

} // endcreateEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >


/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegisterEditor::BalanceDelegate::
BalanceDelegate( AccountRegisterEditor * _editor )
: BaseDelegate( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegisterEditor::BalanceDelegate::
~BalanceDelegate()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegisterEditor::BalanceDelegate::
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
  auto retVal = BaseDelegate::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );
  lineEdit-> setReadOnly( true );
  lineEdit-> setAttributeValue( "style", "text-align:right;" );
#endif

  return retVal;

} // endcreateEditor( ... ) const-> std::unique_ptr< Wt::WWidget >


/* * * * * * * * * * * * * * * * * * * * * * * * * * */


GCW::Gui::AccountRegisterEditor::SuggestionDelegate::
SuggestionDelegate( AccountRegisterEditor * _editor )
: BaseDelegate( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegisterEditor::SuggestionDelegate::
~SuggestionDelegate()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegisterEditor::SuggestionDelegate::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "(): " << _index.row() << "," << _index.column()
    << " SuggestionDelegate::" << __FUNCTION__
    << " '" << Wt::asString( _index.data( Wt::ItemDataRole::Edit ) ) << "'"
    << std::endl;
#endif

  auto retVal = BaseDelegate::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );

  if( false /* lineEdit */ )
  {
    // options for email address suggestions
    Wt::WSuggestionPopup::Options popupOptions =
    {
      "<b>",                // highlightBeginTag
      "</b>",               // highlightEndTag
      ',',                  // listSeparator      (for multiple addresses)
      " \n",                // whitespace
      "()[]{}-., \"@\n;:",  // wordSeparators     (within an address)
      ""                    // appendReplacedText (prepare next email address)
     };

    auto popup = retVal-> addChild( std::make_unique< Wt::WSuggestionPopup >( popupOptions ) );
    popup-> forEdit( lineEdit );

//    auto batchEditModel  = dynamic_cast< const Wt::WBatchEditProxyModel*             >( _index.model() );
//    auto sortFilterModel = dynamic_cast< const Wt::WSortFilterProxyModel*            >( _index.model() );;
//    auto baseModel       = dynamic_cast< const GCW::Gui::AccountRegister::BaseModel* >( sortFilterModel-> sourceModel().get() );
    auto baseModel       = dynamic_cast< const GCW::Gui::AccountRegister::BaseModel* >( _index.model() );

    for( auto item : baseModel-> suggestionsFromColumn( _index.column() ) )
      popup-> addSuggestion( item, item );
  }

  return retVal;

} // endcreateEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >


/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegisterEditor::AccountDelegate::
AccountDelegate( AccountRegisterEditor * _editor )
: BaseDelegate( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegisterEditor::AccountDelegate::
~AccountDelegate()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegisterEditor::AccountDelegate::
createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << "(): " << _index.row() << "," << _index.column()
    << " AccountDelegate::" << __FUNCTION__
    << " '" << Wt::asString( _index.data( Wt::ItemDataRole::Edit ) ) << "'"
    << std::endl;
#endif

  auto retVal   = BaseDelegate::createEditor       ( _index, _flags );
  auto cw       = dynamic_cast< Wt::WContainerWidget* > ( retVal.get()   );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >        ( cw-> widget(0) );

  auto popup = retVal-> addChild( std::make_unique< GCW::Gui::AccountSuggestionPopup >() );
  popup-> forEdit( lineEdit, Wt::PopupTrigger::Editing /* | Wt::PopupTrigger::DropDownIcon */ );

  return retVal;

} // endcreateEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >


/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * */


GCW::Gui::AccountRegisterEditor::
AccountRegisterEditor()
{
  m_delegateHeader = std::make_shared< HeaderDelegate     >( this );
  m_delegateDate   = std::make_shared< DateDelegate       >( this );
  m_delegateNum    = std::make_shared< SuggestionDelegate >( this );
  m_delegateMemo   = std::make_shared< SuggestionDelegate >( this );
  m_delegateAcct   = std::make_shared< AccountDelegate    >( this );
  m_delegateReco   = std::make_shared< ReconcileDelegate  >( this );
  m_delegateIn     = std::make_shared< ValueDelegate      >( this );
  m_delegateOut    = std::make_shared< ValueDelegate      >( this );
  m_delegateBal    = std::make_shared< BalanceDelegate    >( this );

} // endAccountRegisterEditor()


auto
GCW::Gui::AccountRegisterEditor::
setTableView( GCW::Gui::TableView * _tableView )-> void
{
  m_tableView = _tableView;

  tableView()-> setHeaderItemDelegate    ( m_delegateHeader   );
  tableView()-> setItemDelegateForColumn ( 0, m_delegateDate  );
  tableView()-> setItemDelegateForColumn ( 1, m_delegateNum   );
  tableView()-> setItemDelegateForColumn ( 2, m_delegateMemo  );
  tableView()-> setItemDelegateForColumn ( 3, m_delegateAcct  );
  tableView()-> setItemDelegateForColumn ( 4, m_delegateReco  );
  tableView()-> setItemDelegateForColumn ( 5, m_delegateIn    );
  tableView()-> setItemDelegateForColumn ( 6, m_delegateOut   );
  tableView()-> setItemDelegateForColumn ( 7, m_delegateBal   );

}

auto
GCW::Gui::AccountRegisterEditor::
editRow( Wt::WModelIndex _index )-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " " << __FUNCTION__ << "(" << _index.row() << "," << _index.column() << ")"
    << std::endl;
#endif

  /*
  ** before editing the row, ask if the user wants to
  **  save the existing row
  */
  if( m_index.isValid() )
  {
    if( m_index.row() != _index.row() )
    {



//      Wt::WMessageBox::show( "Data Changed", "Do you want to record these changes?", Wt::StandardButton::Yes | Wt::StandardButton::No );
    }
  }

  if( _index.isValid() )
  {
    /*
    ** if more than one other row is selected (should NEVER happen!)
    **  then for sure we'll clear any selections.  But, if the row
    **  number is the same, then we don't want to clear, since it's
    **  the same row.
    */
    if( tableView()-> selectedIndexes().size() > 1
     || tableView()-> selectedIndexes().begin()-> row() != _index.row()
      )
    {
      tableView()-> clearSelection();
      tableView()-> closeEditors( true );
    }

    /*
    **  make sure it is in view.
    */
    tableView()-> scrollTo( _index );

    for( int column=0; column< tableView()-> model()-> columnCount(); column++ )
    {
      tableView()-> edit( tableView()-> model()-> index( _index.row(), column ) );
    }

  } // endif( _index.isValid() )

  /*
  ** remember what we're editing
  */
  m_index = _index;

} // endeditRow( Wt::WModelIndex _index )-> void


auto
GCW::Gui::AccountRegisterEditor::
setDirty( Wt::WModelIndex _index ) const-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << _index.isValid() << std::endl;

  std::cout << __FILE__ << ":" << __LINE__ << " " << m_index.isValid() << std::endl;

  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << "(): " << m_index.isValid()
    << "(): " << _index.row()
    << std::endl;
#endif

} // endsetDirty( Wt::WModelIndex _index )-> void


