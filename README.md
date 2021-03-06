# ubxgps

Arduino sample sketch of uBlox position and altitude in UBX Binary mode. based on Sparkfun GPS Library (https://github.com/sparkfun/SparkFun_Ublox_Arduino_Library)

### Hardware setup

Adafruit Feather 32u4 basic proto with TX/RX connected directly to NEO-M8P-2
https://learn.adafruit.com/adafruit-feather-32u4-basic-proto/pinouts

* Use https://www.sparkfun.com/products/15005 NEO-M8P-2 RTK GPS Module
* Use https://www.adafruit.com/product/2771 Atmega32u4 @8Mhz
* Use https://www.adafruit.com/product/3463 NXP 9DOF
* RX/TX (Arduino Serial2) connected to TX/RX (null-modem) of NEO-M8P2 with 3" (8cm) wire
* Use 26AWG flexible silicon wire for attaching the digital signals and power (UART, I2C, 3V3) as below:
* Bring out 3V3/GND wires from Feather 32U4 to receive 3V power from the onboard Feather power adapter.
* Connect GPS 3V3 and GND to Feather 32U4 3V3/GND Pair 2
* Connect Feather 32U4 TX to GPS RX, 32U4 RX to GPS TX
* Power is provided by Feather onboard 500mA peak AP2112K-3.3.
```

SparkFun Ublox Example
GPS: trying 38400 baud
GPS serial connected
Current update rate:1
Lat: xxxx Long: -yyyy (degrees * 10^-7) Alt: 86090 (mm) SIV: 14 Fix: 3D RTK: 0 Speed: 4 (mm/s) Heading: 27287756 (degrees * 10^-5) pDOP: 1.32


```
