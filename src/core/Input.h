#pragma once
#include <M5Unified.h>

namespace Input {
  inline bool ok()       { return M5.BtnA.wasPressed(); }
  inline bool next()     { return M5.BtnB.wasPressed(); }
  inline bool back()     { return M5.BtnPWR.wasClicked(); }

  inline bool okLong()   { return M5.BtnA.pressedFor(600); }
  inline bool nextLong() { return M5.BtnB.pressedFor(600); }
}
