#pragma once
#include "App.h"

namespace StateManager {
  constexpr int MAX_DEPTH = 8;

  void begin(App* root);
  void push(App* app);
  void pop();
  App* current();
  void tick();
}
