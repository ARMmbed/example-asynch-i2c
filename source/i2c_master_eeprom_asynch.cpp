/* mbed Microcontroller Library
 * Copyright (c) 2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>

#include "mbed.h"
#include "minar/minar.h"
#include "mbed-util/Event.h"

/* EEPROM 24LC256 Test Unit, to test I2C asynchronous communication.
 */

#if DEVICE_I2C && DEVICE_I2C_ASYNCH

#if defined(TARGET_K64F)
#define TEST_SDA_PIN PTE25
#define TEST_SCL_PIN PTE24
#else
#error Target not supported
#endif

using namespace minar;

const char pattern[] = {0x66, (char)~0x66, 0x00, 0xFF, 0xA5, 0x5A, 0xF0, 0x0F};
const int eeprom_address = 0xA0;
const size_t buffer_size = 8;

class I2CTest {

public:
    I2CTest() : i2c(TEST_SDA_PIN, TEST_SCL_PIN) {
        i2c.frequency(400000);
    }

    void start() {
        printf("Starting transfer test \r\n");
        init_tx_buffer();
        init_rx_buffer();
        set_tx_pattern(2); // set 0,0, pattern
        i2c.transfer(eeprom_address, tx_data, sizeof(tx_data), NULL, 0, I2C::event_callback_t(this, &I2CTest::slave_ready), I2C_EVENT_ALL, false);
    }

private:
    void slave_ready(Buffer tx_buffer, Buffer rx_buffer, int narg) {
        (void)tx_buffer;
        (void)rx_buffer;
        printf("Writing DONE, event is %d\r\n", narg);
        // check if slave is ready, register another callback
        i2c.transfer(eeprom_address, NULL, 0, NULL, 0, I2C::event_callback_t(this, &I2CTest::read_data_cb), I2C_EVENT_ALL, false);
    }

    void read_data_cb(Buffer tx_buffer, Buffer rx_buffer, int narg) {
        (void)tx_buffer;
        (void)rx_buffer;
        printf("Writing DONE (slave is ready), event is %d\r\n", narg);
        tx_data[0] = 0;
        tx_data[1] = 0;
        i2c.transfer(eeprom_address, tx_data, 2, rx_data, 8, I2C::event_callback_t(this, &I2CTest::compare_data_cb), I2C_EVENT_ALL, false);
    }

    void compare_data_cb(Buffer tx_buffer, Buffer rx_buffer, int narg) {
        (void)tx_buffer;
        (void)rx_buffer;
        // received buffer match with pattern
        int rc = memcmp(pattern, rx_data, sizeof(rx_data));
        if (rc == 0) {
            printf("Read data match with written data, event is %d\r\n", narg);
        } else {
            printf("Read data doesn't match with written data, event is %d\r\n", narg);
        }
        printf("**** Test done ****\r\n");
    }

    void init_tx_buffer() {
        for (uint32_t i = 0; i < sizeof(tx_data); i++) {
            tx_data[i] = 0;
        }
    }

    void init_rx_buffer() {
        for (uint32_t i = 0; i < sizeof(rx_data); i++) {
            rx_data[i] = 0;
        }
    }

    void set_tx_pattern(uint32_t offset) {
        for (uint32_t i = offset, j = 0; i < sizeof(tx_data) && j < sizeof(pattern); i++, j++) {
            tx_data[i] = pattern[j];
        }
    }

private:
    I2C i2c;
    char tx_data[buffer_size];
    char rx_data[buffer_size];
};


void app_start(int, char*[]) {
    static I2CTest test;
    // set 115200 baud rate for stdout
    static Serial pc(USBTX, USBRX);
    pc.baud(115200);
    Scheduler::postCallback(mbed::util::FunctionPointer0<void>(&test, &I2CTest::start).bind());
}

#else

void app_start(int, char*[]) {
    // set 115200 baud rate for stdout
    static Serial pc(USBTX, USBRX);
    pc.baud(115200);
    printf("The target does not support I2C asynch API.\r\n");
}
#endif
