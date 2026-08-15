#pragma once
#include <M5GFX.h>

namespace Theme {

  constexpr int SCREEN_W = 240;
  constexpr int SCREEN_H = 135;
  constexpr int STATUS_H = 16;

  inline uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
  }

  inline uint16_t bg()        { return rgb(12, 14, 18);    }
  inline uint16_t bgAlt()     { return rgb(22, 26, 32);    }
  inline uint16_t text()      { return rgb(232, 236, 240); }
  inline uint16_t textDim()   { return rgb(120, 130, 140); }
  inline uint16_t accent()    { return rgb(255, 138, 0);   }
  inline uint16_t accentDim() { return rgb(120, 66, 0);    }
  inline uint16_t good()      { return rgb(60, 200, 120);  }
  inline uint16_t warn()      { return rgb(240, 190, 40);  }
  inline uint16_t bad()       { return rgb(230, 70, 70);   }
  inline uint16_t line()      { return rgb(40, 46, 54);    }

  extern uint16_t g_accent;
}
