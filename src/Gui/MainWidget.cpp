#line 2 "src/Gui/MainWidget.cpp"

#include <random>

#include <Wt/WDialog.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/Json/Serializer.h>

#include "../define.h"
#include "../GnuCashew.h"
#include "../Eng/TransactionManager.h"
#include "MainWidget.h"
#include "FilePropertiesWidget.h"
#include "LanguagePicker.h"

class PushButton
: public Wt::WPushButton
{
  public:

    PushButton( const Wt::WString & _text )
    : Wt::WPushButton( _text )
    {
      setStyleClass( "btn-xs" );
      setAttributeValue( "style", "margin-left:3px;margin-right:3px" );
    }

};

GCW::Gui::MainWidget::
MainWidget()
{
  addStyleClass( "MainWidget" );

  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );
  lw-> setSpacing( 0 );

  m_navBar        = lw-> addWidget( std::make_unique< Wt::WNavigationBar      >()    );
  m_navBar-> addStyleClass( "NavBar" );

  m_toolBar       = lw-> addWidget( std::make_unique< Wt::WToolBar            >()    );
  m_toolBar-> addStyleClass( "ToolBar" );

  m_centralWidget = lw-> addWidget( std::make_unique< GCW::Gui::CentralWidget >(), 1 );

  m_statusBar     = lw-> addWidget( std::make_unique< Wt::WContainerWidget    >()    );
  m_statusBar-> addStyleClass( "StatusBar" );

} // endGCW::MainWidget::MainWidget()

auto
GCW::Gui::MainWidget::
load()-> void
{
  Wt::WContainerWidget::load();

  /*
  ** Set up the navbar
  */
  auto link = Wt::WLink( TR8("gcw_gui.doxygen_link") );
  link.setTarget( Wt::LinkTarget::NewWindow );
  navBar()-> setResponsive( true );
  navBar()-> addStyleClass( "navbar-light bg-light" );
  navBar()-> setTitle( "GCW", link );

  /*
  ** install the main menu
  */
  {
    auto w_ = std::make_unique< GCW::Gui::MainMenu >( this );
    m_mainMenu = w_.get();
    navBar()-> addMenu( std::move( w_ ) );
  }

  /*
  ** install the site language selector
  */
  navBar()-> addWidget( std::make_unique< LanguagePicker >(), Wt::AlignmentFlag::Right );

  /*
  ** plop all the buttons down
  */
  toolBar()-> addButton( std::make_unique< PushButton >( TR( "gcw.MainWidget.tb.save"       ) ) );
  toolBar()-> addButton( std::make_unique< PushButton >( TR( "gcw.MainWidget.tb.close"      ) ) );
  toolBar()-> addButton( std::make_unique< PushButton >( TR( "gcw.MainWidget.tb.newInvoice" ) ) );
  toolBar()-> addButton( std::make_unique< PushButton >( TR( "gcw.MainWidget.tb.open"       ) ) );

  {
    auto b = std::make_unique< PushButton >( TR( "gcw.MainWidget.tb.edit" ) );
    auto e = b.get();
    toolBar()-> addButton( std::move(b) );
    e-> clicked().connect( [=](){ openSelectedAccount(); });
  }

  toolBar()-> addButton( std::make_unique< PushButton >( TR( "gcw.MainWidget.tb.new"    ) ) );
  toolBar()-> addButton( std::make_unique< PushButton >( TR( "gcw.MainWidget.tb.delete" ) ) );

#ifdef ENABLE_DEV
  {
    auto b = std::make_unique< PushButton >( "devtest" );
    auto e = b.get();
    toolBar()-> addButton( std::move(b) );
    e-> clicked().connect( [=](){ test(); });
  }
#endif

  statusBar()-> addNew< Wt::WText >( "status bar" );

} // endload()-> void

auto
GCW::Gui::MainWidget::
open_properties()-> void
{
  if( !GCW::app()-> gnucashew_session().isOpen() )
    return;

  auto dialog = addChild( std::make_unique< Wt::WDialog >( TR( "gcw.PropertiesWidget.titleBar" ) ) );
  dialog-> rejectWhenEscapePressed( true );
  dialog-> contents()-> addNew< GCW::Gui::FilePropertiesWidget >();
  dialog-> show();
  dialog->
    finished().connect( [=]()
    {
      removeChild( dialog );
    });

} // endopen_properties()

