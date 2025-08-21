#line 2 "src/Gui/Customer/MainWidget.h"

#ifndef __GUI_CUSTOMER_MAINWIDGET_H___
#define __GUI_CUSTOMER_MAINWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WTableView.h>

#include "../../Eng/CustomersModel.h"
#include "Invoices.h"

namespace GCW {
  namespace Gui {
    namespace Customer {

/*!
** \brief Customer Overview
**
**
*/
class MainWidget
: public Wt::WContainerWidget
{
  public:
    using Model = GCW::Eng::CustomersModel;

    MainWidget();

    auto model () const-> std::shared_ptr< Model >   { return m_model; }
    auto view  () const-> Wt::WTableView           * { return m_view;  }

    auto doubleClicked()-> Wt::Signal< std::string > & { return m_doubleClicked; }

    auto selectedAccount() const-> std::string ;

    auto editAccount( const std::string & _accountGuid )-> void ;
    auto editSelectedAccount()->                           void ;

    auto toJson() const-> Wt::Json::Object ;
    auto fromJson( const Wt::Json::Object & _jobj )-> bool ;


  private:

    auto setModel()-> void ;
    auto doubleClicked( const Wt::WModelIndex & index, const Wt::WMouseEvent & event )-> void ;

    Wt::WTableView               * m_view         = nullptr ;
    std::shared_ptr< Model >       m_model                  ;
    std::vector< std::string >     m_columns                ;
    Wt::Signal< std::string >      m_doubleClicked          ;
    GCW::Gui::Customer::Invoices * m_invoicesView = nullptr ;

};  // endclass MainWidget

    } // endnamespace Customer {
  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_CUSTOMER_MAINWIDGET_H___


