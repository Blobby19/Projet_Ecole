#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ensea_i2c.h"
#include "acc.h"
#include <math.h>

#define M_PI 3.14159265358979323846
#define RAD_TO_DEG 57.29578

int file;

int main(void){
	lsm303dlhc_struct lsm303;
	char *filename = "/dev/i2c-2";
	if((file = open_i2c(filename))<0){
		exit(0);
	}

	/*lsm303dlhc_initialize(file);*/
	/*lsm303dlhc_init_acc(file, LSM303DLHC_ODR_100HZ, LSM303DLHC_NORMAL);
	lsm303dlhc_get_acc_x(file, lsm303.accX);
	lsm303dlhc_get_acc_y(file, lsm303.accY);
	lsm303dlhc_get_acc_z(file, lsm303.accZ);*/

	lsm303dlhc_init_acc(file, LSM303DLHC_ODR_100HZ, LSM303DLHC_NORMAL);
	lsm303dlhc_get_acc_x(file, lsm303.accX);
	lsm303dlhc_get_acc_y(file, lsm303.accY);
	lsm303dlhc_get_acc_z(file, lsm303.accZ);

	lsm303dlhc_init_mag(file, LSM303DLHC_MAG_DATA_RATE_220HZ, LSM303DLHC_SENSOR_TEMP_EN);
	lsm303dlhc_get_mag_x(file, lsm303.magX);
	lsm303dlhc_get_mag_y(file, lsm303.magY);
	lsm303dlhc_get_mag_z(file, lsm303.magZ);

	lsm303dlhc_get_temp(file, lsm303.temp);

	float x= (float)((((lsm303.accX[1]<<8 | lsm303.accX[0]))<<16)>>16)/16383;
	float y= (float)((((lsm303.accY[1]<<8 | lsm303.accY[0]))<<16)>>16)/16383;
	float z= (float)((((lsm303.accZ[1]<<8 | lsm303.accZ[0]))<<16)>>16)/16383;
	float accXangle = (float) (atan2(y,z)+M_PI)*RAD_TO_DEG;
	float accYangle = (float) (atan2(z,x)+M_PI)*RAD_TO_DEG;
	printf("accX: %d %d\n", lsm303.accX[0], lsm303.accX[1]);
	printf("accX: %.3f\n", x);
	printf("angleX: %.3f\n", accXangle);
	printf("accY: %d %d\n", lsm303.accY[0], lsm303.accY[1]);
	printf("accY: %.3f\n", y);
	printf("angleY: %.3f\n", accYangle);
	printf("accZ: %d %d\n", lsm303.accZ[0], lsm303.accZ[1]);
	printf("accZ: %.3f\n", z);
	printf("magX: %d %d\n", lsm303.magX[0], lsm303.magX[1]);
	printf("magY: %d %d\n", lsm303.magY[0], lsm303.magY[1]);
	printf("magZ: %d %d\n", lsm303.magZ[0], lsm303.magZ[1]);
	printf("temp: %d %d\n", lsm303.temp[0], lsm303.temp[1]);
}
