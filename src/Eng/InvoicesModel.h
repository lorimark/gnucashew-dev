#line 2 "src/Eng/InvoicesModel.h"

#ifndef __ENG_INVOICESMODEL_H___
#define __ENG_INVOICESMODEL_H___

#include <Wt/WStandardItemModel.h>
#include <Wt/Dbo/QueryModel.h>

#include "../Dbo/Invoices/Invoices.h"

namespace GCW {
  namespace Eng {

class InvoicesModel
: public Wt::Dbo::QueryModel< GCW::Dbo::Invoices::Item::Ptr >
{
  public:

    InvoicesModel();
    InvoicesModel( const std::vector< Wt::WFormModel::Field > & _fields );

    auto setCustomerGuid( const std::string & _guid )-> void;

    auto refreshFromDisk()-> void ;

  private:

    std::string m_customerGuid;

    std::vector< Wt::WFormModel::Field > m_fields;

}; // endclass InvoicesModel

  } //  namespace Eng {
} // endnamespace GCW {

#endif // #ifndef __ENG_INVOICESMODEL_H___



