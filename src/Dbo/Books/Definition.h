#line 2 "src/Dbo/Books/Definition.h"

#ifndef __DBO_BOOKS_DEFINITION_H___
#define __DBO_BOOKS_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace Books {

extern const char * s_tableName;

      namespace Field {

extern const Wt::WFormModel::Field guid               ; // text(32) PRIMARY KEY NOT NULL,
extern const Wt::WFormModel::Field root_account_guid  ; // text(32) NOT NULL,
extern const Wt::WFormModel::Field root_template_guid ; // text(32) NOT NULL

      } // endnamespace Field {
    } // endnamespace Books {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_BOOKS_DEFINITION_H___



