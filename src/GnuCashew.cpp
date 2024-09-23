#line 2 "src/GnuCashew.cpp"

#include <thread>
#include <ctime>
#include <iostream>
#include <fstream>

#include <Wt/WMenu.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>
#include <Wt/WTabWidget.h>
#include <Wt/WText.h>
#include <Wt/WTime.h>
#include <Wt/WToolBar.h>
#include <Wt/WTreeTableNode.h>

#include "GnuCashew.h"


DECIMAL::decimal_format GCW::Cfg::decimal_format()
{
  return DECIMAL::decimal_format( '.', ',' );
}


std::string GCW::Cfg::date_format()
{
  return "MM/dd/yyyy";
//  return "yyyy-MM-dd";
}


std::string GCW::Cfg::time_format()
{
  return "hh:mm:ss";
}


