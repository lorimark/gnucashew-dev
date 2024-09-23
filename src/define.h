#line 2 "src/define.h"

#ifndef __DEFINE_H___
#define __DEFINE_H___

/*
** This project can use GNUCASHEW or GNUCASH sessions.
**  The GNUCASHEW session makes direct SQL calls to a sqlite file
**  The GNUCASH session makes use of the libgnucash api.
**
*/
//#define USE_GNUCASH_ENGINE
#define USE_GNUCASHEW_SESSION



#define TR(X) Wt::WString::tr(X)
#define TR8(X) TR(X).toUTF8()



#endif // #ifndef __DEFINE_H___


