#line 2 "src/Gui/AccountRegister/Widget.cpp"

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
#include "SuggestionPopup.h"
#include "Widget.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * */

auto
GCW::Gui::AccountRegister::Widget::
init()-> void
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

  /*
  ** Poke a tool bar up at the top of the area.
  */
  m_toolBar = lw-> addWidget( std::make_unique< ToolBar >() );



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
//  tableView()-> setAlternatingRowColors ( true                                                          ); /// \todo need to redo this
  tableView()-> setSelectionBehavior    ( Wt::SelectionBehavior::Rows                                   );
  tableView()-> setSelectionMode        ( Wt::SelectionMode::Single                                     );
//  tableView()-> setEditTriggers         ( Wt::EditTrigger::None                                         );
  tableView()-> setEditTriggers         ( Wt::EditTrigger::SingleClicked                                );
//  tableView()-> setEditOptions          ( Wt::EditOption::SingleEditor | Wt::EditOption::SaveWhenClosed );
  tableView()-> setEditOptions          ( Wt::EditOption::MultipleEditors | Wt::EditOption::LeaveEditorsOpen );

  /*
  ** in order to allow right-click in the browser this oncontextmenu
  **  attribute must be set in the table which allows Wt to pick up the
  **  right-click event.
  */
  tableView()-> setAttributeValue    ( "oncontextmenu","event.cancelBubble=true;event.returnValue=false;return false;" );
  tableView()-> mouseWentUp().connect( this, &Widget::on_showPopup_triggered );

  /*
  ** set the column delegates/editors
  */
  Editor::applyDelegates( tableView() );

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
  **  to fire again.  So, there is a little 'selecting' interlock
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

#ifdef KEYPRESSED_ONLY_FIRES_WHEN_EDITORS_ARE_NOT_OPEN_NOT_USEFUL_HERE
  tableView()->
    keyPressed().connect( [=]( Wt::WKeyEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " " << _event.charCode() << std::endl;
    });
#endif

  tableView()-> clicked().connect( this,  &Widget::on_tableView_clicked );

  m_baseModel       = std::make_shared< BaseModel                 >();
  m_sortFilterModel = std::make_shared< Wt::WSortFilterProxyModel >();
  m_batchEditModel  = std::make_shared< Wt::WBatchEditProxyModel  >();
//
//  m_sortFilterModel-> setSourceModel( m_baseModel       );
//  m_sortFilterModel-> sort(0);
//  m_batchEditModel -> setSourceModel( m_sortFilterModel );
//  m_batchEditModel -> setSourceModel( m_baseModel );

  baseModel()->
    goneDirty().connect( [&]( Wt::WModelIndex _index )
    {
//      std::cout << __FILE__ << ":" << __LINE__ << " " << _index.row() << std::endl;
//      baseModel()-> refreshFromDisk();
//      m_batchEditModel -> setSourceModel( m_baseModel );
//      std::cout << __FILE__ << ":" << __LINE__ << " " << _index.row() << std::endl;
    });

} // endinit()-> void


GCW::Gui::AccountRegister::Widget::
Widget()
{
  init();


} // endGCW::AccountRegister::AccountRegister( const std::string & _accountGuid )


auto
GCW::Gui::AccountRegister::Widget::
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
GCW::Gui::AccountRegister::Widget::
setReadOnly( bool _state )-> void
{
  baseModel()-> setReadOnly( _state );

} // endsetReadOnly( bool _state = true )

auto
GCW::Gui::AccountRegister::Widget::
deleteRow( int _row )-> void
{
  // BUGBUG working on the register, fix this!

  auto splitGuid = baseModel()-> getSplitGuid( _row );
//  auto transMan = GCW::Eng::Transaction::Manager();
//  transMan.loadSplit( splitGuid );
//  transMan.deleteTransaction();

  baseModel()-> refreshFromDisk();

} // enddeleteRow( int _row )-> void

auto
GCW::Gui::AccountRegister::Widget::
on_sortBy_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_sortBy_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_filterBy_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_filterBy_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_renamePage_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_renamePage_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_duplicate_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_duplicate_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
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
    msgBox-> show(); // exec() blocks other users, show() doesn't

    auto rememberAlways  = templt-> bindNew< Wt::WCheckBox   >( "rememberAlways" , TR("gcw.AccountRegister.delete.rem1"  ) );
    auto rememberSession = templt-> bindNew< Wt::WCheckBox   >( "rememberSession", TR("gcw.AccountRegister.delete.rem2"  ) );
    auto pbCancel        = templt-> bindNew< Wt::WPushButton >( "cancel"         , TR("gcw.AccountRegister.delete.cancel") );
    auto pbDelete        = templt-> bindNew< Wt::WPushButton >( "delete"         , TR("gcw.AccountRegister.delete.delete") );

    auto splitGuid = baseModel()-> getSplitGuid( m_rightClickIndex.row() );
