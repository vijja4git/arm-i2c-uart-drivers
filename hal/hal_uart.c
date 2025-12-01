/**
 * @file hal_uart.c
 * @brief Simulated Hardware Abstraction Layer for UART.
 *
 * This HAL allows the UART driver to run on any host machine (Mac/Linux/Windows)
 * without real hardware. It simulates:
 *   - UART TX ready state
 *   - UART RX ready state
 *   - DATA register behavior
 *   - Baudrate, stop-bit, parity configuration (stored but not functional)
 *
 * For real embedded systems, replace the simulated registers with actual MCU
 * register accesses.
 */

#include "hal_uart.h"
#include "board.h"
#include "stdio.h"

/* -------------------------------------------------------------------------- */
/*                      Simulated Peripheral Register Instance                 */
/* -------------------------------------------------------------------------- */

UART_Registers_t UART1 = {
    .STATUS = UART_STATUS_TX_READY, /* TX ready at start */
    .DATA = 0,
    .CTRL = 0,
    .BAUD = 115200
};

/* -------------------------------------------------------------------------- */
/*                           Clock & Pin Configuration                         */
/* -------------------------------------------------------------------------- */

void HAL_UART_EnableClock(void)
{
    /* No real clock control needed for simulation */
}

void HAL_UART_ConfigurePins(void)
{
    /* No real pin configuration in simulation */
}

/* -------------------------------------------------------------------------- */
/*                         UART Configuration Functions                        */
/* -------------------------------------------------------------------------- */

void HAL_UART_Enable(void)
{
    UART1.CTRL |= UART_CTRL_ENABLE;
}

void HAL_UART_SetBaudrate(uint32_t baudrate)
{
    UART1.BAUD = baudrate;
}

void HAL_UART_SetParity(uint32_t parity)
{
    UART1.CTRL &= ~(UART_CTRL_PARITY_EVEN | UART_CTRL_PARITY_ODD);

    if (parity == 1)
        UART1.CTRL |= UART_CTRL_PARITY_EVEN;
    else if (parity == 2)
        UART1.CTRL |= UART_CTRL_PARITY_ODD;
}

void HAL_UART_SetStopBits(uint32_t stop_bits)
{
    if (stop_bits == 2)
        UART1.CTRL |= UART_CTRL_STOP_2;
    else
        UART1.CTRL &= ~UART_CTRL_STOP_2;
}

/* -------------------------------------------------------------------------- */
/*                          UART Data Transfer Functions                       */
/* -------------------------------------------------------------------------- */

void HAL_UART_SendByte(uint8_t byte)
{
    UART1.DATA = byte;
    putchar(byte);
    fflush(stdout);
    UART1.STATUS |= UART_STATUS_TX_READY;
}

uint8_t HAL_UART_ReadByte(void)
{
    UART1.STATUS &= ~UART_STATUS_RX_READY; /* Clear flag */
    return (uint8_t)UART1.DATA;
}

/* -------------------------------------------------------------------------- */
/*                              Status Check Functions                         */
/* -------------------------------------------------------------------------- */

bool HAL_UART_IsTxReady(void)
{
    /* Always ready in simulation */
    return (UART1.STATUS & UART_STATUS_TX_READY);
}

bool HAL_UART_IsRxReady(void)
{
    /* Simulate RX ready by manually toggling in tests or main loop */
    return (UART1.STATUS & UART_STATUS_RX_READY);
}
