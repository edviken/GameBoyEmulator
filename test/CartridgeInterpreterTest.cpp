//
// Created by Martin Edviken on 2022-08-20.
//
#include "disassembler/Cartridge.hpp"
#include "root_path.h"

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
  std::string root_path = PROJECT_ROOT_STRING;
  std::string file_path = root_path + "/test/cartridges/simpleInputData.bin";
  cartridge.readDataFromFile(file_path);
  data = cartridge.getData();
  ASSERT_EQ(data, refData);
}