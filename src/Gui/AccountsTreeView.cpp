#line 2 "src/Gui/AccountsTreeView.cpp"

//#define EDIT_FORM_AS_POPUP_DIALOG
#define EDIT_FORM_AS_SPLIT_PAGE


#include <any>

#include <Wt/Json/Array.h>
#include <Wt/Json/Parser.h>
#include <Wt/Json/Serializer.h>
#include <Wt/WText.h>
#include <Wt/WTreeTableNode.h>
#include <Wt/WMessageBox.h>

#include "../define.h"
#include "AccountEditor.h"
#include "AccountsTreeView.h"

GCW::Gui::AccountsTreeView::
AccountsTreeView( const std::string & _selectedAccountGuid, int _columnCount )
: m_columnCount( _columnCount )
{
  init();

  setSelected( _selectedAccountGuid );

} // endAccountsTreeView( const std::string & _selectedAccountGuid, int _columnCount )

GCW::Gui::AccountsTreeView::
AccountsTreeView( int _columnCount )
: m_columnCount( _columnCount )
{
  init();

} // endAccountsTreeView( int _columnCount )

auto
GCW::Gui::AccountsTreeView::
init()-> void
{
  addStyleClass( "AccountsTreeView" );

  m_gridLayout = setLayout( std::make_unique< Wt::WGridLayout >() );
//  lw-> setSpacing( 0 );

  m_view = m_gridLayout-> addWidget( std::make_unique< Wt::WTreeView >(), 0, 0 );

  view()-> setSelectionBehavior( Wt::SelectionBehavior::Rows );
  view()-> setSelectionMode(     Wt::SelectionMode::Single   );
  view()-> setAlternatingRowColors( true );
  view()-> doubleClicked().connect( this, &AccountsTreeView::on_doubleClicked );
  view()-> setAttributeValue( "oncontextmenu","event.cancelBubble=true;event.returnValue=false;return false;" );
  view()-> mouseWentUp().connect( this, &AccountsTreeView::on_showPopup_triggered );

  std::vector< std::string > cols =
  {
    "accountcode"       ,
    "accountcolor"      ,
    "accountname"       ,
    "balance"           ,
    "balancelimit"      ,
    "balanceperiod"     ,
    "balanceusd"        ,
    "cleared"           ,
    "clearedusd"        ,
    "commodity"         ,
    "description"       ,
    "futureminimum"     ,
    "futureminimumusd"  ,
    "hidden"            ,
    "lastnum"           ,
    "lastreconciledate" ,
    "notes"             ,
    "openingbalance"    ,
    "placeholder"       ,
    "present"           ,
    "presentusd"        ,
    "reconciled"        ,
    "reconciledusd"     ,
    "taxinfo"           ,
    "total"             ,
    "totalperiod"       ,
    "totalusd"          ,
    "type"
  };

  for( int i=0; i< m_columnCount; i++ )
    m_columns.push_back( TR8( "gcw.AccountsTreeView.column." + cols.at(i) ) );

  setModel();

  loadConfig();

  view()-> collapsed        ().connect( this, &AccountsTreeView::saveConfig    );
  view()-> expanded         ().connect( this, &AccountsTreeView::saveConfig    );
  view()-> selectionChanged ().connect( this, &AccountsTreeView::saveConfig    );

} // endinit()-> void

