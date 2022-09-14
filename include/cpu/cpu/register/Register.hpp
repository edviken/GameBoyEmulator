//
// Created by Martin Edviken on 2022-08-27.
//

#ifndef GAMEBOYEMULATOR_REGISTER_HPP
#define GAMEBOYEMULATOR_REGISTER_HPP

#include <cstdint>
#include <limits>
#include <utility>

class WordRegister;  ///< Forward declaration

template <class T>
class Register {
 public:
  virtual void set(const T value) = 0;
  virtual T value() const = 0;
  virtual void reset() = 0;
};

class ByteRegister : public Register<uint8_t> {
 public:
  ByteRegister(uint8_t& flag) : _flag(flag) {}

  ByteRegister& operator=(const uint8_t rhs) {
    if (this->_value != rhs) {
      this->_value = rhs;
    }
    return *this;
  }

  ByteRegister& operator+=(const ByteRegister& rhs) {
    checkIfZeroResult(rhs._value);
    if (!checkIfOverflow(rhs._value)) {
      _value += rhs._value;
    }
    return *this;
  }

  ByteRegister& operator+=(const WordRegister& rhs);

  friend ByteRegister operator+(ByteRegister& lhs, const ByteRegister& rhs) {
    lhs += rhs;
    return lhs;
  }

  void set(const uint8_t value) override { _value = value; }

  uint8_t value() const override { return _value; }

  void reset() override {
    _value = 0x00;
    _flag = 0x00;
  }

 private:
  bool checkIfOverflow(const uint8_t& rhs) {
    bool res = false;
    if (_value > 0 && rhs > std::numeric_limits<decltype(_value)>::max() - _value) {
      _flag |= 0x01 << 4;
      _value = 0;
      res = true;
    }
    return res;
  }

  void checkIfZeroResult(const uint8_t& rhs) {
    if (_value == 0 && rhs == 0) {
      _flag |= 0x01 << 7;
    }
  }

  uint8_t _value{0x00};
  uint8_t& _flag;
};

class WordRegister : public Register<uint16_t> {
 public:
  WordRegister(ByteRegister& high, ByteRegister& low) : _high(high), _low(low) {}

  WordRegister& operator=(const uint16_t& rhs) {
    set(rhs);
    return *this;
  }

  void set(uint16_t value) override {
    _high = (value & 0xFF00) >> 8;
    _low = value & 0x00FF;
  }

  uint16_t value() const override { return _high.value() << 8 | _low.value(); }

  void reset() override {
    _high.reset();
    _low.reset();
  }

 private:
  ByteRegister& _high;
  ByteRegister& _low;
};

class FlagRegister : public Register<uint8_t> {
 public:
  enum class Flag : uint8_t { C = 4, H, N, Z, NbrOfBits };

  FlagRegister() = default;

  void set(uint8_t value) override { _value = value; }

  void set(Flag f) { _value |= (0x01 << static_cast<std::underlying_type_t<Flag>>(f)); }

  void reset() override { _value = 0; }

  uint8_t value() const override { return _value; }

 private:
  uint8_t _value;
};

#endif  //GAMEBOYEMULATOR_REGISTER_HPP
