#line 2 "src/Eng/CustomersModel.cpp"

#include "../App.h"
#include "EmployeesModel.h"

GCW::Eng::EmployeesModel::
EmployeesModel()
: Wt::Dbo::QueryModel< GCW::Dbo::Employees::Item::Ptr >()
{
  refreshFromDisk();

#ifdef NEVER
  dataChanged().connect( [=]( Wt::WModelIndex _index1, Wt::WModelIndex _index2 )
  {
//    std::cout << __FILE__ << ":" << __LINE__
//    << " r1:" << _index1.row() << " c1:" << _index1.column()
//    << " r2:" << _index2.row() << " c2:" << _index2.column()
//    << std::endl;

  });

  itemChanged().connect( [=]( Wt::WStandardItem * _item )
  {
//    std::cout << __FILE__ << ":" << __LINE__ << " " << Wt::asString( _item-> data() ) << std::endl;

  });
#endif

  std::cout << __FILE__ << ":" << __LINE__ << " " << std::endl;

} // endEmployeesModel()

GCW::Eng::EmployeesModel::
EmployeesModel( const std::vector< Wt::WFormModel::Field > & _fields )
//: Wt::WStandardItemModel(),
: Wt::Dbo::QueryModel< GCW::Dbo::Employees::Item::Ptr >(),
  m_fields( _fields )
{
  refreshFromDisk();

}

/*!
** \brief Refresh From Disk
**
*/
auto
GCW::Eng::EmployeesModel::
refreshFromDisk()-> void
{

  if( GCW::app()-> gnucashew_session().isOpen() )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    auto results =
      GCW::app()-> gnucashew_session().find< GCW::Dbo::Employees::Item >()
      ;

    setQuery( results );

    std::cout << __FILE__ << ":" << __LINE__ << " " << rowCount() << std::endl;

  } // endif( GCW::app()-> gnucashew_session().isOpen() )

  if( m_fields.size() > 0 )
  {
    for( auto field : m_fields )
      addColumn( field );
  }

  else
  {
    addAllFieldsAsColumns();
  }

} // endrefreshFromDisk()-> void



