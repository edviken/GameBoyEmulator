//
// Created by Martin Edviken on 2022-08-05.
//

#include "cpu/Cpu.hpp"

void Cpu::execute(uint8_t instruction) {
  switch (instruction) {
    case 0x80:
      addAB();
      break;
  }
}

void Cpu::setRegA(uint8_t value) {
  a = value;
}

void Cpu::setRegB(uint8_t value) {
  b = value;
}

uint8_t Cpu::getRegA() {
  return a;
}

uint8_t Cpu::getRegF() {
  return f;
}