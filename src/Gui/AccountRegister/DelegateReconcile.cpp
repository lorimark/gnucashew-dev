#line 2 "src/Gui/AccountRegister/DelegateReconcile.cpp"

#include <Wt/WHBoxLayout.h>
#include <Wt/WDateTime.h>

#include "DelegateReconcile.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

GCW::Gui::AccountRegister::DelegateReconcile::
DelegateReconcile( Editor * _editor )
: DelegateBase( _editor )
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

GCW::Gui::AccountRegister::DelegateReconcile::
~DelegateReconcile()
{
//  std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "(): " << std::endl;
}

auto
GCW::Gui::AccountRegister::DelegateReconcile::
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
GCW::Gui::AccountRegister::DelegateReconcile::
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
GCW::Gui::AccountRegister::DelegateReconcile::
doTabAction( Wt::WKeyEvent _keyEvent ) const-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " ReconciledDelegate::doTabAction()" << std::endl;
#endif

} // enddoTabAction( Wt::WKeyEvent _keyEvent ) const-> void

auto
GCW::Gui::AccountRegister::DelegateReconcile::
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
GCW::Gui::AccountRegister::DelegateReconcile::
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
GCW::Gui::AccountRegister::DelegateReconcile::
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

  DelegateBase::setModelData( _editState, _model, _index );

} // endsetModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void



