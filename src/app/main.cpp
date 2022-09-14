#include <iostream>

#include "disassembler/CartridgeLoader.hpp"
#include "generated/root_path.h"
#include "memory/Memory.hpp"

int main(int argc, char** args) {
  if (argc < 2) {
    std::cout << "Please enter rom path as argument" << std::endl;
    return 0;
  }
  std::cout << "The rom path entered is: " << args[1] << std::endl;
  std::cout << "Hello, World!" << std::endl;

  CartridgeLoader cartridge{};
  cartridge.readDataFromFile(args[1]);
  auto progData = cartridge.getProgramData();

  [[maybe_unused]] Memory mem{};
  //  mem.setProgramData();

  return 0;
}
