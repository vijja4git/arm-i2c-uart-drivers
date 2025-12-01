/**
 * @file test_i2c_uart.c
 * @brief Unit tests for UART + I2C driver simulation.
 *
 * These tests run on a host PC (no hardware required). They validate the
 * behavior of simulated HAL layers, ensuring correct functionality of the
 * firmware drivers.
 *
 * This is not a full testing framework, but simple, clear tests suitable
 * for demonstration in a portfolio.
 */

#include <stdio.h>
#include <assert.h>

#include "../drivers/uart.h"
#include "../drivers/i2c.h"
#include "../include/hal_uart.h"
#include "../include/hal_i2c.h"

/* -------------------------------------------------------------------------- */
/*                 Manual Mock Register Instances for Testing                 */
/* -------------------------------------------------------------------------- */

UART_Registers_t UART1 = {0};
I2C_Registers_t I2C1 = {0};

/* -------------------------------------------------------------------------- */
/*                        Helper Functions for Testing                        */
/* -------------------------------------------------------------------------- */

static void reset_uart_registers(void)
{
    UART1.STATUS = UART_STATUS_TX_READY; /* TX ready */
    UART1.DATA = 0;
    UART1.CTRL = 0;
    UART1.BAUD = 0;
}

static void reset_i2c_registers(void)
{
    I2C1.CR = 0;
    I2C1.SR = I2C_SR_TXE; /* TX empty */
    I2C1.DR = 0;
    I2C1.CCR = 0;
}

/* -------------------------------------------------------------------------- */
/*                               UART TESTS                                   */
/* -------------------------------------------------------------------------- */

static void test_uart_write_read(void)
{
    reset_uart_registers();

    UART_Config_t cfg = {
        .baudrate = 9600,
        .stop_bits = UART_STOPBITS_1,
        .parity = UART_PARITY_NONE
    };

    UART_Init(&cfg);

    /* Simulate RX ready and a byte in register */
    UART1.STATUS |= UART_STATUS_RX_READY;
    UART1.DATA = 'A';

    /* Test reading */
    char received = UART_ReadChar();
    assert(received == 'A');

    /* Test writing: send byte should update DATA register */
    UART_WriteChar('Z');
    assert(UART1.DATA == 'Z');

    printf("[UART] Read/Write test passed.\n");
}

/* -------------------------------------------------------------------------- */
/*                                I2C TESTS                                   */
/* -------------------------------------------------------------------------- */

static void test_i2c_write(void)
{
    reset_i2c_registers();

    /* Simulate HAL behavior */
    I2C1.SR |= I2C_SR_ADDR; /* Address phase OK */

    I2C_Config_t cfg = {
        .speed = I2C_SPEED_STANDARD,
        .addressing_mode = I2C_ADDR_7BIT
    };

    I2C_Init(&cfg);

    I2C_Status_t status = I2C_WriteByte(0x48, 0x55);
    assert(status == I2C_STATUS_OK);

    printf("[I2C] Write test passed.\n");
}

static void test_i2c_read(void)
{
    reset_i2c_registers();

    /* Simulate HAL behavior */
    I2C1.SR |= I2C_SR_ADDR;  /* Address OK */
    I2C1.SR |= I2C_SR_RXNE;  /* Data ready */
    I2C1.DR = 0x33;

    I2C_Config_t cfg = {
        .speed = I2C_SPEED_STANDARD,
        .addressing_mode = I2C_ADDR_7BIT
    };

    I2C_Init(&cfg);

    uint8_t value = 0;
    I2C_Status_t status = I2C_ReadByte(0x48, &value);

    assert(status == I2C_STATUS_OK);
    assert(value == 0x33);

    printf("[I2C] Read test passed.\n");
}

/* -------------------------------------------------------------------------- */
/*                                     MAIN                                   */
/* -------------------------------------------------------------------------- */

int main(void)
{
    printf("Running UART + I2C Driver Tests...\n");

    test_uart_write_read();
    test_i2c_write();
    test_i2c_read();

    printf("All tests passed successfully.\n");
    return 0;
}
