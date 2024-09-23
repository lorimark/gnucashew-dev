

#include "Accounts.h"

const char * GCW::Dbo::Accounts::s_tableName = "accounts";

const std::vector< GCW::Dbo::Accounts::AccountDef_t > GCW::Dbo::Accounts::s_accountDefs =
{// type                                   dbcr                                name           colAccount   colDr        colCr
  { GCW::Dbo::Accounts::Type::INVALID    , GCW::Dbo::Accounts::DrCr::NONE   ,  "INVALID"    , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::NONE       , GCW::Dbo::Accounts::DrCr::NONE   ,  "NONE"       , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::BANK       , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "BANK"       , "transfer" , "deposit"  , "withdrawal"  },
  { GCW::Dbo::Accounts::Type::CASH       , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "CASH"       , "transfer" , "receive"  , "spend"       },
  { GCW::Dbo::Accounts::Type::CREDIT     , GCW::Dbo::Accounts::DrCr::CREDIT ,  "CREDIT"     , "blank"    , "payment"  , "charge"      },
  { GCW::Dbo::Accounts::Type::ASSET      , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "ASSET"      , "transfer" , "deposit"  , "withdrawal"  },
  { GCW::Dbo::Accounts::Type::LIABILITY  , GCW::Dbo::Accounts::DrCr::CREDIT ,  "LIABILITY"  , "account"  , "payment"  , "charge"      },
  { GCW::Dbo::Accounts::Type::STOCK      , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "STOCK"      , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::MUTUAL     , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "MUTUAL"     , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::CURRENCY   , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "CURRENCY"   , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::INCOME     , GCW::Dbo::Accounts::DrCr::CREDIT ,  "INCOME"     , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::EXPENSE    , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "EXPENSE"    , "transfer" , "expense"  , "rebate"      },
  { GCW::Dbo::Accounts::Type::EQUITY     , GCW::Dbo::Accounts::DrCr::CREDIT ,  "EQUITY"     , "transfer" , "decrease" , "increase"    },
  { GCW::Dbo::Accounts::Type::RECEIVABLE , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "RECEIVABLE" , "transfer" , "invoice"  , "payment"     },
  { GCW::Dbo::Accounts::Type::PAYABLE    , GCW::Dbo::Accounts::DrCr::CREDIT ,  "PAYABLE"    , "account"  , "payment"  , "charge"      },
  { GCW::Dbo::Accounts::Type::ROOT       , GCW::Dbo::Accounts::DrCr::NONE   ,  "ROOT"       , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::TRADING    , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "TRADING"    , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::CHECKING   , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "CHECKING"   , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::SAVINGS    , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "SAVINGS"    , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::MONEYMRKT  , GCW::Dbo::Accounts::DrCr::DEBIT  ,  "MONEYMRKT"  , "account"  , "debit"    , "credit"      },
  { GCW::Dbo::Accounts::Type::CREDITLINE , GCW::Dbo::Accounts::DrCr::CREDIT ,  "CREDITLINE" , "account"  , "debit"    , "credit"      },
};

const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::guid             = "guid"           ; // text(32) PRIMARY KEY NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::name             = "name"           ; // text(2048) NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::account_typeName = "account_type"   ; // text(2048) NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::commodity_guid   = "commodity_guid" ; // text(32)
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::commodity_scu    = "commodity_scu"  ; // integer NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::non_std_scu      = "non_std_scu"    ; // integer NOT NULL
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::parent_guid      = "parent_guid"    ; // text(32)
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::code             = "code"           ; // text(2048)
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::description      = "description"    ; // text(2048)
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::hidden           = "hidden"         ; // integer
const Wt::WFormModel::Field GCW::Dbo::Accounts::Field::placeHolder      = "placeholder"    ; // integer



