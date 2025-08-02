#line 2 "src/Gui/AccountEditor.cpp"

#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WFitLayout.h>
#include <Wt/WGridLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>
#include <Wt/WCheckBox.h>

#include "AccountEditor.h"

class AccountTypeCombo
: public Wt::WComboBox
{
  public:

    AccountTypeCombo( const std::string & _initialValue )
    {
      /*
      ** Load all the items in the combo box, based on a translation of the
      **  backend name of the account type.
      **
      */
      for( auto & def : GCW::Dbo::Accounts::s_accountDefs )
        addItem( Wt::WString::tr( Wt::WString("gcw.AccountsType.{1}").arg( def.backendName ).toUTF8() ) );

      /*
      ** Find the backend name requested, and make sure that is the
      **  selected item.
      **
      */
      int index = 0;
      for( auto & def : GCW::Dbo::Accounts::s_accountDefs )
      {
        if( def.backendName == _initialValue )
          break;
        index++;
      }
      setCurrentIndex( index );

    } // endAccountTypeCombo( const std::string & _initialValue )

}; // endclass AccountTypeCombo

class SecurityCombo
: public Wt::WComboBox
{
  public:

    SecurityCombo()
    {
    }

}; // endclass AccountTypeCombo

class SmallestFractionCombo
: public Wt::WComboBox
{
  public:

    SmallestFractionCombo()
    {
      addItem( TR( "gcw.AccountEditor.usecommodity" ) );
      addItem( "1"                                    );
      addItem( "1/10"                                 );
      addItem( "1/100"                                );
      addItem( "1/1000"                               );
      addItem( "1/10000"                              );
      addItem( "1/100000"                             );
      addItem( "1/1000000"                            );
      addItem( "1/10000000"                           );
      addItem( "1/100000000"                          );
      addItem( "1/1000000000"                         );
    }

}; // endclass AccountTypeCombo

GCW::Gui::AccountEditor::Tab1::
Tab1( const std::string & _accountGuid )
: m_accountGuid( _accountGuid )
{
  /*
  ** Get the accountItem loaded so we can pluck things from it.
  **
  */
  auto accountItem = GCW::Dbo::Accounts::load( m_accountGuid );

  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );
  auto t1 = lw-> addWidget( std::make_unique< Wt::WTemplate >( TR( "gcw_gui.accounteditor.form.tab1" ) ) );

  t1-> bindString( "name-label"        , TR( "gcw.AccountEditor.name"        ) );
  t1-> bindString( "code-label"        , TR( "gcw.AccountEditor.code"        ) );
  t1-> bindString( "desc-label"        , TR( "gcw.AccountEditor.desc"        ) );
  t1-> bindString( "parent-label"      , TR( "gcw.AccountEditor.parent"      ) );
  t1-> bindString( "accountType-label" , TR( "gcw.AccountEditor.accountType" ) );
  t1-> bindString( "security-label"    , TR( "gcw.AccountEditor.security"    ) );
  t1-> bindString( "fraction-label"    , TR( "gcw.AccountEditor.fraction"    ) );
  t1-> bindString( "color-label"       , TR( "gcw.AccountEditor.color"       ) );
  t1-> bindString( "notes-label"       , TR( "gcw.AccountEditor.notes"       ) );

  auto name           = t1-> bindNew< Wt::WLineEdit              >( "name"           , accountItem-> name()                     );
  auto code           = t1-> bindNew< Wt::WLineEdit              >( "code"           , accountItem-> code()                     );
  auto desc           = t1-> bindNew< Wt::WLineEdit              >( "desc"           , accountItem-> description()              );
  auto parent         = t1-> bindNew< GCW::Gui::AccountsTreeView >( "parent"         , accountItem-> parent_guid() , 7          );
  auto accountType    = t1-> bindNew< AccountTypeCombo           >( "accountType"    , accountItem-> accountTypeName()          );
  auto security       = t1-> bindNew< SecurityCombo              >( "security"                                                  );
  auto fraction       = t1-> bindNew< SmallestFractionCombo      >( "fraction"                                                  );
  auto color          = t1-> bindNew< Wt::WPushButton            >( "color"          , TR( "gcw.AccountEditor.colorpicker"    ) );
  auto colordefault   = t1-> bindNew< Wt::WPushButton            >( "colordefault"   , TR( "gcw.AccountEditor.colordefault"   ) );
  auto notes          = t1-> bindNew< Wt::WTextArea              >( "notes"                                                     );
  auto placeholder    = t1-> bindNew< Wt::WCheckBox              >( "placeholder"    , TR( "gcw.AccountEditor.placeholder"    ) );
  auto hidden         = t1-> bindNew< Wt::WCheckBox              >( "hidden"         , TR( "gcw.AccountEditor.hidden"         ) );
  auto autoTransfer   = t1-> bindNew< Wt::WCheckBox              >( "autoTransfer"   , TR( "gcw.AccountEditor.autoTransfer"   ) );
  auto taxRelated     = t1-> bindNew< Wt::WCheckBox              >( "taxRelated"     , TR( "gcw.AccountEditor.taxRelated"     ) );
  auto openingBalance = t1-> bindNew< Wt::WCheckBox              >( "openingBalance" , TR( "gcw.AccountEditor.openingBalance" ) );

  color        -> setWidth( "100%" );
  colordefault -> setWidth( "100%" );

  parent-> setMaximumSize( Wt::WLength::Auto, Wt::WLength("220px") );

} // endTab1( const std::string & _accountGuid )

