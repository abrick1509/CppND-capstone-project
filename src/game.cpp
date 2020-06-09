#include "game.h"
#include "SDL.h"
#include "SDL_version.h"
#include <algorithm>
#include <iostream>
#include <string>

Game::Game(std::size_t grid_width, std::size_t grid_height,
           const std::size_t number_of_players, Logger &logger)
    : engine(dev()) {
  snakes.reserve(number_of_players);
  for (std::size_t i = 0; i < number_of_players; ++i) {
    snakes.emplace_back(grid_width, grid_height, i, number_of_players);
  }
  // in the beginning whole grid is free to navigate
  free_space.reserve(grid_width * grid_height);
  for (std::size_t col = 0; col < grid_width; ++col) {
    for (std::size_t row = 0; row < grid_height; ++row) {
      free_space.push_back({static_cast<int>(col), static_cast<int>(row)});
    }
  }
  PlaceFood(logger);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               const std::size_t target_frame_duration, Logger &logger) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(logger,  //
                           running, //
                           snakes);
    Update(running, logger);
    renderer.Render(snakes, //
                    food,   //
                    obstacles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(snakes, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood(Logger &logger) {
  if (free_space.empty()) {
    return;
  }
  // get random index in free space
  std::uniform_int_distribution<std::size_t> random_idx(0, free_space.size());
  while (true) {
    const auto idx = random_idx(engine);
    const auto free_pt = free_space.at(idx);
    // Check that the location is not occupied by a snake item before placing
    // food.
    const auto occupied_by_snake =
        std::any_of(snakes.begin(), snakes.end(), [&](const auto &snake) {
          return snake.SnakeCell(free_pt.x, free_pt.y);
        });
    if (!occupied_by_snake) {
      food.x = free_pt.x;
      food.y = free_pt.y;
      free_space.erase(free_space.begin() + idx);
      logger.LogMessage("New food item has been placed at: [" +
                        std::to_string(food.x) + ", " + std::to_string(food.y) +
                        "].");
      return;
    }
  }
}

void Game::AddObstacle(Logger &logger) {
  if (free_space.empty()) {
    return;
  }
  // get random index in free space
  std::uniform_int_distribution<std::size_t> random_idx(0, free_space.size());
  while (true) {
    const auto idx = random_idx(engine);
    const auto free_pt = free_space.at(idx);
    // Check that the location is not occupied by a snake item before placing
    // food.
    const auto occupied_by_snake =
        std::any_of(snakes.begin(), snakes.end(), [&](const auto &snake) {
          return snake.SnakeCell(free_pt.x, free_pt.y);
        });
    const auto occupied_by_food = free_pt == food;
    if (!occupied_by_snake && !occupied_by_food) {
      obstacles.push_back(free_pt);
      free_space.erase(free_space.begin() + idx);
      logger.LogMessage("New obstacle has been placed at: [" +
                        std::to_string(free_pt.x) + ", " +
                        std::to_string(free_pt.y) + "].");
      return;
    }
  }
}

void Game::Update(bool &running, Logger &logger) {
  const auto any_snake_dead =
      std::any_of(snakes.begin(), //
                  snakes.end(),   //
                  [](const Snake &snake) { return !snake.alive; });
  if (any_snake_dead) {
    running = false;
    return;
  }

  for (std::size_t i = 0; i < snakes.size(); ++i) {
    auto &snake = snakes.at(i);
    snake.Update();
    // check if this snake has moved into one of the other snakes
    if (snake.InCollision(snakes) || snake.InCollision(obstacles)) {
      logger.LogMessage("Snake " + std::to_string(i) + " collided.");
      snake.alive = false;
      running = false;
      return;
    }

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
      logger.LogMessage("Snake " + std::to_string(i) + " has eaten.");
      snake.IncreaseScore();
      // Grow snake and increase speed.
      snake.GrowBody();
      for (auto &snake : snakes) {
        snake.speed += 0.02;
      }
      logger.LogMessage("Increased speed to " + std::to_string(snake.speed));
      PlaceFood(logger);
      // Add obstacles if food was found
      AddObstacle(logger);
    }
  }
}
