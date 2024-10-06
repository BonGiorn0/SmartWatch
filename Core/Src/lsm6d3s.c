#include "lsm6d3s.h"

static void LSM6DS3_I2C_Write(uint8_t reg, uint8_t val){
	HAL_I2C_Mem_Write(&LSM6DS3_I2C_PORT, LSM6DS3_I2C_WRITE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, &val, 1, HAL_MAX_DELAY);
}

static void LSM6DS3_I2C_Read(uint8_t reg, uint8_t *val){
	HAL_I2C_Mem_Read(&LSM6DS3_I2C_PORT, LSM6DS3_I2C_READ_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, val, 1, HAL_MAX_DELAY);
}

void LSM6DS3_Init(){
	uint8_t ctrl1_val = LSM6DS3_CTRL1_XL_ODR_XL_1_66kHz |
						LSM6DS3_CTRL1_XL_FS_XL_2g		|
						LSM6DS3_CTRL1_XL_BW_XL_400Hz	;
	LSM6DS3_I2C_Write(LSM6DS3_CTRL1_XL, ctrl1_val);
	uint8_t ctrl2_val = LSM6DS3_CTRL2_G_ODR_G_1_66kHz |
						LSM6DS3_CTRL2_G_FS_G_250dps	  ;
	LSM6DS3_I2C_Write(LSM6DS3_CTRL2_G, ctrl2_val);
	uint8_t ctrl3_val = LSM6DS3_CTRL3_C_IF_INC;
	LSM6DS3_I2C_Write(LSM6DS3_CTRL2_G, ctrl3_val);
	uint8_t ctrl8_val = LSM6DS3_CTRL8_XL_LOW_PASS_EN;
	LSM6DS3_I2C_Write(LSM6DS3_CTRL8_XL, ctrl8_val);
}


void LSM6DS3_WhoAmI(uint8_t *val){
	LSM6DS3_I2C_Read(LSM6DS3_WHO_AM_I, val);
}

void LSM6DS3_AccGetRawXYZ(int16_t *buff){
	uint8_t tmp;
	LSM6DS3_I2C_Read(LSM6DS3_OUTX_H_XL, &tmp);
	buff[0] = (int16_t)tmp << 8;
	LSM6DS3_I2C_Read(LSM6DS3_OUTX_L_XL, &tmp);
	buff[0] |= (int16_t)tmp;
	LSM6DS3_I2C_Read(LSM6DS3_OUTY_H_XL, &tmp);
	buff[1] = (int16_t)tmp << 8;
	LSM6DS3_I2C_Read(LSM6DS3_OUTY_L_XL, &tmp);
	buff[1] |= (int16_t)tmp;
	LSM6DS3_I2C_Read(LSM6DS3_OUTZ_H_XL, &tmp);
	buff[2] = (int16_t)tmp << 8;
	LSM6DS3_I2C_Read(LSM6DS3_OUTZ_L_XL, &tmp);
	buff[2] |= (int16_t)tmp;

}

void LSM6DS3_AccGetXYZ(float *buff){
	int16_t raw_buff[3];
	uint8_t tmp;
	float coef = 0;

	LSM6DS3_AccGetRawXYZ(raw_buff);
	LSM6DS3_I2C_Read(LSM6DS3_CTRL1_XL, &tmp);
	switch(tmp & LSM6DS3_CTRL1_XL_FS_XL_MASK){
	case LSM6DS3_CTRL1_XL_FS_XL_2g:
		coef = 2;
		break;
	case LSM6DS3_CTRL1_XL_FS_XL_4g:
		coef = 4;
		break;
	case LSM6DS3_CTRL1_XL_FS_XL_8g:
		coef = 8;
		break;
	case LSM6DS3_CTRL1_XL_FS_XL_16g:
		coef = 16;
		break;
	}
	for (int i = 0; i < 3; ++i) {
		buff[i] = (float)raw_buff[i] / INT16_MAX * coef;
	}



}
