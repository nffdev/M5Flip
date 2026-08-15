#include "Settings.h"
#include <Preferences.h>
#include <M5Unified.h>
#include "../ui/Theme.h"

namespace Settings {

  Data data;
  static Preferences prefs;
  static const char* kNamespace = "m5flip";

  void load() {
    prefs.begin(kNamespace, true);
    data.accent     = prefs.getUChar("accent", 0);
    data.brightness = prefs.getUChar("bright", 3);
    data.rotation   = prefs.getUChar("rot", 1);
    prefs.end();

    if (data.accent >= kAccentCount) data.accent = 0;
    if (data.brightness > 4) data.brightness = 3;
    if (data.rotation > 3) data.rotation = 1;
  }

  void save() {
    prefs.begin(kNamespace, false);
    prefs.putUChar("accent", data.accent);
    prefs.putUChar("bright", data.brightness);
    prefs.putUChar("rot", data.rotation);
    prefs.end();
  }

  uint16_t accentColor() {
    return kAccentColors[data.accent];
  }

  uint8_t brightnessPct() {
    static const uint8_t levels[] = { 20, 40, 60, 80, 100 };
    return levels[data.brightness > 4 ? 4 : data.brightness];
  }

  void apply() {
    Theme::g_accent = accentColor();
    M5.Display.setBrightness(brightnessPct() * 255 / 100);
    M5.Display.setRotation(data.rotation);
  }
}
