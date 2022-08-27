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

uint8_t Cpu::getRegA() {
  return _a.value();
}

uint8_t Cpu::getRegF() {
  return _f;
}