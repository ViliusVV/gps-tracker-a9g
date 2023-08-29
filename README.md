#### Debugging using FT232 chip/adapter using platformIO

Set FT232H usb driver to winUsb in Zadig [link](https://zadig.akeo.ie)

Connect FT232H to ESP32:
* FT232->  ESP32
* AD0  ->  13
* AD1  ->  12
* AD2  ->  15
* AD3  ->  14
* GND  ->  GND
* 5V   ->  5V

#### Create config.h file in src folder with following content:
```
#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "secret"
#define BACKEND_HOST "domain.com"
#define BACKEND_PORT 1111
```
