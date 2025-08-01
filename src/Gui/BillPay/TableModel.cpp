#line 2 "src/Gui/BillPay/TableModel.cpp"

#include <Wt/WStandardItem.h>

#include "../../App.h"
#include "../Dbo/Vars/Vars.h"
#include "BillPay.h"

namespace {

GCW::Gui::BillPay::ColumnDef_t columns[] =
{
//  name,          width,    alignment
  { "accountKey" , "120px" , Wt::AlignmentFlag::Left    },
  { "last4"      ,  "60px" , Wt::AlignmentFlag::Center  },
  { "Nickname"   , "100px" , Wt::AlignmentFlag::Left    },
  { "Gp"         ,  "50px" , Wt::AlignmentFlag::Center  },
  { "Dy"         ,  "50px" , Wt::AlignmentFlag::Center  },
  { "Min"        ,  "50px" , Wt::AlignmentFlag::Right   },
  { "Bgt"        ,  "50px" , Wt::AlignmentFlag::Right   },
  { "Actual"     ,  "75px" , Wt::AlignmentFlag::Right   },
  { "Au"         ,  "50px" , Wt::AlignmentFlag::Center  },
  { "01"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "02"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "03"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "04"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "05"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "06"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "07"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "08"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "09"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "10"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "11"         ,  "35px" , Wt::AlignmentFlag::Center  },
  { "12"         ,  "35px" , Wt::AlignmentFlag::Center  },
};

#define COLUMN_COUNT (sizeof(columns)/sizeof(GCW::Gui::BillPay::ColumnDef_t))

} // endnamespace {

GCW::Gui::BillPay::TableModel::
TableModel( int _selectedMonth, const Status _status )
: Wt::WStandardItemModel( 0, COLUMN_COUNT ),
  m_status( _status )
{

  auto _toolTip = [&]( int _col )
  {
    return TR( std::string("gcw.billPay.ttp." ) + columns[ _col ].name );
  };

  /*
  ** Load the header _only_ on the 'unpaid' view.
  **
  ** The unpaid view is represented first in the widget so that
  **  bills that are unpaid appear at the top of the browser
  **  window.  The unpaid view, therefore, is the only view
  **  that includes the header.  If the other two remaining
  **  views (Paid, Disabled) also had a header the gui would
  **  get too cluttered, so those headers are left blank.
  */
  if( m_status == GCW::Gui::BillPay::Status::Unpaid )
  {
    for( int col = 1; col< COLUMN_COUNT; col++ )
    {
      setHeaderData( col, Wt::Orientation::Horizontal, columns[ col ].name    , Wt::ItemDataRole::Display );
      setHeaderData( col, Wt::Orientation::Horizontal, _toolTip( col )        , Wt::ItemDataRole::ToolTip );
    }
  }

  /*
  ** Load the data based on the month selected.
  */
  loadData( _selectedMonth );

} // endTableModel( const Status _status )

