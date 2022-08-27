//
// Created by Martin Edviken on 2022-08-24.
//
#include "cpu/Cpu.hpp"
#include "disassembler/Cartridge.hpp"

#include <gtest/gtest.h>

class OpCodesTest : public ::testing::TestWithParam<std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>> {
 protected:
  void SetUp() override {}

  void TearDown() override {}

  Cartridge cartridge{};
  Cpu cpu{};
};

//TEST_F(OpCodesTest, eightBitLoadInstructions) {}
//TEST_F(OpCodesTest, sixteenBitLoadInstructions) {}
//TEST_F(OpCodesTest, eightBitArithmeticInstructions) {}
//TEST_F(OpCodesTest, sixteenBitArithmeticInstructions) {}
//TEST_F(OpCodesTest, rotateAndShiftInstructions) {}
//TEST_F(OpCodesTest, singleBitOperationInstructions) {}
//TEST_F(OpCodesTest, cpuControlInstructions) {}
//TEST_F(OpCodesTest, jumpInstructions) {}

TEST_P(OpCodesTest, testOpCodeAddAB) {
  // ADD A B flags: z0hc
  cpu.setRegA(std::get<0>(GetParam()));
  cpu.setRegB(std::get<1>(GetParam()));

  cpu.execute(0x80);
  ASSERT_EQ(std::get<2>(GetParam()), cpu.getRegA());
  ASSERT_EQ(std::get<3>(GetParam()), cpu.getRegF());
}

// Values in the tuple are: std::tuple<in_A, in_B, out_A, out_F>
INSTANTIATE_TEST_SUITE_P(testOpCodeAddAB, OpCodesTest,
                         testing::Values(std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(0x01, 0x01, 0x02, 0x00),
                                         std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(0x01, 0x0A, 0x0B, 0x00),
                                         std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(0x01, 0xFF, 0x00, 0x10),
                                         std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(0x00, 0x00, 0x00, 0x80)));
