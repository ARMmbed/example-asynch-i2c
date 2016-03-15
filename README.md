# Asynchronous I2C Example

This repository is an example for asynchronous I2C. It is a test unit with test cases for asynchronous I2C methods, using 24LC256 EEPROM.

### Pre-Requisites

To build and run this example the following requirements are necessary:

* A computer with the following software installed:
	* [CMake](http://www.cmake.org/download/).
	* [yotta](https://github.com/ARMmbed/yotta). Please note that **yotta has its own set of dependencies**, listed in the [installation instructions](http://armmbed.github.io/yotta/#installing-on-windows).
	* [Python](https://www.python.org/downloads/).
	* [ARM GCC toolchain](https://launchpad.net/gcc-arm-embedded).
	* A serial terminal emulator (e.g. screen, pySerial, cu).
* An FRDM-K64F development board.
* A micro-USB cable.
* 24LC256 eeprom.
* If your OS is Windows, please follow the installation instructions [for the serial port driver](https://developer.mbed.org/handbook/Windows-serial-configuration).

### Pins

SDA and SCL pin definitions are target-specific. To function correctly, the code and the physical board must both be using the same pins. Follow these steps to determine which pins the code is configured to use.

1. First, find the pin references in the source files.  In this example, view ``i2c_master_eeprom_asynch.cpp``. The pin references are ``YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SDA``, ``YOTTA_CFG_HARDWARE_TEST_PINS_I2C_SCL``.

2. Next, find these target-specific pin references in the configuration data by running the command:
 ```
 yotta config
 ```
 Each keyword in the pin reference represents a level in the target configuration structure.  To find what ``YOTTA_CFG_HARDWARE_TEST_PINS_I2C`` resolves to, look under config...hardware...test-pins...i2c.

 In this example, the SCL and SDA pins are defined as:
 ```
 "i2c": {
   "sda": "PTE25",
   "scl": "PTE24"
 }
 ```

3. Locate those pins on the board's pinout picture: <img src="https://developer.mbed.org/media/uploads/sam_grove/frdm-k64f-pinnout-1.jpg" width="700">

4. Wire the SDA and SCL pins from FRDM-K64F to EEPROM as follows:

```
   3.3V 3.3V
    ^    ^
    |    |
   +++  +++
10k| |  | |10k (typical for 100kHz)
   +++  +++
    |    |  +--------------+
    |    |  |              |                          3.3V
    |  +-+--+I2C_SDA       |                           ^
    |  |    |              |           +---+XXXX+---+  |
    +-------+I2C_SCL       |           |1          8+--+
    |  |    |              |           |            |
    |  |    |   FRDM+K64F  |           |2  EEPROM  7|
    |  |    |              |           |            |
    |  |    |              |           |3          6+-----+
    |  |    |              |           |            |     |
    |  |    |              |        +--+4          5+--+- |
    |  |    |              |        |  +------------+  |  |
    |  |    +--------------+       +++                 |  |
    |  |                           GND                 |  |
    |  |                      SDA                      |  |
    |  +-----------------------------------------------+- |
    |                         SCL                         |
    +-----------------------------------------------------+

```

The EEPROM pinout diagram can be found in the datasheet [here](http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Components/General%20IC/34979_SPCN.pdf).

### Getting Started

1. Connect the FRDM-K64F to the computer with the micro-USB cable, being careful to use the micro-USB port labeled "OpenSDA".

3. Assuming you have cloned this repository or receive it with a release tarball, open a terminal window and navigate to the repository's folder.

    ```
    cd /path/to/example-asynch-i2c
	```
   
3. Select the yotta target and build to it:

	```
	yotta target frdm-k64f-gcc
	yotta build
    ```

3. Copy ``build/frdm-k64f-gcc/source/example-asynch-i2c.bin`` to your mbed board and wait until the LED next to the USB port stops blinking.

4. Start the serial terminal emulator and connect to the virtual serial port presented by FRDM-K64F. For settings, use 115200 baud, 8N1, no flow control.

5. Press the reset button on the board.

6. The output in the terminal should look like this:

    ```
    Starting transfer test
    Writing DONE, event is 8
    Slave is ready for reading, event is 8
    Reading DONE, event is 8
    Read data match with written data, event is 8
    **** Test done ****
    ```

