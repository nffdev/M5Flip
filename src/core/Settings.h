#pragma once
#include <Arduino.h>

namespace Settings {

  static const uint16_t kAccentColors[] = {
    0xFC40,
    0x3E4F,
    0x2B7F,
    0xFDE5,
    0xE228,
    0xFFFF,
  };
  static const char* const kAccentNames[] = {
    "Orange", "Green", "Blue", "Yellow", "Red", "White",
  };
  static const uint8_t kAccentCount = sizeof(kAccentColors) / sizeof(kAccentColors[0]);

  struct Data {
    uint8_t accent     = 0;
    uint8_t brightness = 3;
    uint8_t rotation   = 1;
  };

  extern Data data;

  void load();
  void save();

  void apply();

  uint16_t accentColor();
  uint8_t  brightnessPct();
}
