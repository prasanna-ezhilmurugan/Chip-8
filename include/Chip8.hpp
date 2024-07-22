#pragma once
#include <array>
#include <cstdint>

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

  Chip8();
  void loadROM(char const *filename);

  void _00E0(); // CLR - clear the display
  void _00EE(); // reutrn froma subroutine
  void _1nnn(); //Jump the location nnn
  void _2nnn(); // Call subroutine at nnn
  void _3xkk(); // Skip next instruction if Vx = kk
  void _4xkk(); //Skip next instruction if Vx != kk
  void _5xy0(); // Skip next instruction if Vx = Vy
  void _6xkk(); //set Vx = kk
  void _7xkk(); //set Vx = Vx + kk (ADD Vx, byte)
  void _8xy0(); // set Vx = Vy
  void _8xy1(); // set Vx = Vx OR Vy

};    
