#line 2 "src/Dbo/Entries/Definition.h"

#ifndef __DBO_ENTRIES_DEFINITION_H___
#define __DBO_ENTRIES_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace Entries {

extern const char * s_tableName;

      namespace Field {

extern const Wt::WFormModel::Field guid             ; // text(32) PRIMARY KEY NOT NULL,
extern const Wt::WFormModel::Field date             ; //  text(19) NOT NULL,
extern const Wt::WFormModel::Field date_entered     ; //  text(19),
extern const Wt::WFormModel::Field description      ; //  text(2048),
extern const Wt::WFormModel::Field action           ; //  text(2048),
extern const Wt::WFormModel::Field notes            ; // text(2048),
extern const Wt::WFormModel::Field quantity_num     ; // bigint,
extern const Wt::WFormModel::Field quantity_denom   ; // bigint,
extern const Wt::WFormModel::Field i_acct           ; // text(32),
extern const Wt::WFormModel::Field i_price_num      ; // bigint,
extern const Wt::WFormModel::Field i_price_denom    ; // bigint,
extern const Wt::WFormModel::Field i_discount_num   ; // bigint,
extern const Wt::WFormModel::Field i_discount_denom ; // bigint,
extern const Wt::WFormModel::Field invoice          ; // text(32),
extern const Wt::WFormModel::Field i_disc_type      ; // text(2048),
extern const Wt::WFormModel::Field i_disc_how       ; // text(2048),
extern const Wt::WFormModel::Field i_taxable        ; // integer,
extern const Wt::WFormModel::Field i_taxincluded    ; // integer,
extern const Wt::WFormModel::Field i_taxtable       ; // text(32),
extern const Wt::WFormModel::Field b_acct           ; // text(32),
extern const Wt::WFormModel::Field b_price_num      ; // bigint,
extern const Wt::WFormModel::Field b_price_denom    ; // bigint,
extern const Wt::WFormModel::Field bill             ; // text(32),
extern const Wt::WFormModel::Field b_taxable        ; // integer,
extern const Wt::WFormModel::Field b_taxincluded    ; // integer,
extern const Wt::WFormModel::Field b_taxtable       ; // text(32),
extern const Wt::WFormModel::Field b_paytype        ; // integer,
extern const Wt::WFormModel::Field billable         ; // integer,
extern const Wt::WFormModel::Field billto_type      ; // integer,
extern const Wt::WFormModel::Field billto_guid      ; // text(32),
extern const Wt::WFormModel::Field order_guid       ; // text(32)

      } // endnamespace Field {
    } // endnamespace Entries {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_ENTRIES_DEFINITION_H___



