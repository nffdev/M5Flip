#pragma once
#include "../core/App.h"
#include "../core/Input.h"
#include "../ui/UI.h"

class SystemApp : public App {
public:
  const char* title() const override { return "System"; }

  Action update() override {
    if (Input::back()) return Action::Pop;

    float ax, ay, az;
    M5.Imu.getAccel(&ax, &ay, &az);

    UI::clear();
    UI::statusBar("System");

    int y = Theme::STATUS_H + 8;
    char buf[32];
    snprintf(buf, sizeof(buf), "%d%%  %dmV", M5.Power.getBatteryLevel(),
             M5.Power.getBatteryVoltage());
    kv("Battery", buf, y); y += 18;

    kv("Charging", M5.Power.isCharging() ? "yes" : "no", y); y += 18;

    snprintf(buf, sizeof(buf), "%.2f %.2f %.2f", ax, ay, az);
    kv("Accel", buf, y); y += 18;

    unsigned long s = millis() / 1000;
    snprintf(buf, sizeof(buf), "%02lu:%02lu:%02lu", s / 3600, (s / 60) % 60, s % 60);
    kv("Uptime", buf, y); y += 18;

    snprintf(buf, sizeof(buf), "%u KB", ESP.getFreeHeap() / 1024);
    kv("Free heap", buf, y); y += 18;

    UI::footerHint("PWR: back");
    UI::flush();
    return Action::None;
  }

private:
  void kv(const char* k, const char* v, int y) {
    UI::canvas.setTextSize(1);
    UI::canvas.setTextDatum(middle_left);
    UI::canvas.setTextColor(Theme::textDim());
    UI::canvas.drawString(k, 10, y + 6);
    UI::canvas.setTextColor(Theme::text());
    UI::canvas.setTextDatum(middle_right);
    UI::canvas.drawString(v, Theme::SCREEN_W - 10, y + 6);
  }
};
