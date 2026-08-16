#pragma once
#include "../../core/App.h"
#include "../../core/Input.h"
#include "../../core/StateManager.h"
#include "../../ui/UI.h"
#include "ClockSetApp.h"
#include <M5Unified.h>

class ClockApp : public App {
public:
  const char* title() const override { return "Clock"; }

  void setEditor(ClockSetApp* e) { _editor = e; }

  Action update() override {
    if (Input::back()) return Action::Pop;
    if (Input::ok() && _editor) StateManager::push(_editor);

    auto t = M5.Rtc.getDateTime();

    UI::clear();
    UI::statusBar("Clock");

    char buf[16];
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d",
             t.time.hours, t.time.minutes, t.time.seconds);
    UI::centerText(buf, 58, Theme::text(), 4);

    int wd = t.date.weekDay;
    if (wd < 0 || wd > 6) wd = 0;
    snprintf(buf, sizeof(buf), "%s %02d/%02d/%04d",
             kDays[wd], t.date.date, t.date.month, t.date.year);
    UI::centerText(buf, 96, Theme::g_accent, 1);

    UI::footerHint("A: set time   PWR: back");
    UI::flush();
    return Action::None;
  }

private:
  ClockSetApp* _editor = nullptr;

  static constexpr const char* kDays[7] =
    { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
};
