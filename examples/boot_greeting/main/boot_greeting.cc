#include "picotts.h"
#include <driver/i2c_master.h>
#include "nau88c22.hh"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#define TAG "MAIN"
#include <esp_log.h>
#define TTS_CORE 1

constexpr gpio_num_t PIN_I2C_SDA = (gpio_num_t)5;
constexpr gpio_num_t PIN_I2C_SCL = (gpio_num_t)6;

constexpr gpio_num_t PIN_I2S_MCLK = (gpio_num_t)14;
constexpr gpio_num_t PIN_I2S_FS = (gpio_num_t)21;
constexpr gpio_num_t PIN_I2S_DAC = (gpio_num_t)45;
constexpr gpio_num_t PIN_I2S_ADC = (gpio_num_t)47;
constexpr gpio_num_t PIN_I2S_BCLK = (gpio_num_t)48;
constexpr i2c_port_t I2C_PORT{I2C_NUM_0};

const char greeting[] = "Hallo Läbäthom a s f r 3 4 6 ist bereit";
nau88c22::M *codec;

extern "C" void on_samples(int16_t *buf, unsigned count)
{
  
  codec->WriteAudioData(CodecManager::eChannels::ONE, CodecManager::eSampleBits::SIXTEEN, 16000, count, buf);
  // esp_codec_dev_write(spk_codec, buf, count*2);
}

extern "C" void app_main()
{
  i2c_master_bus_handle_t i2c_master_handle{nullptr};
  i2c_master_bus_config_t i2c_mst_config = {
      .i2c_port = I2C_PORT,
      .sda_io_num = PIN_I2C_SDA,
      .scl_io_num = PIN_I2C_SCL,
      .clk_source = I2C_CLK_SRC_DEFAULT,
      .glitch_ignore_cnt = 7,
      .intr_priority = 0,
      .trans_queue_depth = 0,
      .flags = {
          .enable_internal_pullup = 1,
      }};

  ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &i2c_master_handle));
  codec = new nau88c22::M(i2c_master_handle, PIN_I2S_MCLK, PIN_I2S_BCLK, PIN_I2S_FS, PIN_I2S_DAC, 127, 16000);
  codec->Init();

 unsigned prio = uxTaskPriorityGet(NULL);
  if (picotts_init(prio, on_samples, TTS_CORE))
  {
    picotts_add(greeting, sizeof(greeting));

    vTaskDelay(pdMS_TO_TICKS(10000));

    picotts_shutdown();
  }
  else
  {
    ESP_LOGE(TAG, "Failed to initialise TTS");
  }
}
