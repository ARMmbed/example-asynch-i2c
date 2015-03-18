# Asynchronous I2C

## The demo application

This repository is an example for asynchronous I2C, a test unit with defined test cases for asynchronous I2C methods, using 24LC256 eeprom.

Please look at the target's pin definition in the i2c_master_eeprom_asynch.cpp file (TEST_SDA_PIN and TEST_SCL_PIN). They should be connected to EEPROM.

Currently only the following configuration is supported:
- Freescale FRDM-K64F board
- GCC ARM Embedded Toolchain

### Installation
This is a yotta executable. You need the latest [yotta](https://github.com/ARMmbed/yotta) release version (latest tested: 0.0.43) and all of its dependencies. See also the [yotta documentation](http://armmbed.github.io/yotta/) for further details about the installation and the build process.

Assuming you have cloned this repository, move to its folder. Select target, install and build:
```bash
cd /path/to/mbed-example-asynch-i2c
yotta target frdm-k64f-gcc
yotta install
yotta build
```

The resulting binary file will be located in `build/frdm-k64f-gcc/source/`. After flashing, you can observe the UART output on the USB serial port.

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
- I2C_EVENT_ALL - Logical OR of all available events
