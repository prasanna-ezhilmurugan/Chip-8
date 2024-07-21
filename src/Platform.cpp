#include "../include/Platform.hpp"
#include "../include/Config.hpp"
#include <string>
#include <format>
#include <stdexcept>

namespace Loader{
  SDL_Window* create_window_or_throw(){
    SDL_Window* window = SDL_CreateWindow(Config::window_title.data(), 0, 0, Config::window_width, Config::window_height, SDL_WINDOW_SHOWN);
    if(!window){
      throw std::runtime_error("Failed to create window");
      return nullptr;
    }

    return window;
  }

  SDL_Renderer* create_renderer_or_throw(SDL_Window * window){
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer){
      throw std::runtime_error("Failed to create renderer");
      return nullptr;
    }

    return renderer;
  }
}

Platform::Platform()
  :m_window{Loader::create_window_or_throw(), SDL_DestroyWindow}, m_renderer{Loader::create_renderer_or_throw(m_window.get()), SDL_DestroyRenderer}
{
  if (SDL_Init(SDL_INIT_VIDEO) !=0){
    throw std::runtime_error("Failed to initialize SDL");
  }
}

void Platform::handle_events(){
    while(SDL_PollEvent(&m_event)){
      if(m_event.type == SDL_QUIT){
        m_running = false;
      }
    }
}

Platform::~Platform(){
  SDL_Quit();
}