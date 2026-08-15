#include "StateManager.h"

namespace StateManager {

  static App* stack[MAX_DEPTH];
  static int  depth = 0;

  void begin(App* root) {
    depth = 0;
    stack[depth++] = root;
    root->onEnter();
  }

  void push(App* app) {
    if (depth >= MAX_DEPTH) return;
    stack[depth++] = app;
    app->onEnter();
  }

  void pop() {
    if (depth <= 1) return;
    stack[--depth]->onExit();
  }

  App* current() {
    return depth > 0 ? stack[depth - 1] : nullptr;
  }

  void tick() {
    App* app = current();
    if (!app) return;
    Action a = app->update();
    if (a == Action::Pop) pop();
  }
}
