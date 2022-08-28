//
// Created by Martin Edviken on 2022-08-05.
//

#include "cpu/Cpu.hpp"
#include <iostream>

void Cpu::execute(uint8_t instruction) {
  switch (instruction) {
    case 0x80:
      addAB();
      break;
    case 0x81:
      addAC();
      break;
    case 0x82:
      addAD();
      break;
    case 0x83:
      addAE();
      break;
    case 0x84:
      addAH();
      break;
    case 0x85:
      addAL();
      break;
    case 0x86:
      addAHL();
      break;
    case 0x87:
      addAA();
      break;
    default:
      std::cout << "Warning, unimplemented OpCode executed" << std::endl;
      break;
  }
}

void Cpu::setRegA(uint8_t value) {
  _a = value;
}

void Cpu::setRegB(uint8_t value) {
  _b = value;
}

void Cpu::setRegC(uint8_t value) {
  _c = value;
}

void Cpu::setRegD(uint8_t value) {
  _d = value;
}

void Cpu::setRegE(uint8_t value) {
  _e = value;
}

void Cpu::setRegH(uint8_t value) {
  _h = value;
}

void Cpu::setRegL(uint8_t value) {
  _l = value;
}

void Cpu::setRegHL(uint16_t value) {
  _hl = value;
}

uint8_t Cpu::getRegA() {
  return _a.value();
}

uint8_t Cpu::getRegF() {
  return _f;
}