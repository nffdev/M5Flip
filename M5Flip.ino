#include <M5Unified.h>
#include "src/ui/Theme.h"
#include "src/ui/UI.h"
#include "src/ui/MenuApp.h"
#include "src/core/StateManager.h"

#include "src/modules/WifiApp.h"
#include "src/modules/BleApp.h"
#include "src/modules/IrApp.h"
#include "src/modules/SystemApp.h"

WifiScanApp wifiScan;
BleScanApp  bleScan;
IrApp       irApp;
SystemApp   systemApp;

const char* const kWifiLabels[] = { "Scan networks" };
App* const        kWifiApps[]   = { &wifiScan };
MenuApp wifiMenu("WiFi", kWifiLabels, kWifiApps, 1);

const char* const kBleLabels[] = { "Scan devices" };
App* const        kBleApps[]   = { &bleScan };
MenuApp bleMenu("Bluetooth", kBleLabels, kBleApps, 1);

const char* const kMainLabels[] = { "WiFi", "Bluetooth", "Infrared", "System" };
App* const        kMainApps[]   = { &wifiMenu, &bleMenu, &irApp, &systemApp };
MenuApp mainMenu("M5Flip", kMainLabels, kMainApps, 4);

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setRotation(1);

  UI::begin();
  StateManager::begin(&mainMenu);
}

void loop() {
  M5.update();
  StateManager::tick();
  delay(10);
}