auto
GCW::Gui::MainWidget::
open_aboutWidget()-> void
{
  auto templt = std::make_unique< Wt::WTemplate >( TR( "gcw.AboutWidget.about" ) );
  templt-> bindString( "version", "none" );
  templt-> bindString( "buildid", "none" );
  templt-> bindString( "finance", "none (yet)" );

  auto dialog = addChild( std::make_unique< Wt::WDialog >( TR( "gcw.AboutWidget.titleBar" ) ) );
  dialog-> rejectWhenEscapePressed( true );
  dialog-> contents()-> addWidget( std::move( templt ) );
  dialog-> show();
  dialog->
    finished().connect( [=]()
    {
      removeChild( dialog );
    });

} // endopen_properties()

auto
GCW::Gui::MainWidget::
openSelectedAccount()-> void
{
  centralWidget()-> activateAccountsTreeView();
  centralWidget()-> accountsTreeView()-> editSelectedAccount();

} // endopenSelectedAccount()

auto
GCW::Gui::MainWidget::
setBasicLedger()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

}

auto
GCW::Gui::MainWidget::
setAutosplit()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

}

auto
GCW::Gui::MainWidget::
setTransaction()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

}

auto
GCW::Gui::MainWidget::
setDoubleLine()-> void
{
  if( auto accountRegister = centralWidget()-> currentAccountRegister() )
  {
    auto doubleLine = m_mainMenu-> menuItem( TR( "gcw.MainWidget.mu.view.doubleline" ) );

    accountRegister-> setDoubleLine( doubleLine-> isChecked() );
  }

} // endsetDoubleLine()-> void

