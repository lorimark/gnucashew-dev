#line 2 "src/Gui/AccountRegister.cpp"

#include <Wt/WDateEdit.h>
#include <Wt/WItemDelegate.h>
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

namespace {

auto
setText_( Wt::WText * _widget, GCW_NUMERIC _value )-> void
{
  _widget-> setText( "$" + toString( _value, GCW::Cfg::decimal_format() ) );
}

auto
setText_( Wt::WText * _widget, int _value )-> void
{
  _widget-> setText( std::to_string( _value ) );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

class HeaderDelegate
: public Wt::WItemDelegate
{
  public:


    auto createEditor
    (
     const Wt::WModelIndex & _index,
     Wt::WFlags< Wt::ViewItemRenderFlag > _flags
    ) const-> std::unique_ptr< Wt::WWidget >;

    virtual auto editState( Wt::WWidget *editor, const Wt::WModelIndex &index ) const-> Wt::cpp17::any override;

}; // endclass HeaderDelegate

auto
HeaderDelegate::
createEditor
(
  const Wt::WModelIndex & _index,
  Wt::WFlags< Wt::ViewItemRenderFlag > _flags
) const-> std::unique_ptr< Wt::WWidget >
{
  std::cout << __FILE__ << ":" << __LINE__ << " HeaderDelegate::" << __FUNCTION__ << "(): " << _index.row() << " " << _index.column() << std::endl;

  auto retVal = std::make_unique< Wt::WDateEdit >();

  return std::move( retVal );

} // endcreateEditor

Wt::cpp17::any
HeaderDelegate::
editState( Wt::WWidget *editor, const Wt::WModelIndex &index ) const
{
  auto dateEdit = dynamic_cast< Wt::WDateEdit* >( editor );

  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

  return dateEdit-> text();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * */

class DateDelegate
: public Wt::WItemDelegate
{
  public:

    ~DateDelegate()
    {
//      std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;
    }

    std::unique_ptr< Wt::WWidget > createEditor
    (
     const Wt::WModelIndex & _index,
     Wt::WFlags< Wt::ViewItemRenderFlag > _flags
    ) const;

    virtual Wt::cpp17::any editState( Wt::WWidget *editor, const Wt::WModelIndex &index ) const override;
    void setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const;
    void setModelData ( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const;

    void doCloseEditor( Wt::WDateEdit * _dateEdit, bool save ) const;
    void doTabAction( Wt::WKeyEvent _keyEvent ) const;

    mutable Wt::WDateEdit * m_dateEdit = nullptr;

}; // endclass DateDelegate

std::unique_ptr< Wt::WWidget >
DateDelegate::
createEditor
(
  const Wt::WModelIndex & _index,
  Wt::WFlags< Wt::ViewItemRenderFlag > _flags
) const
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " DateDelegate::" << __FUNCTION__ << "(): " << _index.row() << "," << _index.column() << std::endl;
#endif

  /*
  ** The editor is placed in to a container for layout
  **  management
  **
  */
  auto retVal = std::make_unique< Wt::WContainerWidget >();
#ifndef NEVER
  retVal-> setSelectable( true );

  /*
  ** Get the date from the string value
  **
  */
  auto date =
    Wt::WDate::fromString
    (
     Wt::asString( _index.data( Wt::ItemDataRole::Edit ) ),
     GCW::Cfg::date_format()
    );

  /*
  ** Build an editor
  **
  ** Hitting the 'enter' key or the 'esc' key closes the editor
  **
  */
  auto dateEdit = std::make_unique< Wt::WDateEdit >();
  m_dateEdit = dateEdit.get();
  dateEdit-> setFormat( GCW::Cfg::date_format() );
  dateEdit-> setDate( date );
  dateEdit-> enterPressed  ().connect( [&](){ doCloseEditor( dateEdit.get(), true  ); });
  dateEdit-> escapePressed ().connect( [&](){ doCloseEditor( dateEdit.get(), false ); });
  dateEdit-> keyWentDown   ().connect( [&]( Wt::WKeyEvent _keyEvent ){ doTabAction( _keyEvent ); });

  /*
  ** Stuff it in to the layout
  **
  */
  retVal-> setLayout( std::make_unique< Wt::WHBoxLayout >() );
  retVal-> layout()-> setContentsMargins( 1,1,1,1 );
  retVal-> layout()-> addWidget( std::move( dateEdit ) );
#endif

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " DateDelegate::createEditor<end>" << std::endl;
#endif

  return retVal;

} // endstd::unique_ptr< Wt::WWidget > DateDelegate::createEditor

void
DateDelegate::
doCloseEditor( Wt::WDateEdit * _dateEdit, bool save ) const
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " DateDelegate::doCloseEditor()" << std::endl;
#endif

  closeEditor().emit( _dateEdit, save );

} // endvoid DateDelegate::doCloseEditor( Wt::WDateEdit * _dateEdit, bool save ) const

void
DateDelegate::
doTabAction( Wt::WKeyEvent _keyEvent ) const
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " DateDelegate::doTabAction()" << std::endl;
#endif

}

Wt::cpp17::any
DateDelegate::
editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const
{
  auto cw = dynamic_cast< Wt::WContainerWidget* >( _editor );

  auto de = dynamic_cast< Wt::WDateEdit* >( cw-> children().at(0) );

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

//  return "";
  return m_dateEdit-> text();

} // endWt::cpp17::any DateDelegate::editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const

void
DateDelegate::
setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const
{
//  the '_editor' and 'm_dateEdit' are not the same widget
#ifndef NEVER
  std::cout << FUNCTION_HEADER
    << " " << _editor    << " " << typeid( _editor ).name()
    << " " << m_dateEdit << " " << typeid( m_dateEdit ).name()
    << std::endl;
#endif

//  Wt::WItemDelegate::setEditState( _editor, _index, _value );

} // endvoid DateDelegate::setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const

void
DateDelegate::
setModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " setModelData()"
    << " " << _index.row()
    << " " << _index.column()
    << " " << Wt::asString( _editState )
    << " " << _model
    << std::endl;
#endif

