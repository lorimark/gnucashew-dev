#line 2 "src/Dbo/Customers/Definition.h"

#ifndef __DBO_CUSTOMER_DEFINITION_H___
#define __DBO_CUSTOMER_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace Customer {
      namespace Field {

extern Wt::WFormModel::Field guid           ; // text(32) PRIMARY KEY NOT NULL
extern Wt::WFormModel::Field name           ; // text(2048) NOT NULL
extern Wt::WFormModel::Field id             ; // text(2048) NOT NULL
extern Wt::WFormModel::Field notes          ; // text(2048) NOT NULL,
extern Wt::WFormModel::Field active         ; // integer NOT NULL,
extern Wt::WFormModel::Field discount_num   ; // bigint NOT NULL,
extern Wt::WFormModel::Field discount_denom ; // bigint NOT NULL,
extern Wt::WFormModel::Field credit_num     ; // bigint NOT NULL,
extern Wt::WFormModel::Field credit_denom   ; // bigint NOT NULL,
extern Wt::WFormModel::Field currency       ; // text(32) NOT NULL,
extern Wt::WFormModel::Field tax_override   ; // integer NOT NULL,
extern Wt::WFormModel::Field addr_name      ; // text(1024),
extern Wt::WFormModel::Field addr_addr1     ; // text(1024),
extern Wt::WFormModel::Field addr_addr2     ; // text(1024),
extern Wt::WFormModel::Field addr_addr3     ; // text(1024),
extern Wt::WFormModel::Field addr_addr4     ; // text(1024),
extern Wt::WFormModel::Field addr_phone     ; // text(128),
extern Wt::WFormModel::Field addr_fax       ; // text(128),
extern Wt::WFormModel::Field addr_email     ; // text(256),
extern Wt::WFormModel::Field shipaddr_name  ; // text(1024),
extern Wt::WFormModel::Field shipaddr_addr1 ; // text(1024),
extern Wt::WFormModel::Field shipaddr_addr2 ; // text(1024),
extern Wt::WFormModel::Field shipaddr_addr3 ; // text(1024),
extern Wt::WFormModel::Field shipaddr_addr4 ; // text(1024),
extern Wt::WFormModel::Field shipaddr_phone ; // text(128),
extern Wt::WFormModel::Field shipaddr_fax   ; // text(128),
extern Wt::WFormModel::Field shipaddr_email ; // text(256),
extern Wt::WFormModel::Field terms          ; // text(32),
extern Wt::WFormModel::Field tax_included   ; // integer,
extern Wt::WFormModel::Field taxtable       ; // text(32)

      } // endnamespace Field {
    } // endnamespace Customer {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_CUSTOMER_DEFINITION_H___



