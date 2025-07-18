#line 2 "src/Eng/AccountsTreeViewModel.h"

#ifndef __ENG_ACCOUNTSTREEVIEWMODEL_H___
#define __ENG_ACCOUNTSTREEVIEWMODEL_H___

#include <Wt/Json/Object.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTreeView.h>
#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>

#include "../define.h"
#include "../Dbo/Accounts/Accounts.h"

namespace GCW {
  namespace Eng {

/*!
** \brief AccountsTreeViewModel
**
** This builds a tree-type model for the Accounts to allow them to be
**  displayed and interacted with in a WTreeView type object.
*/
class AccountsTreeViewModel
: public Wt::WStandardItemModel
{
  public:

    auto load( int _columnCount )-> void;

  private:

    auto load( Wt::WStandardItem * _treeItem, GCW::Dbo::Accounts::Item::Ptr _parentAccount )-> void;

    int m_columnCount = -1;

}; // endclass AccountsTreeViewModel

  } // endnamespace Eng {
} // endnamespace GCW {

#endif // end __ENG_ACCOUNTSTREEVIEW_H___


