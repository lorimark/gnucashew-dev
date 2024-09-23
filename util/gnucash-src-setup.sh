#
# Run this script to fetch and set up a dev
#  environment.  This will create the project
#  folder called 'gnucash-dev' in your current
#  folder, and then fetch the gnucash sources
#  and set up a build-directory and then cause
#  gnucash to build.   At the end, you should
#  have a good working gnucash binary available
#  for executing.
#

mkdir gnucash-dev
cd gnucash-dev
git clone https://github.com/Gnucash/gnucash.git src
mkdir build
cd build
cmake ../src

