#line 2 "src/Gui/TableView.cpp"

#include <Wt/WMessageBox.h>
#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>

#include "../Glb/gcwglobal.h"
#include "../GnuCashew.h"
#include "TableView.h"

// Pixels
const int GCW::Gui::TableView::kTableHeaderRowHeight = 30;
const int GCW::Gui::TableView::kTableBodyRowHeight   = 20;
const int GCW::Gui::TableView::kTableCellPadding     = 7;
const int GCW::Gui::TableView::kScrollBarWidth       = 20;
const int GCW::Gui::TableView::kDefaultDateTimeWidth = 120;

namespace {
static auto keyToCode( Wt::Key _key )-> std::string
{
  std::map< Wt::Key, std::string > keyMap =
  {
    { Wt::Key::Unknown   , "Unknown"      },
    { Wt::Key::Enter     , "Enter"        },
    { Wt::Key::Tab       , "Tab"          },
    { Wt::Key::Backspace , "Backspace"    },
    { Wt::Key::Shift     , "Shift"        },
    { Wt::Key::Control   , "Control"      },
    { Wt::Key::Alt       , "Alt"          },
    { Wt::Key::PageUp    , "Page up"      },
    { Wt::Key::PageDown  , "Page down"    },
    { Wt::Key::End       , "End"          },
    { Wt::Key::Home      , "Home"         },
    { Wt::Key::Left      , "Left"         },
    { Wt::Key::Up        , "Up"           },
    { Wt::Key::Right     , "Right"        },
    { Wt::Key::Down      , "Down"         },
    { Wt::Key::Insert    , "Insert"       },
    { Wt::Key::Delete    , "Delete"       },
    { Wt::Key::Escape    , "Escape"       },
    { Wt::Key::F1        , "F1"           },
    { Wt::Key::F2        , "F2"           },
    { Wt::Key::F3        , "F3"           },
    { Wt::Key::F4        , "F4"           },
    { Wt::Key::F5        , "F5"           },
    { Wt::Key::F6        , "F6"           },
    { Wt::Key::F7        , "F7"           },
    { Wt::Key::F8        , "F8"           },
    { Wt::Key::F9        , "F9"           },
    { Wt::Key::F10       , "F10"          },
    { Wt::Key::F11       , "F11"          },
    { Wt::Key::F12       , "F12"          },
    { Wt::Key::Space     , "Space"        },
    { Wt::Key::A         , "'A'"          },
    { Wt::Key::B         , "'B'"          },
    { Wt::Key::C         , "'C'"          },
    { Wt::Key::D         , "'D'"          },
    { Wt::Key::E         , "'E'"          },
    { Wt::Key::F         , "'F'"          },
    { Wt::Key::G         , "'G'"          },
    { Wt::Key::H         , "'H'"          },
    { Wt::Key::I         , "'I'"          },
    { Wt::Key::J         , "'J'"          },
    { Wt::Key::K         , "'K'"          },
    { Wt::Key::L         , "'L'"          },
    { Wt::Key::M         , "'M'"          },
    { Wt::Key::N         , "'N'"          },
    { Wt::Key::O         , "'O'"          },
    { Wt::Key::P         , "'P'"          },
    { Wt::Key::Q         , "'Q'"          },
    { Wt::Key::R         , "'R'"          },
    { Wt::Key::S         , "'S'"          },
    { Wt::Key::T         , "'T'"          },
    { Wt::Key::U         , "'U'"          },
    { Wt::Key::V         , "'V'"          },
    { Wt::Key::W         , "'W'"          },
    { Wt::Key::X         , "'X'"          },
    { Wt::Key::Y         , "'Y'"          },
    { Wt::Key::Z         , "'Z'"          },
    { Wt::Key::Key_1     , "'1'"          },
    { Wt::Key::Key_2     , "'2'"          },
    { Wt::Key::Key_3     , "'3'"          },
    { Wt::Key::Key_4     , "'4'"          },
    { Wt::Key::Key_5     , "'5'"          },
    { Wt::Key::Key_6     , "'6'"          },
    { Wt::Key::Key_7     , "'7'"          },
    { Wt::Key::Key_8     , "'8'"          },
    { Wt::Key::Key_9     , "'9'"          },
    { Wt::Key::Key_0     , "'0'"          }
  }; // endstd::map< Wt::Key, std::string > keyMap =

  return keyMap[_key];

}; // endstatic auto keyToCode( Wt::Key _key )-> std::string

} // endnamespace {


