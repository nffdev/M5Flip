#pragma once
#include "../core/App.h"
#include "../core/Input.h"
#include "../ui/UI.h"
#include <WiFi.h>

class WifiDetailApp : public App {
public:
  const char* title() const override { return "Network"; }

  void setIndex(int i) { _index = i; }

  Action update() override {
    if (Input::back()) return Action::Pop;

    UI::clear();
    UI::statusBar("Network");

    String ssid = WiFi.SSID(_index);
    if (ssid.isEmpty()) ssid = "<hidden>";

    UI::canvas.setTextSize(1);
    UI::canvas.setTextDatum(top_left);
    UI::canvas.setTextColor(Theme::g_accent);
    UI::canvas.drawString(clip(ssid, 28).c_str(), 8, Theme::STATUS_H + 6);

    int y = Theme::STATUS_H + 22;
    int rssi = WiFi.RSSI(_index);
    char buf[40];

    snprintf(buf, sizeof(buf), "%d dBm", rssi);
    kv("Signal", buf, y, rssiColor(rssi)); y += 15;

    snprintf(buf, sizeof(buf), "%d", WiFi.channel(_index));
    kv("Channel", buf, y, Theme::text()); y += 15;

    kv("Security", encName(WiFi.encryptionType(_index)), y, Theme::text()); y += 15;

    kv("BSSID", WiFi.BSSIDstr(_index).c_str(), y, Theme::textDim()); y += 15;

    snprintf(buf, sizeof(buf), "%d%%", rssiToQuality(rssi));
    kv("Quality", buf, y, rssiColor(rssi)); y += 15;

    UI::footerHint("PWR: back");
    UI::flush();
    return Action::None;
  }

private:
  int _index = 0;

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

  static int rssiToQuality(int rssi) {
    if (rssi <= -100) return 0;
    if (rssi >= -50)  return 100;
    return 2 * (rssi + 100);
  }

  static const char* encName(wifi_auth_mode_t m) {
    switch (m) {
      case WIFI_AUTH_OPEN:            return "Open";
      case WIFI_AUTH_WEP:             return "WEP";
      case WIFI_AUTH_WPA_PSK:         return "WPA";
      case WIFI_AUTH_WPA2_PSK:        return "WPA2";
      case WIFI_AUTH_WPA_WPA2_PSK:    return "WPA/2";
      case WIFI_AUTH_WPA3_PSK:        return "WPA3";
      case WIFI_AUTH_WPA2_WPA3_PSK:   return "WPA2/3";
      case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2-E";
      default:                        return "?";
    }
  }
};
