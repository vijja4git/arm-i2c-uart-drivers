

/**
 * @file i2c.c
 * @brief I2C driver implementation for ARM Cortex-M (portable CMSIS-style).
 *
 * This file implements a clean, minimal, production-style I2C master driver
 * using C11 and a hardware abstraction layer (HAL) defined in hal_i2c.h.
 * It demonstrates blocking transfers, start/stop sequencing, ACK/NACK handling,
 * and timeout protection. Interrupt-driven extensions can be added later.
 */

#include "../include/hal_i2c.h"
#include "i2c.h"

/* -------------------------------------------------------------------------- */
/*                           Static I2C Driver Handle                          */
/* -------------------------------------------------------------------------- */

static I2C_Handle_t i2c_handle;

/* -------------------------------------------------------------------------- */
/*                          Internal Helper Functions                          */
/* -------------------------------------------------------------------------- */

static I2C_Status_t I2C_WaitForFlag(bool (*flag_func)(void), uint32_t timeout)
{
    while (!flag_func())
    {
        if (timeout-- == 0)
            return I2C_STATUS_TIMEOUT;
    }
    return I2C_STATUS_OK;
}

/* -------------------------------------------------------------------------- */
/*                          Public API Implementations                         */
/* -------------------------------------------------------------------------- */

void I2C_Init(const I2C_Config_t *config)
{
    i2c_handle.speed = config->speed;
    i2c_handle.addressing_mode = config->addressing_mode;

    HAL_I2C_EnableClock();
    HAL_I2C_ConfigurePins();

    HAL_I2C_SetSpeed(config->speed);
    HAL_I2C_Enable();
}

I2C_Status_t I2C_WriteByte(uint8_t dev_addr, uint8_t data)
{
    HAL_I2C_GenerateStart();

    if (I2C_WaitForFlag(HAL_I2C_IsStartGenerated, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_TIMEOUT;

    HAL_I2C_SendAddress(dev_addr, I2C_WRITE);

    if (I2C_WaitForFlag(HAL_I2C_IsAddressSent, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_ADDR_NACK;

    HAL_I2C_SendData(data);

    if (I2C_WaitForFlag(HAL_I2C_IsTxComplete, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_TIMEOUT;

    HAL_I2C_GenerateStop();
    return I2C_STATUS_OK;
}

I2C_Status_t I2C_WriteBuffer(uint8_t dev_addr, const uint8_t *buffer, uint32_t len)
{
    HAL_I2C_GenerateStart();

    if (I2C_WaitForFlag(HAL_I2C_IsStartGenerated, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_TIMEOUT;

    HAL_I2C_SendAddress(dev_addr, I2C_WRITE);

    if (I2C_WaitForFlag(HAL_I2C_IsAddressSent, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_ADDR_NACK;

    for (uint32_t i = 0; i < len; i++)
    {
        HAL_I2C_SendData(buffer[i]);

        if (I2C_WaitForFlag(HAL_I2C_IsTxComplete, I2C_TIMEOUT) != I2C_STATUS_OK)
            return I2C_STATUS_TIMEOUT;
    }

    HAL_I2C_GenerateStop();
    return I2C_STATUS_OK;
}

I2C_Status_t I2C_ReadByte(uint8_t dev_addr, uint8_t *data)
{
    HAL_I2C_GenerateStart();

    if (I2C_WaitForFlag(HAL_I2C_IsStartGenerated, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_TIMEOUT;

    HAL_I2C_SendAddress(dev_addr, I2C_READ);

    if (I2C_WaitForFlag(HAL_I2C_IsAddressSent, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_ADDR_NACK;

    if (I2C_WaitForFlag(HAL_I2C_IsRxReady, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_TIMEOUT;

    *data = HAL_I2C_ReadData();

    HAL_I2C_GenerateStop();
    return I2C_STATUS_OK;
}

I2C_Status_t I2C_ReadBuffer(uint8_t dev_addr, uint8_t *buffer, uint32_t len)
{
    HAL_I2C_GenerateStart();

    if (I2C_WaitForFlag(HAL_I2C_IsStartGenerated, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_TIMEOUT;

    HAL_I2C_SendAddress(dev_addr, I2C_READ);

    if (I2C_WaitForFlag(HAL_I2C_IsAddressSent, I2C_TIMEOUT) != I2C_STATUS_OK)
        return I2C_STATUS_ADDR_NACK;

    for (uint32_t i = 0; i < len; i++)
    {
        if (I2C_WaitForFlag(HAL_I2C_IsRxReady, I2C_TIMEOUT) != I2C_STATUS_OK)
            return I2C_STATUS_TIMEOUT;

        buffer[i] = HAL_I2C_ReadData();

        if (i == (len - 1))
            HAL_I2C_SendNACK();
        else
            HAL_I2C_SendACK();
    }

    HAL_I2C_GenerateStop();
    return I2C_STATUS_OK;
}