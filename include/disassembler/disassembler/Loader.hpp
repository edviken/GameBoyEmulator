//
// Created by Martin Edviken on 2022-09-24.
//

#ifndef GAMEBOYEMULATOR_LOADER_HPP
#define GAMEBOYEMULATOR_LOADER_HPP

#include <string>

#include "LoaderInterface.hpp"

class Loader : public LoaderInterface {
 public:
  Loader() = default;
  Loader(std::string filename) : _filename(filename) {}

  std::vector<uint8_t> readDataFromFile() override;

 private:
  std::string _filename{};
};

#endif  //GAMEBOYEMULATOR_LOADER_HPP
