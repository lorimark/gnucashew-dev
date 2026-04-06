
to work on this project;

1. run ./devess from the root folder

This will start up a docker environment that contains
 my version of .vimrc and of course all the build tools
 needed to work on anything.  If I need a tool I add
 it to the devess image.  sqlite is in there as well.
 With devess you should have everything you need.

2. to develop; run mc - midnight commander

Midnight Commander is handy for bumping around
 the folders.

3. to build; 

     a. cd to build foler
     b. run; ../doit.sh

The doit.sh script will terminate any running instances
 of the gnucashew binary, and then will build everything
 and then launch it.

~ ~ ~ ~ ~ ~

If you're interested in docker for;

  devess; see dev-essential project on github
  gnucashew-docker; also on github