  Wt::WItemDelegate::setModelData( _editState, _model, _index );

} // endvoid DateDelegate::setModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const




/* * * * * * * * * * * * * * * * * * * * * * * * * * */

class ReconcileDelegate
: public Wt::WItemDelegate
{
  public:

    std::unique_ptr< Wt::WWidget > createEditor
    (
     const Wt::WModelIndex & _index,
     Wt::WFlags< Wt::ViewItemRenderFlag > _flags
    ) const;

    virtual Wt::cpp17::any editState( Wt::WWidget *editor, const Wt::WModelIndex &index ) const override;
    void setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const;
    void setModelData ( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const;

    void doCloseEditor( Wt::WLineEdit * _editor, bool save ) const;
    void doTabAction( Wt::WKeyEvent _keyEvent ) const;

};

std::unique_ptr< Wt::WWidget >
ReconcileDelegate::
createEditor
(
  const Wt::WModelIndex & _index,
  Wt::WFlags< Wt::ViewItemRenderFlag > _flags
) const
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " ReconcileDelegate::" << __FUNCTION__ << "(): " << _index.row() << " " << _index.column() << std::endl;
#endif

  /*
  ** The editor is placed in to a container for layout
  **  management
  **
  */
  auto retVal = std::make_unique< Wt::WContainerWidget >();
  retVal-> setSelectable( true );

  /*
  ** Get the date from the string value
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
  reconciledEdit-> enterPressed  ().connect( [&](){ doCloseEditor( reconciledEdit.get(), true  ); });
  reconciledEdit-> escapePressed ().connect( [&](){ doCloseEditor( reconciledEdit.get(), false ); });
  reconciledEdit-> keyWentDown   ().connect( [&]( Wt::WKeyEvent _keyEvent ){ doTabAction( _keyEvent ); });

  /*
  ** Stuff it in to the layout
  **
  */
  retVal-> setLayout( std::make_unique< Wt::WHBoxLayout >() );
  retVal-> layout()-> setContentsMargins( 0,0,0,0 );
  retVal-> layout()-> addWidget( std::move( reconciledEdit ) );

  return retVal;

} // endstd::unique_ptr< Wt::WWidget > ReconciledDelegate::createEditor

void
ReconcileDelegate::
doCloseEditor( Wt::WLineEdit * _editor, bool save ) const
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " ReconciledDelegate::doCloseEditor()" << std::endl;
#endif

  closeEditor().emit( _editor, save );

#ifdef NEVER
  m_editorClosed.emit( m_row, m_col );
  m_row = -1;
  m_col = -1;
#endif

} // endvoid ReconciledDelegate::doCloseEditor( Wt::WDateEdit * _dateEdit, bool save ) const

void
ReconcileDelegate::
doTabAction( Wt::WKeyEvent _keyEvent ) const
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " ReconciledDelegate::doTabAction()" << std::endl;
#endif

}

