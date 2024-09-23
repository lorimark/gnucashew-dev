
#
# This will install all the necessary libraries and development
#  of gnucash
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
	make                        \
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
# gnucash build-dep stuff
# update sources.list so we can pull the "build-dep gnucash" below
#
echo "gnucash build-dep stuff"
# sed -i '/^#.*deb-src/s/^#//' /etc/apt/sources.list
echo "build-dep"
apt-get -y build-dep gnucash

echo "********"
echo "********"
echo "********"
echo "********"
echo "********"
echo "all set!  run 'gnucash-src-setup.sh' as your regular user to fetch and set up your dev working environment"