GCW::Gui::TableView::
TableView()
: Wt::WTableView()
{
  addStyleClass( "Gcw-TableView" );

  /*
  ** To support right-click, we need to disable the built-in browser
  **  context menu.
  **
  ** Note that disabling the context menu and catching the
  **  right-click does not work reliably on all browsers.
  */
#ifdef NEVER
  setAttributeValue
  (
    "oncontextmenu",
    "event.cancelBubble = true; event.returnValue = false; return false;"
  );
#endif

  setHeaderHeight( kTableHeaderRowHeight );
  setRowHeight( kTableBodyRowHeight );

  setLayoutSizeAware( true );

#ifdef NEVER
  clicked()
    .connect( [=]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " clicked row: " << _index.row() << " col: " << _index.column() << std::endl;
    });

  doubleClicked()
    .connect( [=]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " doubleClicked row: " << _index.row() << " col: " << _index.column() << std::endl;

    });

  mouseWentDown ()
    .connect( [=]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " mouseWentDown row: " << _index.row() << " col: " << _index.column() << std::endl;
    });

  mouseWentUp ()
    .connect( [=]( Wt::WModelIndex _index, Wt::WMouseEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " mouseWentUp row: " << _index.row() << " col: " << _index.column() << std::endl;
    });

  touchStart ()
    .connect( [=]( Wt::WModelIndex _index, Wt::WTouchEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " touchStart row: " << _index.row() << " col: " << _index.column() << std::endl;
    });

//  touchStarted ()
//    .connect( [=]( Wt::WModelIndex _index, Wt::WTouchEvent _event )
//    {
//      std::cout << __FILE__ << ":" << __LINE__ << " touchStarted: " << std::endl;
//    });

//  touchMoved ()
//    .connect( [=]( Wt::WModelIndex _index, Wt::WTouchEvent _event )
//    {
//      std::cout << __FILE__ << ":" << __LINE__ << " touchMoved: " << std::endl;
//    });

//  touchEnded ()
//    .connect( [=]( Wt::WModelIndex _index, Wt::WTouchEvent _event )
//    {
//      std::cout << __FILE__ << ":" << __LINE__ << " touchEnded: " << std::endl;
//    });

  selectionChanged ()
    .connect( [=]()
    {
      std::cout << __FILE__ << ":" << __LINE__ << " selectionChanged: " << std::endl;
    });

  pageChanged ()
    .connect( [=]()
    {
      std::cout << __FILE__ << ":" << __LINE__ << " pageChanged: " << std::endl;
    });

  columnResized ()
    .connect( [=]( int, Wt::WLength)
    {
      std::cout << __FILE__ << ":" << __LINE__ << " pageChanged: " << std::endl;
    });


  headerClicked ()
    .connect( [=]( int, Wt::WMouseEvent)
    {
      std::cout << __FILE__ << ":" << __LINE__ << " headerClicked: " << std::endl;
    });


  headerDoubleClicked ()
    .connect( [=]( int, Wt::WMouseEvent )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " headerDoubleClicked: " << std::endl;
    });


  headerMouseWentDown ()
    .connect( [=]( int, Wt::WMouseEvent )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " headerMouseWentDown: " << std::endl;
    });


  headerMouseWentUp ()
    .connect( [=]( int, Wt::WMouseEvent )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " headerMouseWentUp: " << std::endl;
    });


  scrolled ()
    .connect( [=]( Wt::WScrollEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " scrolled"
        << " x:" << _event.scrollX()
        << " y:" << _event.scrollY()
        << " w:" << _event.viewportWidth()
        << " h:" << _event.viewportHeight()
        << std::endl;
    });
#endif

#ifdef NEVER
  keyWentDown ()
    .connect( [=]( Wt::WKeyEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " keyWentDown: " << _event.charCode() << " key:" << keyToCode( _event.key() ) << std::endl;
    });


  keyPressed ()
    .connect( [=]( Wt::WKeyEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " keyPressed: " << _event.charCode() << " key:" << keyToCode( _event.key() ) << std::endl;
    });

  keyWentUp ()
    .connect( [=]( Wt::WKeyEvent _event )
    {
      std::cout << __FILE__ << ":" << __LINE__ << " keyWentUp charCode:" << _event.charCode() << " key:" << keyToCode( _event.key() ) << std::endl;
    });