//    auto transMan = GCW::Eng::Transaction::Manager();
//    transMan.loadSplit( splitGuid );

//    templt-> bindString( "date"  , transMan.getDateAsString () );
//    templt-> bindString( "desc"  , transMan.getDescription  () );
//    templt-> bindString( "amount", transMan.getValueAsString() );

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
GCW::Gui::AccountRegister::Widget::
on_removeSplits_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_removeSplits_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_enter_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_enter_triggered()-> void;

auto
GCW::Gui::AccountRegister::Widget::
on_cancel_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_cancel_triggered()-> void;

auto
GCW::Gui::AccountRegister::Widget::
on_manageDocument_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;


} // endon_manageDocument_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_openDocument_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_openDocument_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_blankTransaction_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_blankTransaction_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_goDate_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_goDate_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_splitTransaction_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_splitTransaction_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_editExchangeRate_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_editExchangeRate_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_schedule_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_schedule_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_jump_triggered()-> void
{
  /*
  ** use a transaction manager so we can find the other split guid
  */
  auto transMan = GCW::Eng::Transaction::Manager();
  transMan.loadSplit( baseModel()-> getSplitGuid( m_rightClickIndex.row() ) );

  /*!
  ** \todo should deal with multiple splits
  **
  ** This function will emit the guid of the account of the 'other'
  **  split used in this transaction.  But, a transaction may contain
  **  multiple splits.  In that instance, this jump routine should
  **  make some different decisions about where to jump.  In gnucash,
  **  it indicates that the jump will jump to the 'highest value'
  **  split... that could work.
  */
  jumpToAccount().emit( transMan.thatSplit()-> guid() );

} // endon_jump_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_edit_triggered()-> void
{


} // endon_edit_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
on_assignPayment_triggered()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endon_assignPayment_triggered()-> void

auto
GCW::Gui::AccountRegister::Widget::
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
    auto item = m_popupMenu.addItem( TR( "gcw.AccountRegister.Popup.Delete"), this, &Widget::on_delete_triggered );

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
#endif

  m_popupMenu.addSeparator();

  // jump
  {
    /*
    ** create the menu item
    */
    auto item =
      m_popupMenu
      .addItem
      (
       TR( "gcw.AccountRegister.Popup.Jump" ),
       this,
       &Widget::on_jump_triggered
      );

    if( !(baseModel()-> isJumpable( _index )) )
      item-> setDisabled( true );
  }

  // edit
//  {
//    auto item =
//      m_popupMenu
//      .addItem
//      (
//       TR( "gcw.AccountRegister.Popup.edit" ),
//       this,
//       &Widget::on_edit_triggered
//      );
//  }



#ifdef NEVER
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
    tableView()-> select( _index, Wt::SelectionFlag::ClearAndSelect );
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
GCW::Gui::AccountRegister::Widget::
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
GCW::Gui::AccountRegister::Widget::
setDoubleLine( bool _state )-> void
{

  baseModel()-> setDoubleLine( _state );

  setAccountGuid( m_accountGuid );

} // endsetDoubleLine( bool _state )-> void

auto
GCW::Gui::AccountRegister::Widget::
lastIndex()-> Wt::WModelIndex
{
  return baseModel()-> index( baseModel()-> rowCount() -1, 0 );

} // endlastIndex()-> Wt::WModelIndex

