//
// Created by Martin Edviken on 2022-09-24.
//

#ifndef GAMEBOYEMULATOR_LOADERMOCK_HPP
#define GAMEBOYEMULATOR_LOADERMOCK_HPP

#include <gmock/gmock.h>
#include <vector>
#include "disassembler/LoaderInterface.hpp"

class LoaderMock : public LoaderInterface {
 public:
  MOCK_METHOD(std::vector<uint8_t>, readDataFromFile, (), (override));
};

#endif  //GAMEBOYEMULATOR_LOADERMOCK_HPP
