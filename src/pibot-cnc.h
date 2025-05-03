/*
 * Definition of the class LGFX for the Pibots project
 * 
 * This program use LovyanGFX for the FT6336U touch and ILI9341 screen connected to the ESP32.
 */
 
#pragma once

#include <Arduino.h>
#include <LovyanGFX.hpp>

//==========================================================
// ENCODER CONFIGURATION
//==========================================================
#define ROTARY_A_PIN GPIO_NUM_22
#define ROTARY_B_PIN GPIO_NUM_27

//==========================================================
// BUTTONS CONFIGURATION
//==========================================================
#define BUTTON_RED_PIN  GPIO_NUM_4
#define BUTTON_YELLOW_PIN GPIO_NUM_16
#define BUTTON_GREEN_PIN GPIO_NUM_17


//==========================================================
// SCREEN CONFIGURATION
//==========================================================

// Screen parameters
#define SCREEN_WIDTH   240     // Screen width in pixels
#define SCREEN_HEIGHT  320     // Screen height in pixels
#define ROTATION       2       // Screen rotation (0, 1, 2, 3)

//==========================================================
// MANUAL CALIBRATION CONFIGURATION
//==========================================================

// Calibration parameters for manual correction in readTouch()
#define TOUCH_FLIP_X   true    // Invert X axis (true/false)
#define TOUCH_FLIP_Y   true    // Invert Y axis (true/false)
#define TOUCH_SWAP_XY  false   // Swap X and Y axes (true/false)

//==========================================================
// HARDWARE CONFIGURATION
//==========================================================

// Pin definitions for FT6336U touch screen
#define TOUCH_SDA 32  // I2C Data
#define TOUCH_SCL 25  // I2C Clock
#define TOUCH_INT 36  // Interrupt

// Pin definitions for TFT screen
#define TFT_CS   15  // Chip Select
#define TFT_DC   2   // Data/Command Select
#define TFT_MOSI 13  // MOSI (SDI)
#define TFT_CLK  14  // SCK Clock
#define TFT_MISO 12  // MISO (SDO) 
#define TFT_RST  -1  // Reset
#define TFT_LED  21  // Backlight control

// Screen configuration with LovyanGFX
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9341 _panel_instance;
  lgfx::Bus_SPI _bus_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Touch_FT5x06 _touch_instance; // Instance for FT6336U (compatible with FT5x06)

public:
  LGFX(void) {
    { // SPI bus configuration
      auto cfg = _bus_instance.config();
      cfg.spi_host = VSPI_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;
      cfg.freq_read = 16000000;
      cfg.spi_3wire = false;
      cfg.use_lock = true;
      cfg.dma_channel = 1;
      cfg.pin_mosi = TFT_MOSI;
      cfg.pin_miso = TFT_MISO;
      cfg.pin_sclk = TFT_CLK;
      cfg.pin_dc = TFT_DC;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    { // LCD panel configuration
      auto cfg = _panel_instance.config();
      cfg.pin_cs = TFT_CS;
      cfg.pin_rst = TFT_RST;
      cfg.pin_busy = -1;
      cfg.memory_width = SCREEN_WIDTH;
      cfg.memory_height = SCREEN_HEIGHT;
      cfg.panel_width = SCREEN_WIDTH;
      cfg.panel_height = SCREEN_HEIGHT;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = ROTATION;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = true;
      cfg.invert = true;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = true;
      _panel_instance.config(cfg);
    }

    { // Backlight configuration
      auto cfg = _light_instance.config();
      cfg.pin_bl = TFT_LED;
      cfg.invert = false;
      cfg.freq = 44100;
      cfg.pwm_channel = 7;
      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);
    }
    
    { // Touch screen configuration
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = SCREEN_WIDTH;
      cfg.y_min = 0;
      cfg.y_max = SCREEN_HEIGHT;
      cfg.pin_int = TOUCH_INT;
      cfg.bus_shared = true;
      cfg.i2c_addr = 0x38;           // FT6336U I2C address
      cfg.i2c_port = 1;              // I2C port
      cfg.freq = 400000;             // I2C frequency
      cfg.pin_sda = TOUCH_SDA;       // SDA pin
      cfg.pin_scl = TOUCH_SCL;       // SCL pin
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    setPanel(&_panel_instance);
  }
};
