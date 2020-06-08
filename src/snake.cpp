#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell,
                       SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) const {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

std::vector<SDL_Point> Snake::GetAllOccupiedCells() const {
  std::vector<SDL_Point> result;
  result.reserve(body.size() + 1);
  // add head
  result.push_back({static_cast<int>(head_x), static_cast<int>(head_y)});
  // add body
  for (const auto &pt : body) {
    result.push_back({pt.x, pt.y});
  }
  return result; // NRVO
}

bool Snake::InCollision(const std::vector<Snake> &snakes) const {
  // get all cells of this snake
  const auto this_snake_cells = this->GetAllOccupiedCells();
  // iterate over all other snakes
  for (const auto &snake : snakes) {
    // skip this snake
    if (&snake == this) {
      continue;
    }
    const auto other_snake_cells = snake.GetAllOccupiedCells();
    // check if they overlap somewhere
    for (std::size_t i = 0;
         i < std::min(this_snake_cells.size(), other_snake_cells.size()); ++i) {
      const auto this_snake_pt = this_snake_cells.at(i);
      const auto other_snake_pt = other_snake_cells.at(i);
      if (this_snake_pt.x == other_snake_pt.x &&
          this_snake_pt.y == other_snake_pt.y) {
        return true; // overlap found, collision detected
      }
    }
  }
  return false; // no overlap found with other snakes
}