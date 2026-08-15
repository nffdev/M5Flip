#pragma once
#include <Arduino.h>

enum class IrProto {
  NEC,
  SONY,
  SAMSUNG,
  RC5,
  RAW,
};

struct IrCode {
  const char* label;
  IrProto     proto;
  uint64_t    value;
  uint16_t    bits;
};

struct IrBrand {
  const char*    name;
  const IrCode*  codes;
  uint8_t        count;
};

static const IrCode kSamsungCodes[] = {
  { "Power",    IrProto::SAMSUNG, 0xE0E040BF, 32 },
  { "Vol +",    IrProto::SAMSUNG, 0xE0E0E01F, 32 },
  { "Vol -",    IrProto::SAMSUNG, 0xE0E0D02F, 32 },
  { "Chan +",   IrProto::SAMSUNG, 0xE0E048B7, 32 },
  { "Chan -",   IrProto::SAMSUNG, 0xE0E008F7, 32 },
  { "Mute",     IrProto::SAMSUNG, 0xE0E0F00F, 32 },
};

static const IrCode kSonyCodes[] = {
  { "Power",    IrProto::SONY, 0xA90, 12 },
  { "Vol +",    IrProto::SONY, 0x490, 12 },
  { "Vol -",    IrProto::SONY, 0xC90, 12 },
  { "Chan +",   IrProto::SONY, 0x090, 12 },
  { "Chan -",   IrProto::SONY, 0x890, 12 },
  { "Mute",     IrProto::SONY, 0x290, 12 },
};

static const IrCode kLgCodes[] = {
  { "Power",    IrProto::NEC, 0x20DF10EF, 32 },
  { "Vol +",    IrProto::NEC, 0x20DF40BF, 32 },
  { "Vol -",    IrProto::NEC, 0x20DFC03F, 32 },
  { "Chan +",   IrProto::NEC, 0x20DF00FF, 32 },
  { "Chan -",   IrProto::NEC, 0x20DF807F, 32 },
  { "Mute",     IrProto::NEC, 0x20DF906F, 32 },
};

static const IrBrand kBrands[] = {
  { "Samsung", kSamsungCodes, sizeof(kSamsungCodes) / sizeof(kSamsungCodes[0]) },
  { "Sony",    kSonyCodes,    sizeof(kSonyCodes)    / sizeof(kSonyCodes[0])    },
  { "LG",      kLgCodes,      sizeof(kLgCodes)      / sizeof(kLgCodes[0])      },
};

static const uint8_t kBrandCount = sizeof(kBrands) / sizeof(kBrands[0]);

static const uint32_t kTvBGonePower[] = {
  0xE0E040BF,
  0x20DF10EF,
  0x10EF08F7,
  0x2FD48B7,
  0x1FE48B7,
  0x57E3C03F,
  0x4CB340BF,
  0xC1AA09F6,
  0x8166817E,
  0xC00C5EA1,
};

static const uint8_t kTvBGoneCount = sizeof(kTvBGonePower) / sizeof(kTvBGonePower[0]);
