//
// Created by Martin Edviken on 2022-09-12.
//
#include <cassert>

#include "disassembler/mbc/MemoryBankController.hpp"
#include "logger/Logger.hpp"

void MBC1::registerCartridgeData(std::vector<uint8_t>&& data) {
  _data = data;
}

uint8_t MBC1::read(uint16_t addr) const {
  if (_data[0] == 0 && _data.size() == 1) {
    LOG_INFO("Data from cartridge is not registered");
    assert(false);
  }
  if (addr >= firstRomBankStart && addr <= firstRomBankEnd) {
    return _data.at(addr);
  } else if (addr >= generalRomBankStart && addr <= generalRomBankEnd) {
    return _data.at(addr + ((_romBankNumber - 1) * generalRomBankStart));
  } else if (addr >= ramBankStart && addr <= ramBankEnd) {
    if (_isRamEnabled) {
      return _data.at(addr + (_ramBankNumber * ramBankSize));
    } else {
      return 0xFF;
    }
  }
  return 0;
}

void MBC1::write(uint16_t addr, uint8_t value) {
  if (addr >= 0x000 && addr <= 0x1FFF) {
    if (value == 0x0A) {
      _isRamEnabled = true;
    } else {
      _isRamEnabled = false;
    }
  } else if (addr >= romBankNumberAddrStart && addr <= romBankNumberAddrEnd) {
    switch (value) {
      case 0x00:
        _romBankNumber = 0x01;
        break;
      case 0x20:
        _romBankNumber = 0x21;
        break;
      case 0x40:
        _romBankNumber = 0x41;
        break;
      case 0x60:
        _romBankNumber = 0x61;
        break;
      default:
        _romBankNumber = value & 0x1F;  // We care only about the 5 LSB
        break;
    }
  } else if (addr >= ramBankNumberAddrStart && addr <= ramBankNumberAddrEnd) {
    if (_isRamBankingMode) {
      _ramBankNumber = value;
    } else {          // is in ROM mode
      value &= 0x03;  // We care only about the two first bits
      _romBankNumber |= (value << 3);
    }
  } else if (addr >= modeSelectAddrStart && addr <= modeSelectAddrEnd) {
    switch (value) {
      case 0x00:
        _isRamBankingMode = false;
        _romSize = 16000000u;
        _ramSize = 8000u;
        break;
      case 0x01:
        _isRamBankingMode = true;
        _romSize = 4000000u;
        _ramSize = 32000u;
        break;
    }
  }
}