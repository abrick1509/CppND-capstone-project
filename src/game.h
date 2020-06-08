#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <random>
#include <vector>

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height,
       const std::size_t number_of_players);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  std::size_t GetNumberOfPlayers() { return snakes.size(); }
  const Snake &GetSnake(const std::size_t i) { return snakes.at(i); }

private:
  std::vector<Snake> snakes;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  void PlaceFood();
  void Update(bool &running);
};

#endif