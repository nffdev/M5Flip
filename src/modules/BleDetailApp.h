#pragma once
#include "../core/App.h"
#include "../core/Input.h"
#include "../ui/UI.h"
#include <NimBLEDevice.h>

struct BleDeviceInfo {
  String   name;
  String   address;
  int      rssi = 0;
  int      addrType = 0;
  bool     hasName = false;
  bool     connectable = false;
  int      serviceCount = 0;
  String   firstService;
};

class BleDetailApp : public App {
public:
  const char* title() const override { return "Device"; }

  void setInfo(const BleDeviceInfo& info) { _info = info; }

  Action update() override {
    if (Input::back()) return Action::Pop;

    UI::clear();
    UI::statusBar("Device");

    UI::canvas.setTextSize(1);
    UI::canvas.setTextDatum(top_left);
    UI::canvas.setTextColor(Theme::g_accent);
    String title = _info.hasName ? _info.name : String("(no name)");
    UI::canvas.drawString(clip(title, 28).c_str(), 8, Theme::STATUS_H + 6);

    int y = Theme::STATUS_H + 22;
    char buf[40];

    kv("Address", _info.address.c_str(), y, Theme::text()); y += 15;

    kv("Addr type", _info.addrType == 0 ? "public" : "random", y, Theme::textDim()); y += 15;

    snprintf(buf, sizeof(buf), "%d dBm", _info.rssi);
    kv("Signal", buf, y, rssiColor(_info.rssi)); y += 15;

    kv("Connect", _info.connectable ? "yes" : "no", y, Theme::text()); y += 15;

    snprintf(buf, sizeof(buf), "%d", _info.serviceCount);
    kv("Services", buf, y, Theme::text()); y += 15;

    if (_info.serviceCount > 0) {
      kv("UUID", clip(_info.firstService, 20).c_str(), y, Theme::textDim()); y += 15;
    }

    UI::footerHint("PWR: back");
    UI::flush();
    return Action::None;
  }

private:
  BleDeviceInfo _info;

  static String clip(const String& s, int n) {
    if ((int)s.length() <= n) return s;
    return s.substring(0, n - 1) + ">";
  }

  void kv(const char* k, const char* v, int y, uint16_t vcol) {
    UI::canvas.setTextSize(1);
    UI::canvas.setTextDatum(top_left);
    UI::canvas.setTextColor(Theme::textDim());
    UI::canvas.drawString(k, 8, y);
    UI::canvas.setTextDatum(top_right);
    UI::canvas.setTextColor(vcol);
    UI::canvas.drawString(v, Theme::SCREEN_W - 8, y);
  }

  static uint16_t rssiColor(int rssi) {
    return rssi > -60 ? Theme::good() : rssi > -75 ? Theme::warn() : Theme::bad();
  }
};
