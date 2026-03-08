
#
# this automatically builds all from source and then runs the app
#  it also copies the bin to the 'live' image so that the
#  live on-line demo is also always up to date.
#
# to run, launch 'from' the 'build' folder.  This assumes there
#  is also a 'run.sh' script available in the same folder so that
#  the application will run after a successful build.
#

[[ -e "gnucashew-live" ]] && rm gnucashew-live

pkill -9 gnucashew-bin
make -j 4 && ../run.sh
# make && ../run.sh

# ../doit.sh

