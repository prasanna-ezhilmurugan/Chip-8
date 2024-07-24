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

  SDL_Texture* create_texture_or_throw(SDL_Renderer * renderer){
    SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, Config::texture_width, Config::texture_height);

    if(!texture){
      throw std::runtime_error("Failed to create renderer");
      return nullptr;
    }

    return texture;
  }
}

Platform::Platform()
  :m_window{Loader::create_window_or_throw(), SDL_DestroyWindow}, m_renderer{Loader::create_renderer_or_throw(m_window.get()), SDL_DestroyRenderer}, m_texture{Loader::create_texture_or_throw(m_renderer.get()), SDL_DestroyTexture}
{
  if (SDL_Init(SDL_INIT_VIDEO) !=0){
    throw std::runtime_error("Failed to initialize SDL");
  }
}

void Platform::handle_events(uint8_t* keys){
  while(SDL_PollEvent(&m_event)){
    switch (m_event.type)
    {
      case SDL_QUIT:
        m_running = false;
        break;

      case SDL_KEYDOWN:
      {
        switch(m_event.key.keysym.sym){
          case SDLK_ESCAPE:
          m_running = false;
          break;
          
          case SDLK_x:
            keys[0] = 1;
            break;

          case SDLK_1:
            keys[1] = 1;
            break;
          
          case SDLK_2:
            keys[2] = 1;
            break;
          
          case SDLK_3:
            keys[3] = 1;
            break;
          
          case SDLK_q:
            keys[4] = 1;
            break;
          
          case SDLK_w:
            keys[5] = 1;
            break;
          
          case SDLK_e:
            keys[6] = 1;
            break;
          
          case SDLK_a:
            keys[7] = 1;
            break;
          
          case SDLK_s:
            keys[8] = 1;
            break;
          
          case SDLK_d:
            keys[9] = 1;
            break;
          
          case SDLK_z:
            keys[0xA] = 1;
            break;
          
          case SDLK_c:
            keys[0xB] = 1;
            break;
          
          case SDLK_4:
            keys[0xC] = 1;
            break;
          
          case SDLK_r:
            keys[0xD] = 1;
            break;
          
          case SDLK_f:
            keys[0xE] = 1;
            break;
          
          case SDLK_v:
            keys[0xF] = 1;
            break;
        }
      } break;

      case SDL_KEYUP:
      {
        switch(m_event.key.keysym.sym){
          case SDLK_ESCAPE:
          m_running = false;
          break;
          
          case SDLK_x:
            keys[0] = 1;
            break;

          case SDLK_1:
            keys[1] = 1;
            break;
          
          case SDLK_2:
            keys[2] = 1;
            break;
          
          case SDLK_3:
            keys[3] = 1;
            break;
          
          case SDLK_q:
            keys[4] = 1;
            break;
          
          case SDLK_w:
            keys[5] = 1;
            break;
          
          case SDLK_e:
            keys[6] = 1;
            break;
          
          case SDLK_a:
            keys[7] = 1;
            break;
          
          case SDLK_s:
            keys[8] = 1;
            break;
          
          case SDLK_d:
            keys[9] = 1;
            break;
          
          case SDLK_z:
            keys[0xA] = 1;
            break;
          
          case SDLK_c:
            keys[0xB] = 1;
            break;
          
          case SDLK_4:
            keys[0xC] = 1;
            break;
          
          case SDLK_r:
            keys[0xD] = 1;
            break;
          
          case SDLK_f:
            keys[0xE] = 1;
            break;
          
          case SDLK_v:
            keys[0xF] = 1;
            break;
        }
      } break;
    }
  }
}

void Platform::update(void const* buffer, int pitch){
  SDL_UpdateTexture(m_texture.get(), nullptr, buffer, pitch);
  SDL_RenderClear(m_renderer.get());
  SDL_RenderCopy(m_renderer.get(), m_texture.get(), nullptr, nullptr);
  SDL_RenderPresent(m_renderer.get());
}

Platform::~Platform(){
  SDL_Quit();
}