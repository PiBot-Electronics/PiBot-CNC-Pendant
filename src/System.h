// Copyright (c) 2023 Mitch Bradley
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#include "Config.h"
#include "Encoder.h"

#ifdef ARDUINO
#    include <Arduino.h>
#    include <LittleFS.h>
constexpr static const int UPDATE_RATE_MS = 30;  // minimum refresh rate in milliseconds
extern Stream&             debugPort;
void                       init_fnc_uart(int uart_num, int tx_pin, int rx_pin);
#endif  // ARDUINO

#    include "LovyanGFX.h"

#    define WHITE TFT_WHITE
#    define BLACK TFT_BLACK
#    define RED TFT_RED
#    define YELLOW TFT_YELLOW
#    define BLUE TFT_BLUE
#    define LIGHTGREY TFT_LIGHTGREY
#    define DARKGREY TFT_DARKGREY
#    define GREEN TFT_GREEN
#    define NAVY TFT_NAVY
#    define CYAN TFT_CYAN
#    define ORANGE TFT_ORANGE
#    define BROWN TFT_BROWN
#    define MAROON TFT_MAROON


extern LGFX_Device&     display;
extern LGFX_Sprite      canvas;
//extern m5::Touch_Class& touch;

void drawPngFile(const char* filename, int x, int y);

void init_system();

void ackBeep();

void update_events();
void delay_ms(uint32_t ms);

void resetFlowControl();

extern bool round_display;

void system_background();

bool screen_encoder(int x, int y, int& delta);
bool screen_button_touched(bool pressed, int x, int y, int& button);
bool switch_button_touched(bool& pressed, int& button);

void deep_sleep(int us);

inline int display_short_side() {
    return (display.width() < display.height()) ? display.width() : display.height();
}

void base_display();
void set_layout(int n);
void next_layout(int delta);

bool ui_locked();
