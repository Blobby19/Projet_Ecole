#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#ifndef H_BARO
#define H_BARO

#define LPS331AP_BARO_ADDRESS 0xB9
#define LPS331AP_BARO_ADDRESS_DEFAULT (LPS331AP_BARO_ADDRESS>>1)

#define LPS331AP_REF_P_XL 0x08
#define LPS331AP_REF_P_L 0x09
#define LPS331AP_REF_P_H 0x0A

#define LPS331AP_WHO_AM_I 0x0F

#define LPS331AP_RES_CONF 0x10

#define LPS331AP_CTRL_REG1 0x20
#define LPS331AP_CTRL_REG2 0x21
#define LPS331AP_CTRL_REG3 0x22

#define LPS331AP_INT_CFG_REG 0x23
#define LPS331AP_INT_SRC_REG 0x24

#define LPS331AP_THS_P_LOW_REG 0x25
#define LPS331AP_THS_P_HIGH_REG 0x26

#define LPS331AP_STATUS_REG 0x27

#define LPS331AP_PRESS_POUT_XL_REG 0x28

#define LPS331AP_PRESS_OUT_L 0x29
#define LPS331AP_PRESS_OUT_H 0x2A
#define LPS331AP_TEMP_OUT_L 0x2B
#define LPS331AP_TEMP_OUT_H 0x2C

#define LPS331AP_AMP_CTRL 0x30

#define LPS331AP_POWER_DOWN 0
#define LPS331AP_NORMAL_MODE 1

#define LPS331AP_ODR_P_ONE_SHOT_T_ONE_SHOT 0
#define LPS331AP_ODR_P_1_HZ_T_1_HZ 1
#define LPS331AP_ODR_P_7_HZ_T_1_HZ 2
#define LPS331AP_ODR_P_12_5_HZ_T_1_HZ 3
#define LPS331AP_ODR_P_25_HZ_T_1_HZ 4
#define LPS331AP_ODR_P_7_HZ_T_7_HZ 5
#define LPS331AP_ODR_P_12_5_HZ_T_12_5_HZ 6
#define LPS331AP_ODR_P_25_HZ_T_25_HZ 7

#endif H_BARO

typedef struct{
  uint8_t baro[3];
  uint8_t temp[2];
}lsp331ap;

void lsp331ap_baro_initialize(int file);
void lsp331ap_init_baro(int file, uint8_t samplingrate, uint8_t mode);
void lsp331ap_get_baro(int file, uint8_t *data);
void lsp331ap_get_temp(int file, uint8_t *data);
