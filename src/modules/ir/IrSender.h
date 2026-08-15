#pragma once
#include <IRsend.h>
#include "IrCodes.h"

namespace IrSender {

  static constexpr uint16_t IR_LED_PIN = 19;

  extern IRsend irsend;

  void begin();
  void send(const IrCode& code);
  void sendNec(uint32_t value);
}