auto
GCW::Gui::BillPay::TableModel::
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
  */
  while( rowCount() > 0 )
    takeRow( 0 );

  /*!
  ** Get all the var items that are for the 'managed bill pay item' (mbpi)
  **  in to a resultList that will then be used to load the
  **  resulting model.
  */
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );
  auto items = GCW::Dbo::Vars::getByCfy( GCW_GUI_BILLPAY_ITEM_CFY );

  /*
  ** Calculate our yes/no status for grabbing items.
  */
  std::string yesNo = "yes";
  if( m_status == GCW::Gui::BillPay::Status::Pending )
    yesNo = "maybe";
  if( m_status == GCW::Gui::BillPay::Status::Unpaid )
    yesNo = "no";

  /*!
  ** Run the resultList collection through an analyzer that will
  **  extract billpay items that match the selection criteria of
  **  paid/unpaid/disabled/yes/no accordingly.
  */
  std::vector< GCW::Gui::BillPay::Item > bpItems;
  for( auto item : items )
  {
    auto bpItem = GCW::Gui::BillPay::Item( item );

    /*
    ** Calculate these boolean.
    */
    auto isActive  = bpItem.isActive () == "yes";
    auto isVisible = bpItem.isVisible() == "yes";

    /*
    ** This is for Paid and Unpaid (not Disabled).
    */
    if( m_status == GCW::Gui::BillPay::Status::Paid
     || m_status == GCW::Gui::BillPay::Status::Pending
     || m_status == GCW::Gui::BillPay::Status::Unpaid
      )
    {
      /*
      ** The item ~must~ be active ~and~ visible.
      */
      if( isActive && isVisible )
      {
        /*
        ** Get the .var. string that has the combo-box values for the monthly
        **  indicators of what has been paid and what has not.  Depending on the
        **  value of that payment status, it must therefore match the yes/no clause
        **  we calculated above.  If it's a match, we grab it.
        */
        if( bpItem.cb( _selectedMonth ) == yesNo )
//        if( i-> getVarString( "cb" + GCW::Gui::BillPay::toString( _selectedMonth ) ) == yesNo )
          bpItems.push_back( bpItem );

      } // endif( isActive && isVisible )

    } // endif( ..is active.. )

    /*
    ** This is for Disabled.
    */
    else
    if( m_status == GCW::Gui::BillPay::Status::Inactive ) // capture disabled items here
    {
      /*
      ** Disabled items are either notActive ~or~ notVisible.
      */
      if( !isActive || !isVisible )
          bpItems.push_back( bpItem );

    } // endelseif( .disabled. )

  } // endfor( auto i : items )

  /*!
  ** Sort all the items by the account group.dueDay.  (The
  **  user is not allowed to sort these views so we do it)  This sorts the items
  **  with the items that are due first, above those that are due next.
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
    */
    auto accountName = std::make_unique< Wt::WStandardItem >();
    auto accountGuid = bpItem.accountGuid();

    if( accountGuid != "" )
    {
      auto accountItem = GCW::Dbo::Accounts::byGuid( accountGuid );

      /*
      ** set the bpItem.guid so we can edit this row
      */
      accountName-> setData( bpItem.guid(), Wt::ItemDataRole::User  );

      /*
      ** sometimes the 'account' can get lost, so check first the
      **  account still exists.
      */
      if( accountItem )
      {
        /*
        ** build the account column to;
        **  display the account name
        **  carry the account-full-name as a toolTip,
        **  carry the guid of the originating bpItem
        */
        accountName-> setData( accountItem-> name() , Wt::ItemDataRole::Display );
        accountName-> setToolTip( GCW::Dbo::Accounts::fullName( accountGuid )   );
      }

    } // endif( accountGuid != "" )

    /*
    ** The columns are pushed in to .columns. variable.
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

    /*
    ** Load 12-columns, one for each month.
    */
    for( int month=1; month<= 12; month++ )
    {
      auto cb = std::make_unique< Wt::WStandardItem >( bpItem.cbtr( month ) );

      /*!
      ** While building the 'month columns', apply a style class to the
      **  column of items according to the month selected.  This causes
      **  the current selected column to be highlighted within the table
      **  view in the browser.
      **
      ** \image html BillPayColumnSelector.png
      */
      if( _selectedMonth == month )
        cb-> setStyleClass( "colsel" );

      columns.push_back( std::move( cb ) );

    } // endfor( int i=1; i<= 12; i++ )

    /*
    ** Push everything in to the model.
    */
    appendRow( std::move( columns ) );

  } // endfor( auto bpItem : bpItems )

} // endloadData( int _selectedMonth )-> void

auto
GCW::Gui::BillPay::TableModel::
columnDef( int col )-> GCW::Gui::BillPay::ColumnDef_t
{
  return columns[col];
}

auto
GCW::Gui::BillPay::TableModel::
sort( std::vector< GCW::Gui::BillPay::Item > & _bpItems )-> void
{
  /*!
  ** Sort the vector of bpItems by group.dueDay
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
       */
       return item1.sortValue()
            < item2.sortValue()
            ;
     }
  );

} // endsort( std::vector< GCW::Gui::BillPay::Item > & _bpItems )-> void


