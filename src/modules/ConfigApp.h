#pragma once
#include "../core/App.h"
#include "../core/Input.h"
#include "../core/Settings.h"
#include "../ui/UI.h"

class ConfigApp : public App {
public:
  const char* title() const override { return "Config"; }

  void onEnter() override { _sel = 0; }
  void onExit() override { Settings::save(); }

  Action update() override {
    if (Input::back()) return Action::Pop;
    if (Input::next()) _sel = (_sel + 1) % kRows;
    if (Input::ok()) {
      changeValue(_sel);
      Settings::apply();
      Settings::save();
    }

    UI::clear();
    UI::statusBar("Config");

    const int top = Theme::STATUS_H + 8;
    drawRow(0, "Accent",     Settings::kAccentNames[Settings::data.accent], top + 0 * kRowH);
    drawRow(1, "Brightness", brightStr(),                                    top + 1 * kRowH);
    drawRow(2, "Rotation",   rotStr(),                                       top + 2 * kRowH);

    UI::footerHint("A: change   B: next   PWR: back");
    UI::flush();
    return Action::None;
  }

private:
  static constexpr int kRows = 3;
  static constexpr int kRowH = 26;
  int _sel = 0;
  char _buf[8];

  void changeValue(int row) {
    switch (row) {
      case 0: Settings::data.accent = (Settings::data.accent + 1) % Settings::kAccentCount; break;
      case 1: Settings::data.brightness = (Settings::data.brightness + 1) % 5; break;
      case 2: Settings::data.rotation = Settings::data.rotation == 1 ? 3 : 1; break;
    }
  }

  const char* brightStr() {
    snprintf(_buf, sizeof(_buf), "%d%%", Settings::brightnessPct());
    return _buf;
  }

  const char* rotStr() {
    return Settings::data.rotation == 1 ? "Normal" : "Flipped";
  }

  void drawRow(int row, const char* label, const char* value, int y) {
    bool sel = (row == _sel);
    if (sel) {
      UI::canvas.fillRoundRect(4, y, Theme::SCREEN_W - 8, kRowH - 3, 4, Theme::g_accent);
      UI::canvas.setTextColor(Theme::bg());
    } else {
      UI::canvas.drawRoundRect(4, y, Theme::SCREEN_W - 8, kRowH - 3, 4, Theme::line());
      UI::canvas.setTextColor(Theme::text());
    }
    UI::canvas.setTextSize(1);
    UI::canvas.setTextDatum(middle_left);
    UI::canvas.drawString(label, 14, y + (kRowH - 3) / 2);

    UI::canvas.setTextDatum(middle_right);
    if (!sel) UI::canvas.setTextColor(Theme::g_accent);
    UI::canvas.drawString(value, Theme::SCREEN_W - 16, y + (kRowH - 3) / 2);
  }
};
