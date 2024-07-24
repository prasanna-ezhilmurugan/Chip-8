#include <cstring>
#include "../include/Chip8.hpp"
#include "../include/Config.hpp"
#include <fstream>
#include <iosfwd>
#include <random>

// 8-bit random number generation 
std::random_device rng{};
std::mt19937 mt_engine{rng()};
std::uniform_int_distribution<uint32_t> dist{0, 255};

uint8_t generate_random_byte() {
  return static_cast<uint8_t>(dist(mt_engine));
}

// constructor 
Chip8::Chip8() {
  pc = Config::START_ADDRESS;

  // Load fonts into memory
  for (unsigned int i = 0; i <Config::FONTSET_SIZE; i++) {
    memory[Config::FONTSET_START_ADDRESS + i] = Config::fontset[i];
  }
}

// loading ROM 
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
      memory[Config::START_ADDRESS + i] = buffer[i];
    }

    // free the buffer
    delete[] buffer;
  }
}

// CLR - clear the display
void Chip8::_00E0(){
  for (uint32_t i = 0; i < video.size(); i++){
    video.at(i) = 0;
  }
}

// return from a subroutine
void Chip8::_00EE(){
  --sp;
  pc = stack[sp];
}

//Jump the location nnn
void Chip8::_1nnn(){
  uint16_t address = (opcode & 0x0FFFu);

  pc = address;
}

// Call subroutine at nnn
void Chip8::_2nnn(){
  uint16_t address = opcode & 0x0FFFu;

  stack[sp] = pc;
  ++sp;
  pc = address;
}

// Skip next instruction if Vx == kk
void Chip8::_3xkk(){
  uint8_t Vx = (opcode & 0x0F00u)>>8u;
  uint8_t byte = opcode & 0xFFFu;

  if(registers[Vx] == byte){
    pc+=2;
  }
}

// Skip next instruction if Vx == kk
void Chip8::_4xkk(){
  uint8_t Vx = (opcode & 0x0F00u)>>8u;
  uint8_t byte = opcode & 0xFFFu;

  if(registers[Vx] != byte){
    pc+=2;
  }
}

//Skip next instruction if Vx = Vy
void Chip8::_5xy0(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  if(registers[Vx] == registers[Vy]){
    pc+=2;
  }
}

// Set Vx = kk
void Chip8::_6xkk(){
  uint8_t Vx = (opcode & 0x0F00) >> 8u;
  uint8_t byte = (opcode & 0x00FF);

  registers[Vx] = byte;
}


// Set Vx = Vx + kk ( ADD Vx, byte)
void Chip8::_7xkk(){
  uint8_t Vx = (opcode & 0x0F00) >> 8u;
  uint8_t byte = (opcode & 0x0FF);

  registers[Vx] = registers[Vx] + byte;
}

// Set Vx = Vy
void Chip8::_8xy0(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[Vx] = registers[Vy];
}

// set Vx = Vx OR Vy
void Chip8::_8xy1(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[Vx] = registers[Vx] | registers[Vy];
}

// set Vx = Vx AND Vy
void Chip8::_8xy2(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[Vx] = registers[Vx] & registers[Vy];
}

// set Vx = Vx XOR Vy
void Chip8::_8xy3(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[Vx] = registers[Vx] ^ registers[Vy];
}


// set Vx = Vx + Vy, set VF = Carry
void Chip8::_8xy4(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0X00F0u) >> 4u;

  uint16_t sum = registers[Vx] + registers[Vy];

  if( sum > 255u){
    registers[0xF] = 1; 
  } else {
    registers[0xF] = 0;
  }

  registers[Vx] = sum & 0xFF;
}

// set Vx = Vx - Vy, set VF = Not Borrow
void Chip8::_8xy5(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  if (registers[Vx] > registers[Vy])
  {
    registers[0xF] = 1; 
  } else {
    registers[0xF] = 0;
  }

  registers[Vx] -= registers[Vy];
}

// set Vx = Vx SHR 1
void Chip8::_8xy6(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  registers[Vx] = (opcode & 0x1u);
  registers[Vx]>>=1;
}

// set Vx= Vy - Vx, set VF = Not Borrow
void Chip8::_8xy7(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  if(registers[Vy] > registers[Vx]){
    registers[0xF] = 1;
  } else {
    registers[0xF] = 0;

    registers[Vx] = registers[Vy] - registers[Vx];
  }
}

// set Vx = Vy SHL 1
void Chip8::_8xyE(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  registers[Vx] = (opcode & 0x80u) >> 7u;
  registers[Vx] <<= 1;
}

