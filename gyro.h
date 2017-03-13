#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef H_GYRO
#define H_GYRO

#define L3GD20_GYR_ADDRESS 0xD4
#define L3GD20_GYR_ADDRESS_DEFAULT (L3GD20_GYR_ADDRESS>>1)

#define L3GD20_WHO_AM_I 0x0F

#define L3GD20_CTRL_REG1 0x20
#define L3GD20_CTRL_REG2 0x21
#define L3GD20_CTRL_REG3 0x22
#define L3GD20_CTRL_REG4 0x23
#define L3GD20_CTRL_REG5 0x24

#define L3GD20_REFERENCE 0x25
#define L3GD20_OUT_TEMP 0x26

#define L3GD20_STATUS_REG 0x27
#define L3GD20_OUT_X_L 0x28
#define L3GD20_OUT_X_H 0x29
#define L3GD20_OUT_Y_L 0x2A
#define L3GD20_OUT_Y_H 0x2B
#define L3GD20_OUT_Z_L 0x2C
#define L3GD20_OUT_Z_H 0x2D

#define L3GD20_FIFO_CTRL_REG 0x2E
#define L3GD20_FIFO_SRC_REG 0x2F

#define L3GD20_INT1_CFG 0x30
#define L3GD20_INT1_SRC 0x31

#define L3GD20_INT1_TSH_XH 0x32
#define L3GD20_INT1_TSH_XL 0x33
#define L3GD20_INT1_TSH_YH 0x34
#define L3GD20_INT1_TSH_YL 0x35
#define L3GD20_INT1_TSH_ZH 0x36
#define L3GD20_INT1_TSH_ZL 0x37
#define L3GD20_INT1_DURATION 0x38

#define L3GD20_ODR_95_HZ 0
#define L3GD20_ODR_190_HZ 1
#define L3GD20_ODR_380_HZ 2
#define L3GD20_ODR_760_HZ 3

#define L3GD20_ODR_95_BW_12_5 0
#define L3GD20_ODR_95_BW_25 1

#define L3GD20_ODR_190_BW_12_5 0
#define L3GD20_ODR_190_BW_25 1
#define L3GD20_ODR_190_BW_50 2
#define L3GD20_ODR_190_BW_75 3

#define L3GD20_ODR_380_BW_20 0
#define L3GD20_ODR_380_BW_25 1
#define L3GD20_ODR_380_BW_50 2
#define L3GD20_ODR_380_BW_100 3

#define L3GD20_ODR_760_BW_30 0
#define L3GD20_ODR_760_BW_35 1
#define L3GD20_ODR_760_BW_50 2
#define L3GD20_ODR_760_BW_100 3

#define L3GD20_NORMAL_MODE 0xF
#define L3GD20_SLEEP_MODE 0x8
#define L3GD20_POWER_DOWN 0x0

#endif H_GYRO

typedef struct{
  uint8_t gyroX[2];
  uint8_t gyroY[2];
  uint8_t gyroZ[2];
}l3gd20_struct;

void l3gd20_gyro_initialize(int file);
void l3gd20_init_gyro(int file, uint8_t samplingrate, uint8_t bandwidth, uint8_t mode);
void l3gd20_get_gyro_x(int file, uint8_t *data);
void l3gd20_get_gyro_y(int file, uint8_t *data);
void l3gd20_get_gyro_z(int file, uint8_t *data);
