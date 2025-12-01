/**
 * @file main.c
 * @brief Example application demonstrating UART + I2C driver usage.
 *
 * This file simulates a simple firmware application:
 *  - Initializes UART
 *  - Initializes I2C
 *  - Reads a fake sensor register over I2C
 *  - Prints the result via UART
 *
 * In real hardware, replace HAL simulation logic with actual registers.
 */

#include "../drivers/uart.h"
#include "../drivers/i2c.h"
#include "../include/board.h"
#include "../include/hal_uart.h"
#include "../include/hal_i2c.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                         Fake Sensor Register Address                        */
/* -------------------------------------------------------------------------- */
#define SENSOR_I2C_ADDRESS   0x48   /* Typical temp sensor address */
#define SENSOR_REG_TEMP      0x00

/* -------------------------------------------------------------------------- */
/*                               Initialization                                */
/* -------------------------------------------------------------------------- */

static void App_InitUART(void)
{
    UART_Config_t cfg = {
        .baudrate = 115200,
        .stop_bits = UART_STOPBITS_1,
        .parity = UART_PARITY_NONE
    };

    UART_Init(&cfg);
    UART_WriteString("UART Initialized.\r\n");
}

static void App_InitI2C(void)
{
    I2C_Config_t cfg = {
        .speed = I2C_SPEED_STANDARD,
        .addressing_mode = I2C_ADDR_7BIT
    };

    I2C_Init(&cfg);
    UART_WriteString("I2C Initialized.\r\n");
}

/* -------------------------------------------------------------------------- */
/*                          Sensor Read Demonstration                          */
/* -------------------------------------------------------------------------- */

static void App_ReadSensor(void)
{
    uint8_t temp_value = 0;

    UART_WriteString("Reading temperature sensor...\r\n");

    /* Write register address */
    if (I2C_WriteByte(SENSOR_I2C_ADDRESS, SENSOR_REG_TEMP) != I2C_STATUS_OK)
    {
        UART_WriteString("I2C Write Error!\r\n");
        return;
    }

    /* Read 1-byte temperature data */
    if (I2C_ReadByte(SENSOR_I2C_ADDRESS, &temp_value) != I2C_STATUS_OK)
    {
        UART_WriteString("I2C Read Error!\r\n");
        return;
    }

    UART_WriteString("Sensor Value (Hex): 0x");
    UART_WriteHex(temp_value);
    UART_WriteString("\r\n");
    fflush(stdout);
}

/* -------------------------------------------------------------------------- */
/*                                     MAIN                                   */
/* -------------------------------------------------------------------------- */

int main(void)
{
    UART_WriteString("System Booting...\r\n");

    App_InitUART();
    App_InitI2C();

    UART_WriteString("System Ready.\r\n");

    for (int i = 0; i < 10; i++)
    {
        App_ReadSensor();
        UART_WriteString("Loop iteration complete.\r\n");
    }

    return 0;
}