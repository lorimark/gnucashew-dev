#line 2 "src/Gui/MainWidget.cpp"

#include <Wt/WMenu.h>
#include <Wt/WDialog.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/Json/Serializer.h>

#include "../define.h"
#include "../GnuCashew.h"
#include "MainWidget.h"
#include "FilePropertiesWidget.h"

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

  /*
  ** Set up the navbar
  **
  */
  auto link = Wt::WLink( TR8("gcw_gui.doxygen_link") );
  link.setTarget( Wt::LinkTarget::NewWindow );
  navBar()-> setResponsive( true );
  navBar()-> addStyleClass( "navbar-light bg-light" );
  navBar()-> setTitle( "GCW", link );

  auto m_menu = navBar()-> addMenu( std::make_unique< Wt::WMenu >() );

  {
    auto m_uFile = m_menu-> addItem( TR("gcw.MainWidget.mu.file") );
    auto popFile = std::make_unique< Wt::WPopupMenu >();
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.new"        ) )-> setDisabled( true );
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.open"       ) )-> setDisabled( true );
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.import"     ) )-> setDisabled( true );
    popFile-> addSeparator();
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.save"       ) )-> setDisabled( true );
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.saveas"     ) )-> setDisabled( true );
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.revert"     ) )-> setDisabled( true );
    popFile-> addSeparator();
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.print"      ) )-> setDisabled( true );
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.pagesetup"  ) )-> setDisabled( true );
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.export"     ) )-> setDisabled( true );
    popFile-> addSeparator();
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.properties" ), this, &GCW::Gui::MainWidget::open_properties );
    popFile-> addSeparator();
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.close"      ) )-> setDisabled( true );
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.quit"       ) )-> setDisabled( true );
    m_uFile-> setMenu( std::move( popFile ) );
  }

  {
    auto m_uEdit = m_menu-> addItem( TR( "gcw.MainWidget.mu.edit" ) );
    auto popEdit = std::make_unique< Wt::WPopupMenu >();
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.cut"             ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.copy"            ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.paste"           ) )-> setDisabled( true );
    popEdit-> addSeparator();
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.edit"            ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.delete"          ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.find"            ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.cascade"         ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.renumber"        ) )-> setDisabled( true );
    popEdit-> addSeparator();
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.openaccount"     ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.opensubaccounts" ) )-> setDisabled( true );
    m_uEdit-> setMenu( std::move( popEdit ) );
  }

  {
    auto m_uView = m_menu-> addItem( TR( "gcw.MainWidget.mu.view" ) );
    auto popView = std::make_unique< Wt::WPopupMenu >();
    popView-> addItem( TR( "gcw.MainWidget.mu.view.toolbar"       ) )-> setDisabled( true );
    popView-> addItem( TR( "gcw.MainWidget.mu.view.summarybar"    ) )-> setDisabled( true );
    popView-> addItem( TR( "gcw.MainWidget.mu.view.statusbar"     ) )-> setDisabled( true );
    popView-> addItem( TR( "gcw.MainWidget.mu.view.tabposition"   ) )-> setDisabled( true );
    popView-> addSeparator();
    popView-> addItem( TR( "gcw.MainWidget.mu.view.filterby"      ) )-> setDisabled( true );
    popView-> addSeparator();
    popView-> addItem( TR( "gcw.MainWidget.mu.view.refresh"       ) )-> setDisabled( true );
    popView-> addItem( TR( "gcw.MainWidget.mu.view.newaccounts"   ) )-> setDisabled( true );
    m_uView-> setMenu( std::move( popView ) );
  }

  {
    auto m_uActions = m_menu-> addItem( TR( "gcw.MainWidget.mu.actions" ) );
    auto popActions = std::make_unique< Wt::WPopupMenu >();
    popActions-> addItem( TR( "gcw.MainWidget.mu.actions.online"        ) )-> setDisabled( true );
    popActions-> addItem( TR( "gcw.MainWidget.mu.actions.scheduled"     ) )-> setDisabled( true );
    popActions-> addItem( TR( "gcw.MainWidget.mu.actions.budget"        ) )-> setDisabled( true );

    if( GCW::app()-> gnucashew_session().hasGnuCashewExtensions() )
      popActions-> addItem( TR( "gcw.MainWidget.mu.actions.billpay"       ), centralWidget(), &GCW::Gui::CentralWidget::open_BillPayWidget );

    popActions-> addItem( "Raw Tables", centralWidget(), &GCW::Gui::CentralWidget::open_TablesWidget );

    popActions-> addSeparator();
    popActions-> addItem( TR( "gcw.MainWidget.mu.actions.resetwarnings" ) )-> setDisabled( true );
    popActions-> addItem( TR( "gcw.MainWidget.mu.actions.renamepage"    ) )-> setDisabled( true );
    m_uActions-> setMenu( std::move( popActions ) );
  }

  {
    auto m_uBusiness = m_menu-> addItem( TR( "gcw.MainWidget.mu.business" ) );
    auto popBusiness = std::make_unique< Wt::WPopupMenu >();

    {
      auto m_uCustomer = popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.customer" ) );
      auto popCustomer = std::make_unique< Wt::WPopupMenu >();
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.overview"       ), centralWidget(), &GCW::Gui::CentralWidget::open_CustomersWidget );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.newCustomer"    ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.findCustomer"   ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.newInvoice"     ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.findInvoice"    ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.newJob"         ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.findJob"        ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.processPayment" ) )-> setDisabled( true );
      m_uCustomer-> setMenu( std::move( popCustomer ) );
    }

    popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.vendor"        ) )-> setDisabled( true );
    popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.employee"      ) )-> setDisabled( true );
    popBusiness-> addSeparator();
    popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.linked"        ) )-> setDisabled( true );
    popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.salestax"      ) )-> setDisabled( true );
    popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.billingterms"  ) )-> setDisabled( true );
    m_uBusiness-> setMenu( std::move( popBusiness ) );
  }

  {
    auto m_uHelp = m_menu-> addItem( TR( "gcw.MainWidget.mu.help" ) );
    auto popHelp = std::make_unique< Wt::WPopupMenu >();
    popHelp-> addItem( TR( "gcw.MainWidget.mu.help.tutorial"      ) )-> setDisabled( true );
    popHelp-> addItem( TR( "gcw.MainWidget.mu.help.tip"           ) )-> setDisabled( true );
    popHelp-> addItem( TR( "gcw.MainWidget.mu.help.contents"      ) )-> setDisabled( true );
    popHelp-> addItem( TR( "gcw.MainWidget.mu.help.about"         ) )-> setDisabled( true );
    m_uHelp-> setMenu( std::move( popHelp ) );
  }

  toolBar()-> addButton( std::make_unique< Wt::WPushButton >( TR( "gcw.MainWidget.tb.save"       ) ) );
  toolBar()-> addButton( std::make_unique< Wt::WPushButton >( TR( "gcw.MainWidget.tb.close"      ) ) );
  toolBar()-> addButton( std::make_unique< Wt::WPushButton >( TR( "gcw.MainWidget.tb.newInvoice" ) ) );
  toolBar()-> addButton( std::make_unique< Wt::WPushButton >( TR( "gcw.MainWidget.tb.open"       ) ) );

  {
    auto b = std::make_unique< Wt::WPushButton >( TR( "gcw.MainWidget.tb.edit" ) );
    auto e = b.get();
    toolBar()-> addButton( std::move(b) );
    e-> clicked().connect( [=](){ openSelectedAccount(); });
  }

  toolBar()-> addButton( std::make_unique< Wt::WPushButton >( TR( "gcw.MainWidget.tb.new"    ) ) );
  toolBar()-> addButton( std::make_unique< Wt::WPushButton >( TR( "gcw.MainWidget.tb.delete" ) ) );

  {
    auto b = std::make_unique< Wt::WPushButton >( "devtest" );
    auto e = b.get();
    toolBar()-> addButton( std::move(b) );
    e-> clicked().connect( [=](){ test(); });
  }

  statusBar()-> addNew< Wt::WText >( "status bar" );

} // endGCW::MainWidget::MainWidget()

void
GCW::Gui::MainWidget::
open_properties()
{
  if( !GCW::app()-> gnucashew_session().isOpen() )
    return;

  auto u_ = std::make_unique< Wt::WDialog >( TR( "gcw.PropertiesWidget.titleBar" ) );
  auto dialog = u_.get();
  addChild( std::move( u_ ) );

  dialog-> rejectWhenEscapePressed( true );
  dialog-> contents()-> addNew< GCW::Gui::FilePropertiesWidget >();

  /*
  ** Clean up after the dialog is closed.
  **
  */
  dialog-> finished().connect( [&]( Wt::DialogCode _code ) { removeChild( dialog ); });
  dialog-> show();

} // endopen_properties()

void
GCW::Gui::MainWidget::
openSelectedAccount()
{
  centralWidget()-> accountsTreeView()-> editSelectedAccount();

} // endopenSelectedAccount()


void test_gnucash()
{

} // endvoid test_gnucash()


void
GCW::Gui::MainWidget::
test()
{
  test_gnucash();

} // endtest()








