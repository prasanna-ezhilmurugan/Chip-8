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
  uint8_t delay_timer{};
  uint8_t sound_timer{};
  std::array<uint8_t, 16> keypad{};
  std::array<uint32_t, 64 * 32> video{};
  uint16_t opcode{};

  Chip8();
  void loadROM(char const *filename);

  void _00E0(); // CLR - clear the display
  void _00EE(); // Reutrn froma subroutine
  void _1nnn(); // Jump the location nnn
  void _2nnn(); // Call subroutine at nnn
  void _3xkk(); // Skip next instruction if Vx = kk
  void _4xkk(); // Skip next instruction if Vx != kk
  void _5xy0(); // Skip next instruction if Vx = Vy
  void _6xkk(); // Set Vx = kk
  void _7xkk(); // Set Vx = Vx + kk (ADD Vx, byte)
  void _8xy0(); // Set Vx = Vy
  void _8xy1(); // Set Vx = Vx OR Vy
  void _8xy2(); // Set Vx = Vx AND Vy
  void _8xy3(); // Set Vx = Vx XOR Vy
  void _8xy4(); // Set Vx = Vx + Vy, set VF = Carry
  void _8xy5(); // Set Vx = Vx - Vy, set VF = Not Borrow
  void _8xy6(); // Set Vx = Vx SRH 1
  void _8xy7(); // Set Vx = Vy - Vx, set VF = Not Borrow
  void _8xyE(); // Set Vx = Vx SHL 1. 
  void _9xy0(); // Skip the next instruction if Vx != Vy
  void _Annn(); // Set Index = nnn;
  void _Bnnn(); // Jump to the location nnn + V0
  void _Cxkk(); // Set Vx =  random byte AND kk
  void _Dxyn(); // Draw Vx, Vy starting at the memory location I at  (Vx, Vy), set VF = collision
  void _Ex9E(); // Skip next instruction if the key with the value of Vx is pressed
  void _ExA1(); // Skip next instruction if the key with the value of Vx is not pressed
  void _Fx07(); // Set Vx = delay timer value
  void _Fx0A(); // Wait for the key press and store the value of that key in Vx
  void _Fx15(); // Set delay_timer = Vx
  void _Fx18(); // Set sound_timer = Vx
  void _Fx1E(); // set index = index + Vx
  void _Fx29(); // set index = location of sptite for the digit Vx 
  void _Fx33(); // Store BCD representation of the Vx in memory location I, I+1, I+2
  void _Fx55(); // store registers V0 through Vx in memory starting at location Index
  void _Fx65(); // Read registers V0 through Vx from the memroy starting at location I
};    
