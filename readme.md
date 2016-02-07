# arduinodPi

This program will provide a TCP connection to the Arduino device.  You need to change the ARDUINO_PORT definition found in arduino.h to match the location of the Arduino device on your system.  Usually, /dev/ttyACM0.

This application was tested on a Raspberry Pi but should work on any Linux distribution.

To compile this application run

```sh
$ make 
```
then:

```sh
$ ./arduinod -h <ip_address> -p <port_number>
```
If you omit the IP address then the application will bind to 0.0.0.0

You can get an example of the usage of this program from [my blog](http://salimhaniff.net/blog/Realtime-Monitoring-Of-A-Sensor-Attached-To-An-Arduino). 

