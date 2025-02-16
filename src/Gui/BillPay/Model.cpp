#line 2 "src/Gui/BillPay/Model.cpp"

#include <Wt/WStandardItem.h>

#include "../../App.h"
#include "../Dbo/Vars/Vars.h"
#include "BillPay.h"

//#define NO_HEADER_ON_SUBSEQUENT_TABLES
#define HEADER_COL0_HAS_TABLE_TYPE_NAME

namespace {

GCW::Gui::BillPay::ColumnDef_t columns[] =
{
  { "accountKey" , "120px", Wt::AlignmentFlag::Left,   "Primary Account Identifier"        },
  { "last4"      ,  "60px", Wt::AlignmentFlag::Center, "Last 4 digits of account number"   },
  { "Nickname"   , "100px", Wt::AlignmentFlag::Left,   "Friendly Nickname for the account" },
  { "Gp"         ,  "50px", Wt::AlignmentFlag::Center, "Grouping"                          },
  { "Dy"         ,  "50px", Wt::AlignmentFlag::Center, "Day that the payment is due"       },
  { "Min"        ,  "50px", Wt::AlignmentFlag::Right,  "Minimum Payment Due"               },
  { "Bdgt"       ,  "50px", Wt::AlignmentFlag::Right,  "Payment Budget"                    },
  { "Actual"     ,  "50px", Wt::AlignmentFlag::Right,  "Actual payment most recently made" },
  { "Au"         ,  "50px", Wt::AlignmentFlag::Center, "Automatic Payment Indicator"       },
  { "01"         ,  "35px", Wt::AlignmentFlag::Center, "January"                           },
  { "02"         ,  "35px", Wt::AlignmentFlag::Center, "February"                          },
  { "03"         ,  "35px", Wt::AlignmentFlag::Center, "March"                             },
  { "04"         ,  "35px", Wt::AlignmentFlag::Center, "April"                             },
  { "05"         ,  "35px", Wt::AlignmentFlag::Center, "May"                               },
  { "06"         ,  "35px", Wt::AlignmentFlag::Center, "June"                              },
  { "07"         ,  "35px", Wt::AlignmentFlag::Center, "July"                              },
  { "08"         ,  "35px", Wt::AlignmentFlag::Center, "August"                            },
  { "09"         ,  "35px", Wt::AlignmentFlag::Center, "September"                         },
  { "10"         ,  "35px", Wt::AlignmentFlag::Center, "October"                           },
  { "11"         ,  "35px", Wt::AlignmentFlag::Center, "November"                          },
  { "12"         ,  "35px", Wt::AlignmentFlag::Center, "December"                          },
};

#define COLUMN_COUNT (sizeof(columns)/sizeof(GCW::Gui::BillPay::ColumnDef_t))

} // endnamespace {

GCW::Gui::BillPay::Model::
Model( int _selectedMonth, const Status _status )
: Wt::WStandardItemModel( 0, COLUMN_COUNT ),
  m_status( _status )
{

  /*
  ** Load the header _only_ on the 'unpaid' view.
  **
  ** The unpaid view is represented first in the widget so that
  **  bills that are unpaid appear at the top of the browser
  **  window.  The unpaid view, therefore, is the only view
  **  that includes the header.  If the other two remaining
  **  views (Paid, Disabled) also had a header the gui would
  **  get too cluttered, so those headers are left blank.
  **
  */
  if( m_status == GCW::Gui::BillPay::Status::Unpaid )
  {
    for( int col = 1; col< COLUMN_COUNT; col++ )
    {
      setHeaderData( col, Wt::Orientation::Horizontal, columns[ col ].name    , Wt::ItemDataRole::Display );
      setHeaderData( col, Wt::Orientation::Horizontal, columns[ col ].toolTip , Wt::ItemDataRole::ToolTip );
    }
  }

  /*
  ** Load the data based on the month selected.
  */
  loadData( _selectedMonth );

} // endModel( const Status _status )

