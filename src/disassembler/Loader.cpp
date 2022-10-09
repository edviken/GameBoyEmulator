//
// Created by Martin Edviken on 2022-09-24.
//

#include "disassembler/Loader.hpp"

#include <errno.h>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "disassembler/Cartridge.hpp"
#include "logger/Logger.hpp"

std::vector<uint8_t> Loader::readDataFromFile() {  // TODO: Adapt for cross-platform compatibility ?
  // TODO: Also do a pre-check that file exists ?
  errno = 0;
  std::ifstream file(_filename, std::ios::in | std::ios::binary);
  if (!file.is_open() || errno != 0) {
    std::cout << "Errno: " << errno << " - " << std::strerror(errno) << std::endl;
    std::cout << "Failed to open file: " << _filename << std::endl;
    char dirBuf[255]{};
    auto dir = getcwd(dirBuf, 255);
    std::cout << "Current dir reading from is: " << dir << std::endl;
    assert(0);
  }

  // Stop eating new lines in binary mode
  file.unsetf(std::ios::skipws);

  // Find size of the file
  file.seekg(0, file.end);
  uint64_t size = file.tellg();
  file.seekg(0, file.beg);
  LOG_INFO("The file size is %d bytes", size);

  // Read the data from the file
  std::vector<uint8_t> rawData{};
  rawData.reserve(size);
  rawData.insert(rawData.begin(), std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>());
  file.close();

  if (rawData.size() >= CartridgeHeader::GlobalChecksum) {
    LOG_INFO("Cartridge type: %d", static_cast<int>(rawData.at(CartridgeHeader::CartridgeType)));
    LOG_INFO("Rom size: %d KiB", romSizes.at(static_cast<int>(rawData.at(CartridgeHeader::RomSize))).first);
    LOG_INFO("Ram size: %d KiB", romSizes.at(static_cast<int>(rawData.at(CartridgeHeader::RamSize))).first);
  }
  return std::move(rawData);
}