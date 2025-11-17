
#
# this automatically builds all from source and then runs the app
#  it also copies the bin to the 'live' image so that the
#  live on-line demo is also always up to date.
#

[[ -e "gnucashew-live" ]] && rm gnucashew-live

pkill -9 gnucashew-bin
make -j 4 && ../run.sh
# make && ../run.sh

# ../doit.sh

