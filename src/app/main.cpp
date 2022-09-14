#include <iostream>

#include "disassembler/CartridgeLoader.hpp"
#include "generated/root_path.h"
#include "logger/Logger.hpp"
#include "memory/Memory.hpp"

int main(int argc, char** args) {
  if (argc < 2) {
    LOG_ERROR("Please enter rom path as argument");
    return 0;
  }
  LOG_INFO("The rom path entered is: %s", args[1]);

  CartridgeLoader cartridge{};
  cartridge.readDataFromFile(args[1]);
  auto progData = cartridge.getProgramData();

  [[maybe_unused]] Memory mem{};
  //  mem.setProgramData();

  return 0;
}
