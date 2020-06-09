#include "controller.h"
#include "SDL.h"
#include "SDL_keycode.h"
#include "logger.h"
#include "snake.h"
#include <iostream>

bool Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) {
    snake.direction = input;
    return true;
  }
  return false;
}

void Controller::HandleInput(Logger &logger, bool &running,
                             std::vector<Snake> &snakes) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      auto &snake = snakes.at(0);
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        if (ChangeDirection(snake, Snake::Direction::kUp,
                            Snake::Direction::kDown)) {
          logger.LogMessage("Snake 1 change direction to UP");
        }
        break;

      case SDLK_DOWN:
        if (ChangeDirection(snake, Snake::Direction::kDown,
                            Snake::Direction::kUp)) {
          logger.LogMessage("Snake 1 change direction to DOWN");
        }
        break;

      case SDLK_LEFT:
        if (ChangeDirection(snake, Snake::Direction::kLeft,
                            Snake::Direction::kRight)) {
          logger.LogMessage("Snake 1 change direction to LEFT");
        }
        break;

      case SDLK_RIGHT:
        if (ChangeDirection(snake, Snake::Direction::kRight,
                            Snake::Direction::kLeft)) {
          logger.LogMessage("Snake 1 change direction to RIGHT");
        }
        break;
      }
      // check if second snake is available
      if (snakes.size() > 1) {
        auto &snake = snakes.at(1);
        switch (e.key.keysym.sym) {
        case SDLK_w:
          if (ChangeDirection(snake, Snake::Direction::kUp,
                              Snake::Direction::kDown)) {
            logger.LogMessage("Snake 2 change direction to UP");
          }
          break;

        case SDLK_s:
          if (ChangeDirection(snake, Snake::Direction::kDown,
                              Snake::Direction::kUp)) {
            logger.LogMessage("Snake 1 change direction to DOWN");
          }
          break;

        case SDLK_a:
          if (ChangeDirection(snake, Snake::Direction::kLeft,
                              Snake::Direction::kRight)) {
            logger.LogMessage("Snake 1 change direction to LEFT");
          }
          break;

        case SDLK_d:
          if (ChangeDirection(snake, Snake::Direction::kRight,
                              Snake::Direction::kLeft)) {
            logger.LogMessage("Snake 1 change direction to RIGHT");
          }
          break;
        }
      }
    }
  }
}