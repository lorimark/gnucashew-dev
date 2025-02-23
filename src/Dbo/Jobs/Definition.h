#line 2 "src/Dbo/Jobs/Definition.h"

#ifndef __DBO_JOBS_DEFINITION_H___
#define __DBO_JOBS_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace Jobs {

extern const char * s_tableName;

      namespace Field {

extern const Wt::WFormModel::Field guid       ; // guid        text(32) PRIMARY KEY NOT NULL,
extern const Wt::WFormModel::Field id         ; // id          text(2048)           NOT NULL,
extern const Wt::WFormModel::Field name       ; // name        text(2048)           NOT NULL,
extern const Wt::WFormModel::Field reference  ; // reference   text(2048)           NOT NULL,
extern const Wt::WFormModel::Field active     ; // active      integer              NOT NULL,
extern const Wt::WFormModel::Field owner_type ; // owner_type  integer,
extern const Wt::WFormModel::Field owner_guid ; // owner_guid  text(32)

      } // endnamespace Field {
    } // endnamespace Jobs {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_JOBS_DEFINITION_H___



