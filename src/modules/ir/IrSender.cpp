#include "IrSender.h"

namespace IrSender {

  IRsend irsend(IR_LED_PIN);

  void begin() {
    irsend.begin();
  }

  void send(const IrCode& code) {
    switch (code.proto) {
      case IrProto::NEC:     irsend.sendNEC(code.value, code.bits);     break;
      case IrProto::SONY:    irsend.sendSony(code.value, code.bits, 2); break;
      case IrProto::SAMSUNG: irsend.sendSAMSUNG(code.value, code.bits); break;
      case IrProto::RC5:     irsend.sendRC5(code.value, code.bits);     break;
      case IrProto::RAW:     break;
    }
  }

  void sendNec(uint32_t value) {
    irsend.sendNEC(value, 32);
  }
}
