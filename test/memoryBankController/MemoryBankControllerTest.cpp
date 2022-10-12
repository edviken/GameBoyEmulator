//
// Created by Martin Edviken on 2022-09-24.
//

#include <gmock/gmock-nice-strict.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>
#include "../../mock/LoaderMock.hpp"
#include "disassembler/Cartridge.hpp"
#include "disassembler/mbc/MemoryBankController.hpp"

using ::testing::NiceMock;
using ::testing::StrictMock;

class MemoryBankControllerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    ON_CALL(*_loaderMock, readDataFromFile).WillByDefault(::testing::Return(inputCartridgeData));
    _cartridge = std::make_unique<Cartridge>(*_loaderMock);

    // MBC1 type
    inputCartridgeData.at(CartridgeHeader::CartridgeType) = 0x01;
    // 64KBytes rom, 4 Banks
    inputCartridgeData.at(CartridgeHeader::RomSize) = 0x01;
    // 32KBytes ram, 4 banks of 8KBytes each
    inputCartridgeData.at(CartridgeHeader::RamSize) = 0x03;
  }

  void TearDown() override {}

  std::unique_ptr<Cartridge> _cartridge;
  std::unique_ptr<LoaderMock> _loaderMock{std::make_unique<NiceMock<LoaderMock>>()};
  MBC1 mbc1{};
  std::vector<uint8_t> inputCartridgeData{std::vector<uint8_t>(0xFFFF)};
};

/*****************************************************
 ********************* Write tests *******************
 *****************************************************/

/// Enable/disable RAM access
TEST_F(MemoryBankControllerTest, RamEnabledAndDisabled) {
  // enabled RAM
  mbc1.write(0x0, 0x0A);
  ASSERT_TRUE(mbc1.isRamEnabled());

  // Disable RAM
  mbc1.write(0x1FFF, 0x00);
  ASSERT_TRUE(!mbc1.isRamEnabled());
}

TEST_F(MemoryBankControllerTest, RomBankNumber) {
  // Normal random cases
  mbc1.write(0x2000, 0xE1);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x01);
  mbc1.write(0x3FFF, 0x01);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x01);
  mbc1.write(0x2000, 0x02);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x02);
  mbc1.write(0x2000, 0x23);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x03);
  mbc1.write(0x2000, 0x65);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x05);

  // Special cases
  mbc1.write(0x2000, 0x00);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x01);
  mbc1.write(0x2000, 0x20);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x21);
  mbc1.write(0x2000, 0x40);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x41);
  mbc1.write(0x2000, 0x60);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x61);
}

TEST_F(MemoryBankControllerTest, RomRamModeSelect) {
  // There are two modes: 16Mb ROM/8KB RAM and 4Mb ROM/32KB RAM.
  // Writing either 0 or 1 will select ROM mode or RAM mode respectively.

  // Select ROM mode
  mbc1.write(0x6000, 0x00);
  ASSERT_EQ(mbc1.getRomSize(), 16000000);
  ASSERT_EQ(mbc1.getRamSize(), 8000);

  // Select RAM mode
  mbc1.write(0x7FFF, 0x01);
  ASSERT_EQ(mbc1.getRomSize(), 4000000);
  ASSERT_EQ(mbc1.getRamSize(), 32000);
}

TEST_F(MemoryBankControllerTest, RamBankNumberSelect) {
  // $4000-$5FFF: RAM Bank Number or Upper Bits of ROM Bank Number (Write Only)
  //
  // Writing to this area of memory will affect the ROM or RAM modes,
  // depending on what is written in $6000-$7FFF.
  // Only the first two bits of the value matter.
  // If in ROM mode (no RAM bank switching), it will specify
  // the upper two bits of the ROM bank number. In this mode, only
  // RAM bank $00 may be used.
  //
  // If in RAM mode, it will specify which RAM bank to load into $A000-$BFFF.
  // In this mode, only ROM banks $00-$1f may be used.

  // Select ROM mode
  mbc1.write(0x6000, 0x00);
  ASSERT_EQ(mbc1.getRomSize(), 16000000);
  ASSERT_EQ(mbc1.getRamSize(), 8000);

  // Specifying the upper two bits in the ROM bank number
  mbc1.write(0x4000, 0x03);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x19);
  // Only first two bits of the value matter.
  mbc1.write(0x4000, 0x0F);
  ASSERT_EQ(mbc1.getRomBankNumber(), 0x19);

  // ----------------------------------------

  // Select RAM mode
  mbc1.write(0x7FFF, 0x01);
  ASSERT_EQ(mbc1.getRomSize(), 4000000);
  ASSERT_EQ(mbc1.getRamSize(), 32000);

  // Select ram bank in RAM mode
  mbc1.write(0x5FFF, 0x03);
  ASSERT_EQ(mbc1.getRamBankNumber(), 0x03);
}