auto
GCW::Gui::AccountRegister::Widget::
loadData()-> void
{
  tableView()-> setModel( m_baseModel );

  // 0 = Date
  tableView()-> setColumnWidth    ( asInt( Col::DATE        ), "125px"                   );
  tableView()-> setHeaderAlignment( asInt( Col::DATE        ), Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( asInt( Col::DATE        ), Wt::AlignmentFlag::Right  );

  // 1 = Action/Num
  tableView()-> setColumnWidth    ( asInt( Col::ACTION      ), "50px"                    );
  tableView()-> setHeaderAlignment( asInt( Col::ACTION      ), Wt::AlignmentFlag::Center );
  tableView()-> setColumnAlignment( asInt( Col::ACTION      ), Wt::AlignmentFlag::Center );

  // 2 = Memo/Description
  tableView()-> setColumnWidth    ( asInt( Col::DESCRIPTION ), "99%"                     );
  tableView()-> setHeaderAlignment( asInt( Col::DESCRIPTION ), Wt::AlignmentFlag::Left   );
  tableView()-> setColumnAlignment( asInt( Col::DESCRIPTION ), Wt::AlignmentFlag::Left   );

  // 3 = Account/Transfer
  tableView()-> setColumnWidth    ( asInt( Col::TRANSFER    ), "150px"                   );
  tableView()-> setHeaderAlignment( asInt( Col::TRANSFER    ), Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( asInt( Col::TRANSFER    ), Wt::AlignmentFlag::Right  );

  // 4 = Reconciliation
  tableView()-> setColumnWidth    ( asInt( Col::RECONCILE   ), "25px"                    );
  tableView()-> setHeaderAlignment( asInt( Col::RECONCILE   ), Wt::AlignmentFlag::Center );
  tableView()-> setColumnAlignment( asInt( Col::RECONCILE   ), Wt::AlignmentFlag::Center );

  // 5 = Debit
  tableView()-> setColumnWidth    ( asInt( Col::DEBIT       ), "85px"                    );
  tableView()-> setHeaderAlignment( asInt( Col::DEBIT       ), Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( asInt( Col::DEBIT       ), Wt::AlignmentFlag::Right  );

  // 6 = Credit
  tableView()-> setColumnWidth    ( asInt( Col::CREDIT      ), "85px"                    );
  tableView()-> setHeaderAlignment( asInt( Col::CREDIT      ), Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( asInt( Col::CREDIT      ), Wt::AlignmentFlag::Right  );

  // 7 = Balance
  tableView()-> setColumnWidth    ( asInt( Col::BALANCE     ), "85px"                    );
  tableView()-> setHeaderAlignment( asInt( Col::BALANCE     ), Wt::AlignmentFlag::Right  );
  tableView()-> setColumnAlignment( asInt( Col::BALANCE     ), Wt::AlignmentFlag::Right  );

  statusBar()-> setPresent    ( baseModel()-> present    () );
  statusBar()-> setProjected  ( baseModel()-> projected  () );
  statusBar()-> setReconciled ( baseModel()-> reconciled () );
  statusBar()-> setFuture     ( baseModel()-> future     () );
  statusBar()-> setCleared    ( baseModel()-> cleared    () );
  statusBar()-> setRowCount   ( baseModel()-> splitCount () );

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
GCW::Gui::AccountRegister::Widget::
do_selectRow( Wt::WModelIndex _index )-> void
{
  /*
  ** if the row hasn't changed, do nothing
  */
  if( m_selectIndex.isValid() )
    if( m_selectIndex.row() == _index.row() )
      return;

  m_selectIndex = _index;

#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " " << __FUNCTION__ << "(" << _index.row() << ")"
    << " isR/O:" << baseModel()-> isReadOnly( _index.row() )
    << " i("  << _index.row() << "," << _index.column() << ")"
    << " si(" << m_selectIndex.row() << "," << m_selectIndex.column() << ")"
    << std::endl;
  wApp-> processEvents();
#endif

  tableView()-> closeEditors( true );
  tableView()-> scrollTo( _index );
//  tableView()-> select( _index, Wt::SelectionFlag::ClearAndSelect );

  if( !baseModel()-> isReadOnly( _index.row() ) )
    editRow( _index );

} // enddo_selectRow( Wt::WModelIndex _index )-> void

auto
GCW::Gui::AccountRegister::Widget::
selectSplit( const std::string & _guid )-> void
{
  auto row = baseModel()-> getSplitRow( _guid );

  if( row > -1 )
  {
    /*!
    ** \todo determine best method to use here - table is not 'selecting/highlighting' properly
    */
    tableView()-> clicked().emit( baseModel()-> index( row, 0 ), Wt::WMouseEvent() );
//    on_tableView_clicked( baseModel()-> index( row, 0 ), Wt::WMouseEvent() );
  }

} // enddo_selectRow( Wt::WModelIndex _index )-> void

auto
GCW::Gui::AccountRegister::Widget::
editRow( Wt::WModelIndex _index )-> void
{
#ifdef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " " << __FUNCTION__ << "(" << _index.row() << "," << _index.column() << ")"
    << " ro:"     << baseModel()-> isReadOnly( _index.row() )
    << " sel:"    << tableView()-> selectedIndexes().size()
    << std::endl;
#endif

//  tableView()-> clearSelection();
  tableView()-> closeEditors( true );
  Editor editor( tableView() );
  editor.editRow( _index );

} // endeditRow( Wt::WModelIndex _index )-> void

auto
GCW::Gui::AccountRegister::Widget::
toJson() const-> Wt::Json::Object
{
  Wt::Json::Object jobj;

  return jobj;
}

auto
GCW::Gui::AccountRegister::Widget::
fromJson( const Wt::Json::Object & _jobj )-> bool
{
  return true;
}



void
GCW::Gui::AccountRegister::Widget::
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


