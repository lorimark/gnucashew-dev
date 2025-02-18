#line 2 "src/Dbo/Commodities/Definition.h"

#ifndef __DBO_COMMODITIES_DEFINITION_H___
#define __DBO_COMMODITIES_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace Commodities {

extern const char * s_tableName;

      namespace Field {

extern const Wt::WFormModel::Field guid          ; // text(32) PRIMARY KEY NOT NULL
extern const Wt::WFormModel::Field nameSpace     ; // text(2048) NOT NULL
extern const Wt::WFormModel::Field mnemonic      ; // text(2048) NOT NULL
extern const Wt::WFormModel::Field fullname      ; // text(2048)
extern const Wt::WFormModel::Field cusip         ; // text(2048)
extern const Wt::WFormModel::Field fraction      ; // integer NOT NULL
extern const Wt::WFormModel::Field quote_flag    ; // integer NOT NULL
extern const Wt::WFormModel::Field quote_source  ; // text(2048)
extern const Wt::WFormModel::Field quote_tz      ; // text(2048)

      } // endnamespace Field {
    } // endnamespace Commodities {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_COMMODITIES_DEFINITION_H___



