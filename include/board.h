

/**
 * @file board.h
 * @brief Board configuration for the ARM I2C/UART driver project.
 *
 * This file provides simulated board-level definitions such as:
 *  - CPU frequency
 *  - Peripheral base addresses
 *  - Pin mappings for I2C and UART
 *
 * On real hardware, replace these with actual MCU register addresses.
 */

#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

/* -------------------------------------------------------------------------- */
/*                           CPU / Clock Configuration                         */
/* -------------------------------------------------------------------------- */

#define BOARD_CPU_CLOCK_HZ      48000000U   /* 48 MHz simulated system clock */
#define BOARD_I2C_CLOCK_HZ      48000000U
#define BOARD_UART_CLOCK_HZ     48000000U

/* -------------------------------------------------------------------------- */
/*                         Peripheral Base Addresses                           */
/* -------------------------------------------------------------------------- */

/**
 * These addresses are placeholders for simulation.
 * Real MCU addresses (e.g., STM32) would map to memory-mapped registers.
 */

#define BOARD_I2C1_BASE   0x40005400U
#define BOARD_UART1_BASE  0x40013800U

/* -------------------------------------------------------------------------- */
/*                               Pin Definitions                               */
/* -------------------------------------------------------------------------- */

/* I2C Pins */
#define BOARD_I2C_SCL_PIN    6    /* Example: PB6 */
#define BOARD_I2C_SDA_PIN    7    /* Example: PB7 */

/* UART Pins */
#define BOARD_UART_TX_PIN    9    /* Example: PA9 */
#define BOARD_UART_RX_PIN    10   /* Example: PA10 */

/* -------------------------------------------------------------------------- */
/*                               Helper Macros                                 */
/* -------------------------------------------------------------------------- */

#define UNUSED(x)   (void)(x)

#endif /* BOARD_H */