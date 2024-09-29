#line 2 "src/Dbo/Employees/Definition.h"

#ifndef __DBO_EMPLOYEES_DEFINITION_H___
#define __DBO_EMPLOYEES_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace Employees {

extern const char * s_tableName;

      namespace Field {

extern const Wt::WFormModel::Field guid           ; // text(32) PRIMARY KEY NOT NULL,
extern const Wt::WFormModel::Field username       ; // text(2048) NOT NULL,
extern const Wt::WFormModel::Field id             ; // text(2048) NOT NULL,
extern const Wt::WFormModel::Field language       ; // text(2048) NOT NULL,
extern const Wt::WFormModel::Field acl            ; // text(2048) NOT NULL,
extern const Wt::WFormModel::Field active         ; // integer NOT NULL,
extern const Wt::WFormModel::Field currency       ; // text(32) NOT NULL,
extern const Wt::WFormModel::Field ccard_guid     ; // text(32),
extern const Wt::WFormModel::Field workday_num    ; // bigint NOT NULL,
extern const Wt::WFormModel::Field workday_denom  ; // bigint NOT NULL,
extern const Wt::WFormModel::Field rate_num       ; // bigint NOT NULL,
extern const Wt::WFormModel::Field rate_denom     ; // bigint NOT NULL,
extern const Wt::WFormModel::Field addr_name      ; // text(1024),
extern const Wt::WFormModel::Field addr_addr1     ; // text(1024),
extern const Wt::WFormModel::Field addr_addr2     ; // text(1024),
extern const Wt::WFormModel::Field addr_addr3     ; // text(1024),
extern const Wt::WFormModel::Field addr_addr4     ; // text(1024),
extern const Wt::WFormModel::Field addr_phone     ; // text(128),
extern const Wt::WFormModel::Field addr_fax       ; // text(128),
extern const Wt::WFormModel::Field addr_email     ; // text(256)

      } // endnamespace Field {
    } // endnamespace Employees {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_EMPLOYEES_DEFINITION_H___



