/**
 * @file i2c.h
 * @brief I2C driver API for ARM Cortex-M (portable CMSIS-style).
 *
 * This header defines the API, enums, and data structures for the I2C driver.
 * It works with a hardware abstraction layer (hal_i2c.h) to remain portable
 * across different ARM Cortex-M microcontrollers.
 */

#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

/* -------------------------------------------------------------------------- */
/*                                  Definitions                                */
/* -------------------------------------------------------------------------- */

#define I2C_TIMEOUT   50000U

typedef enum
{
    I2C_SPEED_STANDARD = 100000,  /**< 100 kHz */
    I2C_SPEED_FAST     = 400000   /**< 400 kHz */
} I2C_Speed_t;

typedef enum
{
    I2C_ADDR_7BIT = 0,
    I2C_ADDR_10BIT
} I2C_AddressMode_t;

typedef enum
{
    I2C_STATUS_OK = 0,
    I2C_STATUS_TIMEOUT,
    I2C_STATUS_ADDR_NACK,
    I2C_STATUS_DATA_NACK,
    I2C_STATUS_ERROR
} I2C_Status_t;

/* Direction values used by HAL */
typedef enum
{
    I2C_WRITE = 0,
    I2C_READ  = 1
} I2C_Direction_t;

/* -------------------------------------------------------------------------- */
/*                               Configuration Struct                          */
/* -------------------------------------------------------------------------- */

typedef struct
{
    I2C_Speed_t speed;
    I2C_AddressMode_t addressing_mode;
} I2C_Config_t;

/* -------------------------------------------------------------------------- */
/*                               Internal Handle                               */
/* -------------------------------------------------------------------------- */

typedef struct
{
    I2C_Speed_t speed;
    I2C_AddressMode_t addressing_mode;
} I2C_Handle_t;

/* -------------------------------------------------------------------------- */
/*                           Public API Function Prototypes                    */
/* -------------------------------------------------------------------------- */

/**
 * @brief Initialize the I2C peripheral with the specified configuration.
 */
void I2C_Init(const I2C_Config_t *config);

/**
 * @brief Write a single byte to an I2C device.
 *
 * @param dev_addr  7-bit or 10-bit device address
 * @param data      Byte to transmit
 * @return I2C_Status_t Status code indicating success or failure
 */
I2C_Status_t I2C_WriteByte(uint8_t dev_addr, uint8_t data);

/**
 * @brief Write a buffer of bytes to an I2C device.
 *
 * @param dev_addr Device address
 * @param buffer   Pointer to data buffer
 * @param len      Number of bytes to send
 */
I2C_Status_t I2C_WriteBuffer(uint8_t dev_addr, const uint8_t *buffer, uint32_t len);

/**
 * @brief Read a single byte from an I2C device.
 *
 * @param dev_addr Device address
 * @param data     Pointer to store read byte
 */
I2C_Status_t I2C_ReadByte(uint8_t dev_addr, uint8_t *data);

/**
 * @brief Read multiple bytes from an I2C device.
 *
 * Handles ACK/NACK automatically.
 *
 * @param dev_addr Device address
 * @param buffer   Buffer to store incoming data
 * @param len      Number of bytes to read
 */
I2C_Status_t I2C_ReadBuffer(uint8_t dev_addr, uint8_t *buffer, uint32_t len);

#endif /* I2C_H */