/*****************************************************
 ********************* Read tests *******************
 *****************************************************/

TEST_F(MemoryBankControllerTest, RomBank0) {
  // Setup
  inputCartridgeData.at(0x0000) = 1;
  inputCartridgeData.at(0x3FFF) = 1;

  mbc1.registerCartridgeData(std::move(inputCartridgeData));

  ASSERT_EQ(mbc1.read(0x0000), 1);
  ASSERT_EQ(mbc1.read(0x3FFF), 1);
  ASSERT_EQ(mbc1.read(0x4000), 0);
}

TEST_F(MemoryBankControllerTest, RomBankGeneral) {
  // Setup for ROM bank 1
  inputCartridgeData.at(0x4000) = 1;
  inputCartridgeData.at(0x7FFF) = 1;

  // Setup for ROM bank 2
  inputCartridgeData.at(0x8000) = 2;
  inputCartridgeData.at(0xBFFF) = 2;
  // Register our ref input data
  mbc1.registerCartridgeData(std::move(inputCartridgeData));

  // set ROM bank 1
  mbc1.write(0x2000, 0x00);

  ASSERT_EQ(mbc1.read(0x4000), 1);
  ASSERT_EQ(mbc1.read(0x7FFF), 1);

  // set ROM bank 2
  mbc1.write(0x2000, 0x02);

  ASSERT_EQ(mbc1.read(0x4000), 2);
  ASSERT_EQ(mbc1.read(0x7FFF), 2);
}

// TODO: Add ROM bank read special case: Bank nr > 1F.
//TEST_F(MemoryBankControllerTest, RomBankSpecial) {
//  // Setup for ROM bank 0x46
//  inputCartridgeData.at(0x4000) = 21;
//  inputCartridgeData.at(0x7FFF) = 21;
//  // Register our ref input data
//  mbc1.registerCartridgeData(std::move(inputCartridgeData));
//
//  // set ROM mode
//  mbc1.write(0x6000, 0);
//  // set ROM bank 46
//  // Write 5 lower bits 0b0000 0110
//  mbc1.write(0x2000, 0x06);
//  // Write 2 upper bits 0b0010 << 5 => 0b0100 0110 = 0x46
//  mbc1.write(0x4000, 0x02);
//
//  ASSERT_EQ(mbc1.read(0x4000), 21);
//  ASSERT_EQ(mbc1.read(0x7FFF), 21);
//}

TEST_F(MemoryBankControllerTest, RamBankReadWrite) {
  // 0xA000–0xBFFF — RAM Bank 00–03, if any
  inputCartridgeData.at(0xA000) = 42;
  inputCartridgeData.at(0xBFFF) = 43;
  inputCartridgeData.at(0xC000) = 100;  // Start of bank 1
  mbc1.registerCartridgeData(std::move(inputCartridgeData));
  mbc1.write(0x0000, 0x00);  // Disable RAM

  // Make sure we only receive 0xFF when RAM is disabled
  ASSERT_EQ(mbc1.read(0xA000), 0xFF);

  // Read when RAM is enabled
  mbc1.write(0x0000, 0x0A);  // Enable RAM
  // Read from RAM bank 0
  ASSERT_EQ(mbc1.read(0xA000), 42);
  ASSERT_EQ(mbc1.read(0xBFFF), 43);

  // Read from other RAM bank 2
  mbc1.write(0x6000, 0x01);           // Select RAM banking mode
  mbc1.write(0x5FFF, 0x01);           // Select RAM bank 1
  ASSERT_EQ(mbc1.read(0xA000), 100);  // Read from RAM bank 1
}