
#
# this will kill a PID suspended by ^Z
#
kill -KILL $(jobs -l | awk '{print $2}')
fg

