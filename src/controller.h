#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
public:
  void HandleInput(bool &running, std::vector<Snake> &snakes) const;

private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif