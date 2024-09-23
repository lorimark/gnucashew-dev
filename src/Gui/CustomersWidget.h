#line 2 "src/Gui/CustomersWidget.h"

#ifndef __GUI_CUSTOMERSWIDGET_H___
#define __GUI_CUSTOMERSWIDGET_H___

#include <Wt/WContainerWidget.h>
#include <Wt/WTableView.h>

#include "../Eng/CustomersModel.h"

namespace GCW {
  namespace Gui {

/*!
** \brief Customer Overview
**
**
*/
class CustomersWidget
: public Wt::WContainerWidget
{
  public:
    using Model = GCW::Eng::CustomersModel;

    CustomersWidget();

    std::shared_ptr< Model >   model () const { return m_model; }
    Wt::WTableView           * view  () const { return m_view;  }

    Wt::Signal< std::string > & doubleClicked() { return m_doubleClicked; }

    std::string selectedAccount() const;

    void editAccount( const std::string & _accountGuid );
    void editSelectedAccount();

    Wt::Json::Object toJson() const;
    bool fromJson( const Wt::Json::Object & _jobj );


  private:

    void setModel();
    void doubleClicked( const Wt::WModelIndex & index, const Wt::WMouseEvent & event );

    Wt::WTableView           * m_view = nullptr;
    std::shared_ptr< Model >   m_model;
    std::vector< std::string > m_columns;
    Wt::Signal< std::string >  m_doubleClicked;


};  // endclass CustomersWidget

  } // endnamespace Gui {
} // endnamespace GCW {

#endif // end __GUI_CUSTOMERSWIDGET_H___


