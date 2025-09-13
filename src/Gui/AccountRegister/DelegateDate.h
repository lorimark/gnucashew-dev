#line 2 "src/Gui/AccountRegister/DelegateDate.h"

#ifndef __GUI_ACCOUNTREGISTER_DELEGATEDATE_H___
#define __GUI_ACCOUNTREGISTER_DELEGATEDATE_H___

#include "DelegateBase.h"

namespace GCW {
  namespace Gui {
    namespace AccountRegister {
      class Editor ;


/*!
** \brief Date Delegate
**
** The date delegate handles the WDateTime value from the model.  Even though a 'transaction'
**  is posted on a 'date' and not particularly a time, the gnucash system still is sensitive
**  to time values in date-only fields.  In the case of the transactions, the 'time'
**  component is set to 10:59:00.  There is a macro that contains this value
**  'GCW_DATE_DEFAULT_TIME' which should be used to reference the correct time-value.  The
**  time-component is important since when reading items out of the database, gnucash
**  responds poorly to posted dates that have a 00:00:00 time component set, it must be set
**  to the 10:59:00 value.  This delegate makes sure that happens (probably shouldn't be
**  done here).
**
*/
class DelegateDate
: public DelegateBase
{
  public:

    DelegateDate();
   ~DelegateDate();
    virtual auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

    /*!
    ** \brief Edit State
    **
    ** A thing about editState, setEditState, setModelData.  Each of these use 'cpp17::any' data
    **  for handling data.  When you 'editState' you can return anything you want that will also
    **  be digested by 'setEditState'.  Then, also, therefore, setModelData will also receive
    **  anything from 'editState'.  So, this can be a handy tool for passing around different
    **  editor info that is specifically tied to a row or item that is being edited.  Right now
    **  we just return the date value, since that's what we're using and poking straight in to the
    **  model and what not, but we could be passing around any object/date/type... just sayin.
    */
    virtual auto editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any override ;
    virtual auto setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void ;
    virtual auto setModelData ( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void ;

    auto doCloseEditor( Wt::WDateEdit * _dateEdit, bool _save ) const-> void ;
    auto doTabAction( Wt::WKeyEvent _keyEvent ) const-> void ;

  private:

    auto setDate( Wt::WDateEdit * _dateEdit, Wt::cpp17::any _value ) const-> void ;

}; // endclass DelegateDate


    } // endnamespace AccountRegister {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // __GUI_ACCOUNTREGISTER_DELEGATEDATE_H___


