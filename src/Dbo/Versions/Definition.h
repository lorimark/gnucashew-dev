#line 2 "src/Dbo/Versions/Definition.h"

#ifndef __DBO_VERSIONS_DEFINITION_H___
#define __DBO_VERSIONS_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace Versions {

extern const char * s_tableName;

      namespace Field {

extern const Wt::WFormModel::Field table_name    ; // text(50) PRIMARY KEY NOT NULL,
extern const Wt::WFormModel::Field table_version ; // integer NOT NULL

      } // endnamespace Field {
    } // endnamespace Versions {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_VERSIONS_DEFINITION_H___



