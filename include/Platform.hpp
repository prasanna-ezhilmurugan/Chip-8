#pragma once

#include <memory>
#include <functional>
#include <SDL2/SDL.h>

class Platform{
  public:
    Platform(int window_width, int window_height, int texture_width, int texture_height);
    void handle_events(std::array<uint8_t, 16> &keys);
    void update(const void* buffer, int pitch);
    bool get_is_running(){
      return m_running;
    }
    ~Platform();
  private:
    SDL_Event m_event{};
    bool m_running{true};
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> m_window;
    std::unique_ptr<SDL_Renderer,std::function<void(SDL_Renderer *)>>m_renderer;
    std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> m_texture;
};