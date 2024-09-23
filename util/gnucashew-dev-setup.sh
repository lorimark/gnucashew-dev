
#
# This will install all the necessary libraries and development
#  of gnucashew
#
# run as root
#

echo "update..."
apt-get update -q
apt-get upgrade -y
apt-get dist-upgrade -y
apt-get autoremove -y

#
# base stuff
#
echo "base stuff..."
apt-get install -y \
	wget \
	mc \
	vim \
	lynx \
	wget

#
# library build stuff
#
echo "library build stuff..."
apt-get install -y \
	libglib2.0-dev \
	pkg-config \
	make                         \
	dconf-cli                    \
	git                          \
	gettext                      \
	gcc                          \
	g++                          \
	libxml2-dev                  \
	libxslt1-dev                 \
	xsltproc                     \
	webkit2gtk-4.0-dev           \
	swig                         \
	guile-2.2-dev                \
	gwenhywfar-tools             \
	build-essential              \
	libofx-dev                   \
	libgtest-dev                 \
	libdbi-dev                   \
	libxml2-utils                \
	libboost-all-dev             \
	libboost-date-time-dev       \
	libboost-filesystem-dev      \
	libboost-locale-dev          \
	libboost-regex-dev           \
	libboost-program-options-dev \
	libboost-system-dev


#
# Set up Wt build environment
#
echo "install build tools"
apt-get install -y         \
	build-essential          \
	cmake                    \
	libboost-all-dev         \
	doxygen                  \
	imagemagick              \
	graphicsmagick           \
	libssl-dev               \
	libgraphicsmagick++1-dev \
	libhpdf-dev              \
	libpango1.0-dev          \
	libghc-openglraw-dev     \
	freeglut3-dev            \
  libcurl4-openssl-dev

echo "fetch and install howard hinnant date library"
git clone https://github.com/HowardHinnant/date.git
cd date
mkdir build && cd build
cmake -DENABLE_DATE_TESTING=ON -DBUILD_TZ_LIB=ON ..
make
make install

cd ../..
echo "install and build wt"
git clone https://github.com/emweb/wt.git wt/src
cd wt
mkdir build
cd build
#-DCMAKE_BUILD_TYPE=Debug \

cmake \
  -DCMAKE_INSTALL_PREFIX=/opt/Wt4 \
  -DWT_WRASTERIMAGE_IMPLEMENTATION=GraphicsMagick \
  -DCONNECTOR_FCGI=OFF \
  -DENABLE_HARU=TRUE \
  ../src

make -j 4
make install

echo "********"
echo "********"
echo "********"
echo "********"
echo "********"
echo "all set!  run 'gnucashew-src-setup.sh' as your regular user to fetch and set up your dev working environment"

