//
// Created by Martin Edviken on 2022-07-22.
//

#include "disassembler/Cartridge.hpp"

#include <cassert>

std::vector<uint8_t> Cartridge::getProgramData() {
  if (_rawData.empty()) {
    assert(0);
  }
  auto romSize = romSizes.at(_rawData.at(CartridgeHeader::RomSize)).first * kiloMultiplyer;
  return std::vector<uint8_t>(
      _rawData.begin() + 0x150,
      _rawData.begin() + 0x150 + romSize);  // TODO: interpret this value from OPCode on 0x0100 - 0x0103
}

std::vector<uint8_t> Cartridge::getData() {
  if (_rawData.empty()) {
    assert(0);
  }
  return _rawData;
}

void Cartridge::setMemoryBankController() {
  auto type = _rawData.at(CartridgeHeader::CartridgeType);
  switch (type) {
    case 0x00: {
      NoMBC noMbc{};
      _mbc = &noMbc;
      break;
    }
    case 0x01: {
      MBC1 mbc1{};
      _mbc = &mbc1;
      break;
    }
  }
}