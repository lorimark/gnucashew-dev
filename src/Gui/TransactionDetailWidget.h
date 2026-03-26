#line 2 "src/Gui/TransactionDetailWidget.h"

#ifndef __GUI_TRANSACTIONDETAILWIDGET_H___
#define __GUI_TRANSACTIONDETAILWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>

namespace GCW {
  namespace Gui {

/*!
** \brief Transaction Detail Widget
**
** This is a widget that will display the contents of a transaction record,
**  with all its attributes and elements, in plain open/free/unrestricted
**  UI editor, and also includes all of the splits.
**
*/
class TransactionDetailWidget
: public Wt::WContainerWidget
{
  public:

    /*!
    ** \brief Empty ctor
    */
    TransactionDetailWidget( const std::string & _tx_guid = "" );

    /*!
    ** \brief Set Transaction GUID
    */
    auto setTxGuid( const std::string & _guid )-> void ;

    /*!
    ** \brief Set Split GUID
    */
    auto setSplitGuid( const std::string & _guid )-> void ;

    /*!
    ** \brief Save the data to the backend
    */
    auto saveData()-> void ;

  private:

    class SplitWidget
    : public Wt::WContainerWidget
    {
      public:

        SplitWidget( const std::string & _guid );

        std::string m_guid ;
    };

    std::string m_tx_guid ;

    Wt::WText  * mtxt_guid        = nullptr ;
    Wt::WText  * mtxt_currency    = nullptr ;
    Wt::WText  * mtxt_num         = nullptr ;
    Wt::WText  * mtxt_post_date   = nullptr ;
    Wt::WText  * mtxt_enter_date  = nullptr ;
    Wt::WText  * mtxt_description = nullptr ;
    Wt::WTable * m_splitsTable    = nullptr ;

//    Wt::WText * mtxt_payFrom  = nullptr ;
//    Wt::WText * mtxt_payTo    = nullptr ;
//    Wt::WText * mtxt_date     = nullptr ;
//    Wt::WText * mtxt_desc     = nullptr ;
//    Wt::WText * mtxt_amount   = nullptr ;

};  // endclass TransactionDetailWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_TRANSACTIONDETAILWIDGET_H___



