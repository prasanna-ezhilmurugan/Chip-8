#pragma once

#include <memory>
#include <functional>
#include <SDL2/SDL.h>

class Platform{
  public:
    Platform();
    void handle_events();
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