// Skip the next instruction if Vx != Vy
void Chip8::_9xy0(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  if( registers[Vx] != registers[Vy]){
    pc+=2;
  }
}

// Set Index = nnn
void Chip8::_Annn(){
  uint16_t address = (opcode & 0x0FFFu);

  index = address;
}

// Jump to the location nnn + 10
void Chip8::_Bnnn(){
  uint16_t address = (opcode & 0x0FFFu);

  pc = address + registers[0x0u];
}

// Set Vx = random byte AND kk
void Chip8::_Cxkk(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  registers[Vx] = generate_random_byte();
}

// Draw Vx, Vy starting at the memory location I at  (Vx, Vy), set VF = collision
void Chip8::_Dxyn(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  uint8_t height = (opcode & 0x000Fu);

  // wrap if going beyond the screen boundaries
  uint8_t x_pos = registers[Vx] % Config::window_width;
  uint8_t y_pos = registers[Vy] % Config::window_height;

  registers[0xF] = 0;

  for( unsigned int row = 0; row < height; ++row){
    uint8_t sprite_byte = memory[index + row];

    for (unsigned int column = 0; column < 8; ++column){
      uint8_t sprite_pixel = sprite_byte & (0x80 >> column);
      uint32_t* screen_pixel = &video[(y_pos + row) * Config::window_width + (x_pos + column)];

			if (sprite_pixel)
			{
				if (*screen_pixel == 0xFFFFFFFF)
				{
					registers[0xF] = 1;
				}
				*screen_pixel ^= 0xFFFFFFFF;
			}
    }
  }
}

// Skip the next instruction if the key with the value of Vx is pressed
void Chip8::_Ex9E(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  uint8_t key = registers[Vx];
  if(keypad[key]){
    pc+=2;
  }
}

// Skip the next instruction if the key with the value of Vx is pressed
void Chip8::_ExA1(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  uint8_t key = registers[Vx];
  if(!keypad[key]){
    pc+=2;
  }
} 

// Set Vx = delay timer value
void Chip8::_Fx07(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  registers[Vx] = delay_timer;
}

// Wait for the key press and set the value of that key in Vx
void Chip8::_Fx0A(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  if(keypad[0]){
    registers[Vx] = 0;
  }
  else if(keypad[1]){
    registers[Vx] = 1;
  }
  else if(keypad[2]){
    registers[Vx] = 2;
  }
  else if(keypad[3]){
    registers[Vx] = 3;
  }
  else if(keypad[4]){
    registers[Vx] = 4;
  }
  else if(keypad[5]){
    registers[Vx] = 5;
  }
  else if(keypad[6]){
    registers[Vx] = 6;
  }
  else if(keypad[7]){
    registers[Vx] = 7;
  }
  else if(keypad[8]){
    registers[Vx] = 8;
  }
  else if(keypad[9]){
    registers[Vx] = 9;
  }
  else if(keypad[10]){
    registers[Vx] = 10;
  }
  else if(keypad[11]){
    registers[Vx] = 11;
  }
  else if(keypad[12]){
    registers[Vx] = 12;
  }
  else if(keypad[13]){
    registers[Vx] = 13;
  }
  else if(keypad[14]){
    registers[Vx] = 14;
  }
  else if(keypad[15]){
    registers[Vx] = 15;
  }
  else {
    pc-=2;
  }
}

// Set delay_timer = Vx
void Chip8::_Fx07(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  delay_timer = registers[Vx];
}

// Set sound_timer = Vx
void Chip8::_Fx18(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  sound_timer = registers[Vx];
}

// set index = index + Vx
void Chip8::_Fx1E(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  index = index + registers[Vx];
}

// Set I = location of sprite for the digit Vx
void Chip8::_Fx29(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t digit = registers[Vx];

  index = Config::FONTSET_START_ADDRESS + (digit * 5);
}

// Store BCD representation of the Vx in memory location T, I+1, I+2
void Chip8::_Fx33(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t decimal = registers[Vx];

  memory[index+2] = decimal%10;
  decimal/=10;

  memory[index+1] = decimal%10;
  decimal/=10;

  memory[index] = decimal%10;
}

// Store registers V0 through Vx in memory starting at memory location index
void Chip8::_Fx55(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  for (uint8_t i = 0; i <= Vx; i++){
    memory[index + i] = registers[i];
  }
}

// Read registers V0 through Vx from the memory starting at location I 
void Chip8::_Fx65(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  for (uint8_t i = 0; i < Vx; i++){
    registers[i] = memory[index + i];
  }
}