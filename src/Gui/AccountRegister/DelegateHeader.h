#line 2 "src/Gui/AccountRegister/DelegateHeader.h"

#ifndef __GUI_ACCOUNTREGISTER_DELEGATEHEADER_H___
#define __GUI_ACCOUNTREGISTER_DELEGATEHEADER_H___

#include <Wt/WItemDelegate.h>
#include <Wt/WModelIndex.h>

#include "DelegateBase.h"

namespace GCW {
  namespace Gui {
    namespace AccountRegister {

class DelegateHeader
: public DelegateBase
{
  public:

    DelegateHeader( Editor * _editor );
   ~DelegateHeader();
    auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;
    virtual auto editState( Wt::WWidget *_editor, const Wt::WModelIndex &_index ) const-> Wt::cpp17::any override ;

}; // endclass DelegateHeader

    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTREGISTER_DELEGATEHEADER_H___