GCW::Gui::AccountEditor::Tab2::
Tab2( const std::string & _accountGuid )
: m_accountGuid( _accountGuid )
{
  auto lw  = setLayout( std::make_unique< Wt::WFitLayout >() );
  auto t2  = lw-> addWidget( std::make_unique< Wt::WTemplate >( TR( "gcw_gui.accounteditor.form.tab2" ) ) );

} // endTab2( const std::string & _accountGuid )


GCW::Gui::AccountEditor::
AccountEditor( const std::string & _accountGuid )
: m_accountGuid( _accountGuid )
{
  addStyleClass( "AccountEditor" );

  /*
  ** Get the accountItem loaded so we can pluck things from it.
  **
  */
  auto accountItem = GCW::Dbo::Accounts::load( m_accountGuid );

  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );

  lw-> addWidget( std::make_unique< Wt::WText >( TR("gcw.AccountEditor.editaccount").arg( accountItem-> fullName() ) ) )->
    setAttributeValue( "style", "margin-bottom:5px" );

//  auto at1 = std::make_unique< Wt::WTemplate >( TR( "gcw_gui.accounteditor.form.tab1" ) );
    auto at1 = std::make_unique< Tab1 >( m_accountGuid );
  m_t1 = at1.get();

//  auto at2 = std::make_unique< Wt::WTemplate >( TR( "gcw_gui.accounteditor.form.tab2" ) );
    auto at2 = std::make_unique< Tab2 >( m_accountGuid );
  m_t2 = at2.get();

  m_tabWidget = lw-> addWidget( std::make_unique< Wt::WTabWidget >(), 1 );
  auto twt1 = tabWidget()-> addTab( std::move( at1 ), "General" );
  auto twt2 = tabWidget()-> addTab( std::move( at2 ), "More Properties" );

  auto model = std::make_shared< Wt::WFormModel >();
       model-> addField( GCW::Dbo::Accounts::Field::name, "Account Name" );

  auto footer = lw-> addWidget( std::make_unique< Wt::WTemplate >( TR( "gcw_gui.accounteditor.form.footer" ) ) );

  footer-> bindNew< Wt::WPushButton >( "help"   , "help"   )-> clicked().connect( this, &AccountEditor::do_help   );
  footer-> bindNew< Wt::WPushButton >( "cancel" , "cancel" )-> clicked().connect( this, &AccountEditor::do_cancel );
  footer-> bindNew< Wt::WPushButton >( "ok"     , "ok"     )-> clicked().connect( this, &AccountEditor::do_ok     );

//  m_placeholder    
//  m_hidden         
//  m_autoTransfer   
//  m_taxRelated     
//  m_openingBalance 

} // endGCW::AccountEditor::AccountEditor( const std::string & _accountGuid )

auto
GCW::Gui::AccountEditor::
do_help()-> void
{
  wApp-> doJavaScript( "window.open( '/dox/html/AccountEditor.html', '_blank' )" );

} // enddo_help()-> void

auto
GCW::Gui::AccountEditor::
do_cancel()-> void
{
  cancel().emit();

} // enddo_cancel()-> void

auto
GCW::Gui::AccountEditor::
do_ok()-> void
{
  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // enddo_ok()-> void

GCW::Gui::AccountEditorDialog::
AccountEditorDialog( const std::string & _accountGuid )
: Wt::WDialog( "Edit Account" )
{
  rejectWhenEscapePressed( true );
  setResizable( true );
  setClosable( true );
  setMinimumSize( "800px", "600px" );

  contents()-> addNew< GCW::Gui::AccountEditor >( _accountGuid );

}; // endclass GCW::Gui::AccountEditorDialog::AccountEditorDialog( const std::string & _accountGuid )



