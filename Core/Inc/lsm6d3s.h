#ifndef LSM6DS3_H
#define LSM6DS3_H

#include "main.h"

// Device Address (when SDO/SA0 pin is connected to ground)
void LSM6DS3_Init();
void LSM6DS3_WhoAmI(uint8_t *val);
void LSM6DS3_AccGetRawXYZ(int16_t *buff);
void LSM6DS3_GyroGetRawXYZ(uint16_t *buff);
void LSM6DS3_AccGetXYZ(float *buff);
void LSM6DS3_GyroGetXYZ(float *buff);

extern I2C_HandleTypeDef hi2c1;
#define LSM6DS3_I2C_PORT hi2c1

#define LSM6DS3_I2C_ADDRESS 0x6A
#define LSM6DS3_I2C_WRITE_ADDRESS 0xD4
#define LSM6DS3_I2C_READ_ADDRESS 0xD5

// Register Addresses
#define LSM6DS3_FUNC_CFG_ACCESS        0x01
#define LSM6DS3_SENSOR_SYNC_TIME_FRAME 0x04
#define LSM6DS3_SENSOR_SYNC_RES_RATIO  0x05
#define LSM6DS3_FIFO_CTRL1             0x06
#define LSM6DS3_FIFO_CTRL2             0x07
#define LSM6DS3_FIFO_CTRL3             0x08
#define LSM6DS3_FIFO_CTRL4             0x09
#define LSM6DS3_FIFO_CTRL5             0x0A
#define LSM6DS3_DRDY_PULSE_CFG         0x0B
#define LSM6DS3_INT1_CTRL              0x0D
#define LSM6DS3_INT2_CTRL              0x0E
#define LSM6DS3_WHO_AM_I               0x0F  // Default value: 0x69
#define LSM6DS3_CTRL1_XL               0x10
#define LSM6DS3_CTRL2_G                0x11
#define LSM6DS3_CTRL3_C                0x12
#define LSM6DS3_CTRL4_C                0x13
#define LSM6DS3_CTRL5_C                0x14
#define LSM6DS3_CTRL6_C                0x15
#define LSM6DS3_CTRL7_G                0x16
#define LSM6DS3_CTRL8_XL               0x17
#define LSM6DS3_CTRL9_XL               0x18
#define LSM6DS3_CTRL10_C               0x19
#define LSM6DS3_WAKE_UP_SRC            0x1B
#define LSM6DS3_TAP_SRC                0x1C
#define LSM6DS3_D6D_SRC                0x1D
#define LSM6DS3_STATUS_REG             0x1E
#define LSM6DS3_OUT_TEMP_L             0x20
#define LSM6DS3_OUT_TEMP_H             0x21
#define LSM6DS3_OUTX_L_G               0x22
#define LSM6DS3_OUTX_H_G               0x23
#define LSM6DS3_OUTY_L_G               0x24
#define LSM6DS3_OUTY_H_G               0x25
#define LSM6DS3_OUTZ_L_G               0x26
#define LSM6DS3_OUTZ_H_G               0x27
#define LSM6DS3_OUTX_L_XL              0x28
#define LSM6DS3_OUTX_H_XL              0x29
#define LSM6DS3_OUTY_L_XL              0x2A
#define LSM6DS3_OUTY_H_XL              0x2B
#define LSM6DS3_OUTZ_L_XL              0x2C
#define LSM6DS3_OUTZ_H_XL              0x2D
#define LSM6DS3_FIFO_STATUS1           0x3A
#define LSM6DS3_FIFO_STATUS2           0x3B
#define LSM6DS3_FIFO_STATUS3           0x3C
#define LSM6DS3_FIFO_STATUS4           0x3D
#define LSM6DS3_FIFO_DATA_OUT_L        0x3E
#define LSM6DS3_FIFO_DATA_OUT_H        0x3F
#define LSM6DS3_TIMESTAMP0_REG         0x40
#define LSM6DS3_TIMESTAMP1_REG         0x41
#define LSM6DS3_TIMESTAMP2_REG         0x42
#define LSM6DS3_STEP_TIMESTAMP_L       0x49
#define LSM6DS3_STEP_TIMESTAMP_H       0x4A
#define LSM6DS3_STEP_COUNTER_L         0x4B
#define LSM6DS3_STEP_COUNTER_H         0x4C
#define LSM6DS3_SENSORHUB1_REG         0x4E
#define LSM6DS3_SENSORHUB2_REG         0x4F
#define LSM6DS3_SENSORHUB3_REG         0x50
#define LSM6DS3_SENSORHUB4_REG         0x51
#define LSM6DS3_SENSORHUB5_REG         0x52
#define LSM6DS3_SENSORHUB6_REG         0x53
#define LSM6DS3_SENSORHUB7_REG         0x54
#define LSM6DS3_SENSORHUB8_REG         0x55
#define LSM6DS3_SENSORHUB9_REG         0x56
#define LSM6DS3_SENSORHUB10_REG        0x57
#define LSM6DS3_SENSORHUB11_REG        0x58
#define LSM6DS3_SENSORHUB12_REG        0x59
#define LSM6DS3_FIFO_DATA_OUT_TAG      0x78
#define LSM6DS3_FIFO_DATA_OUT_TAG_XL   0x79
#define LSM6DS3_FIFO_DATA_OUT_TAG_G    0x7A

