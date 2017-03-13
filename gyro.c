#include "ensea_i2c.h"
#include "gyro.h"

void l3gd20_gyro_initialize(int file){
  slave_adress_i2c(file, L3GD20_GYR_ADDRESS_DEFAULT);
}

void l3gd20_init_gyro(int file, uint8_t samplingrate, uint8_t bandwidth, uint8_t mode){
  uint8_t data[1];
  data[0] = (samplingrate & 0x3)<<6;
  data[0] |= (bandwidth & 0x3)<<4;
  data[0] |= mode & 0xF;
  printf("data acc: %x\n", data[0]);
  l3gd20_gyro_initialize(file);
  config_register_i2c(file, L3GD20_CTRL_REG1, data, 2);
}

void l3gd20_get_gyro_x(int file, uint8_t *data){
  l3gd20_gyro_initialize(file);
  read_data_i2c(file, L3GD20_OUT_X_L | 0x80, data, 2);
}

void l3gd20_get_gyro_y(int file, uint8_t *data){
  l3gd20_gyro_initialize(file);
  read_data_i2c(file, L3GD20_OUT_Y_L | 0x80, data, 2);
}

void l3gd20_get_gyro_z(int file, uint8_t *data){
  l3gd20_gyro_initialize(file);
  read_data_i2c(file, L3GD20_OUT_Z_L | 0x80, data, 2);
}
