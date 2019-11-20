#! /bin/sh
### BEGIN INIT INFO
# Provides:          ipscreen.sh
# Required-Start:    $all
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Start ipscreeb daemon at boot time
# Description:       Shows current ip on an i2c oled display
### END INIT INFO
#

# Some things that run always
touch /var/lock/blah

# Carry out specific functions when asked to by the system
case "$1" in
  start)
    echo "Starting ipscreen"
    screen -S IPSCREEN -d -m /opt/oled-ipscreen/ipscreen
    ;;
  stop)
    echo "Stopping ipscreen"
    screen -S IPSCREEN -X stuff "spawn daemon$(printf \\r)"
    ;;
  *)
    echo "Usage: /etc/init.d/ipscreen.sh {start|stop}"
    exit 1
    ;;
esac

exit 0