auto
GCW::Gui::AccountsTreeView::
on_showPopup_triggered( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void
{
  if( _event.button() == Wt::MouseButton::Right )
  {
    std::cout << __FILE__ << ":" << __LINE__ << " right-click pop-up menu" << std::endl;

#ifdef NEVER
    /*
    ** Set up the items in the pop-up menu
    **
    */
    while( m_popup.count() )
      m_popup.removeItem( m_popup.itemAt(0) );

    m_popup.addItem("icons/folder_new.gif", "Create a New Folder", this, &WEB::FolderTableView::on_pbAddFolder_triggered );
    m_popup.addItem("Rename", this, &WEB::FolderTableView::on_pbRenameItem_triggered ); //->setCheckable(true);

    std::string fileName = Wt::asString(m_tableView.model()-> data( index.row(), 0 )).toUTF8();
    COUT_( fileName );

    if( isFolder(fileName) )
      m_popup.addItem("Delete this Folder", this, &WEB::FolderTableView::on_pbDeleteItem_triggered );
    else
      m_popup.addItem("Delete this File", this, &WEB::FolderTableView::on_pbDeleteItem_triggered );

    m_popup.addSeparator();
    m_popup.addItem("Upload a file", this, &WEB::FolderTableView::on_pbUploadFile_triggered );
    m_popup.addItem("Refresh", this, &WEB::FolderTableView::refresh );
    m_popup.addSeparator();
    m_popup.addItem("Properties", this, &WEB::FolderTableView::on_pbProperties_triggered );

    // Select the item, if it was not yet selected.
    if( !m_tableView.isSelected(index) )
    {
      m_tableView.clearSelection();
      m_tableView.select(index);
    }

    if( m_popup.isHidden() )
    {
      m_popup.popup(event);
    }
    else
    {
      m_popup.hide();
    }

#endif

  }

} // endon_showPopup_triggered( Wt::WModelIndex _index, Wt::WMouseEvent _event )


/*!
** \return GUID String
*/
std::string
GCW::Gui::AccountsTreeView::
selectedAccount() const
{
  std::string retVal;

  /*
  ** The tree-view should have only one selection.  Grab
  **  its index and get to the User data that carries the
  **  GUID of the selected item.
  **
  */
  auto selected = view()-> selectedIndexes();
  if( selected.size() == 1 )
    retVal =
      Wt::asString
      (
       model()-> data( *selected.begin(),
       Wt::ItemDataRole::User
      )
    ).toUTF8();

  return retVal;

} // endstd::string GCW::Gui::AccountsTreeView::selectedAccount()

void
GCW::Gui::AccountsTreeView::
editAccount( const std::string & _accountGuid )
{
  if( _accountGuid == "" )
    return;

#ifdef EDIT_FORM_AS_POPUP_DIALOG
  GCW::Gui::AccountEditorDialog dialog( "Edit Account" );
  dialog.exec();
#endif

#ifdef EDIT_FORM_AS_SPLIT_PAGE

  /*
  **
  **
  */
  if( m_editAccountWidget )
  {
//    m_gridLayout-> removeWidget( m_editWidget );
//    m_editWidget = nullptr;
    Wt::WMessageBox::show( "AccountsTree", "Please close the account you are editing", Wt::StandardButton::Ok );
    return;
  }

  /*
  ** Split the page to open/edit this item
  **
  */
  m_editAccountWidget = m_gridLayout-> addWidget( std::make_unique< GCW::Gui::AccountEditor >( _accountGuid ), 0, 1 );
  m_gridLayout-> setColumnResizable( 0, true, "25%" );

  m_editAccountWidget->
    save().connect( [=]()
    {
//      refreshViews();
      m_gridLayout-> removeWidget( m_editAccountWidget );
      m_editAccountWidget = nullptr;
    });

  m_editAccountWidget->
    cancel().connect( [=]()
    {
//      refreshViews();
      m_gridLayout-> removeWidget( m_editAccountWidget );
      m_editAccountWidget = nullptr;
    });

#endif

} // endvoid GCW::Gui::AccountsTreeView::editAccount( const std::string & _accountGuid )


void
GCW::Gui::AccountsTreeView::
editSelectedAccount()
{
  editAccount( selectedAccount() );

} // endvoid GCW::Gui::AccountsTreeView::editAccount( const std::string & _accountGuid )


void
GCW::Gui::AccountsTreeView::
setModel()
{
  m_model = std::make_shared< Model >();

  m_model-> load( m_columnCount );

  view()-> setModel( m_model );

  view()-> sortByColumn( 0, Wt::SortOrder::Ascending );

} // endvoid GCW::Gui::AccountsTreeView::setModel()

GCW::Dbo::Vars::Item::Ptr
GCW::Gui::AccountsTreeView::
configItem()
{
  GCW::Dbo::Vars::Item::Ptr retVal;

  if( GCW::app()-> gnucashew_session().hasGnuCashewExtensions() )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    retVal = GCW::Dbo::Vars::get( "config", "AccountsTreeView" );
  }

  return retVal;

} // endconfigItem()


