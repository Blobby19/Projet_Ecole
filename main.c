#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <libgen.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include "ensea_i2c.h"
#include "acc.h"
#include "can_communication.h"

#define M_PI 3.14159265358979323846
#define RAD_TO_DEG 57.29578

lsm303dlhc_struct lsm303;

void splash_screen(int duration){
  printf("       _______\n");
  printf("     _/       \\_\n");
  printf("    / |       | \\\n");
  printf("   /  |__   __|  \\\n");
  printf("  |__/((o| |o))\\__|\n");
  printf("  |      | |      |\n");
  printf("  |\\     |_|     /|\n");
  printf("  | \\           / |\n");
  printf("   \\| /  ___  \\ |/ How can I serve you ?\n");
  printf("    \\ | / _ \\ | /\n");
  printf("     \\_________/\n");
  printf("      _|_____|_\n");
  printf(" ____|_________|____\n");
  printf("/                   \\\n");
  sleep(duration);
}

int init_can_communication(char *name){
  printf("----------- Initialisation de la communication CAN... -----------\n");
  int _socket;
  struct ifreq ifr;
  struct sockaddr_can addr;

  if((_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW))<0){
    perror("Socket failed to create!\n");
    return -1;
  }

  addr.can_family = PF_CAN;
  strcpy(ifr.ifr_name, name);
  ioctl(_socket, SIOCGIFINDEX, &ifr);
  addr.can_ifindex = ifr.ifr_ifindex;

  if(bind(_socket, (struct sockaddr*)&addr, sizeof(addr))<0){
    perror("Bind failed!\n");
    return -1;
  }
  printf("----------- Fin de l'Initialisation de la communication CAN ! -----------\n");
  return _socket;
}

