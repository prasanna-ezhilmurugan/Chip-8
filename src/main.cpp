#include "../include/Chip8.hpp"
#include "../include/Config.hpp"
#include "../include/Platform.hpp"
#include <chrono>
#include <cstdlib>
#include <format>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << "<Scale> <Delay> <ROM>\n";
    std::exit(EXIT_FAILURE);
  }

  int video_scale = std::stoi(argv[1]);
  int cycle_delay = std::stoi(argv[2]);
  char const *rom_filename = argv[3];

  Platform platform(Config::video_width * video_scale,
                    Config::video_height * video_scale, Config::video_width,
                    Config::video_height);

  Chip8 chip8;
  chip8.loadROM(rom_filename);

  int video_pitch = sizeof(chip8.video[0]) * Config::video_width;
  const void *buffer = static_cast<const void *>(chip8.video.data());

  auto last_cycle_time = std::chrono::high_resolution_clock::now();
  while (platform.get_is_running()) {
    platform.handle_events(chip8.keypad);

    auto current_time = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(
                   current_time - last_cycle_time)
                   .count();

    if (dt > cycle_delay) {
      last_cycle_time = current_time;

      chip8.cycle();

      platform.update(buffer, video_pitch);
    }
  }

  return 0;
}