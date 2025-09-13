#line 2 "src/Gui/AccountRegister/DelegateSuggestion.h"

#ifndef __GUI_ACCOUNTREGISTER_DELEGATESUGGESTION_H___
#define __GUI_ACCOUNTREGISTER_DELEGATESUGGESTION_H___

#include <Wt/WItemDelegate.h>
#include <Wt/WModelIndex.h>

#include "DelegateBase.h"

namespace GCW {
  namespace Gui {
    namespace AccountRegister {

class DelegateSuggestion
: public DelegateBase
{
  public:

    DelegateSuggestion();
   ~DelegateSuggestion();
    virtual auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

}; // endclass DelegateSuggestion

    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTREGISTER_DELEGATESUGGESION_H___