auto
GCW::Gui::BillPay::Model::
loadData( int _selectedMonth )-> void
{
  /*!
  ** On load, the first column-label is set to indicate the
  **  model type as well as the month selected.
  **
  ** \code
  ** Change the label on the column-0, example;
  **   "03 Unpaid"
  **   "06 Paid"
  **   "12 Disabled"
  ** \endcode
  **
  */
  setHeaderData
  (
   0,
   Wt::Orientation::Horizontal,
   toString( _selectedMonth ) + " " + asString( m_status ),
   Wt::ItemDataRole::Display
  );

  /*!
  ** On load, all existing data in the model is first dumped.
  **
  */
  while( rowCount() > 0 )
    takeRow( 0 );

  /*!
  ** Get all the var items that are for the 'managed bill pay item' (mbpi)
  **  in to a resultList that will then be used to load the
  **  resulting model.
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  auto items =
    GCW::app()-> gnucashew_session().find< GCW::Dbo::Vars::Item >()
      .where( "\"cfyField\" = '" GCW_GUI_BILLPAY_ITEM_CFY "'" )
      .resultList()
      ;

  /*
  ** Calculate our yes/no status for grabbing items.
  */
  std::string yesNo = "yes";
  if( m_status == GCW::Gui::BillPay::Status::Unpaid )
    yesNo = "no";

  /*!
  ** Run the resultList collection through an analyzer that will
  **  extract billpay items that match the selection criteria of
  **  paid/unpaid/disabled/yes/no accordingly.
  **
  */
  std::vector< GCW::Gui::BillPay::Item > bpItems;
  for( auto item : items )
  {
    auto bpItem = GCW::Gui::BillPay::Item( item );

    /*
    ** Calculate these boolean.
    **
    */
    auto isActive  = bpItem.isActive () == "yes";
    auto isVisible = bpItem.isVisible() == "yes";

    /*
    ** This is for Paid and Unpaid (not Disabled).
    **
    */
    if( m_status == GCW::Gui::BillPay::Status::Paid
     || m_status == GCW::Gui::BillPay::Status::Unpaid
      )
    {
      /*
      ** The item ~must~ be active ~and~ visible.
      **
      */
      if( isActive && isVisible )
      {
        /*
        ** Get the .var. string that has the combo-box values for the monthly
        **  indicators of what has been paid and what has not.  Depending on the
        **  value of that payment status, it must therefore match the yes/no clause
        **  we calculated above.  If it's a match, we grab it.
        **
        */
        if( bpItem.cb( _selectedMonth ) == yesNo )
//        if( i-> getVarString( "cb" + GCW::Gui::BillPay::toString( _selectedMonth ) ) == yesNo )
          bpItems.push_back( bpItem );

      } // endif( isActive && isVisible )

    } // endif( m_status != GCW::Gui::BillPay::Status::Disabled )

    /*
    ** This is for Disabled.
    **
    */
    else
    if( m_status == GCW::Gui::BillPay::Status::Disabled ) // capture disabled items here
    {
      /*
      ** Disabled items are either notActive ~or~ notVisible.
      **
      */
      if( !isActive || !isVisible )
          bpItems.push_back( bpItem );

    } // endelse( .disabled. )

  } // endfor( auto i : items )

  /*!
  ** Sort all the items by the account group.dueDay.  (The
  **  user is not allowed to sort these views so we do it)  This sorts the items
  **  with the items that are due first, above those that are due next.
  **
  */
  sort( bpItems );

  /*!
  ** Each item is processed out of the sorted vector and placed
  **  in to the item model.
  */
  for( auto bpItem : bpItems )
  {
    /*
    ** Grab a few handles.
    **
    */
    auto accountName = std::make_unique< Wt::WStandardItem >();
    auto accountGuid = bpItem.accountGuid();

    if( accountGuid != "" )
    {
      auto accountItem = GCW::Dbo::Accounts::byGuid( accountGuid );

      /*
      ** build the account column to;
      **  display the account name
      **  carry the account-full-name as a toolTip,
      **  carry the guid of the originating bpItem
      */
      accountName-> setData( accountItem-> name() , Wt::ItemDataRole::Display );
      accountName-> setData( bpItem.guid()        , Wt::ItemDataRole::User    );
      accountName-> setToolTip( GCW::Dbo::Accounts::fullName( accountGuid )   );

    } // endif( accountGuid != "" )

    /*
    ** The columns are pushed in to this.
    **
    */
    std::vector< std::unique_ptr< Wt::WStandardItem > > columns;
    columns.push_back( std::move( accountName ) );
    columns.push_back( std::make_unique< Wt::WStandardItem >( bpItem.last4    () ) );
    columns.push_back( std::make_unique< Wt::WStandardItem >( bpItem.nickname () ) );
    columns.push_back( std::make_unique< Wt::WStandardItem >( bpItem.group    () ) );
    columns.push_back( std::make_unique< Wt::WStandardItem >( bpItem.dueDay   () ) );
    columns.push_back( std::make_unique< Wt::WStandardItem >( bpItem.minimum  () ) );
    columns.push_back( std::make_unique< Wt::WStandardItem >( bpItem.budget   () ) );
    columns.push_back( std::make_unique< Wt::WStandardItem >( bpItem.actual   () ) );
    columns.push_back( std::make_unique< Wt::WStandardItem >( bpItem.autoPay  () ) );

    for( int month=1; month<= 12; month++ )
    {
      auto cb = std::make_unique< Wt::WStandardItem >( bpItem.cb( month ) );

      /*!
      ** While building the 'month columns', apply a style class to the
      **  column of items according to the month selected.  This causes
      **  the current selected column to be highlighted within the table
      **  view in the browser.
      **
      ** \image html BillPayColumnSelector.png
      **
      */
      if( _selectedMonth == month )
        cb-> setStyleClass( "colsel" );

      columns.push_back( std::move( cb ) );

    } // endfor( int i=1; i<= 12; i++ )

    /*
    ** Push everything in to the model.
    **
    */
    appendRow( std::move( columns ) );

  } // endfor( auto bpItem : bpItems )

} // endloadData( int _selectedMonth )-> void

auto
GCW::Gui::BillPay::Model::
columnDef( int col )-> GCW::Gui::BillPay::ColumnDef_t
{
  return columns[col];
}

auto
GCW::Gui::BillPay::Model::
sort( std::vector< GCW::Gui::BillPay::Item > & _bpItems )-> void
{
  /*!
  ** Sort the vector of bpItems by group.dueDay
  **
  */
  std::sort
  (
   _bpItems.begin(),
   _bpItems.end(),
   []( const GCW::Gui::BillPay::Item item1,
       const GCW::Gui::BillPay::Item item2
     )
     {
//       auto account1 = GCW::Dbo::Accounts::byGuid( item1-> keyField() );
//       auto account2 = GCW::Dbo::Accounts::byGuid( item2-> keyField() );
//       auto name1 = account1-> name();
//       auto name2 = account2-> name();

//       auto name1 = item1.nickname();
//       auto name2 = item2.nickname();

       /*
       ** return .bool. of the comparison
       **
       */
       return item1.sortValue()
            < item2.sortValue()
            ;
     }
  );

} // endsort( std::vector< GCW::Gui::BillPay::Item > & _bpItems )-> void


