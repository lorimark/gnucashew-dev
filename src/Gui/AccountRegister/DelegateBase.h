#line 2 "src/Gui/AccountRegister/DelegateBase.h"

#ifndef __GUI_ACCOUNTREGISTER_DELEGATEBASE_H___
#define __GUI_ACCOUNTREGISTER_DELEGATEBASE_H___

#include <Wt/WItemDelegate.h>
#include <Wt/WModelIndex.h>

#include "Editor.h"

namespace GCW {
  namespace Gui {
    namespace AccountRegister {

/*!
** \brief Base Delegate
**
** This class is strictly for debugging and tracing purposes.  It facilitates the hooking
**  of the various calls in to the delegate classes so that their behaviour and interaction
**  with the view can be studied and understood.
**
*/
class DelegateBase
: public Wt::WItemDelegate
{
  public:

    DelegateBase();
   ~DelegateBase();

    virtual auto createEditor( const Wt::WModelIndex &index, Wt::WFlags< Wt::ViewItemRenderFlag > flags ) const-> std::unique_ptr< Wt::WWidget > ;
    virtual auto update( Wt::WWidget * _widget, const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags )-> std::unique_ptr< Wt::WWidget > ;
    virtual auto updateModelIndex( Wt::WWidget * _widget, const Wt::WModelIndex & _index )-> void ;
    virtual auto validate( const Wt::WModelIndex & _index, const Wt::cpp17::any & _editState ) const-> Wt::ValidationState ;
    virtual auto editState( Wt::WWidget * _widget, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any ;
    virtual auto setEditState( Wt::WWidget * _widget, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void ;
    virtual auto setModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void ;

}; // endclass DelegateBase

    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTREGISTER_DELEGATEBASE_H___

