# FotaHub&reg; Embedded Device SDK for ESP8266&reg;
The FotaHub&reg; Device SDK for ESP8266&reg; enables developers to create firmware for ESP8266&reg;-based IoT devices that can be updated through [FotaHub](http://fotahub.com). It provides a FotaHub client C library along with a set of examples illustrating how the latter can be used and integrated in real applications.

# Installation
To use the FotaHub&reg; Device SDK for ESP8266&reg;, the prerequisites described in the following must be available on your laptop or computer. The easiest and quickest way to make that happen is to use Docker. If you are an experienced user, you may also opt for installing the complete set of prerequisites directly on your machine instead.

## ESP8266 NONOS SDK and toolchain
When using Docker, nothing but [Docker](https://docs.docker.com/get-docker) itself needs to be installed to cover the ESP8266-specific preqrequisites. All of the latter are included in a dedicated Docker image that is provided at [Docker Hub](https://hub.docker.com/r/fotahub/esp8266-nonos-sdk). It gets automatically pulled onto your machine when running the build commands of the various examples included in this project.

In case you prefer to set up the ESP8266 build environment directly on your machine, you don't need Docker but must install the required SDKs and tools manually as explained [here](docs/installation/install-build-environment.md). 

## General purpose tools
In addition to the ESP8266-related prerequisites, the following general purpose tools need to be available on your laptop or computer:
* A text editor or IDE of your choice, e.g., [Visual Studio Code](https://code.visualstudio.com)  
* A serial monitor of your choice, e.g., [CoolTerm](https://freeware.the-meiers.org) (a nice quick start guide can be found [here](https://learn.adafruit.com/getting-started-with-binho-nova/quickstart-with-coolterm))
* The device driver for the USB to serial converter chip of your ESP8266 board (in case it does not get installed automatically by the operating system). Typically, it is one of the following:
  * CP210x: [CP210x USB to UART Bridge Virtual COM Port (VCP) drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
  * FTDI: [FTDI Virtual COM Port Drivers](https://ftdichip.com/drivers/vcp-drivers)

# Getting started
The best way to get started with the FotaHub&reg; Device SDK for ESP8266&reg; is to try out and study the included examples:
* [Simple](docs/getting-started/simple.md) - "Hello World" of firmware over-the-air updating with FotaHub&reg;
* [Rollbackable](docs/getting-started/rollbackable.md) - Downloads and launches a new firmware version provided at FotaHub&reg;, rolls it back to the previous version if something goes wrong
* [Thing Shadow](docs/getting-started/thingshadow.md) - A real-world scenario where FotaHub&reg; is used in combination with the AWS IoT Thing Shadow service to trigger firmware updates over-the-air updates through the cloud

# API Reference
View the [C API reference](include/FotaHub.h) for detailed information about the FotaHub&reg; client library (:construction: *under construction*).

# License
Unless specifically indicated otherwise in a file included in this project, FotaHub&reg; Device SDK for ESP8266&reg; files are provided under the *Apache-2.0* license. See the [LICENSE](LICENSE) file for the full text of this license.

The terms of the license attributed to this project do not alter any rights or obligations you may have under the licenses of any third-party software which is redistributed through the present project. Refer to the [NOTICE](NOTICE.md) file for detailed information regarding these aspects.