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

/**
 * This file contains the main application for demonstrating how UART and I2C
 * drivers work together in a simulated embedded system. Every line is documented
 * to help beginners understand:
 *  - What each function call does
 *  - Where each variable or constant comes from
 *  - How drivers interact with the HAL (Hardware Abstraction Layer)
 *  - How data flows from the application → drivers → HAL → simulated hardware
 */

/* ---------------- Driver Layer Includes (High-Level APIs) ------------------ */
/* uart.h and i2c.h provide user-friendly driver functions. These do NOT touch
 * hardware directly—they call into the HAL layer. */
#include "../drivers/uart.h"    // UART high-level driver functions (UART_Init, UART_WriteString, etc.)
#include "../drivers/i2c.h"     // I2C high-level driver functions (I2C_Init, I2C_WriteByte, I2C_ReadByte)

/* ---------------- HAL Layer Includes (Low-Level Hardware Simulation) ------- */
/* These files contain simulated hardware registers for UART and I2C. The driver
 * functions call these to "pretend" hardware exists. */
#include "../include/hal_uart.h" // Simulated UART register definitions
#include "../include/hal_i2c.h"  // Simulated I2C register definitions

/* ---------------- Board Configuration Include ------------------------------ */
/* Defines core hardware interface structures (UART_Registers_t, I2C_Registers_t) */
#include "../include/board.h"  

/* ---------------- Standard Library Includes -------------------------------- */
/* These headers give us integer types, boolean types, and printf/fflush support. */
#include <stdint.h>   // uint8_t, uint16_t, uint32_t types
#include <stdbool.h>  // bool type
#include <stdio.h>    // printf, fflush for console output flushing

/* -------------------------------------------------------------------------- */
/*                         Fake Sensor Register Address                        */
/* -------------------------------------------------------------------------- */
/**
 * These constants define the I2C address of a simulated temperature sensor.
 * SENSOR_I2C_ADDRESS:
 *    - 0x48 is a common 7‑bit address used by many real temperature sensors.
 * SENSOR_REG_TEMP:
 *    - Register 0x00 typically stores the real-time temperature value.
 */
#define SENSOR_I2C_ADDRESS   0x48   /* Typical temp sensor address */
#define SENSOR_REG_TEMP      0x00

/* -------------------------------------------------------------------------- */
/*                               Initialization                                */
/* -------------------------------------------------------------------------- */

static void App_InitUART(void)
{
    /* UART_Config_t comes from uart.h. It defines how the UART should operate.
     * Each field below configures part of the UART peripheral. */
    UART_Config_t cfg = {
        .baudrate = 115200,          // Bits per second. A common speed for serial monitors.
        .stop_bits = UART_STOPBITS_1, // One stop bit at end of each frame.
        .parity = UART_PARITY_NONE    // No parity bit. Simpler communication.
    };

    /* UART_Init():
     * - Lives in uart.c
     * - Calls HAL_UART_* functions to configure the simulated UART registers.
     */
    UART_Init(&cfg);

    /* Sends a string over UART by writing each character to the simulated register.
     * UART_WriteString() comes from uart.c and internally calls HAL_UART_SendByte(). */
    UART_WriteString("UART Initialized.\r\n");
}

static void App_InitI2C(void)
{
    /* I2C_Config_t comes from i2c.h. It describes communication settings.
     * speed:
     *   - I2C_SPEED_STANDARD = 100 kHz
     * addressing_mode:
     *   - 7-bit addressing (common for most sensors)
     */
    I2C_Config_t cfg = {
        .speed = I2C_SPEED_STANDARD,
        .addressing_mode = I2C_ADDR_7BIT
    };

    /* I2C_Init():
     * - Lives in i2c.c
     * - Configures simulated I2C registers using HAL_I2C_* functions.
     */
    I2C_Init(&cfg);

    UART_WriteString("I2C Initialized.\r\n");  // Confirm initialization
}

/* -------------------------------------------------------------------------- */
/*                          Sensor Read Demonstration                          */
/* -------------------------------------------------------------------------- */

static void App_ReadSensor(void)
{
    uint8_t temp_value = 0; // Will store the 1‑byte temperature value returned by the sensor.

    UART_WriteString("Reading temperature sensor...\r\n");

    /* Step 1: Tell the sensor which register we want to read.
     * I2C_WriteByte():
     *   - Comes from i2c.c
     *   - Calls HAL_I2C_SendAddress() → HAL_I2C_SendData()
     *   - SENSOR_I2C_ADDRESS is the fake sensor address
     *   - SENSOR_REG_TEMP tells the sensor we want the temperature register
     */
    if (I2C_WriteByte(SENSOR_I2C_ADDRESS, SENSOR_REG_TEMP) != I2C_STATUS_OK)
    {
        UART_WriteString("I2C Write Error!\r\n");
        return; // Stop if write fails
    }

    /* Step 2: Read back the temperature value.
     * I2C_ReadByte():
     *   - Again, calls HAL functions to simulate a read cycle.
     *   - The HAL always returns a fake value (0x33) for learning purposes.
     */
    if (I2C_ReadByte(SENSOR_I2C_ADDRESS, &temp_value) != I2C_STATUS_OK)
    {
        UART_WriteString("I2C Read Error!\r\n");
        return;
    }

    /* Output the data over UART.
     * UART_WriteHex() converts a byte into readable HEX characters (e.g., 0x33).
     */
    UART_WriteString("Sensor Value (Hex): 0x");
    UART_WriteHex(temp_value);
    UART_WriteString("\r\n");

    /* fflush(stdout):
     * Ensures all text immediately prints to your terminal instead of waiting
     * in an output buffer.
     */
    fflush(stdout);
}

/* -------------------------------------------------------------------------- */
/*                                     MAIN                                   */
/* -------------------------------------------------------------------------- */

int main(void)
{
    /* Announce system start. At this moment UART is not yet configured,
     * but UART_WriteString uses the simulated HAL which is always enabled.
     */
    UART_WriteString("System Booting...\r\n");

    /* Initialize communication peripherals */
    App_InitUART(); // Sets up UART with baud rate and settings from cfg
    App_InitI2C();  // Sets up I2C with 100 kHz & 7‑bit addressing

    UART_WriteString("System Ready.\r\n");

    /* Main loop (runs only 5 times to avoid infinite output).
     * In real firmware this would typically be while(1) to run forever.
     */
    for (int i = 0; i < 5; i++)
    {
        App_ReadSensor(); // Perform one full I2C transaction and print data
        UART_WriteString("Loop iteration complete.\r\n");
    }

    return 0; // Indicate normal program termination
}