#include "ensea_i2c.h"

/**
* Fonction qui permet d'ouvrir une communication i2c
**/
int open_i2c(char *filename){
  int file = open(filename, O_RDWR);
  if(file<0){
    perror("Failed to open the i2c bus!\n");
    return file;
  }
  return file;
}

/**
* Fonction qui permet de changer d'élément i2c
**/
void slave_adress_i2c(int file, unsigned char address){
  if(ioctl(file, I2C_SLAVE, address)<0){
    perror("Failed to configure slave address!\n");
    return;
  }
}

/**
* Fonction qui permet de configurer un registre
**/
void config_register_i2c(int file, uint8_t _register, uint8_t *data, int length){
  uint8_t buf[length+1];
  buf[0]=_register;
  int old_length = 0;
  //buf[1] = data[0];
  int i;
  for(i=1; i<length; i++) buf[i]=data[i-1];//printf("buf[%d]: %d\n", i, buf[i]);
  if(write(file, buf, length)<0){
    perror("Failed to configure register!\n");
  }
}

/**
* Fonction qui permet de changer de registre
**/
void change_register(int file, uint8_t _register){
  uint8_t buf[1];
  buf[0] = _register;
  if(write(file, buf, 1)<0){
    perror("Failed to change register!\n");
  }
}

/**
* Fonction qui permet de lire les données d'un registre
**/
void read_data_i2c(int file, uint8_t _register, uint8_t *data, int length){
  change_register(file, _register);
  if(read(file, data, length)!=length){
    perror("Failed to read i2c!\n");
  }
}
