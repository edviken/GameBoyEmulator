//
// Created by Martin Edviken on 2022-08-27.
//

#ifndef GAMEBOYEMULATOR_REGISTER_HPP
#define GAMEBOYEMULATOR_REGISTER_HPP

#include <cstdint>

class ByteRegister {
 public:
  ByteRegister(uint8_t& flag) : _flag(flag) {}

  ByteRegister& operator=(const uint8_t rhs) {
    if (this->_value != rhs) {
      this->_value = rhs;
    }
    return *this;
  }

  ByteRegister& operator+=(const ByteRegister& rhs) {
    checkIfZeroResult(rhs);
    if (!checkIfOverflow(rhs)) {
      _value += rhs._value;
    }
    return *this;
  }

  friend ByteRegister operator+(ByteRegister& lhs, const ByteRegister& rhs) {
    lhs += rhs;
    return lhs;
  }

  void set(uint8_t value) { _value = value; }

  void reset() {
    _value = 0x00;
    _flag = 0x00;
  }

  uint8_t value() { return _value; }

 private:
  bool checkIfOverflow(const ByteRegister& rhs) {
    bool res = false;
    if (_value > 0 && rhs._value > std::numeric_limits<decltype(_value)>::max() - _value) {
      _flag |= 0x01 << 4;
      _value = 0;
      res = true;
    }
    return res;
  }

  void checkIfZeroResult(const ByteRegister& rhs) {
    if (_value == 0 && rhs._value == 0) {
      _flag |= 0x01 << 7;
    }
  }

  uint8_t _value{0x00};
  uint8_t& _flag;
};

#endif  //GAMEBOYEMULATOR_REGISTER_HPP