Wt::cpp17::any
ReconcileDelegate::
editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const
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

//  return "";
  return ed-> text();

} // endWt::cpp17::any ReconcileDelegate::editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const

void
ReconcileDelegate::
setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const
{
//  the '_editor' and 'm_dateEdit' are not the same widget
//  std::cout << __FILE__ << ":" << __LINE__ << " " << _editor    << " " << typeid( _editor ).name()    << std::endl;
//  std::cout << __FILE__ << ":" << __LINE__ << " " << m_dateEdit << " " << typeid( m_dateEdit ).name() << std::endl;


} // endvoid DateDelegate::setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const

void
ReconcileDelegate::
setModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const
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

} // endvoid ReconciledDelegate::setModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const


/* * * * * * * * * * * * * * * * * * * * * * * * * * */


class ValueDelegate
: public Wt::WItemDelegate
{
  public:

    std::unique_ptr< Wt::WWidget > createEditor
    (
     const Wt::WModelIndex & _index,
     Wt::WFlags< Wt::ViewItemRenderFlag > _flags
    ) const;

};

std::unique_ptr< Wt::WWidget >
ValueDelegate::
createEditor
(
  const Wt::WModelIndex & _index,
  Wt::WFlags< Wt::ViewItemRenderFlag > _flags
) const
{
  auto retVal = Wt::WItemDelegate::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );

  return retVal;

} // endstd::unique_ptr< Wt::WWidget > ValueDelegate::createEditor


/* * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
** Balance delegate works just like the ValueDelegate but
**  also adds a read-only attribute to the input, so it
**  displays the same, but cannot be edited.  This is done
**  so that the entire line is highlighted fully when
**  selected.
**
*/
class BalanceDelegate
: public Wt::WItemDelegate
{
  public:

    auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

}; // endclass BalanceDelegate

auto
BalanceDelegate::
createEditor
(
  const Wt::WModelIndex & _index,
  Wt::WFlags< Wt::ViewItemRenderFlag > _flags
) const-> std::unique_ptr< Wt::WWidget >
{
  auto retVal = Wt::WItemDelegate::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );
  lineEdit-> setReadOnly( true );
  lineEdit-> setAttributeValue( "style", "text-align:right;" );

  return retVal;

} // endstd::unique_ptr< Wt::WWidget > ValueDelegate::createEditor


/* * * * * * * * * * * * * * * * * * * * * * * * * * */


class SuggestionDelegate
: public Wt::WItemDelegate
{
  public:

    std::unique_ptr< Wt::WWidget > createEditor
    (
     const Wt::WModelIndex & _index,
     Wt::WFlags< Wt::ViewItemRenderFlag > _flags
    ) const;

};

std::unique_ptr< Wt::WWidget >
SuggestionDelegate::
createEditor
(
  const Wt::WModelIndex & _index,
  Wt::WFlags< Wt::ViewItemRenderFlag > _flags
) const
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " SuggestionDelegate::" << __FUNCTION__ << "(): " << _index.row() << " " << _index.column() << std::endl;
#endif

  auto retVal = Wt::WItemDelegate::createEditor( _index, _flags );
  auto cw = dynamic_cast< Wt::WContainerWidget* >( retVal.get() );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >( cw-> widget(0) );

  if( lineEdit )
  {
    // options for email address suggestions
    Wt::WSuggestionPopup::Options popupOptions =
    {
      "<b>",         // highlightBeginTag
      "</b>",        // highlightEndTag
      ',',           // listSeparator      (for multiple addresses)
      " \n",         // whitespace
      "()[]{}-., \"@\n;:", // wordSeparators     (within an address)
      ""             // appendReplacedText (prepare next email address)
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

} // endstd::unique_ptr< Wt::WWidget > SuggestionDelegate::createEditor


/* * * * * * * * * * * * * * * * * * * * * * * * * * */

class AccountDelegate
: public Wt::WItemDelegate
{
  public:

    std::unique_ptr< Wt::WWidget > createEditor
    (
     const Wt::WModelIndex & _index,
     Wt::WFlags< Wt::ViewItemRenderFlag > _flags
    ) const;

};

std::unique_ptr< Wt::WWidget >
AccountDelegate::
createEditor
(
  const Wt::WModelIndex & _index,
  Wt::WFlags< Wt::ViewItemRenderFlag > _flags
) const
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " AccountDelegate::" << __FUNCTION__ << "(): " << _index.row() << " " << _index.column() << std::endl;
#endif

  auto retVal   = Wt::WItemDelegate::createEditor       ( _index, _flags );
  auto cw       = dynamic_cast< Wt::WContainerWidget* > ( retVal.get()   );
  auto lineEdit = dynamic_cast< Wt::WLineEdit* >        ( cw-> widget(0) );

  auto popup = retVal-> addChild( std::make_unique< GCW::Gui::AccountSuggestionPopup >() );
  popup-> forEdit( lineEdit, Wt::PopupTrigger::Editing /* | Wt::PopupTrigger::DropDownIcon */ );

  return retVal;

} // endstd::unique_ptr< Wt::WWidget > AccountDelegate::createEditor

