

/**
 * @file hal_uart.h
 * @brief Hardware Abstraction Layer for UART (Simulated CMSIS-style).
 *
 * This HAL provides a hardware-agnostic interface for the UART driver.
 * It simulates UART register operations so the project can compile and run
 * on any platform (including host PC for testing).
 *
 * On real hardware, replace the register definitions with actual MCU registers.
 */

#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>
#include <stdbool.h>

/* -------------------------------------------------------------------------- */
/*                     Simulated UART Register Definitions                     */
/* -------------------------------------------------------------------------- */

/**
 * These registers mimic what real Cortex-M UART peripherals expose:
 *  - STATUS: TX ready, RX ready flags
 *  - DATA:   transmit/receive buffer
 *  - CTRL:   enable/parity/stop bit config
 *  - BAUD:   baudrate setting
 *
 * Replace these with actual MCU register mappings for real hardware.
 */

typedef struct
{
    volatile uint32_t STATUS;
    volatile uint32_t DATA;
    volatile uint32_t CTRL;
    volatile uint32_t BAUD;
} UART_Registers_t;

/* Simulated peripheral instance */
extern UART_Registers_t UART1;

/* Status register bit masks */
#define UART_STATUS_TX_READY   (1U << 0)
#define UART_STATUS_RX_READY   (1U << 1)

/* Control register bit masks */
#define UART_CTRL_ENABLE       (1U << 0)
#define UART_CTRL_PARITY_EVEN  (1U << 1)
#define UART_CTRL_PARITY_ODD   (1U << 2)
#define UART_CTRL_STOP_2       (1U << 3)

/* -------------------------------------------------------------------------- */
/*                       HAL Function Prototypes (Public API)                 */
/* -------------------------------------------------------------------------- */

/* Clock & pin config -------------------------------------------------------- */

void HAL_UART_EnableClock(void);
void HAL_UART_ConfigurePins(void);

/* UART configuration -------------------------------------------------------- */

void HAL_UART_Enable(void);
void HAL_UART_SetBaudrate(uint32_t baudrate);
void HAL_UART_SetParity(uint32_t parity);
void HAL_UART_SetStopBits(uint32_t stop_bits);

/* UART data operations ------------------------------------------------------ */

void HAL_UART_SendByte(uint8_t byte);
uint8_t HAL_UART_ReadByte(void);

/* Status checks ------------------------------------------------------------- */

bool HAL_UART_IsTxReady(void);
bool HAL_UART_IsRxReady(void);

#endif /* HAL_UART_H */