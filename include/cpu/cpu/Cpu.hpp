//
// Created by Martin Edviken on 2022-08-05.
//

#ifndef GAMEBOYEMULATOR_CPU_HPP
#define GAMEBOYEMULATOR_CPU_HPP

#include <cstdlib>
#include "decoder/Decoder.hpp"

class Cpu {  // TODO: Creat a Sharp SM83 version (add SM83 in class name or new inherited class)
             /**
   * The CPU has 3 states, fetch, decode and execute.
   * Should I model these in a finite state machine?? (with boost::sml)
   */

 public:
  Cpu() = default;

 private:
  /// Decoder object to decode the instructions read from the program
  Decoder decoder;

  /// Accumulator register
  int8_t a;

  /// General purpose registers
  int8_t b, c, d, e, h, l;

  /// Flag register
  int8_t f;

  //----- Alternative to above ------
  int16_t af, bc, de, hl;  // TODO: use this or above option??

  /// Stack pointer
  int32_t sp;

  /// Program counter
  int32_t pc;
};

#endif  //GAMEBOYEMULATOR_CPU_HPP
