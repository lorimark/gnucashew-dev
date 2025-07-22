#line 2 "src/Glb/Numeric.h"

#ifndef __GCW_NUMERIC_H___
#define __GCW_NUMERIC_H___

#include "../3rd/decimal.h"

namespace GCW {

class Numeric
: public DECIMAL::decimal<2>
{
  public:

    Numeric(): DECIMAL::decimal<2>(0) {}
    Numeric( int _value ): DECIMAL::decimal<2>( _value ) {}

    auto addValue( const Wt::WString & _value )-> void
    {
    }

    auto subValue( const Wt::WString & _value )-> void
    {
    }

};

} // endnamespace GCW

#endif

