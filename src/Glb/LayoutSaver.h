#line 2 "src/Glb/LayoutSaver.h"

#ifndef __LAYOUTSAVER_H___
#define __LAYOUTSAVER_H___

namespace GCW {

#ifdef SECONDS_PER_YEAR
#define _SPYR_ (SECONDS_PER_YEAR)
#else
#define _SPYR_ (1 * 60 * 60 * 24 * 365)
#endif

/*
** Use this widget as a 'wrapper' for widgets to capture
**  changes to the layout size changes, so we can record
**  the width of the layout.
**
*/
template <class C>
class LayoutSaver
: public C
{
  public:

    LayoutSaver( const std::string name )
    : C(),
      m_name( name )
    {
      C::setLayoutSizeAware( true );
    }

    void layoutSizeChanged( int width, int height )
    {
      wApp-> setCookie( m_name + "_width",  Wtx::itos( width  ), _SPYR_ );
      wApp-> setCookie( m_name + "_height", Wtx::itos( height ), _SPYR_ );
    }

    std::string m_name;

}; // endclass LayoutSaver

} // endnamespace GCW

#endif


