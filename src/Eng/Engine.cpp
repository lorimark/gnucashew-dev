#line 2 "src/Eng/Engine.cpp"

#include <iostream>

#include <gnucash/gnc-session.h>
#include <gnucash/Account.h>
#include <gnucash/Transaction.h>
#include <gnucash/qofsession.h>

#include "Engine.h"

GCW::Eng::Engine::
Engine()
{
} // endGCW::Eng::Engine::Engine()

bool
GCW::Eng::Engine::
open( const std::string & _filePath )
{
  if( isOpen() )
    return true;

  std::cout << __FILE__ << ":" << __LINE__ << " " << _filePath << std::endl;

  return true;
}

bool
GCW::Eng::Engine::
isOpen()
{
  return true;
}

bool
GCW::Eng::Engine::
hasGnucashewExtensions()
{
  return true;
}
