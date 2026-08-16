#include <M5Unified.h>
#include "src/ui/Theme.h"
#include "src/ui/UI.h"
#include "src/ui/MenuApp.h"
#include "src/core/StateManager.h"
#include "src/core/Settings.h"

#include "src/modules/WifiApp.h"
#include "src/modules/WifiDetailApp.h"
#include "src/modules/BleApp.h"
#include "src/modules/BleDetailApp.h"
#include "src/modules/SystemApp.h"
#include "src/modules/ConfigApp.h"
#include "src/modules/clock/ClockSetApp.h"
#include "src/modules/clock/ClockApp.h"
#include "src/modules/ir/IrSender.h"
#include "src/modules/ir/IrRemoteApp.h"
#include "src/modules/ir/TvBGoneApp.h"

WifiScanApp   wifiScan;
WifiDetailApp wifiDetail;
BleScanApp    bleScan;
BleDetailApp  bleDetail;
IrRemoteApp   irRemote;
TvBGoneApp    tvbGone;
SystemApp     systemApp;
ConfigApp     configApp;
ClockSetApp   clockSet;
ClockApp      clockApp;

const char* const kWifiLabels[] = { "Scan networks" };
App* const        kWifiApps[]   = { &wifiScan };
MenuApp wifiMenu("WiFi", kWifiLabels, kWifiApps, 1);

const char* const kBleLabels[] = { "Scan devices" };
App* const        kBleApps[]   = { &bleScan };
MenuApp bleMenu("Bluetooth", kBleLabels, kBleApps, 1);

const char* const kIrLabels[] = { "Remote", "TV-B-Gone" };
App* const        kIrApps[]   = { &irRemote, &tvbGone };
MenuApp irMenu("Infrared", kIrLabels, kIrApps, 2);

const char* const kMainLabels[] = { "WiFi", "Bluetooth", "Infrared", "Clock", "System", "Config" };
App* const        kMainApps[]   = { &wifiMenu, &bleMenu, &irMenu, &clockApp, &systemApp, &configApp };
MenuApp mainMenu("M5Flip", kMainLabels, kMainApps, 6);

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  Settings::load();
  Settings::apply();

  UI::begin();
  IrSender::begin();

  wifiScan.setDetail(&wifiDetail);
  bleScan.setDetail(&bleDetail);
  clockApp.setEditor(&clockSet);

  StateManager::begin(&mainMenu);
}

void loop() {
  M5.update();
  StateManager::tick();
  delay(10);
}
