#line 2 "src/Gui/AccountRegister/DelegateReconcile.h"

#ifndef __GUI_ACCOUNTREGISTER_DELEGATERECONCILE_H___
#define __GUI_ACCOUNTREGISTER_DELEGATERECONCILE_H___

#include <Wt/WItemDelegate.h>
#include <Wt/WModelIndex.h>

#include "DelegateBase.h"

namespace GCW {
  namespace Gui {
    namespace AccountRegister {

class DelegateReconcile
: public DelegateBase
{
  public:

    /*!
    ** \brief Reconcile Delegate
    **
    ** This delegate will present a WText field for the reconciliation
    **  editor, and will activate that WText with click() response which
    **  will handle the 'edit' portion of this delegate.
    */
    DelegateReconcile();
   ~DelegateReconcile();
    virtual auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;
    virtual auto editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any override ;
    virtual auto setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void ;
    virtual auto setModelData ( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void ;

    virtual auto doCloseEditor( Wt::WLineEdit * _editor, bool _save ) const-> void ;
    virtual auto doTabAction( Wt::WKeyEvent _keyEvent ) const-> void ;

}; // endclass DelegateReconcile

    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTREGISTER_DELEGATERECONCILE_H___

