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

EEPROM pin definitions are target specific - the code and the physical board must both be using the same pins:

1. To know which pins the code is looking for, see the ``i2c_master_eeprom_asynch.cpp`` file for this sample. The pins are defined as ``TEST_SDA_PIN`` and ``TEST_SCL_PIN``.

2. To know where on your board those pins are, please look at its [pinout picture](http://developer.mbed.org/platforms/FRDM-K64F/#overview).

The datasheet for the eeprom can be found [here](http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Components/General%20IC/34979_SPCN.pdf). It requires Vcc, GND, SDA and SCL pins connected to the target.

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
    Writing DONE (slave is ready), event is 8
    Read data match with written data, event is 8
    **** Test done ****
    ```

