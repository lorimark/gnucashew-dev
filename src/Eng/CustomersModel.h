#line 2 "src/Eng/CustomersModel.h"

#ifndef __ENG_CUSTOMERSMODEL_H___
#define __ENG_CUSTOMERSMODEL_H___

#include <Wt/WStandardItemModel.h>
#include <Wt/Dbo/QueryModel.h>

#include "../Dbo/Customers/Customers.h"

namespace GCW {
  namespace Eng {

class CustomersModel
//: public Wt::WStandardItemModel
: public Wt::Dbo::QueryModel< GCW::Dbo::Customers::Item::Ptr >
{
  public:

    CustomersModel();
    CustomersModel( const std::vector< Wt::WFormModel::Field > & _fields );

    auto guid( int _row )-> std::string;

    auto refreshFromDisk()-> void ;

  private:

    std::vector< Wt::WFormModel::Field > m_fields;

}; // endclass CustomersModel

  } //  namespace Eng {
} // endnamespace GCW {


#endif // #ifndef __ENG_CUSTOMERSMODEL_H___



