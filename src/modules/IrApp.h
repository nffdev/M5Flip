#pragma once
#include "../core/App.h"
#include "../core/Input.h"
#include "../ui/UI.h"

class IrApp : public App {
public:
  const char* title() const override { return "IR Remote"; }

  void onEnter() override {
    _sel = 0;
  }

  Action update() override {
    if (Input::back()) return Action::Pop;
    if (Input::next()) _sel = (_sel + 1) % kCount;
    if (Input::ok()) {
      _lastSent = millis();
      transmit(_sel);
    }

    UI::clear();
    UI::statusBar("IR Remote");

    const char* codes[kCount] = { "TV Power", "Volume +", "Volume -", "Channel +" };
    UI::listMenu(codes, kCount, _sel);

    if (millis() - _lastSent < 500) {
      UI::centerText("SENT", Theme::SCREEN_H - 30, Theme::good(), 2);
    }
    UI::footerHint("A: send   B: next   PWR: back");
    UI::flush();
    return Action::None;
  }

private:
  static constexpr int kCount = 4;
  int _sel = 0;
  unsigned long _lastSent = 0;

  void transmit(int index) {
    (void)index;
  }
};
