# How to install the ESP8266 build environment

The build environment for ESP8266 consists of three parts: the [ESP8266 NONOS SDK](#installation-of-esp8266-nonos-sdk), the [ESP8266 toolchain](#installation-of-esp8266-toolchain) and the [esptool](#installation-of-esptool).

## Installation of ESP8266 NONOS SDK

1. Clone the [ESP8266 NONOS SDK](https://github.com/espressif/ESP8266_NONOS_SDK) repository and checkout the **v3.0.4** tag, or download the corresponding [ZIP archive](https://github.com/espressif/ESP8266_NONOS_SDK/archive/refs/tags/v3.0.4.zip) and uncompress it to a location of your choice.

    > &#x26A0; Make sure that the path to the location of the ESP8266 NONOS SDK on your machine does not contain any spaces.

2. Apply the ESP8266 NONOS SDK patches provided along with the FotaHub Device SDK for ESP8266 by copying all content of the `fotahub-device-sdk-esp8266/third-party/esp8266-nonos-sdk-patches` folder over the location where your have installed the original version of the ESP8266 NONOS SDK.
 
    > &#x1F6C8; The ESP8266 NONOS SDK patches enable ESP8266 application code to be compiled as C99, and provide enhancements for mbed TLS and the UART driver library module.
  
## Installation of ESP8266 toolchain

Install the ESP8266 toolchain as explained [here](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#setup-toolchain).

> &#x26A0; When you are using Windows, make sure you refer to version [v4.8.5](https://dl.espressif.com/dl/xtensa-lx106-elf-win32-1.22.0-88-gde0bdc1-4.8.5.tar.gz) of the ESP8266 toolchain and extract the downloaded archive into the `C:\msys32\opt` folder (e.g. using [7-Zip](https://www.7-zip.org)). Also add the `C:\msys32\usr\bin` folder to the user or system `Path` environment variable.

> &#x26A0; When you are using Linux or Mac OS X, extract the downloaded archive into the `/opt` directory (using `tar -xzf <downloaded archive>.tar.gz`)

## Installation of esptool

The [esptool](https://github.com/espressif/esptool) is a ROM bootloader utility for Espressif ESP8266 & ESP32 series chips. You will need it to flash firmware binaries to your ESP8266 board. To install it follow the steps described [here](https://github.com/espressif/esptool#easy-installation).

> &#x26A0; When you are using Windows, make sure that you install esptool using the Python 2.7 installation included in the MSYS2 environment that you've installed along with ESP8266 toolchain. You can achieve that by using the following command:

```sh
C:\msys32\mingw32\bin\pip install esptool
```
