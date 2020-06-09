#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "logger.h"
#include "snake.h"

class Controller {
public:
  void HandleInput(Logger &logger, bool &running,
                   std::vector<Snake> &snakes) const;

private:
  bool ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif