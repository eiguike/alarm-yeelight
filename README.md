## alarm-yeelight
one of my goals for 2020 is to wake up more earlier than 2019 and this my initial efforts to do that (and hopefully successfully).
it will work just turning on and off the yeelight's lamp. that's it!

this application is suppose to be used within your openwrt's router, but it is possible to extract the application and use in your computer.

### instructions to build for openwrt
1. clone this folder to OPENWRT_SDK/package 
2. make menuconfig
3. select this module
4. make package/alarm-yeelight/compile

### instructions to build without openwrt 
1. clone this repository
2. edit FIXED_LOCAL_ADDRESS definition to your local address
3. git submodule init && git submodule update
4. access src folder
5. make
6. execute ./alarm-xaiomi

### references:
- [Yeelight Inter Operation Specs](https://www.yeelight.com/download/Yeelight_Inter-Operation_Spec.pdf)
- [Hello world! for OpenWrt](https://openwrt.org/docs/guide-developer/helloworld/chapter1)
