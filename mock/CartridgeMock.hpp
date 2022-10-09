//
// Created by Martin Edviken on 2022-09-24.
//

#ifndef GAMEBOYEMULATOR_CARTRIDGEMOCK_HPP
#define GAMEBOYEMULATOR_CARTRIDGEMOCK_HPP

#include <gmock/gmock.h>
#include "disassembler/CartridgeInterface.hpp"

class CartridgeMock : public CartridgeInterface {
  MOCK_METHOD(std::vector<uint8_t>, getProgramData, (), (override));
  MOCK_METHOD(std::vector<uint8_t>, getData, (), (override));
};

#endif  //GAMEBOYEMULATOR_CARTRIDGEMOCK_HPP
