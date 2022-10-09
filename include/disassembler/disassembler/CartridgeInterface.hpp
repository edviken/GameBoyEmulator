//
// Created by Martin Edviken on 2022-09-24.
//

#ifndef GAMEBOYEMULATOR_CARTRIDGEINTERFACE_HPP
#define GAMEBOYEMULATOR_CARTRIDGEINTERFACE_HPP

#include <cstdint>
#include <string>
#include "LoaderInterface.hpp"

/**
 * @brief Loads the bytes from a .gb file and reads the cartridge header,
 *        saves information and extracts the game bytes for the CPU to process.
 */
class CartridgeInterface {
 public:
  /// Constructor
  CartridgeInterface() = default;
  CartridgeInterface(LoaderInterface&);

  /**
   * @brief Fetches the program data as specified in the Cartridge header
   * @return The program bytes
   */
  virtual std::vector<uint8_t> getProgramData() = 0;

  /**
   * @brief Gets data from the read file
   * @return The data as bytes
   */
  virtual std::vector<uint8_t> getData() = 0;
};

#endif  //GAMEBOYEMULATOR_CARTRIDGEINTERFACE_HPP
