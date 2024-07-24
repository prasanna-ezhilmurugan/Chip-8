#include "../include/Chip8.hpp"
#include "../include/Platform.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]){
  if(argc != 4){
    std::cerr << "Usage: " << argv[0] << "<Scale> <Delay> <ROM>\n";
    std::exit(EXIT_FAILURE);
  }

  int video_scale = std::stoi(argv[1]);
  int cycle_delay = std::stoi(argv[2]);
  char const* rom_filename = argv[3];

  Platform();

}