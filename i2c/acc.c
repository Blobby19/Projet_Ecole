#include "ensea_i2c.h"
#include "acc.h"

void lsm303dlhc_acc_initialize(int file){
  slave_adress_i2c(file, LSM303DLHC_ACC_DEFAULT_ADDRESS);
}

void lsm303dlhc_mag_initialize(int file){
  slave_adress_i2c(file, LSM303DLHC_MAG_DEFAULT_ADDRESS);
}

void lsm303dlhc_init_acc(int file, uint8_t samplingrate, uint8_t lowpower){
  uint8_t data[1];
  data[0] = (samplingrate & 0xF)<<4;
  data[0] |= 0x7;
  printf("data acc: %x\n", data[0]);
  lsm303dlhc_acc_initialize(file);
  config_register_i2c(file, LSM303DLHC_CTRL_REG1_A, data, 2);
}

void lsm303dlhc_init_mag(int file, uint8_t samplingrate, uint8_t sens_temp){
  uint8_t data[1];
  data[0] = (samplingrate & 0x7) << 2;
  data[0] |= (sens_temp & 0x1)<<7;
  lsm303dlhc_mag_initialize(file);
  config_register_i2c(file, LSM303DLHC_CRA_REG_A, data, 1);
}

void lsm303dlhc_set_register(int file, uint8_t _register){
  change_register(file, _register);
}

void lsm303dlhc_get_acc_x(int file, uint8_t *data /*lsm303dlhc_struct *lsm303*/){
  lsm303dlhc_acc_initialize(file);
  read_data_i2c(file, LSM303DLHC_OUT_X_L_REG | 0x80, data, 2);
}

void lsm303dlhc_get_acc_y(int file, uint8_t *data /*lsm303dlhc_struct *lsm303*/){
  lsm303dlhc_acc_initialize(file);
  read_data_i2c(file, LSM303DLHC_OUT_Y_L_REG | 0x80, data, 2);
}

void lsm303dlhc_get_acc_z(int file, uint8_t *data /*lsm303dlhc_struct *lsm303*/){
  lsm303dlhc_acc_initialize(file);
  read_data_i2c(file, LSM303DLHC_OUT_Z_L_REG | 0x80, data, 2);
}

void lsm303dlhc_get_mag_x(int file, uint8_t *data){
  lsm303dlhc_mag_initialize(file);
  read_data_i2c(file, LSM303DLHC_OUT_X_L_M, &data[0], 1);
  read_data_i2c(file, LSM303DLHC_OUT_X_H_M, &data[1], 1);
}

void lsm303dlhc_get_mag_y(int file, uint8_t *data){
  lsm303dlhc_mag_initialize(file);
  read_data_i2c(file, LSM303DLHC_OUT_Y_L_M, &data[0], 1);
  read_data_i2c(file, LSM303DLHC_OUT_Y_H_M, &data[1], 1);
}

void lsm303dlhc_get_mag_z(int file, uint8_t *data){
  lsm303dlhc_mag_initialize(file);
  read_data_i2c(file, LSM303DLHC_OUT_Z_L_M, &data[0], 1);
  read_data_i2c(file, LSM303DLHC_OUT_Z_H_M, &data[1], 1);
}

void lsm303dlhc_get_temp(int file, uint8_t *data){
  lsm303dlhc_mag_initialize(file);
  read_data_i2c(file, LSM303DLHC_TEMP_OUT_L_M, &data[0], 1);
  read_data_i2c(file, LSM303DLHC_TEMP_OUT_H_M, &data[1], 1);
}
