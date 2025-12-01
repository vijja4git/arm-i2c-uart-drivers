

/**
 * @file uart.c
 * @brief UART driver implementation for ARM Cortex‑M (portable CMSIS‑style).
 *
 * This file provides a minimal, production‑style UART driver using C11.
 * It is hardware‑independent and relies on the abstracted HAL layer
 * defined in hal_uart.h. The goal is to demonstrate how low‑level
 * embedded drivers are structured in real firmware projects.
 */

#include "../include/hal_uart.h"
#include "uart.h"

/* -------------------------------------------------------------------------- */
/*                             Static UART Handle                              */
/* -------------------------------------------------------------------------- */

static UART_Handle_t uart_handle;

/* -------------------------------------------------------------------------- */
/*                           Function Implementations                          */
/* -------------------------------------------------------------------------- */

void UART_Init(const UART_Config_t *config)
{
    uart_handle.baudrate = config->baudrate;
    uart_handle.stop_bits = config->stop_bits;
    uart_handle.parity = config->parity;

    /* Configure UART registers using HAL */
    HAL_UART_EnableClock();
    HAL_UART_ConfigurePins();

    HAL_UART_SetBaudrate(config->baudrate);
    HAL_UART_SetStopBits(config->stop_bits);
    HAL_UART_SetParity(config->parity);

    HAL_UART_Enable();
}

void UART_WriteChar(char c)
{
    /* Wait until TX buffer is empty */
    while (!HAL_UART_IsTxReady())
        ;

    HAL_UART_SendByte((uint8_t)c);
}

void UART_WriteString(const char *str)
{
    while (*str)
    {
        UART_WriteChar(*str++);
    }
}

char UART_ReadChar(void)
{
    /* Wait until RX buffer has data */
    while (!HAL_UART_IsRxReady())
        ;

    return (char)HAL_UART_ReadByte();
}

void UART_WriteHex(uint32_t value)
{
    const char hex_symbols[] = "0123456789ABCDEF";

    for (int i = 28; i >= 0; i -= 4)
    {
        char nibble = hex_symbols[(value >> i) & 0xF];
        UART_WriteChar(nibble);
    }
}

void UART_WriteDec(int value)
{
    char buffer[12];
    int index = 0;

    if (value == 0)
    {
        UART_WriteChar('0');
        return;
    }

    if (value < 0)
    {
        UART_WriteChar('-');
        value = -value;
    }

    while (value > 0)
    {
        buffer[index++] = '0' + (value % 10);
        value /= 10;
    }

    for (int i = index - 1; i >= 0; i--)
    {
        UART_WriteChar(buffer[i]);
    }
}