#endif

} // endGCW::Gui::TableView::TableView( Wt::WContainerWidget* parent )

auto
GCW::Gui::TableView::
layoutSizeChanged( int width, int height )-> void
{
  // Calculate our fixed width columns
  auto nfixed = 0;
  auto nrel   = 0;

  // "fixed" number of pixels
  auto fixed = 0.0;

  for( auto col : widths_ )
    if( col.second.unit() == Wt::LengthUnit::Percentage )
      nrel++;

  auto percent_sum=0.0;
  for( auto col : widths_)
  {
    if( col.second.unit() != Wt::LengthUnit::Percentage )
      fixed += col.second.toPixels();
    else
      percent_sum += col.second.value();
  }

  // Check to see if the relative columns are taking up ~100% of the
  // non-fixed width.  "Roughly" because sometimes they're intentionally off
  // by a fraction just to avoid a scroll bar
  const auto epsilon = 0.5;
  if( 100.0 - percent_sum > epsilon )
    Wt::log("debug")
      << "Warning: Relative column widths do not take up 100% of the available width"
      ;

  // Columns who's width wasn't explicitly set are considered "fixed", and Wt
  // will default them to 150px or something.
  if( model() )
  {
    nfixed = model()->columnCount() - nrel;

    // Show scroll bar?
    bool show_scroll = visible_rows_ > 0 && model()->rowCount() > visible_rows_;

    auto remainder = width - ( fixed + ( kTableCellPadding * model()->columnCount() ) + ( show_scroll ? kScrollBarWidth : 0.0 ) );

  for( auto col : widths_)
    if( col.second.unit() == Wt::LengthUnit::Percentage )
      setColumnWidth
      (
       col.first,
       Wt::WLength
       (
        col.second.value()/100.0*remainder,
        Wt::LengthUnit::Pixel
       )
      );

  } // endif( model() )

  // Pass the call up the chain
  Wt::WTableView::layoutSizeChanged( width, height );

} // endauto GCW::Gui::TableView::layoutSizeChanged( int width, int height ) -> void

auto
GCW::Gui::TableView::
setColumnWidth( int column, const Wt::WLength& width )-> void
{
    // Just save the data and pass the the work up
    widths_.emplace( column, width );

    Wt::WTableView::setColumnWidth( column, width );

} // endauto GCW::Gui::TableView::setColumnWidth(int column, const Wt::WLength& width) -> void

