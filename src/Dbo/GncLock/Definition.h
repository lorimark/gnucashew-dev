#line 2 "src/Dbo/GncLock/Definition.h"

#ifndef __DBO_GNCLOCK_DEFINITION_H___
#define __DBO_GNCLOCK_DEFINITION_H___

#include <Wt/WFormModel.h>

namespace GCW {
  namespace Dbo {
    namespace GncLock {

extern const char * s_tableName;

      namespace FieldDef {

extern const Wt::WFormModel::Field hostname ; // Hostname varchar(255),
extern const Wt::WFormModel::Field pid      ; // PID int

      } // endnamespace Field {
    } // endnamespace GncLock {
  } // endnamespace Dbo {
} // endnamespace GCW {

#endif // #ifndef __DBO_GNCLOCK_H___



