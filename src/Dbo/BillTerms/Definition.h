#line 2 "src/Dbo/BillTerms/Definition.h"

#ifndef __DBO_BILLTERMS_DEFINITION_H___
#define __DBO_BILLTERMS_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace BillTerms {

extern const char * s_tableName;

      namespace Field {

extern const Wt::WFormModel::Field guid           ; // text(32) PRIMARY KEY NOT NULL,
extern const Wt::WFormModel::Field name           ; // text(2048) NOT NULL,
extern const Wt::WFormModel::Field description    ; // text(2048) NOT NULL,
extern const Wt::WFormModel::Field refcount       ; // integer NOT NULL,
extern const Wt::WFormModel::Field invisible      ; // integer NOT NULL,
extern const Wt::WFormModel::Field parent         ; // text(32),
extern const Wt::WFormModel::Field type           ; // text(2048) NOT NULL,
extern const Wt::WFormModel::Field duedays        ; // integer,
extern const Wt::WFormModel::Field discountdays   ; // integer,
extern const Wt::WFormModel::Field discount_num   ; //  bigint,
extern const Wt::WFormModel::Field discount_denom ; // bigint,
extern const Wt::WFormModel::Field cutoff         ; // integer

      } // endnamespace Field {
    } // endnamespace BillTerms {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_BILLTERMS_DEFINITION_H___



