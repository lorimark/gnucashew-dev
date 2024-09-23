#line 2 "src/Gui/AccountsTreeView.h"

#ifndef __GUI_ACCOUNTSTREEVIEW_H___
#define __GUI_ACCOUNTSTREEVIEW_H___

#include <Wt/Json/Object.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTreeView.h>
#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WGridLayout.h>

#include "../define.h"
#include "../GnuCashew.h"
//#include "../Dbo/SessionGnuCash.h"
//#include "../Dbo/SessionGnuCashew.h"
#include "../Eng/AccountsTreeViewModel.h"
#include "../Dbo/Vars/Vars.h"

namespace GCW {
  namespace Gui {
    class AccountEditor;

/*!
** \brief AccountsTreeView
**
** The AccountsTreeView is a widget that displays all of the accounts
**  within the system.  It displays the accounts in a tree-like format
**  with multiple columns representing other field values such as;
**  'notes', 'tax info', 'balance remaining' and so on.  The view is
**  sortable and browsable, and facilitates gaining access to the
**  individual account registers.
**
*/
class AccountsTreeView
: public Wt::WContainerWidget
{
  public:

    class ColDef
    {
      public:

        std::string m_name;

    };

    using Model = GCW::Eng::AccountsTreeViewModel;

    AccountsTreeView( int _columnCount );
    AccountsTreeView( const std::string & _selectedAccountGuid, int _columnCount );

    auto model () const-> std::shared_ptr< Model > { return m_model; }
    auto view  () const-> Wt::WTreeView         *  { return m_view;  }

    auto doubleClicked()-> Wt::Signal< std::string > & { return m_doubleClicked; }

    auto selectedAccount() const-> std::string;

    auto editAccount( const std::string & _accountGuid )-> void;
    auto editSelectedAccount()-> void;

    /*!
    ** \brief Config Item
    **
    ** This returns the single 'config item' that contains the properties of the
    **  tree view.
    **
    */
    auto configItem()-> GCW::Dbo::Vars::Item::Ptr ;

    auto saveConfig()-> void ;
    auto loadConfig()-> void ;

    auto toJson() const-> Wt::Json::Object ;
    auto fromJson( Wt::Json::Object & _jobj )-> bool ;

    auto test()-> void;

  private:

    auto init()-> void;
    auto setModel()-> void;
    auto on_doubleClicked( const Wt::WModelIndex & index, const Wt::WMouseEvent & event )-> void;
    auto iterate( Wt::Json::Array & _jary, Wt::WModelIndex _parent = Wt::WModelIndex() ) const-> bool;
    auto expandNode( const std::string & _accountGuid, Wt::WModelIndex _parent = Wt::WModelIndex() )-> bool;
    auto expandTreeNodes( Wt::Json::Object & _jobj )-> bool;
    auto setSelected( const std::string & _accountGuid )-> bool;
    auto findIndex( const std::string & _accountGuid, Wt::WModelIndex _parentIndex = Wt::WModelIndex() )-> Wt::WModelIndex;

    int                          m_columnCount       = -1      ;
    Wt::WGridLayout            * m_gridLayout        = nullptr ;
    Wt::WTreeView              * m_view              = nullptr ;
    std::shared_ptr< Model >     m_model                       ;
    std::vector< std::string >   m_columns                     ;
    Wt::Signal< std::string >    m_doubleClicked               ;
    GCW::Gui::AccountEditor    * m_editAccountWidget = nullptr ;

};  // endclass AccountsTreeView

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_ACCOUNTSTREEVIEW_H___


