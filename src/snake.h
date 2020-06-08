#ifndef SNAKE_H
#define SNAKE_H

#include "SDL.h"
#include <cstddef>
#include <iostream>
#include <vector>

inline bool operator==(const SDL_Point &lhs, const SDL_Point &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

class Snake {
public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height, const std::size_t current_player,
        const std::size_t total_players)
      : grid_width(grid_width), grid_height(grid_height) {
    head_x = grid_width / (total_players + 1) * (current_player + 1);
    head_y = grid_height / 2;
  }

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y) const;
  std::vector<SDL_Point> GetAllOccupiedCells() const;
  bool InCollision(const std::vector<Snake> &snakes) const;
  bool InCollision(const std::vector<SDL_Point> &obstacles) const;
  void IncreaseScore() { score++; }
  int GetScore() const { return score; }
  std::size_t GetSize() const { return body.size(); }

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
  int score{0};
};

#endif