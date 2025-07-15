#ps aux | grep 8077 | grep artecams | awk '{print $2}' | xargs kill -9
# sleep 1

echo "killing"
killall gnucashew-bin
sleep 1

echo "running"
# gdb --args \
# valgrind -v --leak-check=full --show-leak-kinds=all \
./gnucashew-bin sqlite3data.gnucash \
  --pid-file=gnucashew-bin-dev.pid \
  --config=../src/wt_config.xml \
  --approot="../approot" \
  --docroot="../docroot;.,/images,/resources,/styles,/themes,/dox" \
  --errroot="../errroot" \
  --http-listen 0.0.0.0:$GNUCASHEW_PORT \

