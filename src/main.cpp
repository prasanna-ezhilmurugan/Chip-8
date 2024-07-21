#include "../include/Chip8.hpp"
#include "../include/Platform.hpp"
#include <iostream>
#include <cstdlib>

int main(){
  Platform platform{};
  while (platform.get_is_running())
  {
    platform.handle_events();
  }
  
  return EXIT_SUCCESS;
}