//
// Created by Martin Edviken on 2022-07-22.
//

#ifndef GAMEBOYEMULATOR_CARTRIDGELOADER_HPP
#define GAMEBOYEMULATOR_CARTRIDGELOADER_HPP

#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief Cartridge header that contains information about
 *        the games itself and its expected hardware to run on.
 */
enum CartridgeHeader {
  EntryPoint = 0x0100,
  NintendoLogo = 0x104,
  Title = 0x134,
  ManufacturerCode = 0x013F,
  CGBFlag = 0x143,
  NewLicenseCode = 0x0144,
  SGBFlag = 0x146,
  CartridgeType = 0x147,
  RomSize = 0x148,
  RamSize = 0x149,
  DestinationCode = 0x14A,
  OldLicenseCode = 0x14B,
  VersionNumber = 0x14C,
  HeaderChecksum = 0x14D,
  GlobalChecksum = 0x14E,
};

/**
 * @brief The MBC type used in the cartridge.
 */
enum class CartridgeType {
  ROMOnly,
  MCB1,
  MCB1Ram,
  MCB1RamBattery,
  MCB2 = 0x05,
  MCB2RamBattery,
  RomRam = 0x08,
  RomRamBattery,
  MMM01Ram = 0x0B,
  MMM01RamBattery,
  MBC3TimerBattery = 0x0F,
  MBC3RamTimerBattery,
  MBC3,
  MBC3Ram,
  MBC3RamBattery,
  MBC5 = 0x19,
  MBC5Ram,
  MBC5RamBattery,
  MBC5Rumble,
  MBC5RamRumble,
  MBC5RamBatteryRumble,
  MBC6RamBattery = 0x20,
  MBC7RamBatteryAccelerometer = 0x22,
  PocketCamera = 0xFC,
  BandaiTama5,
  HuC3,
  HuC1RamBattery,
  Unknown,
};

/// Array of pairs where the array index corresponds to the number at address 0x148.
/// The pairs consist of first = ROM size in KiB and second = number of ROM banks.
[[maybe_unused]] static std::array<std::pair<uint16_t, uint8_t>, 12> romSizes{
    {{32, 2},
     {64, 4},
     {128, 8},
     {256, 16},
     {512, 32},
     {1000, 64},
     {2000, 128},
     {4000, 256},
     {8000, 512},
     {1100, 72},
     {1200, 80},
     {1500, 96}}
};

/// Array of pairs where the array index corresponds to the number at address 0x149.
/// The pairs consist of first = ROM size in KiB and second = number of ROM banks.
[[maybe_unused]] static std::array<std::pair<uint16_t, uint8_t>, 6> ramSizes{
    {{0, 0}, {0, 0}, {8, 1}, {32, 4}, {128, 16}, {64, 8}}
};

/**
 * @brief Loads the bytes from a .gb file and reads the cartridge header,
 *        saves information and extracts the game bytes for the CPU to process.
 */
class CartridgeLoader {
 public:
  /// Constructor
  CartridgeLoader() = default;

  /**
   * @brief Given an input filename, it reads the bytes and holds a reference to it
   * @param filename The path to the file
   */
  void readDataFromFile(std::string filename);

  /**
   * @brief Fetches the program data as specified in the Cartridge header
   * @return The program bytes
   */
  std::vector<uint8_t> getProgramData();

  /**
   * @brief Gets data from the read file
   * @return The data as bytes
   */
  std::vector<uint8_t> getData();

 private:
  std::vector<uint8_t> _rawData{};
  uint16_t _kiloMultiplyer = 1000;
};

#endif  // GAMEBOYEMULATOR_CARTRIDGELOADER_HPP