void
GCW::Gui::AccountsTreeView::
saveConfig()
{
  if( !GCW::app()-> gnucashew_session().hasGnuCashewExtensions() )
    return;

  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  configItem().modify()-> setVarField( Wt::Json::serialize( toJson() ) );

} // endsaveConfig()

void
GCW::Gui::AccountsTreeView::
loadConfig()
{
  if( !GCW::app()-> gnucashew_session().hasGnuCashewExtensions() )
    return;

  Wt::Json::Object jobj;
  try {
    Wt::Json::parse( configItem()-> varField(), jobj );
  }
  catch( std::exception & e )
  {
//    std::cout << __FILE__ << ":" << __LINE__ << " " << e.what() << std::endl;
  }

  fromJson( jobj );

} // endloadConfig()

/*
** This will iterate a single a WTreeView and fill
**  a vector of every node which is the .last-expanded.
**  node of every branch.
**
*/
bool
GCW::Gui::AccountsTreeView::
iterate( Wt::Json::Array & _jary, Wt::WModelIndex _parent ) const
{
  /*
  ** If this _parent node is not expanded, then we're basically done.
  **
  */
  if( !view()-> isExpanded( _parent ) )
    return false;

  /*
  ** This _parent node is expanded, so loop through all the
  **  child nodes checking if any of them are expanded.
  **
  */
  bool expanded = false;
  for( int row=0; row< view()-> model()-> rowCount( _parent ); row++ )
    expanded |= iterate( _jary, view()-> model()-> index( row, 0, _parent ) );

  /*
  ** None of the child nodes are expanded, so record this _parent
  **  node as the 'last' node in the tree
  **
  */
  if( !expanded )
  {
    /*
    ** The true root node is not associated with an actual account,
    **  it is simply the invisibleRoot of the tree itself, and only
    **  contains the set of first-root nodes that actually get
    **  displayed.  So, there is no User data in this one, don't record it.
    **
    */
    auto accountGuid = Wt::asString( _parent.data( Wt::ItemDataRole::User ) );
    if( accountGuid != "" )
      _jary.push_back( accountGuid );

  } // endif( !expanded )

  /*
  ** Something is expanded.  Either we are expanded, or
  **  one of the sub-nodes are expanded, so return that 'someone' is
  **  expanded.
  **
  */
  return true;

} // endvoid iterate( Wt::WModelIndex _index ) const


Wt::Json::Object
GCW::Gui::AccountsTreeView::
toJson() const
{
  Wt::Json::Object jobj;

  jobj["selected"] = Wt::WString( selectedAccount() );

  for( int col=0; col< 7; col++ )
    jobj[ Wt::WString("cw{1}").arg( col ).toUTF8() ] = Wt::WString( view()-> columnWidth( col ).cssText() );

  Wt::Json::Array jary;
  iterate( jary );
  jobj["expanded"] = jary;

  return jobj;

}

bool
GCW::Gui::AccountsTreeView::
expandNode( const std::string & _accountGuid, Wt::WModelIndex _parent )
{
  bool retVal = false;

  /*
  ** Loop through all the children in this node
  **
  */
//  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  for( int row=0; row< view()-> model()-> rowCount( _parent ); row++ )
  {
    /*
    ** get the index for this child of this node
    */
    auto child = view()-> model()-> index( row, 0, _parent );

    /*
    ** get the guid of this child
    */
    auto nodeGuid = Wt::asString( child.data( Wt::ItemDataRole::User ) ).toUTF8();

    /*
    ** if this node matches the account, expand it and set the
    **  return to 'found'
    **
    */
    if( nodeGuid == _accountGuid )
    {
      view()-> expand( child );
      retVal |= true;
    }

    /*
    ** remember if any of the sub-nodes get expanded.
    **
    */
    retVal |= expandNode( _accountGuid, child );

  } // endfor( int row=0; row< view()-> model()-> rowCount( _parent ); row++ )

  /*
  ** Either this node was expanded, or any one of
  **  the child nodes was expanded, so therefore we
  **  need to also expand this node.
  **
  */
  if( retVal )
    view()-> expand( _parent );

  /*
  ** None of the nodes here got expanded
  **
  */
  return retVal;

} // endexpandNode( const std::string & _accountGuid, Wt::WModelIndex _parent )

