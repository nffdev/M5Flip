#pragma once
#include "../core/App.h"
#include "../core/Input.h"
#include "../core/StateManager.h"
#include "UI.h"

class MenuApp : public App {
public:
  using SelectCb = void (*)(int index);

  MenuApp(const char* title,
          const char* const* labels,
          App* const* apps,
          int count,
          SelectCb onSelect = nullptr)
    : _title(title), _labels(labels), _apps(apps),
      _count(count), _onSelect(onSelect) {}

  const char* title() const override { return _title; }
  void onEnter() override { _sel = 0; }

  Action update() override {
    if (Input::next()) _sel = (_sel + 1) % _count;
    if (Input::back()) return Action::Pop;
    if (Input::ok()) {
      if (_apps && _apps[_sel]) StateManager::push(_apps[_sel]);
      else if (_onSelect)       _onSelect(_sel);
    }

    UI::clear();
    UI::statusBar(_title);
    UI::listMenu(_labels, _count, _sel);
    UI::footerHint("A: select   B: next   PWR: back");
    UI::flush();
    return Action::None;
  }

private:
  const char*        _title;
  const char* const* _labels;
  App* const*        _apps;
  int                _count;
  SelectCb           _onSelect;
  int                _sel = 0;
};
