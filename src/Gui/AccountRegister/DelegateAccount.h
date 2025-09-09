#line 2 "src/Gui/AccountRegister/DelegateAccount.h"

#ifndef __GUI_ACCOUNTREGISTER_DELEGATEACCOUNT_H___
#define __GUI_ACCOUNTREGISTER_DELEGATEACCOUNT_H___

#include "DelegateBase.h"

namespace GCW {
  namespace Gui {
    namespace AccountRegister {
//      class Editor ;

class DelegateAccount
: public DelegateBase
{
  public:

    DelegateAccount( Editor * _editor );
   ~DelegateAccount();

    virtual auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

}; // endclass DelegateAccount

    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTREGISTER_DELEGATEACCOUNT_H___


