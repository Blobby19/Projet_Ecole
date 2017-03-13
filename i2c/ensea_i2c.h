#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#ifndef H_ENSEA_I2C
#define H_ENSEA_I2C

int open_i2c(char *filename);
void change_register(int file, uint8_t _register);
void slave_adress_i2c(int file, unsigned char addr);
void config_register_i2c(int file, uint8_t _register, uint8_t *data, int length);
void read_data_i2c(int file, uint8_t _register, uint8_t *data, int length);

#endif
