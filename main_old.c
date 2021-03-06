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

int main(void){
	int file;
	char *filename = "/dev/i2c-2";
	if((file = open(filename, O_RDWR))<0){
		//Error
		perror("Failed to open the i2c bus!\n");
		exit(1);
	}
	printf("Le bus i2c est ouvert !\n");


	//Adresse 32 avec un décalage vers la gauche pour y insérer le bit de R/W
	// 0011 0010 (32h) -> 001 1001 (19h)
	unsigned char addr = 0x19; //<< 1 (and 0x1 si write ou 0x0 si read)

	if(ioctl(file, I2C_SLAVE, addr) < 0){
		perror("Failed configure slave address");
		exit(1);
	}
	printf("L'esclave est configure\n");

	uint8_t CTRL_A_1_reg = 0x20;	// Registre de configuration de l'accélérometre
	uint8_t OUT_Z_L_A_reg = 0x2C;	// Registre de lecture des valeurs en X
	uint8_t buf[2];			// Buffer de configuration
	uint8_t value[4];		// Valeurs

	buf[0] = CTRL_A_1_reg;		// Mise de l'adresse du registre de configuration
	buf[1] = 0x57;			// Configuration de l'accélérometre 0x5 pour le scan à 100Hz 0x7 pour l'activation des axes
	if (write(file,buf,2) != 1) {
	    	/* ERROR HANDLING: i2c transaction failed */
	    	printf("Failed to write to the i2c bus.\n");
	    	printf("\n\n");
	}

	buf[0] = CTRL_A_1_reg;
	if (write(file,buf,1) != 1) {
	    	/* ERROR HANDLING: i2c transaction failed */
	    	printf("Failed to write to the i2c bus.\n");
	    	printf("\n\n");
	}
	read(file, &value, 1);		// Vérification de la configuration du registre
	printf("CTRL_REG1_A: %d\n", value[0]);
	sleep(1);

	while(1){
		buf[0] = OUT_X_L_A_reg | 0x80;	// Registre de l'axe X | 0x80 pour auto-incrément
		if (write(file,buf,1) != 1) {
	    	/* ERROR HANDLING: i2c transaction failed */
	    	printf("Failed to write to the i2c bus.\n");
	    	printf("\n\n");
		}
		read(file, &value, 2);
		printf("%d %d \n", value[0],value[1]);
		uint8_t realvalue;
		realvalue = value[0]+value[1]*256;
		float test;
		test = ((float)realvalue)/16384;
		printf("%.3f \n", test);
		sleep(1);
	}

	close(file);

	return 0;
}