bool
GCW::Gui::AccountsTreeView::
expandTreeNodes( Wt::Json::Object & _jobj )
{
  auto jary = _jobj.get("expanded").orIfNull( Wt::Json::Array() );

  for( auto value : jary )
    expandNode( value.orIfNull( "" ) );

  return true;

} // endexpandNodes()

/*!
** \brief Find Index by AccountGuid
**
** This will loop through the tree and locate a specific
**  index by it's accountGuid value.
**
*/
Wt::WModelIndex
GCW::Gui::AccountsTreeView::
findIndex( const std::string & _accountGuid, Wt::WModelIndex _parentIndex )
{
  /*
  ** If this is the index we are looking for, then just return it.
  **
  */
  if( Wt::asString( _parentIndex.data( Wt::ItemDataRole::User ) ) == _accountGuid )
    return _parentIndex;

  /*
  ** Loop through all the child nodes checking them for
  **  matches
  **
  */
  for( int row=0; row< view()-> model()-> rowCount( _parentIndex ); row++ )
  {
    auto childIndex = findIndex( _accountGuid, view()-> model()-> index( row, 0, _parentIndex ) );

    /*
    ** If we get back a valid index, then we have what we
    **  need and can just return it.
    **
    */
    if( childIndex.isValid() )
      return childIndex;

  } // endfor( int row=0; row< view()-> model()-> rowCount( _parentIndex ); row++ )

  /*
  ** Return an invalid index indicating not-found.
  **
  */
  return Wt::WModelIndex();

} // endfindIndex( const std::string & _accountGuid, Wt::WModelIndex _parentIndex )

bool
GCW::Gui::AccountsTreeView::
setSelected( const std::string & _accountGuid )
{
  auto index = findIndex( _accountGuid );

  view()-> select   ( index                                   );
  view()-> scrollTo ( index, Wt::ScrollHint::PositionAtCenter );

  return true;

} // endexpandNodes()

bool
GCW::Gui::AccountsTreeView::
fromJson( Wt::Json::Object & _jobj )
{
  expandTreeNodes( _jobj );

  setSelected( _jobj.get("selected").orIfNull( std::string() ) );

  return true;

} // endfromJson( const Wt::Json::Object & _jobj )

void
GCW::Gui::AccountsTreeView::
test()
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

  std::cout << __FILE__ << ":" << __LINE__ << " " << Wt::Json::serialize( toJson() ) << std::endl;

} // endvoid GCW::Gui::AccountsTreeView::test()


void
GCW::Gui::AccountsTreeView::
on_doubleClicked( const Wt::WModelIndex & index, const Wt::WMouseEvent & event )
{
#ifdef NEVER
  std::cout << std::endl << std::endl << __FILE__ << ":" << __LINE__
    << " " << "on_doubleClicked:"
    << " " << index.row()
    << " " << Wt::asString( m_model-> data( index, Wt::ItemDataRole::User ) )
    << std::endl << std::endl
    << std::endl;
#endif

  /*
  ** The 'model->data::User' element should return the guid of the account
  **
  */
  m_doubleClicked.emit( Wt::asString( m_model-> data( index, Wt::ItemDataRole::User ) ).toUTF8() );

} // endvoid GCW::Gui::AccountsTreeView::on_doubleClicked( const Wt::WModelIndex & index, const Wt::WMouseEvent & event )


