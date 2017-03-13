#include "ensea_i2c.h"


int open_i2c(char *filename){
  int file = open(filename, O_RDWR);
  if(file<0){
    perror("Failed to open the i2c bus!\n");
    return file;
  }
  //printf("i2c bus is now opened!\n");
  return file;
}

void slave_adress_i2c(int file, unsigned char address){
  if(ioctl(file, I2C_SLAVE, address)<0){
    perror("Failed to configure slave address!\n");
    return;
  }
  //printf("Slave address changed!\n");
}

void config_register_i2c(int file, uint8_t _register, uint8_t *data, int length){
  uint8_t buf[length+1];
  buf[0]=_register;
  int old_length = 0;
  buf[1] = data[0];
  /*do{
    buf[old_length+1]=data[old_length];
  }while(++old_length != length);*/
  int i;
  for(i=0; i<length; i++) printf("buf[%d]: %d\n", i, buf[i]);
  if(write(file, buf, length)<0){
    perror("Failed to configure register!\n");
  }
}

void change_register(int file, uint8_t _register){
  uint8_t buf[1];
  buf[0] = _register;
  //printf("register: %d\n", buf[0]);
  if(write(file, buf, 1)<0){
    perror("Failed to change register!\n");
  }
  //printf("change register ok!\n");
}

void read_data_i2c(int file, uint8_t _register, uint8_t *data, int length){
  //printf("test: %x %x\n", data[0], data[1]);
  change_register(file, _register);
  if(read(file, data, length)!=length){
    perror("Failed to read i2c!\n");
  }
  //printf("%x %x\n", data[0], data[1]);
  //printf("read register ok!\n");
}