// Bit Masks and Other Constants
#define LSM6DS3_WHO_AM_I_DEFAULT_VALUE 0x69

// CTRL1_XL Register (0x10) - Accelerometer Control
#define LSM6DS3_CTRL1_XL_ODR_XL_MASK   0xF0
#define LSM6DS3_CTRL1_XL_FS_XL_MASK    0x0C
#define LSM6DS3_CTRL1_XL_BW_XL_MASK    0x03

// CTRL2_G Register (0x11) - Gyroscope Control
#define LSM6DS3_CTRL2_G_ODR_G_MASK     0xF0
#define LSM6DS3_CTRL2_G_FS_G_MASK      0x0E

// CTRL3_C Register (0x12) - Control Register 3
#define LSM6DS3_CTRL3_C_BDU_MASK       0x40
#define LSM6DS3_CTRL3_C_IF_INC_MASK    0x04
#define LSM6DS3_CTRL3_C_SW_RESET_MASK  0x01

// CTRL4_C Register (0x13) - Control Register 4
#define LSM6DS3_CTRL4_C_INT1_MASK      0x80
#define LSM6DS3_CTRL4_C_DRDY_MASK      0x01

// ODR (Output Data Rate) values for CTRL1_XL
#define LSM6DS3_CTRL1_XL_ODR_XL_POWER_DOWN  (0x0 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_13Hz        (0x1 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_26Hz        (0x2 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_52Hz        (0x3 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_104Hz       (0x4 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_208Hz       (0x5 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_416Hz       (0x6 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_833Hz       (0x7 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_1_66kHz     (0x8 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_3_33kHz     (0x9 << 4)
#define LSM6DS3_CTRL1_XL_ODR_XL_6_66kHz     (0xA << 4)

// FS (Full Scale) values for CTRL1_XL
#define LSM6DS3_CTRL1_XL_FS_XL_2g           (0x0 << 2)
#define LSM6DS3_CTRL1_XL_FS_XL_16g          (0x1 << 2)
#define LSM6DS3_CTRL1_XL_FS_XL_4g           (0x2 << 2)
#define LSM6DS3_CTRL1_XL_FS_XL_8g           (0x3 << 2)

// BW (Bandwidth) values for CTRL1_XL
#define LSM6DS3_CTRL1_XL_BW_XL_400Hz        (0x0)
#define LSM6DS3_CTRL1_XL_BW_XL_200Hz        (0x1)
#define LSM6DS3_CTRL1_XL_BW_XL_100Hz        (0x2)
#define LSM6DS3_CTRL1_XL_BW_XL_50Hz         (0x3)

// CTRL2_G (0x11) - Gyroscope Control
#define LSM6DS3_CTRL2_G_ODR_G_MASK          0xF0
#define LSM6DS3_CTRL2_G_FS_G_MASK           0x0E

// ODR (Output Data Rate) values for CTRL2_G
#define LSM6DS3_CTRL2_G_ODR_G_POWER_DOWN    (0x0 << 4)
#define LSM6DS3_CTRL2_G_ODR_G_13Hz          (0x1 << 4)
#define LSM6DS3_CTRL2_G_ODR_G_26Hz          (0x2 << 4)
#define LSM6DS3_CTRL2_G_ODR_G_52Hz          (0x3 << 4)
#define LSM6DS3_CTRL2_G_ODR_G_104Hz         (0x4 << 4)
#define LSM6DS3_CTRL2_G_ODR_G_208Hz         (0x5 << 4)
#define LSM6DS3_CTRL2_G_ODR_G_416Hz         (0x6 << 4)
#define LSM6DS3_CTRL2_G_ODR_G_833Hz         (0x7 << 4)
#define LSM6DS3_CTRL2_G_ODR_G_1_66kHz       (0x8 << 4)
//#define LSM6DS3_CTRL2_G_ODR_G_3_33kHz       (0x9 << 4)
//#define LSM6DS3_CTRL2_G_ODR_G_6_66kHz       (0xA << 4)

