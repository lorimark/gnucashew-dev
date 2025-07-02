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

  {
    auto b = std::make_unique< PushButton >( "devtest" );
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

  static auto dialog = std::make_unique< Wt::WDialog >( TR( "gcw.PropertiesWidget.titleBar" ) );
  dialog-> rejectWhenEscapePressed( true );
  dialog-> contents()-> addNew< GCW::Gui::FilePropertiesWidget >();
  dialog-> show();
  dialog->
    finished().connect( []()
    {
      dialog.reset(nullptr);
    });

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








