#include <iostream>

#include "disassembler/Cartridge.hpp"
#include "memory/Memory.hpp"

int main() {
  std::cout << "Hello, World!" << std::endl;

  Cartridge cartridge{};
  cartridge.readDataFromFile("../../../external/games/Super-Mario-Land-4.gb");
  auto progData = cartridge.getProgramData();

  Memory mem{};
  //  mem.setProgramData();

  return 0;
}
