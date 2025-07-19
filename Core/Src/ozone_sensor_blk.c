#include "ozone_sensor_blk.h"

// From DFRobot definitions
#define MODE_REGISTER             0x03
#define SET_PASSIVE_REGISTER      0x04
#define MEASURE_MODE_PASSIVE      0x01
#define PASSIVE_READ_DATA         0x01
#define PASS_DATA_HIGE_REGISTER   0x07

static HAL_StatusTypeDef i2cWriteReg(OzoneSensor *sensor, uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    return HAL_I2C_Master_Transmit(sensor->hi2c, sensor->address, buf, 2, HAL_MAX_DELAY);
}

static HAL_StatusTypeDef i2cReadData(OzoneSensor *sensor, uint8_t reg, uint8_t *data, uint16_t len) {
    return HAL_I2C_Mem_Read(sensor->hi2c, sensor->address, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

uint8_t ozone_sensor_init(OzoneSensor *sensor, I2C_HandleTypeDef *hi2c, uint8_t address) {
    sensor->hi2c = hi2c;
    sensor->address = address << 1; // 7-bit address like OZONE_ADDRESS_0

    if (HAL_I2C_IsDeviceReady(sensor->hi2c, sensor->address, 3, 100) != HAL_OK) {
        return 1;
    }

    // Set to passive mode using proper register and value
    if (i2cWriteReg(sensor, MODE_REGISTER, MEASURE_MODE_PASSIVE) != HAL_OK) {
        return 1;
    }

    HAL_Delay(100); // Allow time to switch mode
    return 0;
}

double ozone_sensor_read(OzoneSensor *sensor) {
    uint8_t data[2] = {0};
    HAL_StatusTypeDef ret = i2cWriteReg(sensor, SET_PASSIVE_REGISTER, PASSIVE_READ_DATA);

    // Trigger passive read
    if (ret != HAL_OK) {
        return -1;
    }

    HAL_Delay(100); // Wait for sensor to update data

    // Read ozone concentration from passive data registers
    if (i2cReadData(sensor, PASS_DATA_HIGE_REGISTER, data, 2) != HAL_OK) {
        return -1;
    }

    return (double)((data[0] << 8) | data[1]);
}
