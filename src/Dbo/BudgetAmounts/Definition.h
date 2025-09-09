#line 2 "src/Dbo/BudgetAmounts/Definition.h"

#ifndef __DBO_BUDGETAMOUNTS_DEFINITION_H___
#define __DBO_BUDGETAMOUNTS_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace BudgetAmounts {

extern const char * s_tableName;

      namespace Field {

        /*
        ** sqlite> .schema budget_amounts
        ** CREATE TABLE budget_amounts
        ** (
        **  id           integer  PRIMARY KEY AUTOINCREMENT NOT NULL,
        **  budget_guid  text(32) NOT NULL,
        **  account_guid text(32) NOT NULL,
        **  period_num   integer  NOT NULL,
        **  amount_num   bigint   NOT NULL,
        **  amount_denom bigint   NOT NULL
        ** );
        */
extern const Wt::WFormModel::Field budget_guid      ; // text(32) NOT NULL
extern const Wt::WFormModel::Field account_guid     ; // text(32) NOT NULL
extern const Wt::WFormModel::Field period_num       ; // integer  NOT NULL
extern const Wt::WFormModel::Field amount_num       ; // bigint   NOT NULL
extern const Wt::WFormModel::Field amount_denom     ; // bigint   NOT NULL

      } // endnamespace Field {
    } // endnamespace BudgetAmounts {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // __DBO_BUDGETAMOUNTS_DEFINITION_H___



