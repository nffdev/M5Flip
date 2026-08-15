#pragma once
#include "../../core/App.h"
#include "../../core/Input.h"
#include "../../ui/UI.h"
#include "IrCodes.h"
#include "IrSender.h"

class TvBGoneApp : public App {
public:
  const char* title() const override { return "TV-B-Gone"; }

  void onEnter() override {
    _running = false;
    _index = 0;
    _lastStep = 0;
  }
  void onExit() override { _running = false; }

  Action update() override {
    if (Input::back()) {
      if (_running) { _running = false; }
      else return Action::Pop;
    }

    if (Input::ok() && !_running) {
      _running = true;
      _index = 0;
      _lastStep = 0;
    }

    if (_running && millis() - _lastStep > 120) {
      if (_index < kTvBGoneCount) {
        IrSender::sendNec(kTvBGonePower[_index]);
        _index++;
        _lastStep = millis();
      } else {
        _running = false;
      }
    }

    UI::clear();
    UI::statusBar("TV-B-Gone");

    if (_running) {
      UI::centerText("Sending...", 52, Theme::text(), 2);
      drawProgress();
    } else if (_index >= kTvBGoneCount && _index > 0) {
      UI::centerText("Done", 60, Theme::good(), 3);
    } else {
      UI::centerText("Power off TVs", 50, Theme::text(), 2);
      UI::centerText("Point at TV, press A", 78, Theme::textDim(), 1);
    }

    UI::footerHint(_running ? "PWR: cancel" : "A: start   PWR: back");
    UI::flush();
    return Action::None;
  }

private:
  void drawProgress() {
    int barW = 180, barH = 12;
    int x = (Theme::SCREEN_W - barW) / 2, y = 80;
    UI::canvas.drawRoundRect(x, y, barW, barH, 3, Theme::line());
    int fill = (int)((barW - 4) * ((float)_index / kTvBGoneCount));
    if (fill > 0) UI::canvas.fillRoundRect(x + 2, y + 2, fill, barH - 4, 2, Theme::g_accent);

    char buf[16];
    snprintf(buf, sizeof(buf), "%d / %d", _index, kTvBGoneCount);
    UI::centerText(buf, y + barH + 12, Theme::textDim(), 1);
  }

  bool _running = false;
  uint8_t _index = 0;
  unsigned long _lastStep = 0;
};
