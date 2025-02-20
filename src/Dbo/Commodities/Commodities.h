#line 2 "src/Dbo/Commodities/Commodities.h"

#ifndef __DBO_COMMODITIES_H___
#define __DBO_COMMODITIES_H___

#include "Item.h"

namespace GCW {
  namespace Dbo {
    namespace Commodities {

typedef struct COMMODITY_S
{
  std::string isocode;
  std::string fullname;
  std::string unitname;
  std::string partname;
  std::string nameSpace;
  std::string exchangeCode;
  std::string partsPerUnit;
  std::string smallestFraction;
  std::string localSymbol;

} Commodity_t;

/*!
** \brief Get Commodities
**
** This returns the list of commodities from the
**  iso-4217-currencies.xml file
**
*/
auto getIso4217Commodities()-> std::vector< Commodity_t >;

/*!
** \brief Load Account by GUID
**
*/
auto load( const std::string & _guid )-> Item::Ptr;

/*!
** \brief Load Account by GUID
**
*/
auto byGuid( const std::string & _guid )-> Item::Ptr;

    } // Commodities
  } // Dbo
} // GCW



#endif // __DBO_COMMODITIES_H___


