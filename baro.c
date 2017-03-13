#include "ensea_i2c.h"
#include "baro.h"

void lsp331ap_baro_initialize(int file){
  slave_adress_i2c(file, LPS331AP_BARO_ADDRESS_DEFAULT);
}

void lsp331ap_init_baro(int file, uint8_t samplingrate, uint8_t mode){
  uint8_t data[1];
  data[0] = (mode & 0x1)<<7;
  data[0] |= (samplingrate & 0x7)<<4;
  printf("data acc: %x\n", data[0]);
  lsp331ap_baro_initialize(file);
  config_register_i2c(file, LPS331AP_CTRL_REG1, data, 2);
}

void lsp331ap_get_baro(int file, uint8_t *data){
  lsp331ap_baro_initialize(file);
  read_data_i2c(file, LPS331AP_PRESS_POUT_XL_REG | 0x80, data, 3);
}

void lsp331ap_get_temp(int file, uint8_t *data){
  lsp331ap_baro_initialize(file);
  read_data_i2c(file, LPS331AP_TEMP_OUT_L | 0x80, data, 2);
}