/* * * * * * * * * * * * * * * * * * * * * * * * * * */

} // endnamespace {

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

auto GCW::Gui::AccountRegister::StatusBar:: setPresent    ( GCW_NUMERIC _value )-> void  { setText_( m_present    , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setFuture     ( GCW_NUMERIC _value )-> void  { setText_( m_future     , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setCleared    ( GCW_NUMERIC _value )-> void  { setText_( m_cleared    , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setReconciled ( GCW_NUMERIC _value )-> void  { setText_( m_reconciled , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setProjected  ( GCW_NUMERIC _value )-> void  { setText_( m_projected  , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setRowCount   ( int         _value )-> void  { setText_( m_rowCount   , _value ); }

GCW::Gui::AccountRegister::
AccountRegister( const std::string & _accountGuid )
{
  /*
  ** Look in gcw.css for styling.
  **
  */
  addStyleClass( "AccountRegister" );

  /*
  ** use a layout manager to install the table view into, so
  **  that the widget will fit and scroll properly.
  **
  */
  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );
  m_tableView = lw-> addWidget( std::make_unique< GCW::Gui::TableView >(), 1 );
//  tableView()-> setRowHeight( "20px" );

  /*
  ** Poke a status bar down at the bottom of the area.
  **
  */
  m_statusBar = lw-> addWidget( std::make_unique< StatusBar >() );

  /*
  ** Configure the table view.
  **
  */
  tableView()-> setSortingEnabled       ( false                                                         );
  tableView()-> setAlternatingRowColors ( true                                                          );
  tableView()-> setSelectionBehavior    ( Wt::SelectionBehavior::Rows                                   );
  tableView()-> setSelectionMode        ( Wt::SelectionMode::Single                                     );
//  tableView()-> setEditTriggers         ( Wt::EditTrigger::None                                         );
  tableView()-> setEditTriggers         ( Wt::EditTrigger::SingleClicked                                );
//  tableView()-> setEditOptions          ( Wt::EditOption::SingleEditor | Wt::EditOption::SaveWhenClosed );
  tableView()-> setEditOptions          ( Wt::EditOption::MultipleEditors | Wt::EditOption::LeaveEditorsOpen );
  tableView()-> setHeaderItemDelegate   ( std::make_shared< HeaderDelegate >()                          );
  tableView()-> setAttributeValue       ( "oncontextmenu","event.cancelBubble=true;event.returnValue=false;return false;" );
  tableView()-> mouseWentUp().connect   ( this, &AccountRegister::on_showPopup_triggered );

  /*
  ** set column delegates so the editors have assistance with list pickers and
  **  whatnot
  **
  */
  tableView()-> setItemDelegateForColumn ( 0, std::make_shared< DateDelegate       >() );
  tableView()-> setItemDelegateForColumn ( 1, std::make_shared< SuggestionDelegate >() );
  tableView()-> setItemDelegateForColumn ( 2, std::make_shared< SuggestionDelegate >() );
  tableView()-> setItemDelegateForColumn ( 3, std::make_shared< AccountDelegate    >() );
  tableView()-> setItemDelegateForColumn ( 4, std::make_shared< ReconcileDelegate  >() );
  tableView()-> setItemDelegateForColumn ( 5, std::make_shared< ValueDelegate      >() );
  tableView()-> setItemDelegateForColumn ( 6, std::make_shared< ValueDelegate      >() );
  tableView()-> setItemDelegateForColumn ( 7, std::make_shared< BalanceDelegate    >() );

  {
//    dateDelegate->
//      closeEditor().connect( [&]( Wt::WWidget* _widget, bool _save )
//      {
//        std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;
//
//      });


#ifdef NEVER
    dateDelegate->
      editorCreated().connect( [&]( int _row, int _column)
      {
        std::cout << __FILE__ << ":" << __LINE__
          << " row:" << _row
          << " col:" << _column
          << std::endl;

        for( int column = 0; column< tableView()-> model()-> columnCount(); column++ )
        {
          std::cout << __FILE__ << ":" << __LINE__
            << " row:" << _row
            << " col:" << column
            << std::endl;

          tableView()-> itemWidget( tableView()-> model()-> index( _row, column ) )-> addStyleClass( "active" );
        }

      });

    dateDelegate->
      editorClosed().connect( [&]( int _row, int _column )
      {
        std::cout << __FILE__ << ":" << __LINE__
          << " row:" << _row
          << " col:" << _column
          << std::endl;

        for( int column = 0; column< tableView()-> model()-> columnCount(); column++ )
        {
          std::cout << __FILE__ << ":" << __LINE__
            << " row:" << _row
            << " col:" << column
            << std::endl;

          tableView()-> itemWidget( tableView()-> model()-> index( _row, column ) )-> removeStyleClass( "active" );
        }

      });
#endif

  }


  tableView()-> headerClicked().connect( [=]( int col, Wt::WMouseEvent event )
  {
#ifdef NEVER
    if( tableView()-> selectedIndexes().size() == 0 )
      tableView()-> select( baseModel()-> index( 893, 0 ) );
    else
      tableView()-> clearSelection();
#endif
    std::cout << __FILE__ << ":" << __LINE__ << " " << col << std::endl;

  });

#ifdef NEVER
  /*
  ** This 'selectionChanged' procedure is 'clunky'.
  **
  ** This procedure is designed to respond to a row-selection
  **  change event.  When a different row is selected, we want
  **  any open editors to be closed, and the row selection to
  **  move to the newly selected row.
  **
  ** Right now the problem is with the 'select' command, where
  **  it calling 'select' cause this 'selectionChanged' event
  **  to fire again.  So, ther is a littl 'selecting' interlock
  **  built around it to try to prevent this weirdness.
  **
  ** The other problem with this routine is when 'selecting'
  **  a cell that is editable, the editor is immediately engaged
  **  but this 'selectionChanged' signal never fires... so we have
  **  to sort that out.
  **
  */
  tableView()->
    selectionChanged().connect( [=]()
    {
      std::cout << __FILE__ << ":" << __LINE__ << " selectionChanged" << std::endl;
    });
#endif

#ifdef CLICKED_FIRES_FROM_THE_TABLEVIEW_HANDLECLICK_EVENT_HANDLER_MIGHT_NOT_BE_USEFUL_HERE
  /*
  ** the 'clicked()' signal seems to fire even when an editor is open
  **
  */
  tableView()->
    clicked().connect( [=]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " clicked"
        << " row:" << _index.row()
        << " col:" << _index.column()
        << std::endl
        ;

        if( !tableView()-> isEditing( _index ) )
        {
          tableView()-> closeEditors();

          for( int column = 0; column< 7; column++ )
          {
            std::cout << __FILE__ << ":" << __LINE__ << " edit:" << column << std::endl;

            auto index = tableView()-> model()-> index( _index.row(), column );
            tableView()-> edit( index );
          }
        }

        else
        {
          std::cout << __FILE__ << ":" << __LINE__ << " already editing " << std::endl;

        }

    });
#endif

#ifdef KEYPRESSED_ONLY_FIRES_WHEN_EDITORS_ARE_NOT_OPEN
  tableView()->
    keyPressed().connect( [=]( Wt::WKeyEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << _event.charCode() << std::endl;
    });
#endif

#ifndef NEVER
  tableView()->
    clicked().connect( [=]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
    {
#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__ << " clicked"
        << " row:" << _index.row()
        << " col:" << _index.column()
        << std::endl
        ;
#endif

#ifdef NEVER
      if( m_clickedRow != -1
       && m_clickedCol != -1
        )
      {
        std::cout << __FILE__ << ":" << __LINE__ << " unselect:" << m_clickedRow << std::endl;

        for( int column = 0; column< tableView()-> model()-> columnCount(); column++ )
        {
          tableView()->
            itemWidget( tableView()-> model()-> index( m_clickedRow, column ) )->
              removeStyleClass( "active" );
        }

        if( m_clickedRow != _index.row()
          )
          tableView()-> closeEditors( true );
      }
#endif

      /*
      ** If we clicked on a different row, edit the whole row.
      **  if we clicked and it's the same row, then just ignore
      **  it.
      **
      */
      if( m_clickedRow != _index.row() )
      {
        m_clickedRow = _index.row();
        m_clickedCol = _index.column();
        editRow( _index.row() );
      }

#ifdef NEVER
      for( int column = 0; column< tableView()-> model()-> columnCount(); column++ )
      {
        std::cout << __FILE__ << ":" << __LINE__ << " select:" << m_clickedRow << std::endl;

        tableView()-> itemWidget( tableView()-> model()-> index( m_clickedRow, column ) )->
          addStyleClass( "active" );
      }
#endif

#ifdef NEVER
      std::cout << __FILE__ << ":" << __LINE__
        << " " << Wt::WApplication::instance()-> theme()-> activeClass()
        << std::endl;
#endif

//      tableView()-> clearSelection();

//      tableView()-> closeEditors();
    });
#endif

  m_baseModel       = std::make_shared< BaseModel                 >();
//  m_sortFilterModel = std::make_shared< Wt::WSortFilterProxyModel >();
  m_batchEditModel  = std::make_shared< Wt::WBatchEditProxyModel  >();
//
//  m_sortFilterModel-> setSourceModel( m_baseModel       );
//  m_sortFilterModel-> sort(0);
//  m_batchEditModel -> setSourceModel( m_sortFilterModel );
  m_batchEditModel -> setSourceModel( m_baseModel );

  baseModel()->
    goneDirty().connect( [&]( Wt::WModelIndex _index )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << _index.row() << std::endl;
      baseModel()-> refreshFromDisk();
//      m_batchEditModel -> setSourceModel( m_baseModel );
      std::cout << __FILE__ << ":" << __LINE__ << " " << _index.row() << std::endl;
    });


} // endGCW::AccountRegister::AccountRegister( const std::string & _accountGuid )

auto
GCW::Gui::AccountRegister::
setReadOnly( bool _state )-> void
{
  baseModel()-> setReadOnly( _state );

} // endsetReadOnly( bool _state = true )

auto
GCW::Gui::AccountRegister::
deleteRow( int _row )-> void
{
  auto splitGuid = baseModel()-> getSplitGuid( _row );
  auto transMan = GCW::Eng::Transaction::Manager();
  transMan.loadSplit( splitGuid );
  transMan.deleteTransaction();

  baseModel()-> refreshFromDisk();

} // enddeleteRow( int _row )-> void

auto
GCW::Gui::AccountRegister::
on_sortBy_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_sortBy_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_filterBy_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_filterBy_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_renamePage_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_renamePage_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_duplicate_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_duplicate_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_delete_triggered()-> void
{
  /*!
  ** by default, the user will be asked to delete
  **  an item from the register, unless they
  **  have chosen to never be asked.
  **
  ** \bug the logic here is not correct
  */
  static bool askThisSession = true;
         bool askForever     = GCW::Dbo::Prefrences::get().askOnDelete();

  /*
  ** ask sometimes
  */
  if( askThisSession || askForever )
  {
    /*
    ** build out a dialog box to prompt the user to delete or not
    **
    */
    auto msgBox = addChild( std::make_unique< Wt::WDialog >( TR("gcw.AccountRegister.delete.title") ) );
    auto templt = msgBox-> contents()-> addNew< Wt::WTemplate >( TR("gcw.AccountRegister.delete.contents") );
    msgBox-> setClosable( true );
    msgBox-> setMovable ( true );
    msgBox-> show();

    auto rememberAlways  = templt-> bindNew< Wt::WCheckBox   >( "rememberAlways" , TR("gcw.AccountRegister.delete.rem1"  ) );
    auto rememberSession = templt-> bindNew< Wt::WCheckBox   >( "rememberSession", TR("gcw.AccountRegister.delete.rem2"  ) );
    auto pbCancel        = templt-> bindNew< Wt::WPushButton >( "cancel"         , TR("gcw.AccountRegister.delete.cancel") );
    auto pbDelete        = templt-> bindNew< Wt::WPushButton >( "delete"         , TR("gcw.AccountRegister.delete.delete") );

    auto splitGuid = baseModel()-> getSplitGuid( m_rightClickRow );
    auto transMan = GCW::Eng::Transaction::Manager();
    transMan.loadSplit( splitGuid );

    templt-> bindString( "date"  , transMan.getDate().toString( GCW_DATE_FORMAT_DISPLAY ) );
    templt-> bindString( "desc"  , transMan.getDescription  () );
    templt-> bindString( "amount", transMan.getValueAsString() );

    pbCancel-> clicked().connect( msgBox, &Wt::WDialog::reject );
    pbDelete-> clicked().connect( msgBox, &Wt::WDialog::accept );

    /*
    ** when this option is selected, disable the other one
    */
    rememberAlways->
      clicked().connect( [rememberSession,rememberAlways]()
      {
        rememberSession-> setDisabled( rememberAlways-> checkState() == Wt::CheckState::Checked );
      });

    /*
    ** When the dialog finishes, it is either accepted or rejected.
    **  In either case, the dialog will be removed from the addChild
    **  from earlier so we don't got no memory leaks.
    **
    */
    msgBox->
      finished().connect( [this,rememberSession,msgBox]( Wt::DialogCode _code )
      {
        if( _code == Wt::DialogCode::Accepted )
        {
          askThisSession = rememberSession-> checkState() == Wt::CheckState::Checked;

          deleteRow( m_rightClickRow );

        }
        removeChild( msgBox );
      });

  } // endif( ..askFirst.. )

  /*
  ** don't ask, just delete
  */
  else
  {
    deleteRow( m_rightClickRow );
  }

} // endon_delete_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_removeSplits_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_removeSplits_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_enter_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_enter_triggered()-> void;

auto
GCW::Gui::AccountRegister::
on_cancel_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_cancel_triggered()-> void;

auto
GCW::Gui::AccountRegister::
on_manageDocument_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;


} // endon_manageDocument_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_openDocument_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_openDocument_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_blankTransaction_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_blankTransaction_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_goDate_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_goDate_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_splitTransaction_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_splitTransaction_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_editExchangeRate_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_editExchangeRate_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_schedule_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_schedule_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_jump_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_jump_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_assignPayment_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_assignPayment_triggered()-> void

auto
GCW::Gui::AccountRegister::
on_showPopup_triggered( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void
{
  if( _event.button() == Wt::MouseButton::Right )
  {
    m_rightClickRow = _index.row();
    m_rightClickCol = _index.column();

    /*
    ** Set up the items in the pop-up menu
    **  (some of the items are dependent on which row was clicked on
    **   so we dump everything from the popup and reload)
    **
    */
    while( m_popupMenu.count() )
      m_popupMenu.removeItem( m_popupMenu.itemAt(0) );

#ifdef NEVER
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.SortBy"     ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.FilterBy"   ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.RenamePage" ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addSeparator();
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.Duplicate"  ), std::make_unique< Wt::WText >() )-> setDisabled( true );
#endif

    // delete
    {
      auto item = m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.Delete"), this, &AccountRegister::on_delete_triggered );

      /*
      ** delete doesn't work on the 'new' line (need a split guid)
      */
      if( !(baseModel()-> isDeletable( _index )) )
        item-> setDisabled( true );
    }

#ifdef NEVER
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.RemoveSplits"     ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addSeparator();
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.Enter"            ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.Cancel"           ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addSeparator();
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.ManageDocument"   ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.OpenDocument"     ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addSeparator();
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.Jump"             ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addSeparator();
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.BlankTransaction" ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.GoDate"           ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.SplitTransaction" ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.EditExchangeRate" ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.Schedule"         ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.Jump"             ), std::make_unique< Wt::WText >() )-> setDisabled( true );
    m_popupMenu.addSeparator();
    m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.AssignPayment"    ), std::make_unique< Wt::WText >() )-> setDisabled( true );
#endif

    // Select the item, if it was not yet selected.
    if( !tableView()-> isSelected( _index ) )
    {
      editRow( _index.row() );
    }

    if( m_popupMenu.isHidden() )
    {
      m_popupMenu.popup( _event );
    }
    else
    {
      m_popupMenu.hide();
    }

  } // endif( ..right-click.. )

} // endon_showPopup_triggered( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void


auto
GCW::Gui::AccountRegister::
setAccountGuid( const std::string & _accountGuid )-> void
{
  m_accountGuid = _accountGuid;

  baseModel()-> setAccountGuid( _accountGuid );

  loadData();

  /*
  ** Scroll to the bottom of the view, and select the last row.
  **
  */
  editRow( lastIndex().row() );

} // endsetAccountGuid( const std::string & _accountGuid )-> void

auto
GCW::Gui::AccountRegister::
lastIndex()-> Wt::WModelIndex
{
  return baseModel()-> index( baseModel()-> rowCount() -1, 0 );

} // endlastIndex()-> Wt::WModelIndex

auto
GCW::Gui::AccountRegister::
loadData()-> void
{
  tableView()-> setModel( m_baseModel );

  // 0 = Date
  tableView()-> setColumnWidth    ( 0, "150px"                   );
  tableView()-> setHeaderAlignment( 0, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 0, Wt::AlignmentFlag::Right  );

  // 1 = Action/Num
  tableView()-> setColumnWidth    ( 1,  "50px"                   );
  tableView()-> setHeaderAlignment( 1, Wt::AlignmentFlag::Center );
  tableView()-> setColumnAlignment( 1, Wt::AlignmentFlag::Center );

  // 2 = Memo/Description
  tableView()-> setColumnWidth    ( 2,   "99%"                   );
  tableView()-> setHeaderAlignment( 2, Wt::AlignmentFlag::Left   );
  tableView()-> setColumnAlignment( 2, Wt::AlignmentFlag::Left   );

  // 3 = Account/Transfer
  tableView()-> setColumnWidth    ( 3, "150px"                   );
  tableView()-> setHeaderAlignment( 3, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 3, Wt::AlignmentFlag::Right  );

  // 4 = Reconciliation
  tableView()-> setColumnWidth    ( 4,  "25px"                   );
  tableView()-> setHeaderAlignment( 4, Wt::AlignmentFlag::Center );
  tableView()-> setColumnAlignment( 4, Wt::AlignmentFlag::Center );

  // 5 = Debit
  tableView()-> setColumnWidth    ( 5, "100px"                   );
  tableView()-> setHeaderAlignment( 5, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 5, Wt::AlignmentFlag::Right  );

  // 6 = Credit
  tableView()-> setColumnWidth    ( 6, "100px"                   );
  tableView()-> setHeaderAlignment( 6, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 6, Wt::AlignmentFlag::Right  );

  // 7 = Balance
  tableView()-> setColumnWidth    ( 7, "100px"                   );
  tableView()-> setHeaderAlignment( 7, Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( 7, Wt::AlignmentFlag::Right  );

  statusBar()-> setPresent    ( baseModel()-> present    () );
  statusBar()-> setProjected  ( baseModel()-> projected  () );
  statusBar()-> setReconciled ( baseModel()-> reconciled () );
  statusBar()-> setFuture     ( baseModel()-> future     () );
  statusBar()-> setCleared    ( baseModel()-> cleared    () );
  statusBar()-> setRowCount   ( baseModel()-> rowCount   () );

} // endloadData()-> void

//auto
//GCW::Gui::AccountRegister::
//editRow( Wt::WModelIndex _index )-> void
//{
//  tableView()-> closeEditors( true );
//  ( _index.row() );
//
//} // endeditRow( Wt::WModelIndex _index )-> void

auto
GCW::Gui::AccountRegister::
editRow( int _row )-> void
{
  /*
  ** If the row we're editing ~can~ be edited, then
  **  we want to make sure we un-select any other rows
  **  that may still be selected
  **
  */
  if( !baseModel()-> isReadOnly( _row ) )
    tableView()-> clearSelection();

  /*
  ** Close all the editor then scroll down
  **  to that 0-col index row and make sure
  **  it is in view.
  **
  */
  tableView()-> closeEditors( true );
  {
    auto index = baseModel()-> index( _row, 0 );
    tableView()-> scrollTo( index );
  }

  for( int column=0; column< baseModel()-> columnCount(); column++ )
  {
    auto index = baseModel()-> index( _row, column );
    tableView()-> edit( index );
  }

} // endeditRow( int _row )-> void

auto
GCW::Gui::AccountRegister::
toJson() const-> Wt::Json::Object
{
  Wt::Json::Object jobj;

  return jobj;
}

auto
GCW::Gui::AccountRegister::
fromJson( const Wt::Json::Object & _jobj )-> bool
{
  return true;
}



void
GCW::Gui::AccountRegister::
test()
{
  std::cout << __FILE__ << ":" << __LINE__ << " ::test::" << std::endl;

  std::cout << __FILE__ << ":" << __LINE__ << " " << tableView()-> selectedIndexes().size() << std::endl;

  auto selectedIndex = *tableView()-> selectedIndexes().begin();

  if( selectedIndex.isValid() )
  {

    std::cout << __FILE__ << ":" << __LINE__ << " " << tableView()-> selectedIndexes().size() << std::endl;

  }


} // endvoid GCW::Gui::AccountRegister::test()




