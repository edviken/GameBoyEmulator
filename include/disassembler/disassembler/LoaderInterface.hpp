//
// Created by Martin Edviken on 2022-09-24.
//

#ifndef GAMEBOYEMULATOR_LOADERINTERFACE_HPP
#define GAMEBOYEMULATOR_LOADERINTERFACE_HPP

#include <vector>

class LoaderInterface {
 public:
  LoaderInterface() = default;

  virtual std::vector<uint8_t> readDataFromFile() = 0;
};

#endif  //GAMEBOYEMULATOR_LOADERINTERFACE_HPP
