#line 2 "src/Gui/AccountRegister/DelegateBalance.h"

#ifndef __GUI_ACCOUNTREGISTER_DELEGATEBALANCE_H___
#define __GUI_ACCOUNTREGISTER_DELEGATEBALANCE_H___

#include "DelegateBase.h"

namespace GCW {
  namespace Gui {
    namespace AccountRegister {
      class Editor ;

/*
** Balance delegate works just like the ValueDelegate but
**  also adds a read-only attribute to the input, so it
**  displays the same, but cannot be edited.  This is done
**  so that the entire line is highlighted fully when
**  selected.
**
*/
class DelegateBalance
: public DelegateBase
{
  public:

    DelegateBalance();
   ~DelegateBalance();

    auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

}; // endclass DelegateBalance


    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTREGISTER_DELEGATEBALANCE_H___


