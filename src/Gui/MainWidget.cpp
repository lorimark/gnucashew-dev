#line 2 "src/Gui/MainWidget.cpp"

#include <Wt/WDialog.h>
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








