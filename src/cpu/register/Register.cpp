//
// Created by Martin Edviken on 2022-08-27.
//
#include "cpu/register/Register.hpp"

ByteRegister& ByteRegister::operator+=(const WordRegister& rhs) {
  auto addValue = static_cast<uint8_t>(rhs.value());
  checkIfZeroResult(addValue);
  if (!checkIfOverflow(addValue)) {
    _value += addValue;
  }
  return *this;
}