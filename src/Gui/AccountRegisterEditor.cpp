#line 2 "src/Gui/AccountRegisterEditor.cpp"

#include <Wt/WDateEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WSuggestionPopup.h>
#include <Wt/WText.h>
#include <Wt/WTableView.h>
#include <Wt/WTheme.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>

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
BaseDelegate()
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
update( Wt::WWidget * _widget, const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags )-> std::unique_ptr< Wt::WWidget >
{
#ifdef NEVER
 std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
   << "(): " << widget
   << " "    << index.row() << "," << index.column()
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
    << " "    << _index.row() << "," << _index.column()
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
    << "(): " << _index.row() << "," << _index.column()
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
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << "(): " << _widget
    << " "    << _index.row() << "," << _index.column()
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
    << "(): " << _index.row() << "," << _index.column()
    << std::endl;
#endif

  Wt::WItemDelegate::setModelData( _editState, _model, _index );

} // endsetModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegisterEditor::HeaderDelegate::
HeaderDelegate()
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
    << "(): " << _index.row() << "," << _index.column()
    << " HeaderDelegate::" << __FUNCTION__
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
DateDelegate()
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
    auto de = dynamic_cast< Wt::WDateEdit* >( cw-> layout()-> widget() );
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

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " Wt::cpp17::any DateDelegate::editState()"
    << " row:"   << _index.row()
    << " col:"   << _index.column()
    << " id:"    << cw-> id()
    << " oname:" << cw-> objectName()
    << " chlds:" << cw-> children().size()
    << " typid:" << typeid( cw-> children().at(0) ).name()
    << " dated:" << de
    << " mdted:" << m_dateEdit
    << " txt:"   << m_dateEdit-> text()
    << std::endl
    ;
#endif

  return retVal ;

} // endeditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any

auto
GCW::Gui::AccountRegisterEditor::DateDelegate::
setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void
{
//  the '_editor' and 'm_dateEdit' are not the same widget
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
    << "(): " << _editor
    << " "    << _index.row() << "," << _index.column()
    << " '"   << Wt::asString( _value ) << "'"
    << " "    << _value.type().name()
    << std::endl;
#endif

  auto cw = dynamic_cast< Wt::WContainerWidget* >( _editor );
  if(  cw && cw-> layout()-> count() > 0 )
  {
    auto de = dynamic_cast< Wt::WDateEdit* >( cw-> layout()-> widget() );
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
ReconcileDelegate()
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
  ** Hitting the 'enter' key or the 'esc' key closes the editor
  **
  */
  auto reconciledEdit = std::make_unique< Wt::WLineEdit >();
  reconciledEdit-> setReadOnly( true );
  reconciledEdit-> setText( reconciled );
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

  auto ed = dynamic_cast< Wt::WLineEdit* >( cw-> children().at(0) );

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

} // endsetModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void


/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegisterEditor::ValueDelegate::
ValueDelegate()
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
BalanceDelegate()
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

  auto retVal = BaseDelegate::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );
  lineEdit-> setReadOnly( true );
  lineEdit-> setAttributeValue( "style", "text-align:right;" );

  return retVal;

} // endcreateEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget >


/* * * * * * * * * * * * * * * * * * * * * * * * * * */


GCW::Gui::AccountRegisterEditor::SuggestionDelegate::
SuggestionDelegate()
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
AccountDelegate()
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


GCW::Gui::AccountRegisterEditor::
AccountRegisterEditor()
{
  m_delegateDate = std::make_shared< DateDelegate       >();
  m_delegateNum  = std::make_shared< SuggestionDelegate >();
  m_delegateMemo = std::make_shared< SuggestionDelegate >();
  m_delegateAcct = std::make_shared< AccountDelegate    >();
  m_delegateReco = std::make_shared< ReconcileDelegate  >();
  m_delegateIn   = std::make_shared< ValueDelegate      >();
  m_delegateOut  = std::make_shared< ValueDelegate      >();
  m_delegateBal  = std::make_shared< BalanceDelegate    >();

} // endAccountRegisterEditor()


auto
GCW::Gui::AccountRegisterEditor::
setTableView( GCW::Gui::TableView * _tableView )-> void
{
  m_tableView = _tableView;

  tableView()-> setItemDelegateForColumn ( 0, m_delegateDate  );
  tableView()-> setItemDelegateForColumn ( 1, m_delegateNum   );
  tableView()-> setItemDelegateForColumn ( 2, m_delegateMemo  );
  tableView()-> setItemDelegateForColumn ( 3, m_delegateAcct  );
  tableView()-> setItemDelegateForColumn ( 4, m_delegateReco  );
  tableView()-> setItemDelegateForColumn ( 5, m_delegateIn    );
  tableView()-> setItemDelegateForColumn ( 6, m_delegateOut   );
  tableView()-> setItemDelegateForColumn ( 7, m_delegateBal   );

}

