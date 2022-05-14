# AWS IoT Thing Shadow-driven FOTA update example

The *Thing Shadow* example demonstrates a real-world firmware over-the-air update procedure using the AWS IoT Thing Shadow (aka Device Shadow) service. The thing shadow is used to trigger firmware over-the-air updates on the device it represents through the cloud. Thanks to that, the device itself can be located in any place where Wi-Fi and Internet are available and does no longer need to be connected to a USB port of your laptop or computer as with the [Simple](simple.md) and [Rollbackable](rollbackable.md) examples. The thing shadow example also detects misbehaving firmware updates and rolls them back to the previous version.

## Technical context

If you are new to AWS IoT in general or the AWS IoT Thing Shadow service, you can find relevant introductory as well as detailed technical information [here](https://docs.aws.amazon.com/iot/latest/developerguide/what-is-aws-iot.html) and [here](https://docs.aws.amazon.com/iot/latest/developerguide/iot-device-shadows.html).

For the sake of simplicity, an unnamed *classic shadow* is used in this example. The standard [MQTT protocol](https://mqtt.org) and the [thing shadow MQTT topics](https://docs.aws.amazon.com/iot/latest/developerguide/reserved-topics.html#reserved-topics-shadow) defined by AWS are used for the communication between the device and its thing shadow.

## Operating principle

After startup, the device connects first to the configured Wi-Fi network and then to its AWS IoT Thing Shadow. It reports the currently running firmware version resulting in a shadow state document as follows:

```json
{
    "state": {
        "reported": {
            "currentVersion": "1.0",
            "updateStatus": "none"
        }
    }
}
```

From there on, the device listens for MQTT messages being published at the `ShadowTopicPrefix/update/delta` topic. It retrieves the delta state document from the body of such messages, and checks whether it includes a new firmware version the device should be updated to as well as the verification data for the new firmware version. As firmware updates for the ESP8266 always consist of two firmware binaries which contain the same code but are located to two different partitions in the ESP8266's flash memory, the verification data is required to carry along the checksums or signatures of both of these firmware binaries concatenated to each other like in the following example:

```json
{
    "state": {
        "newVersion": "1.1",
        "verificationData": "9fac9b21437c869229ea0f5296d8a5abc92e54a9d627790667ab1f652a515e669db15800e3c951ead25b5aa7c9238e6d170c1824887fbc7b3c82b9e6a901e983"
        }
    },
    ...
}
```

When the update info attributes found in the delta state document are complete and valid, a firmware update procedure is triggered. It involves the device to disconnect from its AWS IoT Thing Shadow, to determine in which partition the currently executing firmware version is located, and then to connect to FotaHub to download the binary of the new firmware version that is located to the other partition. Thereby, it uses a dedicated URL including the id of the product representing the device in FotaHub, and the name, the version and the partition index of the firmware binary to be retrieved, e.g.:

`https://bin.fotahub.com/6258c080-85f6-4a7a-84a2-7a9ef16d03fc/DemoProduct-1.1@1`

The downloaded firmware binary is stored in the device's flash memory using the partition that is not occupied by the still executing firmware version. At the same time, the downloaded firmware binary's checksum or signature gets recalculated and compared to the corresponding checksum or signature included in the previously received delta state document. If both match, the firmware update gets activated by restarting the device and letting boot it into the flash memory partition where the downloaded firmware binary has been stored. 

After the restart, the device starts executing the new firmware version downloaded from FotaHub. To be sure that it behaves as expeced, a built-in self test procedure is launched. Only when the latter completes successfully, the new firmware version is confirmed and becomes definite. In the opposite case, the previous firmware version is restored.

For obvious reasons, the ultimately required self test logic depends heavily on the nature of the underlying IoT application and device. The thing shadow example therefore implements only a very simple self test stub which returns a positive or negative result on a pseudo-random basis (see [DemoFOTAUpdateSelfTest.c](../../examples/huzzah/thingshadow/DemoFOTAUpdateSelfTest.c) for details). Consequently, the firmware update carried out in this example may succeed and remain in place or fail and be rolled back to the previous version depending on how it goes. To see both scenarios happening, just run the same example multiple times. You can also force either of them by setting the `SIMULATED_ACTIVATION_SUCCESS_RATE` constant in [DemoFOTAUpdateSelfTest.h](../../examples/huzzah/thingshadow/DemoFOTAUpdateSelfTest.h) to `100` or `0`.

## Supported targets

The Simple example can be used as is with the [Adafruit Feather HUZZAH](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266) board. With some adaptations, it can also be used with any other ESP8266 development board or hardware product. 

## Installation

A description of the SDKs and tools that must be available on your laptop or computer and advise how to install them can be found [here](../../README.md#installation).

## Usage

### Create an AWS IoT thing

1. If you have never used AWS so far, you must create a new AWS account first. You can follow the steps described [here](https://docs.aws.amazon.com/iot/latest/developerguide/setting-up.html) to do so.

2. Log in to the [AWS IoT Console](https://console.aws.amazon.com/iot/home) and set up an AWS IoT thing for your board: 
   * Create an AWS IoT policy which authorizes your board to exchange messages with AWS IoT 
   * Create the AWS IoT thing itself along with an X.509 board certificate that is used to authenticate your board to AWS IoT

<p style="margin-left: 2em">A comprehensive guide explaining how to proceed in detail can be found <a href="https://docs.aws.amazon.com/iot/latest/developerguide/create-iot-resources.html">here</a>.</p> 

3. Delete the initially created unnamed classic shadow of your AWS IoT thing (`Manage > Things > {{Your AWS IoT thing}} > Device Shadows > Classic Shadow > Delete` when using the *New console experience* which can be activated all down in the left side bar).

### Create a FotaHub product

Create a FotaHub product that represents your board in FotaHub as explained [here](../fotahub/create-product.md). It will be used to upload and provide firmware updates for the same. 

### Get the FotaHub Device SDK for ESP32

If not yet done so, either clone or download and uncompress the [FotaHub Device SDK for ESP8266](https://github.com/fotahub/fotahub-device-sdk-esp8266) to a location of your choice on your machine. 

> &#x26A0; Make sure that the path to the location of the FotaHub Device SDK for ESP8266 on your machine does not contain any spaces.

### Prepare initial firmware version

1. Start the Visual Studio Code and open (`File > Folder...`) the `Thing Shadow` example included in the FotaHub Device SDK for ESP32 (`<device-sdk-root>/examples/huzzah/thingshadow`).

2. Go to the `user_config.c` file and initialize the `WIFI_STATION_SSID` and `WIFI_STATION_PASSPHRASE` variables with the crentials of the Wi-Fi network you want to connect to with your board:

```c
ICACHE_RODATA_ATTR
char const WIFI_STATION_SSID[] = "my-fancy-WiFi-SSID";

ICACHE_RODATA_ATTR
char const WIFI_STATION_PASSWORD[] = "my-cryptic-WiFi-passphrase";
```

3. Open the `DemoProductInfo.c` file and initialize the `DEMO_PRODUCT_ID` and `DEMO_PRODUCT_NAME` variables with the id and the name of the previously created FotaHub product (see `Products > {{Your FotaHub product}} > Settings > General` at [Fotahub](https://fotahub.com)). Leave the `DEMO_PRODUCT_FIRMWARE_VERSION` as is for now:

```c
ICACHE_RODATA_ATTR
char const DEMO_PRODUCT_ID[] = "6258c080-85f6-4a7a-84a2-7a9ef16d03fc";

ICACHE_RODATA_ATTR
char const DEMO_PRODUCT_NAME[] = "Demo Product";

ICACHE_RODATA_ATTR
char const DEMO_PRODUCT_FIRMWARE_VERSION[] = "1.0";
```

<p style="margin-left: 2em">In case you have selected anything else than <code>SHA256</code> as the binary checksum algorithm for your FotaHub product or opted for using a signature instead, you also must adjust the <code>DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM</code> variable in the <code>DemoProductInfo.h</code> file accordingly:

```c
#define DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM FOTA_UPDATE_VERIFICATION_ALGORITHM_SHA256
```

4. Open the `ESP8266AWSIoTThingShadowConfiguration.c` file and initialize the `hostNameEndPoint.hostName` and `awsIoTConnParams.thingName` struct variable fields with your AWS account's [device data endpoint](https://docs.aws.amazon.com/iot/latest/developerguide/iot-connect-devices.html#iot-connect-device-endpoints) and the name of the previously created AWS IoT thing (see `Settings > Device data endpoint` and `Manage > Things` in the [AWS IoT Console](https://console.aws.amazon.com/iot/home) when using the *New console experience* which can be activated all down in the left side bar):

```c
HostNameEndpointAddress_t hostNameEndPoint = 
{
  ...
  .hostName = "c1bskcyiphilz6-ats.iot.eu-central-1.amazonaws.com"
};

...

AWSIoTConnectionParameters_t awsIoTConnParams = 
{
  .thingName = "FotaHubExampleThing", 
  ...
};
```

5. Open the `certificate.cer` and `private_key.cer` files in the `clientCert` folder. Replace all their content with that from the certificate and private key files which you have created and downloaded during the setup of the AWS IoT thing for your board. Those are typically named something like `3d19eba035-certificate.pem.crt` and `3d19eba035-private.pem.key`. 
   
### Build and flash initial firmware version

1. Open the integrated terminal (`Terminal > New Terminal`) and build the example by running `make`.
    
    When you have opted to use the ESP8266 NONOS SDK and ESP8266 toolchain through Docker, `make` must be run inside a Docker container providing the same. You can achieve that conveniently by making sure that Docker is running on your machine and invoking the `mind.bat`/`mind.sh` (**M**ake **IN** **D**ocker) script according to your operating system:
   
**Windows:**   
```bat
mind
```
**Linux/Mac OS X:**   
```sh
./mind.sh
```
<p style="margin-left: 2em">If you have installed the ESP8266 NONOS SDK and ESP8266 toolchain directly on your machine, you can invoke <code>make</code> right away but must indicate the ESP8266 NONOS SDK install or checkout location by setting the <code>SDK_HOME</code> variable. Be sure that this location does not contain any spaces in its path and specify it as <a href="https://cygwin.com/cygwin-ug-net/using.html#using-pathnames">Cygwin POSIX-style path name</a> when working under Windows (e.g., <code>/c/Git/ESP8266_NONOS_SDK</code> instead of <code>C:\Git\ESP8266_NONOS_SDK</code>):</p> 

```bat
make SDK_HOME=<ESP8266 NONOS SDK install/checkout location>
```

2. Connect your board to your laptop or computer using a USB cable, and identify the corresponding serial port (a guide explaining how to do so with ESP32 boards but applies to ESP8266 boards as well can be found [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/establish-serial-connection.html)).

> &#x26A0; It may happen that you are unable to find the serial port your board is connected to. Most of the time this is because the device driver for the USB to serial converter chip of your board is missing. You can fix that by manually installing the same as explained [here](../../README.md#general-purpose-tools).

3. Flash the firmware binary that has resulted from building the example to your board.
   
   If you have used Docker and `mind` to build the firmware binary, you will notice that two new scripts, namely `flash.bat`/`flash.sh` and `erase.bat`/`erase.sh` have been created along the way. Use the first one to flash the firmware binary to your board and provide the serial port it is connected to as argument:

**Windows:**   
```bat
flash <COM port name, e.g., COM3>
```
**Linux/Mac OS X:**   
```sh
./flash.sh <serial port name, e.g., /dev/ttyUSB0>
```

<p style="margin-left: 2em">If you have built the firmware binary with <code>make</code> and the ESP8266 NONOS SDK and ESP8266 toolchain installed on your machine, invoke <code>make flash</code> to flash the firmware binary to your board. Indicate the ESP8266 NONOS SDK install or checkout location and serial port your board is connected to by setting the <code>SDK_HOME</code> and <code>ESPTOOL_COM_PORT</code> variables:</p>  

```bat
make flash SDK_HOME=<ESP8266 NONOS SDK install/checkout location> ESPTOOL_COM_PORT=<COM or serial port name, e.g., COM3 or /dev/ttyUSB0>
```

4. Start your serial monitor app, point it at the serial port your board is connected to, and set the baudrate to `57600` (`Connection > Options...` in CoolTerm). Open the configured serial port (`Connection > Connect` in CoolTerm), observe how the firmware starts up and verify whether it connects to the Wi-Fi network as well as to its AWS IoT Thing Shadow:

![](thingshadow-1.png "Start of initial firmware version")

<p style="margin-left: 2em">Also have a look at the red LED next to the USB port on your board (GPIO #0). It should blink with a period of approx. 1 s.</p> 

5. Go back to the [AWS IoT Console](https://console.aws.amazon.com/iot/home) and visit the unnamed classic shadow of your AWS IoT thing (`Manage > Things > {{Your AWS IoT thing}} > Device Shadows > Classic Shadow` when using the *New console experience* which can be activated all down in the left side bar). Click on the refresh button if no such is displayed. You should see that yields a shadow state document with a `currentVersion` attribute that indicates the currently running firmware version on your board:

![](thingshadow-2.png "Initial thing shadow state")

6. Stop your serial monitor app and disconnect your board from your laptop or computer. Use a USB wall charger to power it instead. Feel free to move your board to a different place if you like.  

### Create and upload a new firmware version to FotaHub

1. Go back to the `DemoProductInfo.c` file and bump the value of the `DEMO_PRODUCT_FIRMWARE_VERSION` variable:

```c
ICACHE_RODATA_ATTR
char const DEMO_PRODUCT_FIRMWARE_VERSION[] = "1.1";
```

2. Make another change in your firmware, e.g., increase the blink frequency of the red LED on your board by going back to the `user_config.h` file and decreasing the `BLINK_PERIOD` constant:

```c
#define BLINK_PERIOD 250
```

3. Rebuild the example using Docker and `mind` or `make` in very much the same way as you did for building the initial firmware version (see step 1 in previous section). Locate the resulting new firmware binary files named `DemoProduct1.bin` and `DemoProduct2.bin` in the `build/bin` folder (using the `Explorer` view).
   
> &#x1F6C8; You can locate the new firmware binary files also in your file system explorer or copy their paths to the clipboard using corresponding Visual Studio Code context menu actions (`Reveal in File Explorer` and `Copy Path`). This can come quite handy in the subsequent steps.

4. Upload the new binaries (`build/bin/DemoProduct1.bin`, `build/bin/DemoProduct2.bin`) as firmware version `1.1` to your FotaHub product as explained [here](../fotahub/upload-firmware.md).

### Perform a cloud-triggered firmare over-the-air update 

You can perfom cloud-triggered firmare over-the-air updates either [interactively](#interactive-firmare-over-the-air-update-using-the-aws-iot-console) through the AWS IoT Console or [programmatically](#programmatic-firmare-over-the-air-update-using-the-aws-cli) by using the AWS CLI.

#### Interactive firmare over-the-air update using the AWS IoT Console

1. Go back to the [AWS IoT Console](https://console.aws.amazon.com/iot/home) and revisit the unnamed classic shadow of your AWS IoT thing (`Manage > Things > {{Your AWS IoT thing}} > Device Shadows > Classic Shadow` when using the *New console experience* which can be activated all down in the left side bar). Open the shadow state document for editing (`Device Shadow document > Edit`). Add a `desired` object with a `newVersion` attribute to indicate the new firmware version your board should be updated to and a `verificationData` attribute with the checksums or signatures of the first and second firmware partition directly concatenated to each other (see `Products > {{Your FotaHub product}} > Details > {{New firmware version}}` at [Fotahub](https://fotahub.com)):

```json
{
    "state": {
        "reported": {
            "currentVersion": "1.0",
            "updateStatus": "none"
        },
        "desired": {
            "newVersion": "1.1",
            "verificationData": "<checksum or signature partition 1><checksum or signature partition 2>"
        }
    }
}
```

2. Save the modified shadow state document (`Edit Device Shadow state > Update`). This will trigger the firmware over-the-air update procedure. Upon successful completion (typically after 1 minute or so), the board will be restarted with the new firmware version downloaded from FotaHub. The built-in self test is executed and, in case it succeeds, the new firmware version is confirmed and stays in place. You can see that
   * by observing the **red LED** on your board - it should end up blinking significantly faster than before
   * by inspecting the **shadow state document** in the AWS IoT Console - it should reflect the new firmware version as the currently running version and include an `updateStatus` attribute indicating the successful completion of the firmware over-the-air update:
   
![](thingshadow-3.png "Thing shadow state after successful FOTA update")

<p style="margin-left: 2em">In case the built-in self test fails, the new fimware version initiates the reversion of the firmware update, the board is restarted another time, and the previous firmware version is resumed. You can see that
<ul>
    <ul>
    <li>by observing the <strong>red LED</strong> on your board - it should continue to blink with the same frequency as before</li>
    <li>by inspecting the <strong>shadow state document</strong> in the AWS IoT Console - it should reflect the initial firmware version as the currently running version and include an <code>updateStatus</code> attribute indicating the failure of the firmware over-the-air update:</li>
    </ul>
</ul>
</p> 

![](thingshadow-4.png "Thing shadow state after failed FOTA update")

#### Programmatic firmare over-the-air update using the AWS CLI

1. If not already done so, [install](https://docs.aws.amazon.com/cli/latest/userguide/install-cliv2.html) and [configure](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-quickstart.html#cli-configure-quickstart-config) the AWS CLI version 2.

2. Go back to the integrated terminal or just open a new one (`Terminal > New Terminal`) and trigger a firmware over-the-air update for your board by entering an [aws iot-data publish](https://awscli.amazonaws.com/v2/documentation/api/latest/reference/iot-data/publish.html) command as shown below. Provide the name of your AWS IoT thing, the new firmware version your board should be updated to as well as the checksums or signatures of the first and second firmware partition directly concatenated to each other (see `Products > {{Your FotaHub product}} > Details > {{New firmware version}}` at [Fotahub](https://fotahub.com)):

**Windows:**   
```bat
aws iot-data publish --topic $aws/things/<Your AWS IoT thing>/shadow/update --cli-binary-format raw-in-base64-out --payload "{\"state\":{\"desired\":{\"newVersion\":\"1.1\",\"verificationData\":\"<checksum or signature partition 1><checksum or signature partition 2>\"}}}"
```
**Linux/Mac OS X:**   
```sh
aws iot-data publish --topic \$aws/things/<Your AWS IoT thing>/shadow/update --cli-binary-format raw-in-base64-out --payload '{"state":{"desired":{"newVersion":"1.1","verificationData":"<checksum or signature partition 1><checksum or signature partition 2>"}}}'
```
  
3. Upon successful completion (typically after 1 minute or so), the board will be restarted with the new firmware version downloaded from FotaHub. The built-in self test is executed and, in case it succeeds, the new firmware version is confirmed and stays in place. You can see that
   * by observing the **red LED** on your board - it should end up blinking significantly faster than before
   * by retrieving the **shadow state document** using the [aws iot-data get-thing-shadow](https://awscli.amazonaws.com/v2/documentation/api/latest/reference/iot-data/get-thing-shadow.html) command as follows - it should reflect the new firmware version as the currently running version and include an `updateStatus` attribute indicating the successful completion of the firmware over-the-air update:

**Windows:**   
```bat
aws iot-data get-thing-shadow --thing-name <Your AWS IoT thing> shadow-state.json && type shadow-state.json 
```
**Linux/Mac OS X:**   
```sh
aws iot-data get-thing-shadow --thing-name <Your AWS IoT thing> shadow-state.json && cat shadow-state.json
```

**Resulting output:**

```bat
{"state":{"reported":{"currentVersion":"1.1","updateStatus":"succeeded"}},"metadata":{...},"version":...,"timestamp":...}
```

<p style="margin-left: 2em">In case the built-in self test fails, the new fimware version initiates the reversion of the firmware update, the board is restarted another time, and the previous firmware version is resumed. You can see that
<ul>
    <ul>
    <li>by observing the <strong>red LED</strong> on your board - it should continue to blink with the same frequency as before</li>
    <li>by inspecting the <strong>shadow state document</strong> retrieved as per above - it should reflect the initial firmware version as the currently running version and include an <code>updateStatus</code> attribute indicating the failure of the firmware over-the-air update:</li>
    </ul>
</ul>
</p> 

```bat
{"state":{"reported":{"currentVersion":"1.0","updateStatus":"failed"}},"metadata":{...},"version":...,"timestamp":...}
```