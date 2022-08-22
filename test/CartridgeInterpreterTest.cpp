//
// Created by Martin Edviken on 2022-08-20.
//
#include "disassembler/Cartridge.hpp"

#include <gtest/gtest.h>

class CartridgeInterpreterTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}

  Cartridge cartridge{};
};

TEST_F(CartridgeInterpreterTest, readBinaryData) {
  std::vector<uint8_t> refData{1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
  std::vector<uint8_t> data;
  cartridge.readDataFromFile("../../test/cartridges/simpleInputData.bin");
  data = cartridge.getData();
  ASSERT_EQ(data, refData);
}