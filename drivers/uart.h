/**
 * @file uart.h
 * @brief UART driver API for ARM Cortex-M (portable CMSIS-style).
 *
 * This header exposes a clean, production-quality UART interface.
 * It is platform‑independent and uses the HAL layer (hal_uart.h)
 * for all hardware-specific interactions.
 */

#ifndef UART_H
#define UART_H

#include <stdint.h>

/* -------------------------------------------------------------------------- */
/*                               UART Data Types                               */
/* -------------------------------------------------------------------------- */

typedef enum
{
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} UART_Parity_t;

typedef enum
{
    UART_STOPBITS_1 = 0,
    UART_STOPBITS_2
} UART_StopBits_t;

/**
 * @brief UART Configuration Structure
 */
typedef struct
{
    uint32_t baudrate;
    UART_StopBits_t stop_bits;
    UART_Parity_t parity;
} UART_Config_t;

/**
 * @brief UART Internal Driver Handle
 */
typedef struct
{
    uint32_t baudrate;
    UART_StopBits_t stop_bits;
    UART_Parity_t parity;
} UART_Handle_t;

/* -------------------------------------------------------------------------- */
/*                              Public API Prototypes                          */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize UART peripheral with given configuration.
 */
void UART_Init(const UART_Config_t *config);

/**
 * @brief Send a single character.
 */
void UART_WriteChar(char c);

/**
 * @brief Send a null-terminated string.
 */
void UART_WriteString(const char *str);

/**
 * @brief Read a single received character (blocking).
 */
char UART_ReadChar(void);

/**
 * @brief Send a 32-bit value as hex string.
 */
void UART_WriteHex(uint32_t value);

/**
 * @brief Send a signed integer as decimal string.
 */
void UART_WriteDec(int value);

#endif /* UART_H */
