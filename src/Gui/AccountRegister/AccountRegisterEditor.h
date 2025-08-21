#line 2 "src/Gui/AccountRegister/AccountRegisterEditor.h"

#ifndef __GUI_ACCOUNTREGISTEREDITOR_H___
#define __GUI_ACCOUNTREGISTEREDITOR_H___

#include <Wt/Json/Object.h>
#include <Wt/WBatchEditProxyModel.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WSortFilterProxyModel.h>
#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WItemDelegate.h>
#include <Wt/WPopupMenu.h>

#include "../../GnuCashew.h"
#include "../../Eng/AccountRegisterModel.h"
#include "../TableView.h"


namespace GCW {

  namespace Gui {

/*!
** \brief Account Register Editor
**
** This object is a controller for editing of line items in the Account Register.  The editor
**  is a local(friend?) to the account register object that provides the delegates for the
**  table view, and manipulates the delegates in relation to each other so as to be able to
**  handle tabbing, up and down arrowing, and so on, within the table view, and keeping all
**  the editors open, and saving them correctly when the user is done bla bla bla.
*/
class AccountRegisterEditor
{
  public:

    /*!
    ** \brief Base Delegate
    **
    ** This class is strictly for debugging and tracing purposes.  It facilitates the hooking
    **  of the various calls in to the delegate classes so that their behaviour and interaction
    **  with the view can be studied and understood.
    **
    */
    class BaseDelegate
    : public Wt::WItemDelegate
    {
      public:

        BaseDelegate( AccountRegisterEditor * _editor );
       ~BaseDelegate();

        auto editor() const-> AccountRegisterEditor * { return m_editor; }

        virtual auto createEditor( const Wt::WModelIndex &index, Wt::WFlags< Wt::ViewItemRenderFlag > flags ) const-> std::unique_ptr< Wt::WWidget > ;
        virtual auto update( Wt::WWidget * _widget, const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags )-> std::unique_ptr< Wt::WWidget > ;
        virtual auto updateModelIndex( Wt::WWidget * _widget, const Wt::WModelIndex & _index )-> void ;
        virtual auto validate( const Wt::WModelIndex & _index, const Wt::cpp17::any & _editState ) const-> Wt::ValidationState ;
        virtual auto editState( Wt::WWidget * _widget, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any ;
        virtual auto setEditState( Wt::WWidget * _widget, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void ;
        virtual auto setModelData( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void ;

        AccountRegisterEditor * m_editor = nullptr ;

    }; // endclass BaseDelegate

    /* * * * * * * * * * * * * * * * * * * * * * * * * * */

    class HeaderDelegate
    : public BaseDelegate
    {
      public:

        HeaderDelegate( AccountRegisterEditor * _editor );
       ~HeaderDelegate();
        auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;
        virtual auto editState( Wt::WWidget *_editor, const Wt::WModelIndex &_index ) const-> Wt::cpp17::any override ;

    }; // endclass HeaderDelegate

    /* * * * * * * * * * * * * * * * * * * * * * * * * * */

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
    class DateDelegate
    : public BaseDelegate
    {
      public:

        DateDelegate( AccountRegisterEditor * _editor );
       ~DateDelegate();
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

    }; // endclass DateDelegate

    /* * * * * * * * * * * * * * * * * * * * * * * * * * */

    class ReconcileDelegate
    : public BaseDelegate
    {
      public:

        /*!
        ** \brief Reconcile Delegate
        **
        ** This delegate will present a WText field for the reconciliation
        **  editor, and will activate that WText with click() response which
        **  will handle the 'edit' portion of this delegate.
        */
        ReconcileDelegate( AccountRegisterEditor * _editor );
       ~ReconcileDelegate();
        virtual auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;
        virtual auto editState( Wt::WWidget * _editor, const Wt::WModelIndex & _index ) const-> Wt::cpp17::any override ;
        virtual auto setEditState( Wt::WWidget * _editor, const Wt::WModelIndex & _index, const Wt::cpp17::any & _value ) const-> void ;
        virtual auto setModelData ( const Wt::cpp17::any & _editState, Wt::WAbstractItemModel * _model, const Wt::WModelIndex & _index ) const-> void ;

        virtual auto doCloseEditor( Wt::WLineEdit * _editor, bool _save ) const-> void ;
        virtual auto doTabAction( Wt::WKeyEvent _keyEvent ) const-> void ;

    }; // endclass ReconcileDelegate

    /* * * * * * * * * * * * * * * * * * * * * * * * * * */

    class ValueDelegate
    : public BaseDelegate
    {
      public:

        ValueDelegate( AccountRegisterEditor * _editor );
       ~ValueDelegate();

        virtual auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

    }; // endclass ValueDelegate

    /* * * * * * * * * * * * * * * * * * * * * * * * * * */

    /*
    ** Balance delegate works just like the ValueDelegate but
    **  also adds a read-only attribute to the input, so it
    **  displays the same, but cannot be edited.  This is done
    **  so that the entire line is highlighted fully when
    **  selected.
    **
    */
    class BalanceDelegate
      : public BaseDelegate
    {
      public:

        BalanceDelegate( AccountRegisterEditor * _editor );
       ~BalanceDelegate();

        auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

    }; // endclass BalanceDelegate

    /* * * * * * * * * * * * * * * * * * * * * * * * * * */

    class SuggestionDelegate
    : public BaseDelegate
    {
      public:

        SuggestionDelegate( AccountRegisterEditor * _editor );
       ~SuggestionDelegate();
        virtual auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

    }; // endclass SuggestionDelegate

    /* * * * * * * * * * * * * * * * * * * * * * * * * * */

    class AccountDelegate
      : public BaseDelegate
    {
      public:

        AccountDelegate( AccountRegisterEditor * _editor );
       ~AccountDelegate();
        virtual auto createEditor( const Wt::WModelIndex & _index, Wt::WFlags< Wt::ViewItemRenderFlag > _flags ) const-> std::unique_ptr< Wt::WWidget > ;

    }; // endclass AccountDelegate


    /* * * * * * * * * * * * * * * * * * * * * * * * * * */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * */


    AccountRegisterEditor();

    auto setTableView( GCW::Gui::TableView * _tableView )-> void ;

    /*!
    ** \brief Table View
    */
    auto tableView()-> GCW::Gui::TableView * { return m_tableView; }

    /*!
    ** \brief Edit Row
    */
    auto editRow( Wt::WModelIndex _index )-> void ;

    auto setDirty( Wt::WModelIndex _index ) const-> void ;

    /*!
    ** \brief Delegate Handles
    **
    ** Here we're going to hold on to the Delegate handles so
    **  we can interact with the UI a little bit
    */
    std::shared_ptr< HeaderDelegate     > m_delegateHeader ; //
    std::shared_ptr< DateDelegate       > m_delegateDate   ; // 0() );
    std::shared_ptr< SuggestionDelegate > m_delegateNum    ; // 1() );
    std::shared_ptr< SuggestionDelegate > m_delegateMemo   ; // 2() );
    std::shared_ptr< AccountDelegate    > m_delegateAcct   ; // 3() );
    std::shared_ptr< ReconcileDelegate  > m_delegateReco   ; // 4() );
    std::shared_ptr< ValueDelegate      > m_delegateIn     ; // 5() );
    std::shared_ptr< ValueDelegate      > m_delegateOut    ; // 6() );
    std::shared_ptr< BalanceDelegate    > m_delegateBal    ; // 7() );

    Wt::WModelIndex                       m_index               ;
    GCW::Gui::TableView                 * m_tableView = nullptr ;

};  // endclass AccountRegisterEditor

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_ACCOUNTREGISTEREDITOR_H___


