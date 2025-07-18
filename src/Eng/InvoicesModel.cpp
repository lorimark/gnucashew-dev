#line 2 "src/Eng/InvoicesModel.cpp"

#include "../App.h"
#include "InvoicesModel.h"

GCW::Eng::InvoicesModel::
InvoicesModel()
: Wt::Dbo::QueryModel< GCW::Dbo::Invoices::Item::Ptr >()
{
  refreshFromDisk();

} // endGCW::Eng::CustomersModel::CustomersModel()

GCW::Eng::InvoicesModel::
InvoicesModel( const std::vector< Wt::WFormModel::Field > & _fields )
: Wt::Dbo::QueryModel< GCW::Dbo::Invoices::Item::Ptr >(),
  m_fields( _fields )
{
  refreshFromDisk();

}

auto
GCW::Eng::InvoicesModel::
setCustomerGuid( const std::string & _guid )-> void
{
  m_customerGuid = _guid;

  refreshFromDisk();

} // endsetCustomerGuid( const std::string & _guid )-> void



/*!
** \brief Refresh From Disk
**
*/
auto
GCW::Eng::InvoicesModel::
refreshFromDisk()-> void
{
  if( GCW::app()-> gnucashew_session().isOpen() )
  {
    Wt::Dbo::Transaction t( GCW::app()-> gnucashew_session() );

    if( m_customerGuid == "" )
    {
      auto results =
        GCW::app()-> gnucashew_session().find< GCW::Dbo::Invoices::Item >()
        ;

      std::cout << __FILE__ << ":" << __LINE__
        << " " << m_customerGuid
        << " " << results.resultList().size()
        << std::endl;

      setQuery( results );
    }

    else
    {
      auto results =
        GCW::app()-> gnucashew_session().find< GCW::Dbo::Invoices::Item >()
        .where( "owner_guid = ? OR owner_guid in (select guid from jobs where owner_guid = ?)" )
//        .where( "billto_guid = ?" )
//        .where( "owner_guid = ?" )
        .bind( m_customerGuid )
        .bind( m_customerGuid )
        ;

      std::cout << __FILE__ << ":" << __LINE__
        << " " << m_customerGuid
        << " " << results.resultList().size()
        << std::endl;

      setQuery( results );
    }

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

  reload();

  std::cout << __FILE__ << ":" << __LINE__ << " " << rowCount() << std::endl;

} // endGCW::Eng::InvoicesModel::refreshFromDisk()



