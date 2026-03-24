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

namespace {

class AccountParentCombo
: public Wt::WComboBox
{
  public:

    AccountParentCombo()
    {
      /// \todo this should be in a 'setValueText' thing
//      for( auto & account : GCW::Dbo::Accounts::activeAccountsAnd( _initialValue ) )
//        addItem( GCW::Dbo::Accounts::fullName( account ) );

//      setValueText( GCW::Dbo::Accounts::fullName( _initialValue ) );

    } // endAccountTypeCombo( const std::string & _initialValue )

}; // endclass AccountParentCombo

class AccountTypeCombo
: public Wt::WComboBox
{
  public:

    AccountTypeCombo()
    {
#ifdef MOVE_ALL_THIS_TO_A_SETVALUETEXT_FUNCTION
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
#endif

    } // endAccountTypeCombo( const std::string & _initialValue )

}; // endclass AccountTypeCombo

class SecurityCombo
: public Wt::WComboBox
{
  public:

    SecurityCombo()
    {
    }

}; // endclass SecurityCombo

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

}; // endclass SmallestFractionCombo

} // endnamespace {

GCW::Gui::AccountEditor::Tab1::
Tab1()
{
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

     m_name           = t1-> bindNew< Wt::WLineEdit         >( "name"                                                      );
     m_code           = t1-> bindNew< Wt::WLineEdit         >( "code"                                                      );
     m_desc           = t1-> bindNew< Wt::WLineEdit         >( "desc"                                                      );
     m_parent         = t1-> bindNew< AccountParentCombo    >( "parent"                                                    );
     m_accountType    = t1-> bindNew< AccountTypeCombo      >( "accountType"                                               );
     m_security       = t1-> bindNew< SecurityCombo         >( "security"                                                  );
     m_fraction       = t1-> bindNew< SmallestFractionCombo >( "fraction"                                                  );
     m_color          = t1-> bindNew< Wt::WPushButton       >( "color"          , TR( "gcw.AccountEditor.colorpicker"    ) );
  auto colordefault   = t1-> bindNew< Wt::WPushButton       >( "colordefault"   , TR( "gcw.AccountEditor.colordefault"   ) );
     m_notes          = t1-> bindNew< Wt::WTextArea         >( "notes"                                                     );
     m_placeholder    = t1-> bindNew< Wt::WCheckBox         >( "placeholder"    , TR( "gcw.AccountEditor.placeholder"    ) );
     m_hidden         = t1-> bindNew< Wt::WCheckBox         >( "hidden"         , TR( "gcw.AccountEditor.hidden"         ) );
     m_autoTransfer   = t1-> bindNew< Wt::WCheckBox         >( "autoTransfer"   , TR( "gcw.AccountEditor.autoTransfer"   ) );
     m_taxRelated     = t1-> bindNew< Wt::WCheckBox         >( "taxRelated"     , TR( "gcw.AccountEditor.taxRelated"     ) );
     m_openingBalance = t1-> bindNew< Wt::WCheckBox         >( "openingBalance" , TR( "gcw.AccountEditor.openingBalance" ) );

  m_color        -> setWidth( "100%" );
    colordefault -> setWidth( "100%" );

  m_parent-> setMaximumSize( Wt::WLength::Auto, Wt::WLength("220px") );

} // endTab1( const std::string & _accountGuid )

auto
GCW::Gui::AccountEditor::Tab1::
loadData( const std::string & _accountGuid )-> void
{
}

auto
GCW::Gui::AccountEditor::Tab1::
saveData( const std::string & _accountGuid )-> void
{
}


GCW::Gui::AccountEditor::Tab2::
Tab2()
{
  auto lw  = setLayout( std::make_unique< Wt::WFitLayout >() );
  auto t2  = lw-> addWidget( std::make_unique< Wt::WTemplate >( TR( "gcw_gui.accounteditor.form.tab2" ) ) );

} // endTab2( const std::string & _accountGuid )

auto
GCW::Gui::AccountEditor::Tab2::
loadData( const std::string & _accountGuid )-> void
{
}

auto
GCW::Gui::AccountEditor::Tab2::
saveData( const std::string & _accountGuid )-> void
{
}


