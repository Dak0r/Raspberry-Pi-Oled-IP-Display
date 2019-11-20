mkdir /opt/oled-ipscreen
cp ./ipscreen /opt/oled-ipscreen
cp ./ipscreen.sh /etc/init.d/ipscreen.sh
chmod 755 /etc/init.d/ipscreen.sh
#update-rc.d ipscreen.sh defaults
echo "Now add '/etc/init.d/ipscreen.sh start' to your /etc/rc.local file!"
