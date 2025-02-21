#line 2 "src/Gui/MainWidget.cpp"

#include <Wt/WMenu.h>
#include <Wt/WDialog.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/Json/Serializer.h>

#include "../define.h"
#include "../GnuCashew.h"
#include "MainWidget.h"
#include "FilePropertiesWidget.h"
#include "LanguagePicker.h"

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
  **
  */
  auto link = Wt::WLink( TR8("gcw_gui.doxygen_link") );
  link.setTarget( Wt::LinkTarget::NewWindow );
  navBar()-> setResponsive( true );
  navBar()-> addStyleClass( "navbar-light bg-light" );
  navBar()-> setTitle( "GCW", link );

  auto m_menu = navBar()-> addMenu( std::make_unique< Wt::WMenu >() );

  /*
  ** install the site language selector
  */
  navBar()-> addWidget( std::make_unique< LanguagePicker >(), Wt::AlignmentFlag::Right );

  /*
  ** FILE
  */
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
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.properties" ), this, &MainWidget:: open_properties );
    popFile-> addSeparator();
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.close"      ) )-> setDisabled( true );
    popFile-> addItem( TR( "gcw.MainWidget.mu.file.quit"       ) )-> setDisabled( true );
    m_uFile-> setMenu( std::move( popFile ) );

  } // endFILE

  /*
  ** EDIT
  */
  {
    auto m_uEdit = m_menu-> addItem( TR( "gcw.MainWidget.mu.edit" ) );
    auto popEdit = std::make_unique< Wt::WPopupMenu >();
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.cut"             ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.copy"            ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.paste"           ) )-> setDisabled( true );
    popEdit-> addSeparator();
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.edit"            ), this, &MainWidget:: openSelectedAccount );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.delete"          ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.find"            ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.cascade"         ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.renumber"        ) )-> setDisabled( true );
    popEdit-> addSeparator();
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.openaccount"     ) )-> setDisabled( true );
    popEdit-> addItem( TR( "gcw.MainWidget.mu.edit.opensubaccounts" ) )-> setDisabled( true );
    m_uEdit-> setMenu( std::move( popEdit ) );

  } // endEDIT

  /*
  ** VIEW
  */
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

  } // endVIEW

  /*
  ** ACTIONS
  */
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

  } // endACTIONS

  /*
  ** BUSINESS
  */
  {
    auto m_uBusiness = m_menu-> addItem( TR( "gcw.MainWidget.mu.business" ) );
    auto popBusiness = std::make_unique< Wt::WPopupMenu >();

    /*
    ** CUSTOMER->
    */
    {
      auto m_uCustomer = popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.customer" ) );
      auto popCustomer = std::make_unique< Wt::WPopupMenu >();
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.overview"       ), centralWidget(), &CentralWidget::open_CustomersWidget );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.newCustomer"    ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.findCustomer"   ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.newInvoice"     ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.findInvoice"    ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.newJob"         ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.findJob"        ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.processPayment" ) )-> setDisabled( true );
      popCustomer-> addItem( TR( "gcw.MainWidget.mu.business.customer.invoicesDue"    ) )-> setDisabled( true );
      m_uCustomer-> setMenu( std::move( popCustomer ) );
    }

    /*
    ** VENDOR->
    */
    {
      auto m_uVendor = popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.vendor"        ) );
      m_uVendor-> setDisabled( true );
      auto popVendor = std::make_unique< Wt::WPopupMenu >();
      popVendor-> addItem( TR( "gcw.MainWidget.mu.business.vendor.overview"       ) /* , centralWidget(), &CentralWidget::open_CustomersWidget */ )-> setDisabled( true );
      popVendor-> addItem( TR( "gcw.MainWidget.mu.business.vendor.newVendor"      ) )-> setDisabled( true );
      popVendor-> addItem( TR( "gcw.MainWidget.mu.business.vendor.findVendor"     ) )-> setDisabled( true );
      popVendor-> addItem( TR( "gcw.MainWidget.mu.business.vendor.newBill"        ) )-> setDisabled( true );
      popVendor-> addItem( TR( "gcw.MainWidget.mu.business.vendor.findBill"       ) )-> setDisabled( true );
      popVendor-> addItem( TR( "gcw.MainWidget.mu.business.vendor.newJob"         ) )-> setDisabled( true );
      popVendor-> addItem( TR( "gcw.MainWidget.mu.business.vendor.findJob"        ) )-> setDisabled( true );
      popVendor-> addItem( TR( "gcw.MainWidget.mu.business.vendor.processPayment" ) )-> setDisabled( true );
      popVendor-> addItem( TR( "gcw.MainWidget.mu.business.vendor.invoicesDue"    ) )-> setDisabled( true );
      m_uVendor-> setMenu( std::move( popVendor ) );
    }

    /*
    ** EMPLOYEE->
    */
    {
      auto m_uEmployee = popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.employee" ) );
      auto popEmployee = std::make_unique< Wt::WPopupMenu >();
      popEmployee-> addItem( TR( "gcw.MainWidget.mu.business.employee.overview"       ), centralWidget(), &CentralWidget::open_EmployeesWidget );
      popEmployee-> addItem( TR( "gcw.MainWidget.mu.business.employee.new"            ) )-> setDisabled( true );
      popEmployee-> addItem( TR( "gcw.MainWidget.mu.business.employee.find"           ) )-> setDisabled( true );
      popEmployee-> addItem( TR( "gcw.MainWidget.mu.business.employee.newExpense"     ) )-> setDisabled( true );
      popEmployee-> addItem( TR( "gcw.MainWidget.mu.business.employee.findExpense"    ) )-> setDisabled( true );
      popEmployee-> addItem( TR( "gcw.MainWidget.mu.business.employee.processPayment" ) )-> setDisabled( true );
      m_uEmployee-> setMenu( std::move( popEmployee ) );
    }

    popBusiness-> addSeparator();
    popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.linked"        ) )-> setDisabled( true );
    popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.salestax"      ) )-> setDisabled( true );
    popBusiness-> addItem( TR( "gcw.MainWidget.mu.business.billingterms"  ) )-> setDisabled( true );
    m_uBusiness-> setMenu( std::move( popBusiness ) );

  } // endBUSINESS

  /*
  ** REPORTS
  */
  {
    auto m_uReports = m_menu-> addItem( TR( "gcw.MainWidget.mu.reports" ) );
    auto popReports = std::make_unique< Wt::WPopupMenu >();

    /*
    ** ASSETS & LIABILITIES->
    */
    {
      auto m_uAssets = popReports-> addItem( TR( "gcw.MainWidget.mu.reports.assets" ) );
      auto popAssets = std::make_unique< Wt::WPopupMenu >();
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.advancedportfolio"   ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.assetchart"          ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.assetpiechart"       ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.balanceforecast"     ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.balancesheet"        ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.balancesheetmulti"   ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.balancesheeteguile"  ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.generaljournal"      ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.generalledger"       ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.investmentlots"      ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.investmentportfolio" ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.liabilitychart"      ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.liabilitypiechart"   ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.networthbarchart"    ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.networthlinechart"   ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.pricescatterplot"    ) )-> setDisabled( true );
      popAssets-> addItem( TR( "gcw.MainWidget.mu.reports.assets.securitypiechart"    ) )-> setDisabled( true );
      m_uAssets-> setMenu( std::move( popAssets ) );
    }

    /*
    ** BUDGET->
    */
    {
      auto m_uBudget = popReports-> addItem( TR( "gcw.MainWidget.mu.reports.budget" ) );
      auto popBudget = std::make_unique< Wt::WPopupMenu >();
      popBudget-> addItem( TR( "gcw.MainWidget.mu.reports.budget.balancesheet"        ) )-> setDisabled( true );
      popBudget-> addItem( TR( "gcw.MainWidget.mu.reports.budget.chart"               ) )-> setDisabled( true );
      popBudget-> addItem( TR( "gcw.MainWidget.mu.reports.budget.flow"                ) )-> setDisabled( true );
      popBudget-> addItem( TR( "gcw.MainWidget.mu.reports.budget.incomestatement"     ) )-> setDisabled( true );
      popBudget-> addItem( TR( "gcw.MainWidget.mu.reports.budget.profitnloss"         ) )-> setDisabled( true );
      popBudget-> addItem( TR( "gcw.MainWidget.mu.reports.budget.report"              ) )-> setDisabled( true );
      m_uBudget-> setMenu( std::move( popBudget ) );
    }

    /*
    ** BUSINESS->
    */
    {
      auto m_uBusiness = popReports-> addItem( TR( "gcw.MainWidget.mu.reports.business" ) );
      auto popBusiness = std::make_unique< Wt::WPopupMenu >();
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.australiantaxinv"  ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.customerreport"    ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.customersummary"   ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.easyinvoice"       ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.employeereport"    ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.fancyinvoice"      ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.jobreport"         ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.payableaging"      ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.printableinvoice"  ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.receipt"           ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.receivableaging"   ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.taxinvoice"        ) )-> setDisabled( true );
      popBusiness-> addItem( TR( "gcw.MainWidget.mu.reports.business.vendorreport"      ) )-> setDisabled( true );
      m_uBusiness-> setMenu( std::move( popBusiness ) );
    }

    /*
    ** EXAMPLES->
    */
    {
      auto m_uExamples = popReports-> addItem( TR( "gcw.MainWidget.mu.reports.examples" ) );
      auto popExamples = std::make_unique< Wt::WPopupMenu >();
      popExamples-> addItem( TR( "gcw.MainWidget.mu.reports.examples.averagebalance"    ) )-> setDisabled( true );
      popExamples-> addItem( TR( "gcw.MainWidget.mu.reports.examples.expdow"            ) )-> setDisabled( true );
      popExamples-> addItem( TR( "gcw.MainWidget.mu.reports.examples.incdow"            ) )-> setDisabled( true );
      popExamples-> addItem( TR( "gcw.MainWidget.mu.reports.examples.samplegraphs"      ) )-> setDisabled( true );
      popExamples-> addItem( TR( "gcw.MainWidget.mu.reports.examples.samplereport"      ) )-> setDisabled( true );
      m_uExamples-> setMenu( std::move( popExamples ) );
    }

    /*
    ** EXPERIMENTAL->
    */
    {
      auto m_uExperimental = popReports-> addItem( TR( "gcw.MainWidget.mu.reports.experimental" ) );
      auto popExperimental = std::make_unique< Wt::WPopupMenu >();
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.experimental.ifrsweighted"      ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.experimental.transbreakd"       ) )-> setDisabled( true );
      m_uExperimental-> setMenu( std::move( popExperimental ) );
    }

    /*
    ** INCOME & EXPENSE->
    */
    {
      auto m_uExperimental = popReports-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp" ) );
      auto popExperimental = std::make_unique< Wt::WPopupMenu >();
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.cashflow"      ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.cashflowbar"   ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.equitystmt"    ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.expensechart"  ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.expensepie"    ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.incngststmt"   ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.incchart"      ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.incnexpbar"    ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.incnexpline"   ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.incpie"        ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.incstmt"       ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.incstmtmulti"  ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.profitloss"    ) )-> setDisabled( true );
      popExperimental-> addItem( TR( "gcw.MainWidget.mu.reports.incnexp.trialbal"      ) )-> setDisabled( true );
      m_uExperimental-> setMenu( std::move( popExperimental ) );
    }

    /*
    ** MULTICOLUMN->
    */
    {
      auto m_uMulcol = popReports-> addItem( TR( "gcw.MainWidget.mu.reports.mulcol" ) );
      auto popMulcol = std::make_unique< Wt::WPopupMenu >();
      popMulcol-> addItem( TR( "gcw.MainWidget.mu.reports.mulcol.custom"            ) )-> setDisabled( true );
      popMulcol-> addItem( TR( "gcw.MainWidget.mu.reports.mulcol.dashb"             ) )-> setDisabled( true );
      m_uMulcol-> setMenu( std::move( popMulcol ) );
    }

    popReports-> addItem( TR( "gcw.MainWidget.mu.reports.accountsumm"     ) )-> setDisabled( true );
    popReports-> addItem( TR( "gcw.MainWidget.mu.reports.futuresched"     ) )-> setDisabled( true );
    popReports-> addItem( TR( "gcw.MainWidget.mu.reports.reconciliation"  ) )-> setDisabled( true );
    popReports-> addItem( TR( "gcw.MainWidget.mu.reports.taxsched"        ) )-> setDisabled( true );
    popReports-> addItem( TR( "gcw.MainWidget.mu.reports.transaction"     ) )-> setDisabled( true );
    popReports-> addItem( TR( "gcw.MainWidget.mu.reports.saved"           ) )-> setDisabled( true );

    m_uReports-> setMenu( std::move( popReports ) );

  } // endREPORTS

  /*
  ** TOOLS->
  */
  {
    auto m_uTools = m_menu-> addItem( TR( "gcw.MainWidget.mu.tools" ) );
    auto popTools = std::make_unique< Wt::WPopupMenu >();

    popTools-> addItem( TR( "gcw.MainWidget.mu.tools.onlinesetup"   ) )-> setDisabled( true );
    popTools-> addItem( TR( "gcw.MainWidget.mu.tools.pricedb"       ) )-> setDisabled( true );
    popTools-> addItem( TR( "gcw.MainWidget.mu.tools.securityedit"  ) )-> setDisabled( true );
    popTools-> addItem( TR( "gcw.MainWidget.mu.tools.loanrepayment" ) )-> setDisabled( true );
    popTools-> addItem( TR( "gcw.MainWidget.mu.tools.closebook"     ) )-> setDisabled( true );
    popTools-> addItem( TR( "gcw.MainWidget.mu.tools.importmap"     ) )-> setDisabled( true );
    popTools-> addItem( TR( "gcw.MainWidget.mu.tools.translinkdoc"  ) )-> setDisabled( true );
    popTools-> addItem( TR( "gcw.MainWidget.mu.tools.generaljourn"  ) )-> setDisabled( true );

    m_uTools-> setMenu( std::move( popTools ) );
  }

  /*
  ** HELP->
  */
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

} // endload()-> void

auto
GCW::Gui::MainWidget::
open_properties()-> void
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

auto
GCW::Gui::MainWidget::
openSelectedAccount()-> void
{
  centralWidget()-> accountsTreeView()-> editSelectedAccount();

} // endopenSelectedAccount()


auto
test_gnucash()-> void
{

} // endvoid test_gnucash()

auto
GCW::Gui::MainWidget::
test()-> void
{
  test_gnucash();

} // endtest()