GCW::Gui::AccountEditor::
AccountEditor()
{
  addStyleClass( "AccountEditor" );

  auto lw = setLayout( std::make_unique< Wt::WVBoxLayout >() );

  m_accountName = lw-> addWidget( std::make_unique< Wt::WText >() );
  m_accountName-> setAttributeValue( "style", "margin-bottom:5px" );

  auto at1 = std::make_unique< Tab1 >();
  m_tab1 = at1.get();

  auto at2 = std::make_unique< Tab2 >();
  m_tab2 = at2.get();

  m_tabWidget = lw-> addWidget( std::make_unique< Wt::WTabWidget >(), 1 );
  auto twt1 = tabWidget()-> addTab( std::move( at1 ), TR("gcw_gui.accounteditor.form.tab1") );
  auto twt2 = tabWidget()-> addTab( std::move( at2 ), TR("gcw_gui.accounteditor.form.tab2") );

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
  save().emit();

} // enddo_ok()-> void

auto
GCW::Gui::AccountEditor::
loadData( const std::string & _accountGuid )-> void
{
  /*
  ** Get the accountItem loaded so we can pluck things from it.
  **
  */
  auto accountItem = GCW::Dbo::Accounts::load( m_accountGuid );

  m_accountName-> setText( TR("gcw.AccountEditor.editaccount").arg( accountItem-> fullName() ) );

  tab1()-> loadData( _accountGuid );
  tab2()-> loadData( _accountGuid );

//     m_name           = t1-> bindNew< Wt::WLineEdit              >( "name"           , accountItem-> name()                     );
//     m_code           = t1-> bindNew< Wt::WLineEdit              >( "code"           , accountItem-> code()                     );
//     m_desc           = t1-> bindNew< Wt::WLineEdit              >( "desc"           , accountItem-> description()              );
//     m_parent         = t1-> bindNew< AccountParentCombo         >( "parent"         , accountItem-> parent_guid()              );
//     m_accountType    = t1-> bindNew< AccountTypeCombo           >( "accountType"    , accountItem-> accountTypeName()          );
//     m_security       = t1-> bindNew< SecurityCombo              >( "security"                                                  );
//     m_fraction       = t1-> bindNew< SmallestFractionCombo      >( "fraction"                                                  );
//     m_color          = t1-> bindNew< Wt::WPushButton            >( "color"          , TR( "gcw.AccountEditor.colorpicker"    ) );
//  auto colordefault   = t1-> bindNew< Wt::WPushButton            >( "colordefault"   , TR( "gcw.AccountEditor.colordefault"   ) );
//     m_notes          = t1-> bindNew< Wt::WTextArea              >( "notes"                                                     );
//     m_placeholder    = t1-> bindNew< Wt::WCheckBox              >( "placeholder"    , TR( "gcw.AccountEditor.placeholder"    ) );
//     m_hidden         = t1-> bindNew< Wt::WCheckBox              >( "hidden"         , TR( "gcw.AccountEditor.hidden"         ) );
//     m_autoTransfer   = t1-> bindNew< Wt::WCheckBox              >( "autoTransfer"   , TR( "gcw.AccountEditor.autoTransfer"   ) );
//     m_taxRelated     = t1-> bindNew< Wt::WCheckBox              >( "taxRelated"     , TR( "gcw.AccountEditor.taxRelated"     ) );
//     m_openingBalance = t1-> bindNew< Wt::WCheckBox              >( "openingBalance" , TR( "gcw.AccountEditor.openingBalance" ) );


} // enddoSave()-> void

auto
GCW::Gui::AccountEditor::
saveData( const std::string & _accountGuid )-> void
{
  tab1()-> saveData( _accountGuid );
  tab2()-> saveData( _accountGuid );

} // enddoSave()-> void

auto
GCW::Gui::AccountEditor::
isDirty() const-> bool
{
  return true;

} // enddo_ok()-> void

GCW::Gui::AccountEditorDialog::
AccountEditorDialog( const std::string & _accountGuid )
: Wt::WDialog( "Edit Account" )
{
  rejectWhenEscapePressed( true );
  setResizable( true );
  setClosable( true );
  setMinimumSize( "800px", "600px" );

  contents()-> addNew< GCW::Gui::AccountEditor >()-> loadData( _accountGuid );


}; // endclass GCW::Gui::AccountEditorDialog::AccountEditorDialog( const std::string & _accountGuid )



