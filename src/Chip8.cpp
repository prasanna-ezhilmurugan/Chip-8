#include <cstring>
#include "../include/Chip8.hpp"
#include "../include/Config.hpp"
#include <fstream>
#include <iosfwd>
#include <random>

std::random_device rng{};
std::mt19937 mt_engine{rng()};
std::uniform_int_distribution<uint32_t> dist{0, 255};

uint8_t generate_random() {
  return static_cast<uint8_t>(dist(mt_engine));
}


Chip8::Chip8() {
  pc = Config::START_ADDRESS;

  // Load fonts into memory
  for (unsigned int i = 0; i <Config::FONTSET_SIZE; i++) {
    memory[Config::FONTSET_START_ADDRESS + i] = Config::fontset[i];
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

}

//Jump the location nnn