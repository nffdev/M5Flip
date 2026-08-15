#pragma once
#include "../core/App.h"
#include "../core/Input.h"
#include "../ui/UI.h"
#include <NimBLEDevice.h>

class BleScanApp : public App {
public:
  const char* title() const override { return "BLE Scan"; }

  void onEnter() override {
    _sel = 0;
    if (!NimBLEDevice::isInitialized()) NimBLEDevice::init("");
    _scan = NimBLEDevice::getScan();
    _scan->setActiveScan(true);
    _scan->setInterval(100);
    _scan->setWindow(90);
    _scan->start(0, false, false);
  }
  void onExit() override { if (_scan) _scan->stop(); }

  Action update() override {
    if (Input::back()) return Action::Pop;

    NimBLEScanResults res = _scan->getResults();
    int n = res.getCount();
    if (Input::next() && n > 0) _sel = (_sel + 1) % n;

    UI::clear();
    UI::statusBar("BLE Scan");

    if (n == 0) {
      UI::centerText("Scanning...", 68, Theme::textDim(), 2);
    } else {
      const int rowH = 20, top = Theme::STATUS_H + 4;
      int visible = (Theme::SCREEN_H - top - 12) / rowH;
      int first = _sel - visible / 2;
      if (first < 0) first = 0;
      if (first > n - visible) first = n - visible;
      if (first < 0) first = 0;

      for (int row = 0; row < visible && first + row < n; ++row) {
        int i = first + row, y = top + row * rowH;
        const NimBLEAdvertisedDevice* d = res.getDevice(i);
        bool sel = (i == _sel);
        if (sel) UI::canvas.fillRoundRect(4, y, Theme::SCREEN_W - 8, rowH - 2, 3, Theme::g_accent);

        String label = d->getName().c_str();
        if (label.isEmpty()) label = d->getAddress().toString().c_str();
        if (label.length() > 18) label = label.substring(0, 17) + ">";

        UI::canvas.setTextSize(1);
        UI::canvas.setTextDatum(middle_left);
        UI::canvas.setTextColor(sel ? Theme::bg() : Theme::text());
        UI::canvas.drawString(label.c_str(), 10, y + rowH / 2 - 1);

        char buf[8]; snprintf(buf, sizeof(buf), "%d", d->getRSSI());
        UI::canvas.setTextDatum(middle_right);
        UI::canvas.setTextColor(sel ? Theme::bg() : Theme::textDim());
        UI::canvas.drawString(buf, Theme::SCREEN_W - 12, y + rowH / 2 - 1);
      }
    }
    UI::footerHint("B: next   PWR: back");
    UI::flush();
    return Action::None;
  }

private:
  NimBLEScan* _scan = nullptr;
  int _sel = 0;
};
