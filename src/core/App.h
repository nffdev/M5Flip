#pragma once
#include <M5Unified.h>

enum class Action {
  None,
  Pop,
};

class App {
public:
  virtual ~App() {}
  virtual const char* title() const = 0;
  virtual void onEnter() {}
  virtual void onExit()  {}
  virtual Action update() = 0;
};
