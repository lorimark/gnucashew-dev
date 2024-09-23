set -x

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

echo "********"
echo "********"
echo "********"
echo "********"
echo "********"
echo "all set!"

