#pragma once
#include "../core/App.h"
#include "../core/Input.h"
#include "../core/StateManager.h"
#include "../ui/UI.h"
#include "WifiDetailApp.h"
#include <WiFi.h>

class WifiScanApp : public App {
public:
  const char* title() const override { return "WiFi Scan"; }

  void setDetail(WifiDetailApp* d) { _detail = d; }

  void onEnter() override {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    _found = -1;
    _sel = 0;
    _scanStart = millis();
    WiFi.scanNetworks(true);
  }
  void onExit() override { WiFi.scanDelete(); WiFi.mode(WIFI_OFF); }

  Action update() override {
    if (Input::back()) return Action::Pop;

    if (_found < 0) {
      int r = WiFi.scanComplete();
      if (r >= 0) _found = r;
    } else {
      if (Input::next() && _found > 0) _sel = (_sel + 1) % _found;
      if (Input::nextLong()) {
        WiFi.scanDelete();
        _found = -1; _sel = 0;
        WiFi.scanNetworks(true);
      }
      if (Input::ok() && _found > 0 && _detail) {
        _detail->setIndex(_sel);
        StateManager::push(_detail);
      }
    }

    UI::clear();
    UI::statusBar("WiFi Scan");

    if (_found < 0) {
      char dots[8]; int n = ((millis() - _scanStart) / 400) % 4;
      strcpy(dots, "..."); dots[n] = 0;
      UI::centerText("Scanning", 60, Theme::text(), 2);
      UI::centerText(dots, 84, Theme::accent(), 2);
    } else if (_found == 0) {
      UI::centerText("No networks", 68, Theme::textDim(), 2);
    } else {
      drawList();
    }
    UI::footerHint("A: detail   B: next   B(hold): rescan");
    UI::flush();
    return Action::None;
  }

private:
  void drawList() {
    const int rowH = 20, top = Theme::STATUS_H + 4;
    int visible = (Theme::SCREEN_H - top - 12) / rowH;
    int first = _sel - visible / 2;
    if (first < 0) first = 0;
    if (first > _found - visible) first = _found - visible;
    if (first < 0) first = 0;

    for (int row = 0; row < visible && first + row < _found; ++row) {
      int i = first + row, y = top + row * rowH;
      bool sel = (i == _sel);
      if (sel) UI::canvas.fillRoundRect(4, y, Theme::SCREEN_W - 8, rowH - 2, 3, Theme::g_accent);

      UI::canvas.setTextDatum(middle_left);
      UI::canvas.setTextSize(1);
      UI::canvas.setTextColor(sel ? Theme::bg() : Theme::text());
      String ssid = WiFi.SSID(i);
      if (ssid.isEmpty()) ssid = "<hidden>";
      if (ssid.length() > 18) ssid = ssid.substring(0, 17) + ">";
      UI::canvas.drawString(ssid.c_str(), 10, y + rowH / 2 - 1);

      int rssi = WiFi.RSSI(i);
      uint16_t rc = rssi > -60 ? Theme::good() : rssi > -75 ? Theme::warn() : Theme::bad();
      char buf[8]; snprintf(buf, sizeof(buf), "%d", rssi);
      UI::canvas.setTextDatum(middle_right);
      UI::canvas.setTextColor(sel ? Theme::bg() : rc);
      UI::canvas.drawString(buf, Theme::SCREEN_W - 12, y + rowH / 2 - 1);

      if (WiFi.encryptionType(i) != WIFI_AUTH_OPEN) {
        UI::canvas.drawString("*", Theme::SCREEN_W - 40, y + rowH / 2 - 1);
      }
    }
  }

  int _found = -1;
  int _sel = 0;
  unsigned long _scanStart = 0;
  WifiDetailApp* _detail = nullptr;
};