namespace {

auto randomNumber( int _min, int _max )-> int
{
  static std::random_device rd;  // Non-deterministic seed
  static std::mt19937 gen( rd() ); // Mersenne Twister RNG

  std::uniform_int_distribution<> dist( _min, _max ); // inclusive range

  auto retVal = dist( gen );

  return retVal;

} // endauto randomNumber( int _min, int _max )-> int

auto
test_tableview()-> void
{
  auto model = std::make_shared< Wt::WStandardItemModel >();
  for( int row = 0; row< 3; row++ )
  {
    std::vector< std::unique_ptr< Wt::WStandardItem > > rowset;
    for( int col = 0; col< 3; col++ )
    {
      auto item = std::make_unique< Wt::WStandardItem >( Wt::WString("row{1} col{2}").arg( row ).arg( col) );
      rowset.push_back( std::move( item ) );
    }

    model-> appendRow( std::move( rowset ) );
  }

  auto tableView = std::make_unique< Wt::WTableView >();
  tableView-> setSelectionBehavior    ( Wt::SelectionBehavior::Items );
//  tableView-> setSelectionBehavior    ( Wt::SelectionBehavior::Rows  );
//  tableView-> setSelectionMode        ( Wt::SelectionMode::Single    );
  tableView-> setSelectionMode        ( Wt::SelectionMode::Extended  );
  tableView-> setColumnResizeEnabled  ( false                        );
  tableView-> setAlternatingRowColors ( true                         );
  tableView-> setModel                ( model                        );

  Wt::WDialog dialog( "test" );
  dialog.contents()-> addWidget( std::move( tableView ) );
  dialog.rejectWhenEscapePressed( true );
  dialog.setClosable( true );
  dialog.exec();

} // endtest_tableview()-> void

auto
load_random_transactions()
{
  std::map< std::string, std::vector< std::string > > expenses = {
    { "Expenses:Medical Expenses",
      {
        "Copay for doctor visit",
        "Prescription refill – CVS",
        "Dental cleaning – Dr. Smith",
        "Urgent care visit – weekend",
        "Eye exam – optometrist",
        "Physical therapy session",
        "Lab tests – Quest Diagnostics",
        "Over-the-counter medication",
        "Hospital parking fee",
        "Flu shot – Walgreens"
      }},
    { "Expenses:Laundry/Dry Cleaning",
      {
        "Dry cleaning suit – Cleaners Plus",
        "Wash & fold service",
        "Shirt pressing – Express Cleaners",
        "Comforter dry cleaned",
        "Stain removal – silk blouse",
        "Laundry card refill",
        "Pickup & delivery laundry",
        "Uniform cleaning",
        "Curtain dry cleaning",
        "Weekly laundry service"
      }},
    { "Expenses:Groceries",
      {
        "Weekly grocery run – Walmart",
        "Produce market – fresh veggies",
        "Milk and bread – local store",
        "Bulk items – Costco",
        "Organic produce – Whole Foods",
        "Meat & seafood purchase",
        "Baking supplies – holiday",
        "Frozen goods – Aldi",
        "Snacks and beverages",
        "Pet food – grocery aisle"
      }},
    { "Expenses:Cable",
      {
        "Monthly cable bill – Spectrum",
        "Sports channel add-on",
        "Premium movie package",
        "DVR upgrade fee",
        "Service technician visit",
        "Late payment fee",
        "Internet & cable bundle",
        "Pay-per-view boxing event",
        "Channel upgrade request",
        "Equipment rental fee"
      }},
    { "Expenses:Taxes:Other Tax",
      {
        "Local occupancy tax",
        "Vehicle registration tax",
        "Luxury goods tax",
        "Parking permit tax",
        "Short-term rental tax",
        "City environmental fee",
        "Import duty – online order",
        "Special assessment tax",
        "Utility usage surcharge",
        "Tourism tax"
      }},
    { "Expenses:Computer",
      {
        "New laptop purchase",
        "External hard drive – backup",
        "Software subscription – Adobe",
        "Keyboard & mouse combo",
        "Replacement charger",
        "RAM upgrade",
        "Anti-virus renewal",
        "Laptop repair service",
        "Cloud storage subscription",
        "Graphics card upgrade"
      }},
    { "Expenses:Phone",
      {
        "Monthly mobile bill – Verizon",
        "New phone case",
        "Data overage charge",
        "International calling plan",
        "Screen protector purchase",
        "Device insurance premium",
        "Phone upgrade fee",
        "SIM card replacement",
        "Voicemail-to-text add-on",
        "Mobile hotspot charge"
      }},
    { "Expenses:Books",
      {
        "Textbook purchase – college",
        "E-book download – Kindle",
        "Magazine subscription",
        "Used books – thrift store",
        "Study guide – exam prep",
        "Children’s storybook",
        "Hardcover bestseller",
        "Travel guidebook",
        "Audio book subscription",
        "Book club order"
      }},
    { "Expenses:Insurance:Health Insurance",
      {
        "Monthly premium – Blue Cross",
        "Policy renewal fee",
        "Dependent coverage add-on",
        "COBRA payment",
        "Out-of-network reimbursement",
        "Health plan deductible payment",
        "Policy admin charge",
        "Wellness program fee",
        "Health savings account contribution",
        "Employer premium adjustment"
      }},
    { "Expenses:Supplies",
      {
        "Office paper & pens",
        "Printer ink cartridges",
        "Cleaning supplies – janitorial",
        "Packaging tape – shipping",
        "Storage bins purchase",
        "Paper towels & tissues",
        "Refill for whiteboard markers",
        "Safety gloves & masks",
        "Breakroom coffee supplies",
        "Stationery order"
      }},
    { "Expenses:Taxes:Social Security",
      {
        "Social security tax withholding",
        "Additional SS tax adjustment",
        "Employer SS contribution",
        "Self-employment SS tax",
        "Catch-up SS payment",
        "Late SS filing fee",
        "SS estimated tax",
        "Overpayment refund offset",
        "Correction to SS tax",
        "Supplemental SS fee"
      }},
    { "Expenses:Entertainment:Recreation",
      {
        "Movie tickets – Friday night",
        "Bowling alley fee",
        "Zoo admission",
        "Amusement park day pass",
        "Concert ticket – local band",
        "Game rental – board games",
        "Streaming movie rental",
        "Mini golf outing",
        "Escape room experience",
        "Comedy club cover charge"
      }},
    { "Expenses:Online Services",
      {
        "Cloud backup subscription",
        "Website hosting fee",
        "Domain renewal – personal site",
        "Streaming service – Netflix",
        "VPN annual plan",
        "Stock photo download",
        "Music subscription – Spotify",
        "Online course enrollment",
        "Web app premium upgrade",
        "Paid newsletter subscription"
      }},
    { "Expenses:Taxes:State/Province",
      {
        "State income tax payment",
        "Quarterly state estimated tax",
        "State tax penalty",
        "State tax refund offset",
        "State franchise tax",
        "State use tax – online order",
        "State excise tax",
        "State annual filing fee",
        "State surtax adjustment",
        "State environmental surcharge"
      }},
    { "Expenses:Insurance:Life Insurance",
      {
        "Term life premium – annual",
        "Whole life policy contribution",
        "Beneficiary change fee",
        "Policy loan interest payment",
        "Cash value withdrawal fee",
        "Additional rider premium",
        "Coverage renewal",
        "Life insurance underwriting fee",
        "Group life policy payment",
        "Late policy premium fee"
      }},
    { "Expenses:Auto:Fuel",
      {
        "Gas fill-up – Shell",
        "Diesel purchase – truck",
        "Premium fuel – road trip",
        "Gasoline – self-service",
        "Fuel for rental car",
        "Prepaid gas card load",
        "Gas station coffee & snack",
        "Topping off tank – holiday",
        "Discount fuel club purchase",
        "Fleet vehicle refueling"
      }}
  };

// Assets:Current Assets:Checking Account
// Income:Salary

  auto pb_expense = std::make_unique< Wt::WPushButton >( "load random expenses" );
  pb_expense.get()->
    clicked().connect( [=]()
    {
      GCW::Eng::Transaction::Manager transMan;

      auto account1 = GCW::Dbo::Accounts::byFullName( "Assets:Current Assets:Checking Account" );
      std::cout << __FILE__ << ":" << __LINE__
        << " " << account1
        << " " << expenses.size()
        << " " << account1-> name()
        << std::endl;

      for( auto expense : expenses )
      {
        auto account2 = GCW::Dbo::Accounts::byFullName( expense.first );

        std::cout << __FILE__ << ":" << __LINE__
          << " " << account2
          << " " << expense.second.size()
          << " " << expense.first
          << std::endl;

        for( auto second : expense.second )
        {
          GCW_NUMERIC value( float( 1234.0 / randomNumber( 1, 99 ) ) );

          auto number = randomNumber( 0, 9 );

          transMan
            .newTransaction
            (
             account1-> guid(),
             account2-> guid(),
             Wt::WDate::currentDate().addDays( randomNumber( 0, 365) ),
             -value,
             expense.second.at( number )
            );

        } // endfor( auto second : expense.second )

      } // endfor( auto expense : expenses )

    });

  auto pb_income = std::make_unique< Wt::WPushButton >( "load random income" );
  pb_income.get()->
    clicked().connect( [=]()
    {
      GCW::Eng::Transaction::Manager transMan;

      auto account1 = GCW::Dbo::Accounts::byFullName( "Assets:Current Assets:Checking Account" );
      std::cout << __FILE__ << ":" << __LINE__
        << " " << account1
        << " " << expenses.size()
        << " " << account1-> name()
        << std::endl;

      auto account2 = GCW::Dbo::Accounts::byFullName( "Income:Salary" );

      for( int i=0; i< 12; i++ )
      {
          GCW_NUMERIC value( randomNumber( 1000, 2000 ) );

          transMan
            .newTransaction
            (
             account1-> guid(),
             account2-> guid(),
             Wt::WDate::currentDate().addDays( 60 + 28 * i + randomNumber( -5, 5 ) ),
             value,
             "Income"
            );

      } // endfor( auto expense : expenses )

    });

  Wt::WDialog dialog( "random transactions" );
  dialog.contents()-> addWidget( std::move( pb_expense ) );
  dialog.contents()-> addWidget( std::make_unique< Wt::WBreak >() );
  dialog.contents()-> addWidget( std::move( pb_income  ) );
  dialog.rejectWhenEscapePressed( true );
  dialog.setClosable( true );
  dialog.exec();

} // endload_random_transactions()

} // endnamespace {

auto
GCW::Gui::MainWidget::
test()-> void
{
//  test_tableview();
  load_random_transactions();

} // endtest()








