//
// Created by Martin Edviken on 2022-08-05.
//

#ifndef GAMEBOYEMULATOR_CPU_HPP
#define GAMEBOYEMULATOR_CPU_HPP

#include <cstdlib>
#include <limits>
#include "decoder/Decoder.hpp"

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

  uint8_t getRegA();
  uint8_t getRegF();

 private:
  void addAB() {
    if (a > 0 && b > std::numeric_limits<uint8_t>::max() - a) {
      f |= 0x01 << 4;
    } else if (a == 0 && b == 0) {
      f |= 0x01 << 7;
    }
    a += b;
  }

  /// Decoder object to decode the instructions read from the program
  Decoder decoder;

  /// Accumulator register
  uint8_t a{0};

  /// General purpose registers
  uint8_t b{0}, c{0}, d{0}, e{0}, h{0}, l{0};

  /// Flag register
  uint8_t f{0};

  /// Stack pointer
  uint16_t sp{0};

  /// Program counter
  uint16_t pc{0};
};

#endif  //GAMEBOYEMULATOR_CPU_HPP
