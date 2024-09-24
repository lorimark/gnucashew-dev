#line 2 "src/Gui/CentralWidget.cpp"

#include <Wt/WMenuItem.h>
#include <Wt/WTabWidget.h>
#include <Wt/WText.h>

#include "../define.h"
#include "../App.h"
#include "../Dbo/Books/Books.h"
#include "../Dbo/BillTerms/BillTerms.h"
#include "../Dbo/Accounts/Accounts.h"
#include "../Dbo/Entries/Entries.h"
#include "../Dbo/Invoices/Invoices.h"
#include "../Dbo/GncLock/GncLock.h"
#include "../Dbo/Customers/Customers.h"
#include "../Dbo/Slots/Slots.h"
#include "../Dbo/Splits/Splits.h"
#include "../Dbo/Transactions/Transactions.h"
#include "../Dbo/Versions/Versions.h"
#include "BillPay/MainWidget.h"
#include "CentralWidget.h"
#include "CustomerReportWidget.h"
#include "CustomersWidget.h"
#include "RawTableWidget.h"

/*!
** \brief Central Widget
**
** The CentralWidget is the component on the main user interface that
**  acts as a tab widget for being able to select from one tab to
**  another.
**
** The first tab is usually the 'accounts' tab.  This tab normally cannot
**  be closed.  The other tabs open and close on reports or other views
**  as they are requested.
**
*/
GCW::Gui::CentralWidget::
CentralWidget()
{
  addStyleClass( "CentralWidget" );

  /*
  ** Always use a layout
  **
  */
  m_gridLayout = setLayout( std::make_unique< Wt::WGridLayout >() );
//  m_gridLayout-> setSpacing( 0 );

  /*
  ** Build the tab-widget
  **
  */
  m_tabWidget = m_gridLayout-> addWidget( std::make_unique< Wt::WTabWidget >(), 0, 0 );

  /*
  ** This procedure will ~delete~ the tab and its contents when the tab
  **  is closed.  Normally, on 'close' the tab is only 'hidden' and not
  **  actually deleted.  This prevents the widgets from remaining in
  **  memory when the tabs are closed.
  **
  */
  tabWidget()->
    tabClosed().connect( [=]( int tabIndex )
    {
      tabWidget()-> removeTab( tabWidget()-> widget( tabIndex ) );
    });

  /*
  ** Attach the accounts widget tree view as a non-closeable-tab, so that the
  **  user can navigate around the accounts.
  **
  */
  {
    auto widget = std::make_unique< GCW::Gui::AccountsTreeView >( 7 );
    m_accountsTreeView = widget.get();
    tabWidget()-> addTab( std::move( widget ), TR( "gcw.AccountsTreeView.tabName" ) );

    accountsTreeView()-> doubleClicked().connect( this, &GCW::Gui::CentralWidget::open_AccountRegister );
  }

} // endGCW::CentralWidget::CentralWidget()

auto
GCW::Gui::CentralWidget::
tabIndex( const std::string & _text )-> int
{
  for( int i=0; i< tabWidget()-> count(); i++ )
    if( tabWidget()-> tabText( i ) == _text )
      return i;

  return -1;

} // endtabIndex( const std::string & _text )-> int

auto
GCW::Gui::CentralWidget::
open_AccountRegister( const std::string & _accountGuid )-> void
{
  Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

  /*
  ** Grab the account so we can fetch things from it.
  **
  */
  auto accountItem = GCW::Dbo::Accounts::byGuid( _accountGuid );

  /*
  ** If we didn't get an account (this shouldn't happen) then
  **  there's nothing for us to do... perhaps pop an error dialog
  **  or something.
  **
  */
  if( !accountItem )
    return;

  /*
  ** See if this tab exists, if not, then add it.
  **
  */
  if( tabIndex( accountItem-> name() ) == -1 )
  {
    /*
    ** Open a new AccountRegister tab that is connected to the account
    **
    */
    auto tab =
      tabWidget()->
        insertTab
        ( 1,
          std::make_unique< GCW::Gui::AccountRegister >( _accountGuid ),
          accountItem-> name()
        );

    tabWidget()-> setTabToolTip( 1, fullName( accountItem ) );

    tab-> setCloseable( true );

  } // endif( tabIndex( _account-> name() ) == -1 )

  /*
  ** Go straight to the tab.
  **
  */
  tabWidget()-> setCurrentIndex( tabIndex( accountItem-> name() ) );

} // endopen_AccountRegister( const std::string & _accountGuid )-> void

