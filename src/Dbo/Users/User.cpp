

#include "User.h"


const char * GCW::Dbo::Users::s_tableName = "gcw_users";

const Wt::WFormModel::Field GCW::Dbo::Users::Field::employee_guid = "employee_guid" ; // text(32) PRIMARY KEY NOT NULL

DBO_INSTANTIATE_TEMPLATES( GCW::Dbo::Users::Item );



