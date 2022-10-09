//
// Created by Martin Edviken on 2022-08-07.
//

#ifndef GAMEBOYEMULATOR_DECODER_HPP
#define GAMEBOYEMULATOR_DECODER_HPP

#include <array>
#include <cstdint>
#include <map>

/// The possible instructions and their occupancy of bytes.
/// tuple contains <first = bytes used by the instruction,
///                second = number of clock cycles (M-cycles)
///                third = Flags that are set by the instructions>
static std::map<uint8_t, std::tuple<uint8_t, uint8_t, uint8_t>> opCodes{
    {0x80, {1, 1, 0x90}}, // ADD A B flags: z0hc
    {0x81, {1, 1, 0x90}}, // ADD A C flags: z0hc
};

/**
 * @brief Decodes bytes into CPU instructions
 */
class Decoder {
  // We need a relation between, Instruction Hex value, number of cycles,
  // and number of following bytes used by the instruction.
};

#endif  //GAMEBOYEMULATOR_DECODER_HPP
