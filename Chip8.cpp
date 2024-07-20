#include <array>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <random>

std::random_device rng{};
std::mt19937 mt_engine{rng()};
std::uniform_int_distribution<uint32_t> dist{0, 255};

uint8_t generate_random() {
  return static_cast<uint8_t>(dist(mt_engine));
}

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;

uint8_t fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8 {
public:
  std::array<uint8_t, 16> registers{};
  std::array<uint8_t, 4096> memory{};
  uint16_t index{};
  uint16_t pc{};
  std::array<uint16_t, 16> stack{};
  uint8_t sp{};
  uint8_t delayTimer{};
  uint8_t soundTimer{};
  std::array<uint8_t, 16> keypad{};
  std::array<uint32_t, 64 * 32> video{};
  uint16_t opcode{};

  Chip8() ;
  void loadROM(char const *filename);
};

Chip8::Chip8() {
  pc = START_ADDRESS;

  // Load fonts into memory
  for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
    memory[FONTSET_START_ADDRESS + i] = fontset[i];
  }
}

void Chip8::loadROM(char const *filename) {
  // open the file as a stream and move the pointer to the end of the file
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {
    // get the size of the file and allocate a buffer to hold the contents
    std::streampos size = file.tellg();
    char *buffer = new char[size];

    // go back to the beginning of the file and fill the buffer
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    // load the ROM contents into the chip8's memory, starting at 0x200
    for (long i = 0; i < size; i++) {
      memory[START_ADDRESS + i] = buffer[i];
    }

    // free the buffer
    delete[] buffer;
  }
}
