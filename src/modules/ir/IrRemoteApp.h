#pragma once
#include "../../core/App.h"
#include "../../core/Input.h"
#include "../../ui/UI.h"
#include "IrCodes.h"
#include "IrSender.h"

class IrRemoteApp : public App {
public:
  const char* title() const override { return "IR Remote"; }

  void onEnter() override {
    _brand = 0;
    _sel = 0;
    _pickingBrand = true;
    _lastSent = 0;
  }

  Action update() override {
    if (_pickingBrand) return updateBrandPick();
    return updateRemote();
  }

private:
  Action updateBrandPick() {
    if (Input::back()) return Action::Pop;
    if (Input::next()) _brand = (_brand + 1) % kBrandCount;
    if (Input::ok()) { _pickingBrand = false; _sel = 0; }

    const char* names[kBrandCount];
    for (uint8_t i = 0; i < kBrandCount; ++i) names[i] = kBrands[i].name;

    UI::clear();
    UI::statusBar("IR Remote");
    UI::listMenu(names, kBrandCount, _brand);
    UI::footerHint("A: open   B: next   PWR: back");
    UI::flush();
    return Action::None;
  }

  Action updateRemote() {
    const IrBrand& b = kBrands[_brand];

    if (Input::back()) { _pickingBrand = true; return Action::None; }
    if (Input::next()) _sel = (_sel + 1) % b.count;
    if (Input::ok()) {
      IrSender::send(b.codes[_sel]);
      _lastSent = millis();
    }

    const char* labels[8];
    uint8_t n = b.count > 8 ? 8 : b.count;
    for (uint8_t i = 0; i < n; ++i) labels[i] = b.codes[i].label;

    UI::clear();
    UI::statusBar(b.name);
    UI::listMenu(labels, n, _sel);

    if (millis() - _lastSent < 400) {
      UI::centerText("SENT", Theme::SCREEN_H - 28, Theme::good(), 2);
    }
    UI::footerHint("A: send   B: next   PWR: brands");
    UI::flush();
    return Action::None;
  }

  uint8_t _brand = 0;
  uint8_t _sel = 0;
  bool _pickingBrand = true;
  unsigned long _lastSent = 0;
};
