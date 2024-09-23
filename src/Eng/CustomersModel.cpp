#line 2 "src/Eng/CustomersModel.cpp"

#include <gnucash/gncCustomer.h>

#include "../App.h"
#include "CustomersModel.h"

GCW::Eng::CustomersModel::
CustomersModel()
: Wt::WStandardItemModel()
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

} // endGCW::Eng::CustomersModel::CustomersModel()

GCW::Eng::CustomersModel::
CustomersModel( const std::vector< Wt::WFormModel::Field > & _fields )
: Wt::WStandardItemModel(),
  m_fields( _fields )
{
  refreshFromDisk();

}

/*!
** \brief Refresh From Disk
**
**
*/
void
GCW::Eng::CustomersModel::
refreshFromDisk()
{

#ifdef NEVER
  if( GCW::app()-> gnucashew_session().isOpen() )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    auto results =
      GCW::app()-> gnucashew_session().find< GCW::Dbo::Customers::Item >()
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
#endif

} // endGCW::Eng::RegisterModel::refreshFromDisk()



