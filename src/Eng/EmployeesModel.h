#line 2 "src/Eng/EmployeesModel.h"

#ifndef __ENG_EMPLOYEESMODEL_H___
#define __ENG_EMPLOYEESMODEL_H___

#include <Wt/WStandardItemModel.h>
#include <Wt/Dbo/QueryModel.h>

#include "../Dbo/Employees/Employees.h"

namespace GCW {
  namespace Eng {

class EmployeesModel
: public Wt::Dbo::QueryModel< GCW::Dbo::Employees::Item::Ptr >
{
  public:

    EmployeesModel();
    EmployeesModel( const std::vector< Wt::WFormModel::Field > & _fields );

    auto refreshFromDisk()-> void ;

  private:

    std::vector< Wt::WFormModel::Field > m_fields;

}; // endclass EmployeesModel

  } //  namespace Eng {
} // endnamespace GCW {


#endif // #ifndef __ENG_EMPLOYEESMODEL_H___



