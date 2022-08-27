//
// Created by Martin Edviken on 2022-08-05.
//

#ifndef GAMEBOYEMULATOR_CPU_HPP
#define GAMEBOYEMULATOR_CPU_HPP

#include <cstdlib>
#include <limits>
#include "decoder/Decoder.hpp"
#include "register/Register.hpp"

class Cpu {  // TODO: Creat a Sharp SM83 version (add SM83 in class name or new inherited class)
             /**
   * The CPU has 3 states, fetch, decode and execute.
   * Should I model these in a finite state machine?? (with boost::sml)
   */

 public:
  Cpu() = default;

  void execute(uint8_t instruction);

  void setRegA(uint8_t value);
  void setRegB(uint8_t value);
  void setRegC(uint8_t value);

  uint8_t getRegA();
  uint8_t getRegF();

 private:
  void addAB() { _a += _b; }

  void addAC() { _a += _c; }

  /// Decoder object to decode the instructions read from the program
  Decoder decoder;

  /// Flag register
  uint8_t _f{0};

  /// Accumulator register
  ByteRegister _a{_f};

  /// General purpose registers
  ByteRegister _b{_f}, _c{_f}, _d{_f}, _e{_f}, _h{_f}, _l{_f};

  /// Stack pointer
  uint16_t _sp{0};

  /// Program counter
  uint16_t _pc{0};
};

#endif  //GAMEBOYEMULATOR_CPU_HPP