int main(int argc, char **argv){
  static int _socket, _i2c;
  char *filename = "/dev/i2c-2";
  int nbytes, send_enable = 0;
  canid_t last_send_id;
  struct can_frame frame = {
    .can_dlc = 1,
  };

  struct can_frame _frame = {
    .can_dlc = 1,
  };

  splash_screen(2);

  if((_socket = init_can_communication("can0"))<0){
    printf("Erreur à l'Initialisation du bus CAN!\n");
    return 0;
  }

  if((_i2c = open_i2c(filename))<0){
		exit(0);
	}

  //lsm303dlhc_init_acc(_i2c, LSM303DLHC_ODR_100HZ, LSM303DLHC_NORMAL);

  srand(time(NULL));

  while(1){
    nbytes = read(_socket, &frame, sizeof(struct can_frame));
    if (nbytes < sizeof(struct can_frame)) {
            fprintf(stderr, "read: incomplete CAN frame\n");
            return 1;
    }
    if(frame.can_id == CAN_ID_REQUEST){
      if((frame.data[0] & CAN_EN_ACC_MASK)>>ACC_OFFSET){
          printf("Accelerometre\n");
          lsm303dlhc_init_acc(_i2c, LSM303DLHC_ODR_100HZ, LSM303DLHC_NORMAL);
          lsm303dlhc_get_acc_x(_i2c, lsm303.accX);
          lsm303dlhc_get_acc_y(_i2c, lsm303.accY);
          lsm303dlhc_get_acc_z(_i2c, lsm303.accZ);
          _frame.can_id = CAN_ID_ACC;
          _frame.can_dlc = 6;
          _frame.data[0] = lsm303.accX[0];
          _frame.data[1] = lsm303.accX[1];
          _frame.data[2] = lsm303.accY[0];
          _frame.data[3] = lsm303.accY[1];
          _frame.data[4] = lsm303.accZ[0];
          _frame.data[5] = lsm303.accZ[1];
          nbytes = write(_socket, &_frame, sizeof(struct can_frame));
          printf("J\'ai envoye: %x %x %x %x %x %x\n", _frame.data[0], _frame.data[1], _frame.data[2], _frame.data[3], _frame.data[4], _frame.data[5]);
          float x= (float)((((lsm303.accX[1]<<8 | lsm303.accX[0]))<<16)>>16)/16383;
        	float y= (float)((((lsm303.accY[1]<<8 | lsm303.accY[0]))<<16)>>16)/16383;
        	float z= (float)((((lsm303.accZ[1]<<8 | lsm303.accZ[0]))<<16)>>16)/16383;
          float accXangle = (float) (atan2(y,z)+M_PI)*RAD_TO_DEG;
        	float accYangle = (float) (atan2(z,x)+M_PI)*RAD_TO_DEG;
          printf("J\'ai envoye: %.3f %.3f %.3f\n", x, y, z);
          printf("angleX: %.3f\n", accXangle);
          printf("angleY: %.3f\n", accYangle);
      }
      if((frame.data[0] & CAN_EN_GYR_MASK)>>GYR_OFFSET){
          printf("Gyroscope\n");
          _frame.can_id = CAN_ID_GYR;
          _frame.can_dlc = 6;
          _frame.data[0] = 0x24;
          _frame.data[1] = 0x24;
          _frame.data[2] = 0x24;
          _frame.data[3] = 0x24;
          _frame.data[4] = 0x24;
          _frame.data[5] = 0x24;
          nbytes = write(_socket, &_frame, sizeof(struct can_frame));
          printf("J\'ai envoye: %x %x %x %x %x %x\n", _frame.data[0], _frame.data[1], _frame.data[2], _frame.data[3], _frame.data[4], _frame.data[5]);
      }
      if((frame.data[0] & CAN_EN_MAG_MASK)>>MAG_OFFSET){
          printf("Magnetometre\n");
          lsm303dlhc_init_mag(_i2c, LSM303DLHC_MAG_DATA_RATE_220HZ, 0x1);
          lsm303dlhc_get_mag_x(_i2c, lsm303.magX);
          lsm303dlhc_get_mag_y(_i2c, lsm303.magY);
          lsm303dlhc_get_mag_z(_i2c, lsm303.magZ);
          _frame.can_id = CAN_ID_MAG;
          _frame.can_dlc = 6;
          _frame.data[0] = lsm303.magX[0];
          _frame.data[1] = lsm303.magX[1];
          _frame.data[2] = lsm303.magY[0];
          _frame.data[3] = lsm303.magY[1];
          _frame.data[4] = lsm303.magZ[0];
          _frame.data[5] = lsm303.magZ[1];
          nbytes = write(_socket, &_frame, sizeof(struct can_frame));
          printf("J\'ai envoye: %x %x %x %x %x %x\n", _frame.data[0], _frame.data[1], _frame.data[2], _frame.data[3], _frame.data[4], _frame.data[5]);
      }
      if((frame.data[0] & CAN_EN_BAR_MASK)>>BAR_OFFSET){
          printf("Barometre\n");
          _frame.can_id = CAN_ID_BAR;
          _frame.can_dlc = 2;
          _frame.data[0] = 0xff;
          _frame.data[1] = 0xff;
          nbytes = write(_socket, &_frame, sizeof(struct can_frame));
          printf("J\'ai envoye: %x %x\n", _frame.data[0], _frame.data[1]);
      }
      if(frame.data[0] & CAN_EN_TEMP_MASK){
          printf("Température\n");
          lsm303dlhc_init_mag(_i2c, LSM303DLHC_MAG_DATA_RATE_220HZ, 0x1);
          lsm303dlhc_get_temp(_i2c, lsm303.temp);
          _frame.can_id = CAN_ID_TEMP;
          _frame.can_dlc = 2;
          _frame.data[0] = lsm303.temp[0];
          _frame.data[1] = lsm303.temp[1];
          int temp = (_frame.data[0] | _frame.data[1]<<8);
          nbytes = write(_socket, &_frame, sizeof(struct can_frame));
          printf("J\'ai envoye: %x %x\n", _frame.data[0], _frame.data[1]);
          printf("%d\n", temp);
      }
    }
    else{
      printf("Unrecognized ID!\n");
    }
  }

	return 0;
}