// FS (Full Scale) values for CTRL2_G
#define LSM6DS3_CTRL2_G_FS_G_125dps         (0x1 << 1)
#define LSM6DS3_CTRL2_G_FS_G_250dps         (0x0 << 2)
#define LSM6DS3_CTRL2_G_FS_G_500dps         (0x1 << 2)
#define LSM6DS3_CTRL2_G_FS_G_1000dps        (0x2 << 2)
#define LSM6DS3_CTRL2_G_FS_G_2000dps        (0x3 << 2)

// CTRL3_C (0x12) - Control Register 3
#define LSM6DS3_CTRL3_C_BOOT                (0x1 << 7)
#define LSM6DS3_CTRL3_C_BDU                 (0x1 << 6)
#define LSM6DS3_CTRL3_C_H_LACTIVE           (0x1 << 5)
#define LSM6DS3_CTRL3_C_PP_OD               (0x1 << 4)
#define LSM6DS3_CTRL3_C_SIM                 (0x1 << 3)
#define LSM6DS3_CTRL3_C_IF_INC              (0x1 << 2)
#define LSM6DS3_CTRL3_C_BLE                 (0x1 << 1)
#define LSM6DS3_CTRL3_C_SW_RESET            (0x1)

// CTRL4_C (0x13) - Control Register 4
#define LSM6DS3_CTRL4_C_INT2_ON_INT1        (0x1 << 7)
#define LSM6DS3_CTRL4_C_SLEEP               (0x1 << 6)
#define LSM6DS3_CTRL4_C_INT2_DRDY           (0x1 << 3)
#define LSM6DS3_CTRL4_C_DRDY_MASK           (0x1)

// CTRL5_C (0x14) - Control Register 5
#define LSM6DS3_CTRL5_C_ROUNDING_MASK       (0x7 << 5)
#define LSM6DS3_CTRL5_C_ST_G_MASK           (0x3 << 3)
#define LSM6DS3_CTRL5_C_ST_XL_MASK          (0x3 << 1)

// CTRL6_C (0x15) - Control Register 6
#define LSM6DS3_CTRL6_C_TRIG_EN             (0x1 << 7)
#define LSM6DS3_CTRL6_C_LVL1_EN             (0x1 << 6)
#define LSM6DS3_CTRL6_C_LVL2_EN             (0x1 << 5)
#define LSM6DS3_CTRL6_C_HM_MODE             (0x1 << 4)
#define LSM6DS3_CTRL6_C_ODR_TSW_MASK        (0xF)

// CTRL7_G (0x16) - Control Register 7
#define LSM6DS3_CTRL7_G_HPM_G_MASK          (0x3 << 4)
#define LSM6DS3_CTRL7_G_HP_EN_G             (0x1 << 4)
#define LSM6DS3_CTRL7_G_ROUNDING_STATUS     (0x1 << 2)

// CTRL8_XL (0x17) - Accelerometer Settings
#define LSM6DS3_CTRL8_XL_LOW_PASS_ON_6D     (0x1 << 6)
#define LSM6DS3_CTRL8_XL_HP_SLOPE_XL_EN     (0x1 << 5)
#define LSM6DS3_CTRL8_XL_FASTSETTL          (0x1 << 4)
#define LSM6DS3_CTRL8_XL_HPCF_XL_MASK       (0x3 << 2)
#define LSM6DS3_CTRL8_XL_LOW_PASS_EN        (0x1 << 1)
#define LSM6DS3_CTRL8_XL_INPUT_COMPOSITE    (0x1)

// CTRL9_XL (0x18) - Accelerometer Settings
#define LSM6DS3_CTRL9_XL_SOFT_EN            (0x1 << 1)
#define LSM6DS3_CTRL9_XL_TIMESTAMP_EN       (0x1)

// CTRL10_C (0x19) - Control Register 10
#define LSM6DS3_CTRL10_C_SIGN_MOTION_EN     (0x1)

#endif // LSM6DS3_H
