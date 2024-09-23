

\mainpage GnuCashew ~ Web Based Version of GnuCash

First off... I love <a href="https://www.gnucash.org" target="_blank">GnuCash!</a>

Secondly... this is ~not~ GnuCash.  At present, no GnuCash code is in use
 here.  This tool works directly with gnucash.sqlite files only, by making
 direct calls to the database.  Therefore, Gnucashew intends to replicate
 the functionality of the gnucash engine (lots to do there!).

This is an attempt to produce a web-based interface for the GnuCash program.
 Knowing that there have been several other attempts, this is based on my
 interest of hacking on GnuCash and also adding additional features, such
 as managed-bill-pay, mobile-friendly app and so forth.

\image html GnucashewMainscreen.png width=640px

If you are interested in an active demo, you can find it here;

https://gnucashew.lorimarksolutions.com/demo

Source Code Repository is found here;

https://github.com/lorimark/gnucashew

This project uses Wt (https://www.webtoolkit.eu/wt) as the web rendering library.


\page AccountEditor Account Editor

This will edit the details of the selected account.

\image html EditAccountDetailForm.png "Edit Account Detail Form" width=320


\page Tables Gnucash SQL Table Creation List

SQL Tables

\code
 CREATE TABLE gnclock
 (
  Hostname varchar(255),
  PID int
 );

 CREATE TABLE versions
 (
  table_name text(50) PRIMARY KEY NOT NULL,
  table_version integer NOT NULL
 );

 CREATE TABLE books
 (
   guid text(32) PRIMARY KEY NOT NULL,
   root_account_guid text(32) NOT NULL,
   root_template_guid text(32) NOT NULL
 );

 CREATE TABLE commodities
 (
  guid text(32) PRIMARY KEY NOT NULL,
  namespace text(2048) NOT NULL,
  mnemonic text(2048) NOT NULL,
  fullname text(2048),
  cusip text(2048),
  fraction integer NOT NULL,
  quote_flag integer NOT NULL,
  quote_source text(2048),
  quote_tz text(2048)
 );

 CREATE TABLE accounts
 (
  guid text(32) PRIMARY KEY NOT NULL,
  name text(2048) NOT NULL,
  account_type text(2048) NOT NULL,
  commodity_guid text(32),
  commodity_scu integer NOT NULL,
  non_std_scu integer NOT NULL,
  parent_guid text(32),
  code text(2048),
  description text(2048),
  hidden integer,
  placeholder integer
 );

 CREATE TABLE budgets
 (
  guid text(32) PRIMARY KEY NOT NULL,
  name text(2048) NOT NULL,
  description text(2048),
  num_periods integer NOT NULL
 );

 CREATE TABLE budget_amounts
 (
  id integer PRIMARY KEY AUTOINCREMENT NOT NULL,
  budget_guid text(32) NOT NULL,
  account_guid text(32) NOT NULL,
  period_num integer NOT NULL,
  amount_num bigint NOT NULL,
  amount_denom bigint NOT NULL
 );

 CREATE TABLE sqlite_sequence
 (
  name,
  seq
 );

 CREATE TABLE prices
 (
  guid text(32) PRIMARY KEY NOT NULL,
  commodity_guid text(32) NOT NULL,
  currency_guid text(32) NOT NULL,
  date text(19) NOT NULL,
  source text(2048),
  type text(2048),
  value_num bigint NOT NULL,
  value_denom bigint NOT NULL
 );

 CREATE TABLE transactions
 (
  guid text(32) PRIMARY KEY NOT NULL,
  currency_guid text(32) NOT NULL,
  num text(2048) NOT NULL,
  post_date text(19),
  enter_date text(19),
  description text(2048)
 );
 CREATE INDEX tx_post_date_index ON transactions(post_date);

 CREATE TABLE splits
 (
  guid text(32) PRIMARY KEY NOT NULL,
  tx_guid text(32) NOT NULL,
  account_guid text(32) NOT NULL,
  memo text(2048) NOT NULL,
  action text(2048) NOT NULL,
  reconcile_state text(1) NOT NULL,
  reconcile_date text(19),
  value_num bigint NOT NULL,
  value_denom bigint NOT NULL,
  quantity_num bigint NOT NULL,
  quantity_denom bigint NOT NULL,
  lot_guid text(32)
 );
 CREATE INDEX splits_tx_guid_index ON splits(tx_guid);
 CREATE INDEX splits_account_guid_index ON splits(account_guid);

 CREATE TABLE slots
 (
  id integer PRIMARY KEY AUTOINCREMENT NOT NULL,
  obj_guid text(32) NOT NULL,
  name text(4096) NOT NULL,
  slot_type integer NOT NULL,
  int64_val bigint,
  string_val text(4096),
  double_val float8,
  timespec_val text(19),
  guid_val text(32),
  numeric_val_num bigint,
  numeric_val_denom bigint,
  gdate_val text(8)
 );
 CREATE INDEX slots_guid_index ON slots(obj_guid);

 CREATE TABLE recurrences
 (
  id integer PRIMARY KEY AUTOINCREMENT NOT NULL,
  obj_guid text(32) NOT NULL,
  recurrence_mult integer NOT NULL,
  recurrence_period_type text(2048) NOT NULL,
  recurrence_period_start text(8) NOT NULL,
  recurrence_weekend_adjust text(2048) NOT NULL
 );

 CREATE TABLE schedxactions
 (
  guid text(32) PRIMARY KEY NOT NULL,
  name text(2048),
  enabled integer NOT NULL,
  start_date text(8),
  end_date text(8),
  last_occur text(8),
  num_occur integer NOT NULL,
  rem_occur integer NOT NULL,
  auto_create integer NOT NULL,
  auto_notify integer NOT NULL,
  adv_creation integer NOT NULL,
  adv_notify integer NOT NULL,
  instance_count integer NOT NULL,
  template_act_guid text(32) NOT NULL
 );

 CREATE TABLE lots
 (
  guid text(32) PRIMARY KEY NOT NULL,
  account_guid text(32),
  is_closed integer NOT NULL
 );

 CREATE TABLE billterms
 (
  guid text(32) PRIMARY KEY NOT NULL,
  name text(2048) NOT NULL,
  description text(2048) NOT NULL,
  refcount integer NOT NULL,
  invisible integer NOT NULL,
  parent text(32),
  type text(2048) NOT NULL,
  duedays integer,
  discountdays integer,
  discount_num bigint,
  discount_denom bigint,
  cutoff integer
 );

 CREATE TABLE employees
 (
  guid text(32) PRIMARY KEY NOT NULL,
  username text(2048) NOT NULL,
  id text(2048) NOT NULL,
  language text(2048) NOT NULL,
  acl text(2048) NOT NULL,
  active integer NOT NULL,
  currency text(32) NOT NULL,
  ccard_guid text(32),
  workday_num bigint NOT NULL,
  workday_denom bigint NOT NULL,
  rate_num bigint NOT NULL,
  rate_denom bigint NOT NULL,
  addr_name text(1024),
  addr_addr1 text(1024),
  addr_addr2 text(1024),
  addr_addr3 text(1024),
  addr_addr4 text(1024),
  addr_phone text(128),
  addr_fax text(128),
  addr_email text(256)
 );

 CREATE TABLE entries
 (
  guid text(32) PRIMARY KEY NOT NULL,
  date text(19) NOT NULL,
  date_entered text(19),
  description text(2048),
  action text(2048),
  notes text(2048),
  quantity_num bigint,
  quantity_denom bigint,
  i_acct text(32),
  i_price_num bigint,
  i_price_denom bigint,
  i_discount_num bigint,
  i_discount_denom bigint,
  invoice text(32),
  i_disc_type text(2048),
  i_disc_how text(2048),
  i_taxable integer,
  i_taxincluded integer,
  i_taxtable text(32),
  b_acct text(32),
  b_price_num bigint,
  b_price_denom bigint,
  bill text(32),
  b_taxable integer,
  b_taxincluded integer,
  b_taxtable text(32),
  b_paytype integer,
  billable integer,
  billto_type integer,
  billto_guid text(32),
  order_guid text(32)
 );

 CREATE TABLE invoices
 (
  guid text(32) PRIMARY KEY NOT NULL,
  id text(2048) NOT NULL,
  date_opened text(19),
  date_posted text(19),
  notes text(2048) NOT NULL,
  active integer NOT NULL,
  currency text(32) NOT NULL,
  owner_type integer,
  owner_guid text(32),
  terms text(32),
  billing_id text(2048),
  post_txn text(32),
  post_lot text(32),
  post_acc text(32),
  billto_type integer,
  billto_guid text(32),
  charge_amt_num bigint,
  charge_amt_denom bigint
 );

 CREATE TABLE jobs
 (
  guid text(32) PRIMARY KEY NOT NULL,
  id text(2048) NOT NULL,
  name text(2048) NOT NULL,
  reference text(2048) NOT NULL,
  active integer NOT NULL,
  owner_type integer,
  owner_guid text(32)
 );

 CREATE TABLE orders
 (
  guid text(32) PRIMARY KEY NOT NULL,
  id text(2048) NOT NULL,
  notes text(2048) NOT NULL,
  reference text(2048) NOT NULL,
  active integer NOT NULL,
  date_opened text(19) NOT NULL,
  date_closed text(19) NOT NULL,
  owner_type integer NOT NULL,
  owner_guid text(32) NOT NULL
 );

 CREATE TABLE taxtables
 (
  guid text(32) PRIMARY KEY NOT NULL,
  name text(50) NOT NULL,
  refcount bigint NOT NULL,
  invisible integer NOT NULL,
  parent text(32)
 );

 CREATE TABLE taxtable_entries
 (
  id integer PRIMARY KEY AUTOINCREMENT NOT NULL,
  taxtable text(32) NOT NULL,
  account text(32) NOT NULL,
  amount_num bigint NOT NULL,
  amount_denom bigint NOT NULL,
  type integer NOT NULL
 );

 CREATE TABLE vendors
 (
  guid text(32) PRIMARY KEY NOT NULL,
  name text(2048) NOT NULL,
  id text(2048) NOT NULL,
  notes text(2048) NOT NULL,
  currency text(32) NOT NULL,
  active integer NOT NULL,
  tax_override integer NOT NULL,
  addr_name text(1024),
  addr_addr1 text(1024),
  addr_addr2 text(1024),
  addr_addr3 text(1024),
  addr_addr4 text(1024),
  addr_phone text(128),
  addr_fax text(128),
  addr_email text(256),
  terms text(32),
  tax_inc text(2048),
  tax_table text(32)
 );

/endcode



