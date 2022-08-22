//
// Created by Martin Edviken on 2022-08-07.
//

#ifndef GAMEBOYEMULATOR_DECODER_HPP
#define GAMEBOYEMULATOR_DECODER_HPP

#include <array>

// TODO: 1. Add NOP and JP instructions to decoder.
// TODO: 2. JP should change the CPU PC

/// The possible instructions and their occupancy of bytes.
/// pair contains <first = instruction code in hex,
///                second = bytes used by the instruction,
///                third = number of clock cycles (not M-cycles)>
static std::array<std::tuple<uint16_t, uint8_t, uint8_t>, 255> instructions{
    {
      // CPU Control instructions
     {0x00, 1, 4}, // NOP
        // JMP instructions
        {0xC3, 3, 16}, ///< JP nn
        {0xE9, 1, 4}, ///< JP HL
        {0x, 3, 16/12}, ///< JP f,nn
        {0x, 2, 12}, ///< JP PC+dd
        {0x, 2, 12/8}, ///< JP f,PC+dd
        {0xCD, 3, 24}, ///< call nn
        {0x, 3, 24/12}, ///< call f,nn
        {0xC9, 1, 16}, ///< ret
        {0x, 1, 20/8}, ///< ret f
        {0xD9, 1, 16}, ///< reti
        {0x, 1, 16}, ///< rst n TODO: Contains several Instruction code values, how to handle??
    }
};

/**
 * @brief Decodes bytes into CPU instructions
 */
class Decoder {
  // We need a relation between, Instruction Hex value, number of cycles,
  // and number of following bytes used by the instruction.
};

#endif  //GAMEBOYEMULATOR_DECODER_HPP
