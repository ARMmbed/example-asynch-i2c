# Asynchronous I2C

## The demo application

This repository is an example for asynchronous I2C, a test unit with defined test cases for asynchronous I2C methods, using 24LC256 eeprom.

Please look at the target's pin definition in the i2c_master_eeprom_asynch.cpp file (TEST_SDA_PIN and TEST_SCL_PIN). They should be connected to EEPROM.
The pin definitions are target specific, look at the [mbed platform page](https://developer.mbed.org/platforms), where each platform has pinout picture.

The datasheet for the eeprom can be found [here](http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Components/General%20IC/34979_SPCN.pdf). It requires Vcc, GND, SDA and SCL pins connected to the target.

Currently only the following configuration is supported:
- Freescale FRDM-K64F board
- GCC ARM Embedded Toolchain

### Pre-requisites

To build and run this example the requirements below are necessary:
* A computer with the following software installed
  * CMake
  * yotta
  * python
  * ARM-GCC toolchain
  * a serial terminal emulator (e.g. screen, pyserial, cu)
* A frdm-k64f development board
* A micro-USB cable
* 24LC256 eeprom

### Getting started
This is a yotta executable. You need the latest [yotta](https://github.com/ARMmbed/yotta) release version (latest tested: 0.2.2) and all of its dependencies. See also the [yotta documentation](http://armmbed.github.io/yotta/) for further details about the installation and the build process.

1. Connect the frdm-k64f to the computer with the micro-USB cable, being careful to use the micro-usb port labeled "OpenSDA"

2. Assuming you have cloned this repository, move to its folder. Select target, update, install and build:
    ```
    cd /path/to/mbed-example-asynch-i2c
    yotta target frdm-k64f-gcc
    yotta build
    ```

3. Copy 'build/frdm-k64f-gcc/source/mbed-example-asynch-i2c.bin` to your mbed board and wait until the LED next to the USB port stops blinking.

4. Start the serial terminal emulator and connect to the virtual serial port presented by frdm-k64f. For settings, use 9600 baud, 8N1, no flow control.

5. Press the reset button on the board.

6. The output in the terminal should look like:

    ```
    TEST(I2C_Master_EEPROM_Asynchronous, tx_rx_pattern) - 1 ms
    TEST(I2C_Master_EEPROM_Asynchronous, tx_rx_one_byte_one_transactions) - 1 ms
    TEST(I2C_Master_EEPROM_Asynchronous, tx_rx_one_byte_separate_transactions) - 1 ms

    OK (3 tests, 3 ran, 13 checks, 0 ignored, 0 filtered out, 25 ms)

    {{success}}
    {{end}}

    ```

7. LED should be slowly blinking (toggling about 1 Hz).

## API overview

The current mbed I2C API provides blocking method write() and read() methods.

This user guide describes the non-blocking methods which are array oriented. The transfer method initiates the transfer and return to the caller. The registered event is reported via callbacks.

### Asynch methods

The I2C API was expanded by two methods, transfer() and abort_transfer().

The transfer method starts the non-blocking transfer. The tx_buffer can be a pointer to a TX buffer, transfering data will start or NULL - receiving data will start. If rx_buffer is NULL, received data are ignored.
```
    int transfer(int address, char *tx_buffer, int tx_length, char *rx_buffer, int rx_length, void (*callback)(int), int event = I2C_EVENT_TRANSFER_COMPLETE, bool repeated = false);

    void abort_transfer();

```

### Events

The following I2C events are available:

- I2C_EVENT_ERROR - Generic I2C error
- I2C_EVENT_ERROR_NO_SLAVE - No slave found
- I2C_EVENT_TRANSFER_COMPLETE - All data were transfered or received, depends on the transfer parameters
- I2C_EVENT_TRANSFER_EARLY_NACK - transfered not completed with nack received from a slave
- I2C_EVENT_ALL - Logical OR of all available events
