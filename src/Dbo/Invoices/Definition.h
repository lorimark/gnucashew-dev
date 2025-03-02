#line 2 "src/Dbo/Invoices/Definition.h"

#ifndef __DBO_INVOICES_DEFINITION_H___
#define __DBO_INVOICES_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace Invoices {

extern const char * s_tableName;

      namespace Field {

extern const Wt::WFormModel::Field guid             ; // text(32) PRIMARY KEY NOT NULL,
extern const Wt::WFormModel::Field id               ; // text(2048)           NOT NULL,
extern const Wt::WFormModel::Field date_opened      ; // text(19),
extern const Wt::WFormModel::Field date_posted      ; // text(19),
extern const Wt::WFormModel::Field notes            ; // text(2048)           NOT NULL,
extern const Wt::WFormModel::Field active           ; // integer              NOT NULL,
extern const Wt::WFormModel::Field currency         ; // text(32)             NOT NULL,
extern const Wt::WFormModel::Field owner_type       ; // integer,
extern const Wt::WFormModel::Field owner_guid       ; // text(32),
extern const Wt::WFormModel::Field terms            ; // text(32),
extern const Wt::WFormModel::Field billing_id       ; // text(2048),
extern const Wt::WFormModel::Field post_txn         ; // text(32),
extern const Wt::WFormModel::Field post_lot         ; // text(32),
extern const Wt::WFormModel::Field post_acc         ; // text(32),
extern const Wt::WFormModel::Field billto_type      ; // integer,
extern const Wt::WFormModel::Field billto_guid      ; // text(32),
extern const Wt::WFormModel::Field charge_amt_num   ; // bigint,
extern const Wt::WFormModel::Field charge_amt_denom ; // bigint

      } // endnamespace Field {
    } // endnamespace Invoices {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_INVOICES_DEFINITION_H___



