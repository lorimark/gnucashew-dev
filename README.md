# GnuCashew
Web based Accounting System compatible with GnuCash data files.

<small><b>(this is NOT gnucash ~ no gnucash code is in use here)</b></small>

This is an attempt to produce a web-based interface for the
 GnuCash data files.  Knowing that there have been many other
 attempts, this is based on my interest of hacking on GnuCash
 and also adding additional features, such as managed-bill-pay
 and so forth.  My preference is to hook directly in to the
 gnucash codebase for reading and writing to the data files,
 but I am finding the code there to be pretty daunting... so
 I'll try from the 'other side' and see how far I can get.

If you want to fiddle with a simple demo, go to;

https://gnucashew.lorimarksolutions.com/demo

This will put you in to a generic default gnucash sqlite file
 with basically nothing.  This file doesn't get regenerated
 or replaced, so any entries you put in there will remain.  I
 will try to keep the demo running, but if you find it isn't
 shoot me a message.

The source-generated doxygen files can be found here;

https://gnucashew.lorimarksolutions.com/dox/html/index.html

This project uses Wt (https://www.webtoolkit.eu/wt) as the
 web rendering library.

Have fun!  Let me know what you think!

mark@lorimarksolutions.com

