#include "UI.h"

namespace UI {

  M5Canvas canvas(&M5.Display);

  void begin() {
    canvas.setColorDepth(16);
    canvas.setPsram(true);
    canvas.createSprite(Theme::SCREEN_W, Theme::SCREEN_H);
    canvas.setTextWrap(false);
  }

  void flush() {
    canvas.pushSprite(0, 0);
  }

  void clear() {
    canvas.fillSprite(Theme::bg());
  }

  static void drawBattery(int x, int y) {
    int level = M5.Power.getBatteryLevel();
    bool charging = M5.Power.isCharging();

    const int w = 22, h = 10;
    uint16_t col = level > 20 ? Theme::text() : Theme::bad();
    if (charging) col = Theme::good();

    canvas.drawRect(x, y, w, h, col);
    canvas.fillRect(x + w, y + 3, 2, 4, col);

    int fillW = (int)((w - 4) * (level / 100.0f));
    if (fillW > 0) canvas.fillRect(x + 2, y + 2, fillW, h - 4, col);

    if (charging) {
      canvas.fillTriangle(x + 10, y + 1, x + 6, y + 6, x + 11, y + 6, Theme::bg());
      canvas.fillTriangle(x + 11, y + 4, x + 16, y + 4, x + 12, y + 9, Theme::bg());
    }
  }

  void statusBar(const char* title) {
    canvas.fillRect(0, 0, Theme::SCREEN_W, Theme::STATUS_H, Theme::bgAlt());
    canvas.drawFastHLine(0, Theme::STATUS_H, Theme::SCREEN_W, Theme::g_accent);

    canvas.setTextSize(1);
    canvas.setTextColor(Theme::g_accent);
    canvas.setTextDatum(middle_left);
    canvas.drawString(title, 6, Theme::STATUS_H / 2);

    drawBattery(Theme::SCREEN_W - 26, 3);
    canvas.setTextColor(Theme::textDim());
    canvas.setTextDatum(middle_right);
    char buf[8];
    snprintf(buf, sizeof(buf), "%d%%", M5.Power.getBatteryLevel());
    canvas.drawString(buf, Theme::SCREEN_W - 30, Theme::STATUS_H / 2);
  }

  void centerText(const char* s, int y, uint16_t color, uint8_t size) {
    canvas.setTextSize(size);
    canvas.setTextColor(color);
    canvas.setTextDatum(middle_center);
    canvas.drawString(s, Theme::SCREEN_W / 2, y);
  }

  void footerHint(const char* hint) {
    canvas.setTextSize(1);
    canvas.setTextColor(Theme::textDim());
    canvas.setTextDatum(bottom_center);
    canvas.drawString(hint, Theme::SCREEN_W / 2, Theme::SCREEN_H - 2);
  }

  void listMenu(const char* const* items, int count, int selected) {
    const int rowH = 22;
    const int top = Theme::STATUS_H + 6;
    const int usableH = Theme::SCREEN_H - top - 12;
    const int visible = usableH / rowH;

    int first = 0;
    if (count > visible) {
      first = selected - visible / 2;
      if (first < 0) first = 0;
      if (first > count - visible) first = count - visible;
    }

    for (int row = 0; row < visible && (first + row) < count; ++row) {
      int i = first + row;
      int y = top + row * rowH;
      bool sel = (i == selected);

      if (sel) {
        canvas.fillRoundRect(4, y, Theme::SCREEN_W - 8, rowH - 3, 4, Theme::g_accent);
        canvas.setTextColor(Theme::bg());
      } else {
        canvas.drawRoundRect(4, y, Theme::SCREEN_W - 8, rowH - 3, 4, Theme::line());
        canvas.setTextColor(Theme::text());
      }
      canvas.setTextSize(1);
      canvas.setTextDatum(middle_left);
      canvas.drawString(items[i], 14, y + (rowH - 3) / 2);
    }

    if (count > visible) {
      int trackH = visible * rowH;
      int barH = trackH * visible / count;
      int barY = top + trackH * first / count;
      canvas.fillRoundRect(Theme::SCREEN_W - 3, barY, 2, barH, 1, Theme::g_accent);
    }
  }
}
