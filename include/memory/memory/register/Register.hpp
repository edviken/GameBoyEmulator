//
// Created by Martin Edviken on 2022-08-08.
//

#ifndef GAMEBOYEMULATOR_REGISTER_HPP
#define GAMEBOYEMULATOR_REGISTER_HPP

#include <cstdint>

template <class T>
class RegisterBase {
 public:
  RegisterBase() = default;
};

class HalfWordReg : RegisterBase<int16_t> {};

class ByteReg : RegisterBase<int8_t> {};

#endif  //GAMEBOYEMULATOR_REGISTER_HPP