auto
GCW::Gui::CentralWidget::
open_CustomerReportWidget( const std::string & _customerGuid )-> void
{
  /*
  ** Grab the account so we can fetch things from it.
  **
  */
  auto customerItem = GCW::Dbo::Customers::byGuid( _customerGuid );

  /*
  ** If we didn't get a customer (this shouldn't happen) then
  **  there's nothing for us to do... perhaps pop an error dialog
  **  or something.
  **
  */
  if( !customerItem )
    return;

  /*
  ** build a tab name
  **
  */
  auto tabName = TR8( "gcw.cw.tabName.Customer" ) + ": " + customerItem-> name();

  /*
  ** See if this tab exists, if not, then add it.
  **
  */
  if( tabIndex( tabName ) == -1 )
  {
    /*
    ** Open a new CustomerReportWidget tab that is connected to the account.
    **  When inserting the tab, insert it immediately after the currently
    **  selected customer.
    **
    */
    auto tab =
      tabWidget()->
        insertTab
        ( tabWidget()-> currentIndex() + 1,
          std::make_unique< GCW::Gui::CustomerReportWidget >( _customerGuid ),
          tabName
        );

    tab-> setCloseable( true );

  } // endif( tabIndex( _account-> name() ) == -1 )

  /*
  ** Go straight to the tab.
  **
  */
  tabWidget()-> setCurrentIndex( tabIndex( tabName ) );

} // endopen_CustomerReportWidget( const std::string & _customerGuid )-> void

auto
GCW::Gui::CentralWidget::
open_CustomersWidget()-> void
{
  auto tabName = TR8( "gcw.cw.tabName.Customers" );

  /*
  ** See if this tab exists, if not, then add it.
  **
  */
  if( tabIndex( tabName ) == -1 )
  {
    /*
    ** Open a new CustomersWidget tab that is connected to the account
    **
    */
    auto widget = std::make_unique< GCW::Gui::CustomersWidget >();
    auto w = widget.get();

    /*
    ** Double Clicking on a customer causes the customer report
    **  widget to open.
    **
    */
    w->
      doubleClicked().connect( [=]( const std::string & _customerGuid )
      {
        open_CustomerReportWidget( _customerGuid );
      });

    auto tab =
      tabWidget()->
        insertTab
        ( 1,
          std::move( widget ),
          tabName
        );

    tab-> setCloseable( true );

  } // endif( tabIndex( _account-> name() ) == -1 )

  /*
  ** Go straight to the tab.
  **
  */
  tabWidget()-> setCurrentIndex( tabIndex( tabName ) );

} // endopen_CustomersWidget()-> void

auto
GCW::Gui::CentralWidget::
open_BillPayWidget()-> void
{
  auto tabName = TR8( "gcw.cw.tabName.BillPay" );

  /*
  ** See if this tab exists, if not, then add it.
  **
  */
  if( tabIndex( tabName ) == -1 )
  {
    /*
    ** Open a new CustomersWidget tab that is connected to the account
    **
    */
    std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

    auto widget = std::make_unique< GCW::Gui::BillPay::MainWidget >();
    std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

    auto w = widget.get();

    auto tab =
      tabWidget()->
        insertTab
        ( 1,
          std::move( widget ),
          tabName
        );

    tab-> setCloseable( true );

  } // endif( tabIndex( _account-> name() ) == -1 )

  /*
  ** Go straight to the tab.
  **
  */
  tabWidget()-> setCurrentIndex( tabIndex( tabName ) );

} // endopen_BillPayWidget()-> void

auto
GCW::Gui::CentralWidget::
open_TablesWidget()-> void
{
  auto tabName = "RawTables";

  /*
  ** See if this tab exists, if not, then add it.
  **
  */
  if( tabIndex( tabName ) == -1 )
  {
    /*
    ** Open a new SlotsWidget tab that is connected to the account
    **
    */
//    auto widget = std::make_unique< GCW::Gui::SlotsWidget >();
    auto widget = std::make_unique< Wt::WTabWidget >();

    auto tw = widget.get();

    auto tab =
      tabWidget()->
        insertTab
        ( 1,
          std::move( widget ),
          tabName
        );

    tab-> setCloseable( true );

    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Books        ::Item > >(), "books"        );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: BillTerms    ::Item > >(), "billterms"    );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Accounts     ::Item > >(), "accounts"     );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Versions     ::Item > >(), "versions"     );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Entries      ::Item > >(), "entries"      );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Invoices     ::Item > >(), "invoices"     );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: GncLock      ::Item > >(), "gnclock"      );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Customers    ::Item > >(), "customers"    );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Slots        ::Item > >(), "slots"        );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Splits       ::Item > >(), "splits"       );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Transactions ::Item > >(), "transactions" );
    tw-> addTab( std::make_unique< GCW::Gui::RawTableWidget< typename GCW::Dbo:: Vars         ::Item > >(), "vars"         );

  } // endif( tabIndex( _account-> name() ) == -1 )

  /*
  ** Go straight to the tab.
  **
  */
  tabWidget()-> setCurrentIndex( tabIndex( tabName ) );

} // endopen_TablesWidget()-> void

auto
GCW::Gui::CentralWidget::
test()-> void
{
  if( auto registerWidget = dynamic_cast< GCW::Gui::AccountRegister* >( tabWidget()-> widget( tabWidget()-> currentIndex() ) ) )
  {
    registerWidget-> test();
  }

} // endtest()-> void



