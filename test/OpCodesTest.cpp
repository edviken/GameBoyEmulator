//
// Created by Martin Edviken on 2022-08-24.
//
#include "../mock/LoaderMock.hpp"
#include "cpu/Cpu.hpp"
#include "disassembler/Cartridge.hpp"

#include <gtest/gtest.h>

class OpCodesTest : public ::testing::TestWithParam<std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>> {
 protected:
  void SetUp() override {}

  void TearDown() override {}

  std::unique_ptr<LoaderMock> _loader = std::make_unique<LoaderMock>();
  Cartridge cartridge{*_loader};
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

TEST_P(OpCodesTest, testOpCodeAddAC) {
  // ADD A C flags: z0hc
  cpu.setRegA(std::get<0>(GetParam()));
  cpu.setRegC(std::get<1>(GetParam()));

  cpu.execute(0x81);
  ASSERT_EQ(std::get<2>(GetParam()), cpu.getRegA());
  ASSERT_EQ(std::get<3>(GetParam()), cpu.getRegF());
}

TEST_P(OpCodesTest, testOpCodeAddAD) {
  // ADD A D flags: z0hc
  cpu.setRegA(std::get<0>(GetParam()));
  cpu.setRegD(std::get<1>(GetParam()));

  cpu.execute(0x82);
  ASSERT_EQ(std::get<2>(GetParam()), cpu.getRegA());
  ASSERT_EQ(std::get<3>(GetParam()), cpu.getRegF());
}

TEST_P(OpCodesTest, testOpCodeAddAE) {
  // ADD A E flags: z0hc
  cpu.setRegA(std::get<0>(GetParam()));
  cpu.setRegE(std::get<1>(GetParam()));

  cpu.execute(0x83);
  ASSERT_EQ(std::get<2>(GetParam()), cpu.getRegA());
  ASSERT_EQ(std::get<3>(GetParam()), cpu.getRegF());
}

TEST_P(OpCodesTest, testOpCodeAddAH) {
  // ADD A H flags: z0hc
  cpu.setRegA(std::get<0>(GetParam()));
  cpu.setRegH(std::get<1>(GetParam()));

  cpu.execute(0x84);
  ASSERT_EQ(std::get<2>(GetParam()), cpu.getRegA());
  ASSERT_EQ(std::get<3>(GetParam()), cpu.getRegF());
}

TEST_P(OpCodesTest, testOpCodeAddAL) {
  // ADD A L flags: z0hc
  cpu.setRegA(std::get<0>(GetParam()));
  cpu.setRegL(std::get<1>(GetParam()));

  cpu.execute(0x85);
  ASSERT_EQ(std::get<2>(GetParam()), cpu.getRegA());
  ASSERT_EQ(std::get<3>(GetParam()), cpu.getRegF());
}

// Values in the tuple are: < 0: in_A,
//                            1: in_other,
//                            2: out_A,
//                            3: out_F >
INSTANTIATE_TEST_SUITE_P(testOpCodeAdd, OpCodesTest,
                         testing::Values(std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(0x01, 0x01, 0x02, 0x00),
                                         std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(0x01, 0x0A, 0x0B, 0x00),
                                         std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(0x01, 0xFF, 0x00, 0x10),
                                         std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(0x00, 0x00, 0x00, 0x80)));

/* ========================================================
 * ========================================================
 * ======================================================== */

// Special case for ADD A HL
class OpCodesAddahlTest : public testing::TestWithParam<std::tuple<uint8_t, uint16_t, uint8_t, uint8_t>> {
 protected:
  Cpu cpu{};
};

// TODO: Should this test have other input params as well ?
TEST_P(OpCodesAddahlTest, ADD_A_HL) {
  // ADD A HL flags: z0hc
  cpu.setRegA(std::get<0>(GetParam()));
  cpu.setRegHL(std::get<1>(GetParam()));

  cpu.execute(0x86);
  ASSERT_EQ(std::get<2>(GetParam()), cpu.getRegA());
  ASSERT_EQ(std::get<3>(GetParam()), cpu.getRegF());
}

// Values in the tuple are: < 0: in_A,
//                            1: in_HL,
//                            2: out_A,
//                            3: out_F >
INSTANTIATE_TEST_SUITE_P(testOpCodeAddAHL, OpCodesAddahlTest,
                         testing::Values(std::tuple<uint8_t, uint16_t, uint8_t, uint8_t>(0x01, 0x01, 0x02, 0x00),
                                         std::tuple<uint8_t, uint16_t, uint8_t, uint8_t>(0x01, 0x0A, 0x0B, 0x00),
                                         std::tuple<uint8_t, uint16_t, uint8_t, uint8_t>(0x01, 0xFF, 0x00, 0x10),
                                         std::tuple<uint8_t, uint16_t, uint8_t, uint8_t>(0x00, 0x00, 0x00, 0x80),
                                         std::tuple<uint8_t, uint16_t, uint8_t, uint8_t>(0x01, 0xFFFF, 0x00, 0x10),
                                         std::tuple<uint8_t, uint16_t, uint8_t, uint8_t>(0x01, 0xFF00, 0x01, 0x00)));

/* ========================================================
 * ========================================================
 * ======================================================== */

// Special case for ADD A A
class OpCodesAddaaTest : public testing::TestWithParam<std::tuple<uint8_t, uint8_t, uint8_t>> {
 protected:
  Cpu cpu{};
};

TEST_P(OpCodesAddaaTest, ADD_A_A) {  // TODO: This test really needs different params
  // ADD A A flags: z0hc
  cpu.setRegA(std::get<0>(GetParam()));

  cpu.execute(0x87);
  ASSERT_EQ(std::get<1>(GetParam()), cpu.getRegA());
  ASSERT_EQ(std::get<2>(GetParam()), cpu.getRegF());
}

// Values in the tuple are: < 0: in_A,
//                            1: out_A,
//                            2: out_F >
INSTANTIATE_TEST_SUITE_P(testOpCodeADDAA, OpCodesAddaaTest,
                         testing::Values(std::tuple<uint8_t, uint8_t, uint8_t>(0x03, 0x06, 0x00),
                                         std::tuple<uint8_t, uint8_t, uint8_t>(0xF5, 0x00, 0x10),
                                         std::tuple<uint8_t, uint8_t, uint8_t>(0x00, 0x00, 0x80)));