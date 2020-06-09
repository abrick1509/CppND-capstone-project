#include "SDL_log.h"
#include "controller.h"
#include "game.h"
#include "prompt.h"
#include "renderer.h"
#include <algorithm>
#include <iostream>
#include <string>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{800};
  constexpr std::size_t kScreenHeight{800};
  constexpr std::size_t kGridWidth{50};
  constexpr std::size_t kGridHeight{50};

  Renderer renderer(kScreenWidth,  //
                    kScreenHeight, //
                    kGridWidth,    //
                    kGridHeight);
  int kNumberOfPlayers{1};
  const auto success = QueryForNumberOfPlayers(renderer.GetWindow(), //
                                               kNumberOfPlayers);
  if (!success) {
    SDL_Log("Game will not be started, determining number of players failed.");
    return -1;
  }
  Controller controller;
  Game game(kGridWidth,  //
            kGridHeight, //
            kNumberOfPlayers);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Number of Players: " << game.GetNumberOfPlayers() << "\n";
  std::vector<std::pair<std::string, int>> scores;
  for (std::size_t i = 0; i < game.GetNumberOfPlayers(); ++i) {
    const auto this_snake = game.GetSnake(i);
    std::cout << "Player " << i << ":\n";
    std::cout << "\tScore: \t\t" << this_snake.GetScore() << std::endl;
    std::cout << "\tSnake size: \t" << this_snake.GetSize() << std::endl;
    std::cout << "\tSnake alive: \t" << this_snake.alive << std::endl;
    // sort scores of all players that survived
    if (this_snake.alive) {
      scores.push_back({"Player " + std::to_string(i), this_snake.GetScore()});
    }
  }
  std::sort(scores.begin(), scores.end(), [](const auto &lhs, const auto &rhs) {
    return lhs.second < rhs.second;
  });
  const auto &winner = scores.back();
  std::cout << "The winner is: " << winner.first
            << ", with a score of: " << winner.second << std::endl;
  ShowFinalScore(renderer.GetWindow(), winner);
  return 0;
}