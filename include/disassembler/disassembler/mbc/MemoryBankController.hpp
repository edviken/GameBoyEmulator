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
 */
class MemoryBankController {
 public:
  MemoryBankController() = default;

  virtual uint8_t read() const = 0;
  virtual void write() = 0;

 private:
  /// Memory that hold Read Only data
  std::vector<uint8_t> _rom{0};

  /// Memory that hold Read/Write data
  std::vector<uint8_t> _ram{0};
};

/**
 * @brief Type MBC1
 */
class MBC1 : public MemoryBankController {
 public:
  MBC1() = default;

 private:
  WordRegister _romBank;
  WordRegister _ramBank;
  bool _mode{0};
};

#endif  //GAMEBOYEMULATOR_MEMORYBANKCONTROLLER_HPP