/*!
** \brief Handle Click Event
**
** This handler responds to 'click' events in the view.
**
** The intent here is to provide some 'handling' when the user
**  is mouse-ing around the table view.  He should be able to
**  click around to get editors to open, and select rows and
**  whatnot.
**
** The 'purpose' for the handler is due to the fact that the
**  view responds differently if the view is editable or not.
**  For instance, if an index is read-only, clicking on it
**  causes the view to 'select' the entire row.  But, if the
**  index is 'Editable' then you are placed in to the editor
**  but the view 'selection' is still visible, even if it's on
**  another row.  Further, the editor widget that opened, did
**  not signal to the rest of the row that it should be 'selected'.
**
*/
#ifdef NEVER
auto
GCW::Gui::TableView::
handleClick( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " handleClick:<start>"
    << " row:" << _index.row()
    << " col:" << _index.column()
    << std::endl
    ;
#endif

#ifdef NEVER
  if( selectedIndexes().size() > 0 )
  {
    auto selectedIndex = *selectedIndexes().begin();

#ifdef NEVER
    std::cout << __FILE__ << ":" << __LINE__
      << " selected:" << selectedIndexes().size()
      << " row:" << selectedIndex.row()
      << " col:" << selectedIndex.column()
       << std::endl
      ;
#endif

    /*
    ** If the selection is different in any way, then clear
    **  the entire selection.  If the selection is the same
    **  as the 'index', then we are handling the same click
    **  on the same index that is already selected - don't
    **  do anything.  But if the _index is different than
    **  the current selection, then we need to clear the
    **  current selection.
    **
    */
    if( selectedIndex.row    () != _index.row    ()
     && selectedIndex.column () != _index.column ()
      )
    {
      clearSelection();
    }

    closeEditors();

  }
#endif

#ifdef NEVER
  {
    auto m = dynamic_cast< Wt::WStandardItemModel* >( model().get() );

    auto row = _index.row();
    for( int column = 0; column< m-> columnCount(); column++ )
    {
      std::cout << __FILE__ << ":" << __LINE__
        << " row:" << row
        << " col:" << column
        << std::endl;

      auto index = m-> index( row, column );
      auto item = m-> itemFromIndex( index );

      item-> setFlags( Wt::ItemFlag::Editable );
//      edit( index );

    } // endfor( int column = 0; column< m-> columnCount(); column++ )
  }
#endif

#ifdef NEVER
  /*
  ** The 'selector' is funky.  If an 'editor' is enabled, then
  **  selecting the cell causes the editor to open, but the previous
  **  selection does not get un-selected, so it looks like a whole row
  **  is selected, and then a cell is open in another row.
  **
  */
  if( selectedIndexes().size() )
  {
    auto oldIndex = *selectedIndexes().begin();

    std::cout << __FILE__ << ":" << __LINE__ << " handleCLick()"
      << " old:" << oldIndex.row()
      << " new:" << _index.row()
      << std::endl;

    if( _index.row() != oldIndex.row() )
    {
      clearSelection();
      closeEditors( true );
    }

  }
#endif

  /*
  ** Call the stock click handler
  **
  */
  Wt::WTableView::handleClick( _index, _event );

#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " handleClick:<end>" << std::endl;
#endif

} // endvoid GCW::Gui::TableView::handleClick( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )
#endif

#ifdef NEVER
auto
GCW::Gui::TableView::
handleDoubleClick( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " handleDoubleClick:<start>"
    << " row:" << _index.row()
    << " col:" << _index.column()
    << std::endl
    ;
#endif

  Wt::WTableView::handleDoubleClick( _index, _event );

#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " handleDoubleClick:<end>" << std::endl;
#endif

} // endhandleDoubleClick ( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )
#endif

#ifndef NEVER
auto
GCW::Gui::TableView::
handleMouseDown( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void
{

  // we can test the model and the table and the row and detect if the
  //  row we ~were~ on is dirty, and if it needs to be saved
//  Wt::WMessageBox::show( "TableView", "something or whatever", Wt::StandardButton::Ok );

#ifdef NEVER
  std::cout << BREAKHEADER
    << " row:" << _index.row()
    << " col:" << _index.column()
    << std::endl
    ;
#endif

#ifdef NEVER
  if( m_lastIndexClick.isValid() )
    if( m_lastIndexClick. row    () != _index. row    ()
     || m_lastIndexClick. column () != _index. column ()
      )
    {
      clearSelection();
      closeEditors();
    }
#endif

#ifdef NEVER
  auto balanceIndex = model()-> index( _index.row(), 7 );

  std::cout << __FILE__ << ":" << __LINE__ << " " <<balanceIndex.data( Wt::ItemDataRole::User ).type().name() << std::endl;

  auto balanceValue = Wt::cpp17::any_cast< GCW_NUMERIC >( balanceIndex.data( Wt::ItemDataRole::User ) );
  std::cout << __FILE__ << ":" << __LINE__ << " " << balanceValue << std::endl;
#endif

  Wt::WTableView::handleMouseDown( _index, _event );

#ifdef NEVER
  std::cout << BREAKFOOTER;
#endif

  /*
  ** remember the last index clicked
  **
  */
  m_lastIndexClick = _index;

} // endhandleMouseDown( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )
#endif

#ifdef NEVER
auto
GCW::Gui::TableView::
handleMouseUp( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )-> void
{
#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__
    << " handleMouseUp:<start>"
    << " row:" << _index.row()
    << " col:" << _index.column()
    << std::endl
    ;
#endif

  Wt::WTableView::handleMouseUp( _index, _event );

#ifndef NEVER
  std::cout << __FILE__ << ":" << __LINE__ << " handleMouseUp:<end>" << std::endl;
#endif

} // endhandleMouseUp( const Wt::WModelIndex & _index, const Wt::WMouseEvent & _event )
#endif



