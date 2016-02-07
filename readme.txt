arduinod creates a TCP connection to talk to the Arduino device
Copyright (C) 2015  Salim Haniff <blog@salimhaniff.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should review the GNU General Public License to accept the agreements to 
use this program. Available at http://www.gnu.org/licenses/gpl-3.0.html .

This program will provide a TCP connection to the Arduino device.  You need to change the ARDUINO_PORT definition found in arduino.h to match the location of the Arduino device on your system.  Usually, /dev/ttyACM0.

This application was tested on a Raspberry Pi but should work on any Linux distr
ibution.


To compile this application run

$ make

then:

$ ./arduinod -h <ip_address> -p <port_number>

You can get more information about these programs from [my blog](http://salimhaniff.net/blog/Realtime-Monitoring-Of-A-Sensor-Attached-To-An-Arduino).
