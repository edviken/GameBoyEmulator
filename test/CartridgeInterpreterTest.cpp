//
// Created by Martin Edviken on 2022-08-20.
//
#include "disassembler/Cartridge.hpp"
#include "generated/root_path.h"

#include <gtest/gtest.h>

class CartridgeInterpreterTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}

  std::string root_path = PROJECT_ROOT_STRING;
  std::string file_path = root_path + "/test/cartridges/simpleInputData.bin";
  Loader loader{file_path};
  Cartridge cartridge{loader};
};

TEST_F(CartridgeInterpreterTest, readBinaryData) {
  std::vector<uint8_t> refData{1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
  std::vector<uint8_t> data;
  data = cartridge.getData();
  ASSERT_EQ(data, refData);
}

TEST_F(CartridgeInterpreterTest, ReadOutHeader) {
  std::array<uint8_t, 0x14F> input{0};
  input.at(0x100) = 0x00;  // EntryPoint
  input.at(0x104) = 0x00;  // NintendoLogo
  input.at(0x134) = 0x00;  // Title
  input.at(0x13F) = 0x00;  // ManufacturerCode
  input.at(0x143) = 0x00;  // CGBFlag
  input.at(0x144) = 0x00;  // NewLicesnseCode
  input.at(0x146) = 0x00;  //SBGFlag
  input.at(0x147) = 0x00;  //CartridgeType
  input.at(0x148) = 0x01;  // RomSize
  input.at(0x149) = 00;    // RamSize
  input.at(0x14A) = 0x00;  // DestinationCode
  input.at(0x14B) = 0x00;  // OldLicenseCode
  input.at(0x14C) = 0x00;  // VersionNumber
  input.at(0x14D) = 0x00;  // HeaderChecksum
  input.at(0x14E) = 0x00;  // GlobalChecksum
}