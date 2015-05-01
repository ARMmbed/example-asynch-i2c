# Asynchronous I2C API

The current mbed I2C API provides blocking ``write()`` and ``read()`` methods.

This user guide describes the new array-oriented, non-blocking methods. The transfer method initiates the transfer and return to the caller. The registered event is reported via callbacks.

Currently only the following configuration is supported:

- Freescale FRDM-K64F board.
- GCC ARM Embedded Toolchain.

### Asynch Methods

The I2C API has two new methods: ``transfer()`` and ``abort_transfer()``.

The transfer method starts the non-blocking transfer. The ``tx_buffer`` can be either a pointer to a TX buffer (transfer data) or NULL (receive data). If ``rx_buffer`` is NULL, received data are ignored.

```
    int transfer(int address, char *tx_buffer, int tx_length, char *rx_buffer, int rx_length, void (*callback)(int), int event = I2C_EVENT_TRANSFER_COMPLETE, bool repeated = false);

    void abort_transfer();

```

### Events

The following I2C events are available for event handling:

- I2C_EVENT_ERROR - Generic I2C error.
- I2C_EVENT_ERROR_NO_SLAVE - No slave found.
- I2C_EVENT_TRANSFER_COMPLETE - All data were transferred or received (depending on the transfer parameters).
- I2C_EVENT_TRANSFER_EARLY_NACK - Transfer not completed with nack received from a slave.
- I2C_EVENT_ALL - Logical OR of all available events.

## The Demo Application

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
    cd /path/to/mbed-example-asynch-i2c
	```
   
3. Select the yotta target and build to it:

	```
	yotta target frdm-k64f-gcc
	yotta build
    ```

3. Copy ``build/frdm-k64f-gcc/source/mbed-example-asynch-i2c.bin`` to your mbed board and wait until the LED next to the USB port stops blinking.

4. Start the serial terminal emulator and connect to the virtual serial port presented by FRDM-K64F. For settings, use 9600 baud, 8N1, no flow control.

5. Press the reset button on the board.

6. The output in the terminal should look like this:

    ```
    TEST(I2C_Master_EEPROM_Asynchronous, tx_rx_pattern) - 1 ms
    TEST(I2C_Master_EEPROM_Asynchronous, tx_rx_one_byte_one_transactions) - 1 ms
    TEST(I2C_Master_EEPROM_Asynchronous, tx_rx_one_byte_separate_transactions) - 1 ms

    OK (3 tests, 3 ran, 13 checks, 0 ignored, 0 filtered out, 25 ms)

    {{success}}
    {{end}}

    ```

7. The LED should be slowly blinking (toggling about 1 Hz).

