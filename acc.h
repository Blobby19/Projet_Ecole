#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef H_ACC
#define H_ACC

#define LSM303DLHC_ACC_ADDRESS 0x32
#define LSM303DLHC_ACC_DEFAULT_ADDRESS (LSM303DLHC_ACC_ADDRESS>>1)

#define LSM303DLHC_MAG_ADDRESS 0x3C
#define LSM303DLHC_MAG_DEFAULT_ADDRESS (LSM303DLHC_MAG_ADDRESS>>1)

#define LSM303DLHC_CTRL_REG1_A 0x20
#define LSM303DLHC_CTRL_REG2_A 0x21
#define LSM303DLHC_CTRL_REG3_A 0x22
#define LSM303DLHC_CTRL_REG4_A 0x23
#define LSM303DLHC_CTRL_REG5_A 0x24
#define LSM303DLHC_CTRL_REG6_A 0x25
#define LSM303DLHC_REFERENCE_A 0x26
#define LSM303DLHC_STATUS_REG_A 0x27

#define LSM303DLHC_OUT_X_L_REG 0x28
#define LSM303DLHC_OUT_X_H_REG 0x29

#define LSM303DLHC_OUT_Y_L_REG 0x2A
#define LSM303DLHC_OUT_Y_H_REG 0x2B

#define LSM303DLHC_OUT_Z_L_REG 0x2C
#define LSM303DLHC_OUT_Z_H_REG 0x2D

#define LSM303DLHC_FIFO_CTRL_REG_A 0x2E
#define LSM303DLHC_FIFO_SRC_REG_A 0x2F

#define LSM303DLHC_INT1_CFG_A 0x30
#define LSM303DLHC_INT1_SOURCE_A 0x31
#define LSM303DLHC_INT1_THS_A 0x32
#define LSM303DLHC_INT1_DURATION_A 0x33

#define LSM303DLHC_INT2_CFG_A 0x34
#define LSM303DLHC_INT2_SOURCE_A 0x35
#define LSM303DLHC_INT2_THS_A 0x36
#define LSM303DLHC_INT2_DURATION_A 0x37

#define LSM303DLHC_CLICK_CFG_A 0x38
#define LSM303DLHC_CLICK_SRC_A 0x39
#define LSM303DLHC_CLICK_THS_A 0x3A

#define LSM303DLHC_TIME_LIMIT_A 0x3B
#define LSM303DLHC_TIME_LATENCY_A 0x3C
#define LSM303DLHC_TIME_WINDOW_A 0x3D

#define LSM303DLHC_CRA_REG_A 0x00
#define LSM303DLHC_CRB_REG_A 0x01
#define LSM303DLHC_MR_REG_A 0x02

#define LSM303DLHC_OUT_X_H_M 0x03
#define LSM303DLHC_OUT_X_L_M 0x04

#define LSM303DLHC_OUT_Y_H_M 0x07
#define LSM303DLHC_OUT_Y_L_M 0x08

#define LSM303DLHC_OUT_Z_H_M 0x05
#define LSM303DLHC_OUT_Z_L_M 0x06

#define LSM303DLHC_SR_REG_M 0x09
#define LSM303DLHC_IRA_REG_M 0x0A
#define LSM303DLHC_IRB_REG_M 0x0B
#define LSM303DLHC_IRC_REG_M 0x0C

#define LSM303DLHC_TEMP_OUT_H_M 0x31
#define LSM303DLHC_TEMP_OUT_L_M 0x32

#define LSM303DLHC_ODR_STOP 0
#define LSM303DLHC_ODR_1HZ 1
#define LSM303DLHC_ODR_10HZ 2
#define LSM303DLHC_ODR_25HZ 3
#define LSM303DLHC_ODR_50HZ 4
#define LSM303DLHC_ODR_100HZ 5
#define LSM303DLHC_ODR_200HZ 6
#define LSM303DLHC_ODR_400HZ 7
#define LSM303DLHC_ODR_1620HZ 8
#define LSM303DLHC_ODR_1344HZ 9

#define LSM303DLHC_SENSOR_TEMP_EN 1
#define LSM303DLHC_SENSOR_TEMP_DIS 0

#define LSM303DLHC_MAG_DATA_RATE_0_75HZ 0
#define LSM303DLHC_MAG_DATA_RATE_0_15HZ 1
#define LSM303DLHC_MAG_DATA_RATE_3HZ 2
#define LSM303DLHC_MAG_DATA_RATE_7_5HZ 3
#define LSM303DLHC_MAG_DATA_RATE_15HZ 4
#define LSM303DLHC_MAG_DATA_RATE_30HZ 5
#define LSM303DLHC_MAG_DATA_RATE_75HZ 6
#define LSM303DLHC_MAG_DATA_RATE_220HZ 7

#define LSM303DLHC_NORMAL 0
#define LSM303DLHC_LOWPOWER 1

#endif

typedef struct{
  uint8_t accX[2];
  uint8_t accY[2];
  uint8_t accZ[2];
  uint8_t magX[2];
  uint8_t magY[2];
  uint8_t magZ[2];
  uint8_t temp[2];
}lsm303dlhc_struct;

void lsm303dlhc_acc_initialize(int file);
void lsm303dlhc_mag_initialize(int file);
void lsm303dlhc_init_acc(int file, uint8_t samplingrate, uint8_t lowpower);
void lsm303dlhc_init_mag(int file, uint8_t samplingrate, uint8_t sens_temp);
void lsm303dlhc_get_acc_x(int file, uint8_t *data/*lsm303dlhc_struct *lsm303*/);
void lsm303dlhc_get_acc_y(int file, uint8_t *data/*lsm303dlhc_struct *lsm303*/);
void lsm303dlhc_get_acc_z(int file, uint8_t *data/*lsm303dlhc_struct *lsm303*/);
void lsm303dlhc_get_mag_x(int file, uint8_t *data);
void lsm303dlhc_get_mag_y(int file, uint8_t *data);
void lsm303dlhc_get_mag_z(int file, uint8_t *data);
void lsm303dlhc_get_temp(int file, uint8_t *data);
