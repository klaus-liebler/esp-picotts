#ifndef ESP_BOX_H
#define ESP_BOX_H

#include "sdkconfig.h"
#include "driver/i2c.h"
#include "driver/i2s_std.h"
#include "esp_codec_dev.h"

#define BSP_I2C_SCL           (GPIO_NUM_6)
#define BSP_I2C_SDA           (GPIO_NUM_5)

#define BSP_I2S_SCLK          (GPIO_NUM_48)
#define BSP_I2S_MCLK          (GPIO_NUM_14)
#define BSP_I2S_LCLK          (GPIO_NUM_21)
#define BSP_I2S_DOUT          (GPIO_NUM_45) // To Codec ES8311
#define BSP_I2S_DSIN          (GPIO_NUM_47) // From ADC ES7210
#define BSP_POWER_AMP_IO      (GPIO_NUM_38)
#define BSP_MUTE_STATUS       (GPIO_NUM_1)

#define BSP_I2C_NUM           CONFIG_BSP_I2C_NUM

esp_err_t bsp_i2c_init(void);
esp_err_t bsp_audio_init(const i2s_std_config_t *i2s_config);
esp_codec_dev_handle_t bsp_audio_codec_speaker_init(void);


#endif
