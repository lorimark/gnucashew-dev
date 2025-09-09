#line 2 "src/Gui/AccountRegister/StatusBar.h"

#ifndef __GUI_ACCOUNTREGISTER_STATUSBAR_H___
#define __GUI_ACCOUNTREGISTER_STATUSBAR_H___

#include <Wt/WItemDelegate.h>
#include <Wt/WModelIndex.h>

namespace GCW {
  namespace Gui {
    namespace AccountRegister {

/*!
** The status-bar presents various totals from the register,
**  including the rowCount().
*/
class StatusBar
: public Wt::WContainerWidget
{
  public:
    StatusBar();

    auto setPresent   ( GCW_NUMERIC _value = GCW_NUMERIC(0) )-> void ;
    auto setFuture    ( GCW_NUMERIC _value = GCW_NUMERIC(0) )-> void ;
    auto setCleared   ( GCW_NUMERIC _value = GCW_NUMERIC(0) )-> void ;
    auto setReconciled( GCW_NUMERIC _value = GCW_NUMERIC(0) )-> void ;
    auto setProjected ( GCW_NUMERIC _value = GCW_NUMERIC(0) )-> void ;
    auto setRowCount  ( int         _value = 0              )-> void ;

  private:

    auto setText( Wt::WText * _widget, GCW_NUMERIC _value )-> void ;
    auto setText( Wt::WText * _widget, int _value )-> void ;

    Wt::WText * m_present    = nullptr ;
    Wt::WText * m_future     = nullptr ;
    Wt::WText * m_cleared    = nullptr ;
    Wt::WText * m_reconciled = nullptr ;
    Wt::WText * m_projected  = nullptr ;
    Wt::WText * m_rowCount   = nullptr ;

}; // endclass StatusBar

    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTREGISTER_STATUSBAR_H___

