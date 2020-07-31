# Raspberry Pi Oled IP Display

Display the local ip adress on an 0.96" I²C OLED Display for headless installations.

Uses: https://github.com/bitbank2/oled_96.git

# How to install:

1. Run      ```sudo ./setup_build_tools.sh```
1. Run      ```sudo ./compile_oled_library.sh```
1. Run      ```make```
1. Run      ```sudo ./install_setup_script.sh```
2. Add the line ```/etc/init.d/ipscreen.sh start``` to ```/etc/rc.local```


# Alternate Setup, that disables the screen once you are logged in:

1. Add to ```/etc/rc.local``` (Starts IPScreen on boot) \
        ```su pi -c '/home/pi/path/to/RunIpScreen.sh'```
2. Add to ```~/.bashrc``` (disables IP Screen when logged in) \
        ```/home/pi/path/to/KillIPScreen.sh```
3. Add to ```~/.bashrc_logout``` (restarts ip Screen when logged out) \
        ```/home/pi/path/to/RunIpScreen.sh```
