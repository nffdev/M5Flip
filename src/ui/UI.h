#pragma once
#include <M5Unified.h>
#include "Theme.h"

namespace UI {

  extern M5Canvas canvas;

  void begin();
  void flush();
  void clear();
  void statusBar(const char* title);
  void listMenu(const char* const* items, int count, int selected);
  void centerText(const char* s, int y, uint16_t color, uint8_t size = 1);
  void footerHint(const char* hint);
}
