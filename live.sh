
while :
do

echo "killing previous task"
killall gnucashew-live
sleep 1

echo "running"
# valgrind -v --leak-check=full --show-leak-kinds=all \
# gdb --args \
./gnucashew-live /home/serveradmin/gnucash-dev.gnucash \
  --pid-file=gnucashew-bin-live.pid \
  --config=wt_config.xml \
  --approot="approot" \
  --docroot="docroot;.,/images,/resources,/styles,/themes,/dox" \
  --errroot="errroot" \
  --http-listen 0.0.0.0:8081 \

echo "restarting in 5..."
sleep 1
echo "restarting in 4..."
sleep 1
echo "restarting in 3..."
sleep 1
echo "restarting in 2..."
sleep 1
echo "restarting in 1..."
sleep 1

done

