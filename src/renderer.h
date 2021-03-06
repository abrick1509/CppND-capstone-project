#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "snake.h"
#include <vector>

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(const std::vector<Snake> &snakes, SDL_Point const &food,
              const std::vector<SDL_Point> &obstalces);
  void UpdateWindowTitle(const std::vector<Snake> &snakes, int fps);

  SDL_Window *GetWindow() { return sdl_window; }

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif