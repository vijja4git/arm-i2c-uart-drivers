/**
 * @file hal_i2c.h
 * @brief Hardware Abstraction Layer for I2C (Simulated CMSIS-style).
 *
 * This HAL provides a hardware-agnostic interface for the I2C driver.
 * It simulates I2C register operations so the project can compile and run
 * on any platform (including host PC for testing).
 *
 * On real hardware, replace the register definitions and functions with
 * actual MCU register accesses (e.g., STM32, NXP, TI).
 */

#ifndef HAL_I2C_H
#define HAL_I2C_H

#include <stdint.h>
#include <stdbool.h>
#include "../drivers/i2c.h"  /* For I2C_Direction_t */

/* -------------------------------------------------------------------------- */
/*                     Simulated I2C Register Definitions                      */
/* -------------------------------------------------------------------------- */

/**
 * These registers mimic common I2C peripheral registers:
 *  - CR:   control register (enable, start, stop, ACK)
 *  - SR:   status register (flags for busy, TXE, RXNE, ADDR)
 *  - DR:   data register
 *  - CCR:  clock control (speed)
 *
 * Replace these with actual MCU register mappings for real hardware.
 */

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CCR;
} I2C_Registers_t;

/* Simulated peripheral instance */
extern I2C_Registers_t I2C1;

/* Control register bit masks */
#define I2C_CR_ENABLE      (1U << 0)
#define I2C_CR_START       (1U << 1)
#define I2C_CR_STOP        (1U << 2)
#define I2C_CR_ACK         (1U << 3)

/* Status register bit masks */
#define I2C_SR_BUSY        (1U << 0)
#define I2C_SR_TXE         (1U << 1)   /* Transmit buffer empty */
#define I2C_SR_RXNE        (1U << 2)   /* Receive buffer not empty */
#define I2C_SR_ADDR        (1U << 3)   /* Address sent/matched */

/* -------------------------------------------------------------------------- */
/*                       HAL Function Prototypes (Public API)                 */
/* -------------------------------------------------------------------------- */

/* Clock & pin config -------------------------------------------------------- */

void HAL_I2C_EnableClock(void);
void HAL_I2C_ConfigurePins(void);

/* I2C configuration --------------------------------------------------------- */

void HAL_I2C_Enable(void);
void HAL_I2C_SetSpeed(uint32_t speed_hz);

/* I2C control operations ---------------------------------------------------- */

void HAL_I2C_GenerateStart(void);
void HAL_I2C_GenerateStop(void);
void HAL_I2C_SendACK(void);
void HAL_I2C_SendNACK(void);

/* Address & data operations ------------------------------------------------- */

void HAL_I2C_SendAddress(uint8_t address, I2C_Direction_t direction);
void HAL_I2C_SendData(uint8_t data);
uint8_t HAL_I2C_ReadData(void);

/* Status checks ------------------------------------------------------------- */

bool HAL_I2C_IsStartGenerated(void);
bool HAL_I2C_IsAddressSent(void);
bool HAL_I2C_IsTxComplete(void);
bool HAL_I2C_IsRxReady(void);

#endif /* HAL_I2C_H */
