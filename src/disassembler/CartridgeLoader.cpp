//
// Created by Martin Edviken on 2022-07-22.
//

#include "disassembler/CartridgeLoader.hpp"

#include <errno.h>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include "logger/Logger.hpp"

void CartridgeLoader::readDataFromFile(std::string filename) {  // TODO: Adapt for cross-platform compatibility ?
  // TODO: Also do a pre-check that file exists ?
  errno = 0;
  std::ifstream file(filename, std::ios::in | std::ios::binary);
  if (!file.is_open() || errno != 0) {
    std::cout << "Errno: " << errno << " - " << std::strerror(errno) << std::endl;
    std::cout << "Failed to open file: " << filename << std::endl;
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
  _rawData.reserve(size);
  _rawData.insert(_rawData.begin(), std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>());
  file.close();

  if (_rawData.size() >= CartridgeHeader::GlobalChecksum) {
    LOG_INFO("Cartridge type: %d", static_cast<int>(_rawData.at(CartridgeHeader::CartridgeType)));
    LOG_INFO("Rom size: %d KiB", romSizes.at(static_cast<int>(_rawData.at(CartridgeHeader::RomSize))).first);
    LOG_INFO("Ram size: %d KiB", romSizes.at(static_cast<int>(_rawData.at(CartridgeHeader::RamSize))).first);
  }
}

std::vector<uint8_t> CartridgeLoader::getProgramData() {
  if (_rawData.empty()) {
    assert(0);
  }
  auto romSize = romSizes.at(_rawData.at(CartridgeHeader::RomSize)).first * _kiloMultiplyer;
  return std::vector<uint8_t>(
      _rawData.begin() + 0x150,
      _rawData.begin() + 0x150 + romSize);  // TODO: interpret this value from OPCode on 0x0100 - 0x0103
}

std::vector<uint8_t> CartridgeLoader::getData() {
  if (_rawData.empty()) {
    assert(0);
  }
  return _rawData;
}