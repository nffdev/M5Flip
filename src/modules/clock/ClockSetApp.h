#pragma once
#include "../../core/App.h"
#include "../../core/Input.h"
#include "../../ui/UI.h"
#include <M5Unified.h>

class ClockSetApp : public App {
public:
  const char* title() const override { return "Set Time"; }

  void onEnter() override {
    auto t = M5.Rtc.getDateTime();
    _hh = t.time.hours;
    _mm = t.time.minutes;
    _dd = t.date.date;
    _mo = t.date.month;
    _yy = t.date.year;
    _field = 0;
  }

  Action update() override {
    if (Input::back()) {
      commit();
      return Action::Pop;
    }
    if (Input::next()) _field = (_field + 1) % kFields;
    if (Input::ok()) increment();

    UI::clear();
    UI::statusBar("Set Time");

    char buf[16];
    snprintf(buf, sizeof(buf), "%02d:%02d", _hh, _mm);
    UI::centerText(buf, 50, Theme::text(), 4);

    snprintf(buf, sizeof(buf), "%02d/%02d/%04d", _dd, _mo, _yy);
    UI::centerText(buf, 84, Theme::text(), 2);

    drawUnderline();

    UI::footerHint("A: +   B: field   PWR: save");
    UI::flush();
    return Action::None;
  }

private:
  static constexpr int kFields = 5;
  int _hh = 0, _mm = 0, _dd = 1, _mo = 1, _yy = 2025;
  int _field = 0;

  void increment() {
    switch (_field) {
      case 0: _hh = (_hh + 1) % 24; break;
      case 1: _mm = (_mm + 1) % 60; break;
      case 2: _dd = _dd % daysInMonth(_mo, _yy) + 1; break;
      case 3: _mo = _mo % 12 + 1; if (_dd > daysInMonth(_mo, _yy)) _dd = daysInMonth(_mo, _yy); break;
      case 4: _yy = _yy >= 2099 ? 2020 : _yy + 1; break;
    }
  }

  void commit() {
    m5::rtc_datetime_t dt;
    dt.time.hours   = _hh;
    dt.time.minutes = _mm;
    dt.time.seconds = 0;
    dt.date.date    = _dd;
    dt.date.month   = _mo;
    dt.date.year    = _yy;
    dt.date.weekDay = weekDay(_yy, _mo, _dd);
    M5.Rtc.setDateTime(&dt);
  }

  static int weekDay(int y, int m, int d) {
    static const int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    if (m < 3) y -= 1;
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
  }

  void drawUnderline() {
    struct Seg { int cx, y, w; };
    static const Seg time[] = { { 96, 74, 44 }, { 144, 74, 44 } };
    static const Seg date[] = { { 78, 100, 26 }, { 120, 100, 26 }, { 176, 100, 46 } };

    Seg s;
    if (_field < 2) s = time[_field];
    else            s = date[_field - 2];

    UI::canvas.fillRect(s.cx - s.w / 2, s.y, s.w, 3, Theme::g_accent);
  }

  static int daysInMonth(int m, int y) {
    static const int d[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)) return 29;
    return d[m - 1];
  }
};
