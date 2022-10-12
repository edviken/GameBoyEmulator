//
// Created by Martin Edviken on 2022-09-12.
//

#ifndef GAMEBOYEMULATOR_MEMORYBANKCONTROLLER_HPP
#define GAMEBOYEMULATOR_MEMORYBANKCONTROLLER_HPP

#include <cstdint>
#include <vector>
#include "cpu/register/Register.hpp"

/**
 * @brief Interface for the different MBC types
 * A ROM bank is 16KBytes in size
 */
class MemoryBankController {
 public:
  MemoryBankController() = default;

  virtual uint8_t read(uint16_t addr) const = 0;
  virtual void write(uint16_t addr, uint8_t value) = 0;
  virtual void registerCartridgeData(std::vector<uint8_t>&& data) = 0;
};

/**
 * @brief No memory bank controller
 * Containts up to 32KBytes of ROM and/or 8KBytes of RAM
 */
class NoMBC : public MemoryBankController {
 public:
  NoMBC() = default;

  uint8_t read(uint16_t addr) const override { return 0; };

  void write(uint16_t addr, uint8_t value) override{};

  void registerCartridgeData(std::vector<uint8_t>&& data) override{};
};

/**
 * @brief Type MBC1
 * max 2MByte ROM (125 banks) and/or up to 32KByte RAM
 */
class MBC1 : public MemoryBankController {
  // To read: https://retrocomputing.stackexchange.com/questions/11732/how-does-the-gameboys-memory-bank-switching-work#comment36213_11732
 public:
  MBC1() = default;

  uint8_t read(uint16_t addr) const override;

  void write(uint16_t addr, uint8_t value) override;

  void registerCartridgeData(std::vector<uint8_t>&& data) override;

  bool isRamEnabled() { return _isRamEnabled; }

  uint8_t getRomBankNumber() { return _romBankNumber; }
  uint8_t getRamBankNumber() { return _ramBankNumber; }

  uint32_t getRomSize() { return _romSize; }

  uint32_t getRamSize() { return _ramSize; }

 private:
  bool _isRamBankingMode = false;  ///< Mode 0 (Rom mode) or mode 1 (Ram mode)
  bool _isRamEnabled = false;
  uint8_t _romBankNumber = 1;
  uint8_t _ramBankNumber = 0;
  uint32_t _romSize = 16000000u;  ///< Size in Bytes
  uint32_t _ramSize = 8000u;      ///< Size in Bytes

  // Write only address ranges
  static constexpr uint16_t romBankNumberAddrStart = 0x2000u;
  static constexpr uint16_t romBankNumberAddrEnd = 0x3FFFu;
  static constexpr uint16_t modeSelectAddrStart = 0x6000u;
  static constexpr uint16_t modeSelectAddrEnd = 0x7FFFu;
  static constexpr uint16_t ramBankNumberAddrStart = 0x4000;
  static constexpr uint16_t ramBankNumberAddrEnd = 0x5FFF;

  // Read/Write address ranges
  static constexpr uint16_t ramBankStart = 0xA000;
  static constexpr uint16_t ramBankEnd = 0xBFFF;
  static constexpr uint16_t ramBankSize = 0x2000;

  // Read only address ranges
  static constexpr uint16_t firstRomBankStart = 0x0000u;
  static constexpr uint16_t firstRomBankEnd = 0x3FFFu;
  static constexpr uint16_t generalRomBankStart = 0x4000u;
  static constexpr uint16_t generalRomBankEnd = 0x7FFFu;

  std::vector<uint8_t> _data{0u};
};

#endif  //GAMEBOYEMULATOR_MEMORYBANKCONTROLLER_HPP
