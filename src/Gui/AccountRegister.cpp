#line 2 "src/Gui/AccountRegister.cpp"

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

} // endnamespace {

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

auto GCW::Gui::AccountRegister::StatusBar:: setPresent    ( GCW_NUMERIC _value )-> void  { setText_( m_present    , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setFuture     ( GCW_NUMERIC _value )-> void  { setText_( m_future     , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setCleared    ( GCW_NUMERIC _value )-> void  { setText_( m_cleared    , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setReconciled ( GCW_NUMERIC _value )-> void  { setText_( m_reconciled , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setProjected  ( GCW_NUMERIC _value )-> void  { setText_( m_projected  , _value ); }
auto GCW::Gui::AccountRegister::StatusBar:: setRowCount   ( int         _value )-> void  { setText_( m_rowCount   , _value ); }


/* * * * * * * * * * * * * * * * * * * * * * * * * * */


GCW::Gui::AccountRegister::
AccountRegister( const std::string & _accountGuid )
{
  /*
  ** see; gcw.css for styling.
  */
  addStyleClass( "AccountRegister" );

  /*
  ** use a layout manager to install the table view into, so
  **  that the widget will fit and scroll properly.
  */
  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );
  m_tableView = lw-> addWidget( std::make_unique< GCW::Gui::TableView >(), 1 );
//  tableView()-> setRowHeight( "20px" );

  /*
  ** Poke a status bar down at the bottom of the area.
  */
  m_statusBar = lw-> addWidget( std::make_unique< StatusBar >() );

  /*
  ** Configure the table view.
  */
  tableView()-> setSortingEnabled       ( false                                                         );
  tableView()-> setAlternatingRowColors ( true                                                          );
  tableView()-> setSelectionBehavior    ( Wt::SelectionBehavior::Rows                                   );
  tableView()-> setSelectionMode        ( Wt::SelectionMode::Single                                     );
//  tableView()-> setEditTriggers         ( Wt::EditTrigger::None                                         );
  tableView()-> setEditTriggers         ( Wt::EditTrigger::SingleClicked                                );
//  tableView()-> setEditOptions          ( Wt::EditOption::SingleEditor | Wt::EditOption::SaveWhenClosed );
  tableView()-> setEditOptions          ( Wt::EditOption::MultipleEditors | Wt::EditOption::LeaveEditorsOpen );
  tableView()-> setHeaderItemDelegate   ( std::make_shared< AccountRegisterEditor::HeaderDelegate >()   );

  /*
  ** in order to allow right-click in the browser this oncontextmenu
  **  attribute must be set in the table which allows Wt to pick up the
  **  right-click event.
  */
  tableView()-> setAttributeValue    ( "oncontextmenu","event.cancelBubble=true;event.returnValue=false;return false;" );
  tableView()-> mouseWentUp().connect( this, &AccountRegister::on_showPopup_triggered );

  /*
  ** set column delegates so the editors have assistance with list pickers and
  **  whatnot
  */
  editor().setTableView( tableView() );

  tableView()-> headerClicked().connect( [=]( int col, Wt::WMouseEvent event )
  {
#ifdef NEVER
    if( tableView()-> selectedIndexes().size() == 0 )
      tableView()-> select( baseModel()-> index( 893, 0 ) );
    else
      tableView()-> clearSelection();
#endif

    std::cout << __FILE__ << ":" << __LINE__ << " headerClicked:" << col << std::endl;

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
  */
  tableView()->
    selectionChanged().connect( [=]()
    {
      std::cout << __FILE__ << ":" << __LINE__
        << " selectionChanged"
        << std::endl;
    });
#endif

#ifdef KEYPRESSED_ONLY_FIRES_WHEN_EDITORS_ARE_NOT_OPEN
  tableView()->
    keyPressed().connect( [=]( Wt::WKeyEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << _event.charCode() << std::endl;
    });
#endif

  tableView()-> clicked().connect( this,  &AccountRegister::on_tableView_clicked );

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
//      std::cout << __FILE__ << ":" << __LINE__ << " " << _index.row() << std::endl;
//      baseModel()-> refreshFromDisk();
//      m_batchEditModel -> setSourceModel( m_baseModel );
//      std::cout << __FILE__ << ":" << __LINE__ << " " << _index.row() << std::endl;
    });


} // endGCW::AccountRegister::AccountRegister( const std::string & _accountGuid )


auto
GCW::Gui::AccountRegister::
on_tableView_clicked( Wt::WModelIndex _index, Wt::WMouseEvent _event )-> void
{
#ifdef NEVER
 std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__
   << " index("     << _index.row()         << "," << _index.column()         << ")"
   << " m_clicked(" << m_clickedIndex.row() << "," << m_clickedIndex.column() << ")"
   << std::endl
   ;
#endif

  /*
  ** do the select-row business.  this may seem somewhat redundant to call
  **  selectRow again here, since clicking on the row causes it to be selected,
  **  but we have additional logic we want to employ.
  */
  do_selectRow( _index );

} // endtableView()->clicked().connect( [=]( Wt::WModelIndex _index, Wt::WMouseEvent _event )


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

    auto splitGuid = baseModel()-> getSplitGuid( m_rightClickIndex.row() );
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
    */
    msgBox->
      finished().connect( [this,rememberSession,msgBox]( Wt::DialogCode _code )
      {
        if( _code == Wt::DialogCode::Accepted )
        {
          askThisSession = rememberSession-> checkState() == Wt::CheckState::Checked;

          deleteRow( m_rightClickIndex.row() );

        }
        removeChild( msgBox );
      });

  } // endif( ..askFirst.. )

  /*
  ** don't ask, just delete
  */
  else
  {
    deleteRow( m_rightClickIndex.row() );
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
  /*
  ** pop-up is only on right-click
  */
  if( _event.button() != Wt::MouseButton::Right )
    return;

  /*
  ** remember
  */
  m_rightClickIndex = _index;

  /*
  ** Set up the items in the pop-up menu
  **  (some of the items are dependent on which row was clicked on
  **   so we dump everything from the popup and reload)
  **
  ** NOTE: we're doing this because m_popupMenu is local (ie; not
  **  a pointer!) so it is persistent within this object. So,
  **  anything we do in it needs to be reset before we do anything
  **  else.
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
    editRow( _index );
  }

  if( m_popupMenu.isHidden() )
  {
    m_popupMenu.popup( _event );
  }
  else
  {
    m_popupMenu.hide();
  }

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
  */
  do_selectRow( lastIndex() );

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
do_selectRow( Wt::WModelIndex _index )-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " " << __FUNCTION__ << "(" << _index.row() << ")"
    << " ro:" << baseModel()-> isReadOnly( _index.row() )
    << " i: ("  << _index.row() << "," << _index.column() << ")"
    << " si: (" << m_selectIndex.row() << "," << m_selectIndex.column() << ")"
    << std::endl;
#endif

  /*
  ** if the row hasn't changed, do nothing
  */
  if( m_selectIndex.row() == _index.row() )
    return;

  tableView()-> clearSelection();
  tableView()-> closeEditors( true );
  tableView()-> scrollTo( _index );
  tableView()-> select( _index, Wt::SelectionFlag::ClearAndSelect );

  m_selectIndex = _index;

  if( !baseModel()-> isReadOnly( _index.row() ) )
    editRow( _index );

} // enddo_selectRow( Wt::WModelIndex _index )-> void

auto
GCW::Gui::AccountRegister::
editRow( Wt::WModelIndex _index )-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " " << __FUNCTION__ << "(" << _index.row() << "," << _index.column() << ")"
    << " ro:"     << baseModel()-> isReadOnly( _index.row() )
    << " sel:"    << tableView()-> selectedIndexes().size()
    << " selrow:" << tableView()-> selectedIndexes().begin()-> row()
    << std::endl;
#endif

  /*
  ** If the row we're editing ~can~ be edited, then
  **  we want to make sure we un-select any other rows
  **  that may still be selected
  */
//  if( !baseModel()-> isReadOnly( _row ) )
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

  } // endif( !baseModel()-> isReadOnly( _index.row() ) )

  /*
  **  make sure it is in view.
  */
  {
    auto index = baseModel()-> index( _index.row(), 0 );
    tableView()-> scrollTo( index );
  }

  for( int column=0; column< baseModel()-> columnCount(); column++ )
  {
    auto index = baseModel()-> index( _index.row(), column );
    tableView()-> edit( index );
  }

} // endeditRow( int _index.row() )-> void

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




