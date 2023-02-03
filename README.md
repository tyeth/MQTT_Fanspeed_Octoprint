## MQTT Remote Fan Client for Octoprint

Setup your details in the sketch and then compile and flash to your esp32 QTPY.

If you pick another pin from Pin 15 then then update the code accordingly

Expected serial output is like so (generated on wokwi.com https://wokwi.com/projects/355650188569818113 ):
```
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
configspi:0x000000b9
SPIWP:0x00
mode:DIO, clock div:1
load:0x3fce3808,len:0x370
load:0x403c9700,len:0x900
load:0x403cc700,len:0x2364
SHA-256 comparison failed:
Calculated: bea01f04c6f0e287a682f128805e3fce115955179100e98d8f412fe7697f8bdc
Expected: 08ea492e448f88de75319ed18ac319444e578d9c6bc7003c5c4807382bf389bd
Attempting to boot anyway...
entry 0x403c98ac
Connecting to WiFi...
Connected to WiFi
fanspeed PWM duty cycle for analogWrite:
0
Attempting MQTT connection...
MQTT connected!
mqtt msg callback:
mqtt msg has fanspeed:
100%
fanspeed PWM duty cycle for analogWrite:
255
mqtt msg callback:
mqtt msg has fanspeed:
100%
fanspeed unchanged.
mqtt msg callback:
mqtt msg has fanspeed:
100%
fanspeed unchanged.
```