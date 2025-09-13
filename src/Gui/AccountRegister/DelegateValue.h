#line 2 "src/Gui/AccountRegister/DelegateValue.h"

#ifndef __GUI_ACCOUNTREGISTER_DELEGATEVALUE_H___
#define __GUI_ACCOUNTREGISTER_DELEGATEVALUE_H___

#include <Wt/WItemDelegate.h>
#include <Wt/WModelIndex.h>

#include "DelegateBase.h"

namespace GCW {
  namespace Gui {
    namespace AccountRegister {

class DelegateValue
: public DelegateBase
{
  public:

    DelegateValue();
   ~DelegateValue();

    virtual auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

}; // endclass DelegateValue

    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTREGISTER_DELEGATEVALUE_H___

