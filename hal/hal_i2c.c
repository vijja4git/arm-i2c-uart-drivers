/**
 * @file hal_i2c.c
 * @brief Simulated Hardware Abstraction Layer for I2C.
 *
 * This file provides a software-only simulation of an I2C peripheral so that
 * the firmware drivers (i2c.c) can run on a host PC without real hardware.
 *
 * The simulated behavior:
 *  - Start condition sets the START bit and clears STOP
 *  - Address phase always succeeds (ADDR flag set)
 *  - TXE is always ready after writing DR
 *  - RXNE becomes ready with DR containing a pseudo-random value
 *
 * For real microcontrollers, replace ALL logic with actual register accesses.
 */

#include "hal_i2c.h"
#include "board.h"

/* -------------------------------------------------------------------------- */
/*                          Simulated Peripheral Instance                      */
/* -------------------------------------------------------------------------- */

I2C_Registers_t I2C1 = {0};

/* -------------------------------------------------------------------------- */
/*                        Clock & Pin Configuration (Simulated)               */
/* -------------------------------------------------------------------------- */

void HAL_I2C_EnableClock(void)
{
    /* No real clock control in simulation */
}

void HAL_I2C_ConfigurePins(void)
{
    /* No real pin config; simulated environment */
}

/* -------------------------------------------------------------------------- */
/*                                Initialization                               */
/* -------------------------------------------------------------------------- */

void HAL_I2C_Enable(void)
{
    I2C1.CR |= I2C_CR_ENABLE;
}

void HAL_I2C_SetSpeed(uint32_t speed_hz)
{
    /* In real hardware, CCR depends on CPU clock and required I2C speed. */
    I2C1.CCR = speed_hz;
}

/* -------------------------------------------------------------------------- */
/*                             I2C Control Operations                          */
/* -------------------------------------------------------------------------- */

void HAL_I2C_GenerateStart(void)
{
    I2C1.CR |= I2C_CR_START;
    I2C1.CR &= ~I2C_CR_STOP;
    I2C1.SR |= I2C_SR_BUSY;
}

void HAL_I2C_GenerateStop(void)
{
    I2C1.CR |= I2C_CR_STOP;
    I2C1.CR &= ~I2C_CR_START;
    I2C1.SR &= ~I2C_SR_BUSY;
}

void HAL_I2C_SendACK(void)
{
    I2C1.CR |= I2C_CR_ACK;
}

void HAL_I2C_SendNACK(void)
{
    I2C1.CR &= ~I2C_CR_ACK;
}

/* -------------------------------------------------------------------------- */
/*                         Address & Data Operations                           */
/* -------------------------------------------------------------------------- */

void HAL_I2C_SendAddress(uint8_t address, I2C_Direction_t direction)
{
    /* Simulate address match */
    I2C1.DR = (address << 1) | (direction & 0x01);
    I2C1.SR |= I2C_SR_ADDR;

    /* TX ready after address sent */
    I2C1.SR |= I2C_SR_TXE;
}

void HAL_I2C_SendData(uint8_t data)
{
    I2C1.DR = data;
    I2C1.SR |= I2C_SR_TXE; /* TX done */
}

uint8_t HAL_I2C_ReadData(void)
{
    /* In simulation, always return DR */
    return (uint8_t)I2C1.DR;
}

/* -------------------------------------------------------------------------- */
/*                               Status Checkers                               */
/* -------------------------------------------------------------------------- */

bool HAL_I2C_IsStartGenerated(void)
{
    return (I2C1.CR & I2C_CR_START);
}

bool HAL_I2C_IsAddressSent(void)
{
    return (I2C1.SR & I2C_SR_ADDR);
}

bool HAL_I2C_IsTxComplete(void)
{
    return (I2C1.SR & I2C_SR_TXE);
}

bool HAL_I2C_IsRxReady(void)
{
    /* Simulate data ready */
    I2C1.SR |= I2C_SR_RXNE;
    I2C1.DR = 0x33;  /* Fake sensor data */
    return true;
}
