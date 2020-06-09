#include "prompt.h"
#include "SDL_log.h"
#include "SDL_messagebox.h"
#include "SDL_video.h"
#include <algorithm>
#include <assert.h>
#include <cstring>
#include <string>

bool QueryForNumberOfPlayers(SDL_Window *parent_window,
                             int &number_of_players) {
  SDL_MessageBoxButtonData buttons[4];
  buttons[0] = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Ok"};
  buttons[1] = {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Quit"};
  buttons[2] = {0, 2, "Up"};
  buttons[3] = {0, 3, "Down"};
  number_of_players = 1;

  char buffer[100];

  auto generateMessage = [&]() -> char * {
    strcpy(buffer,
           "Please change number of players by UP/DOWN. Current Number: ");
    strcat(buffer, std::to_string(number_of_players).c_str());
    return buffer;
  };

  SDL_MessageBoxData message_box;
  message_box.flags = SDL_MESSAGEBOX_INFORMATION;
  message_box.window = parent_window;
  message_box.title = "How many players want to play (max. 2)?";
  message_box.message = generateMessage();
  message_box.numbuttons = SDL_arraysize(buttons);
  message_box.buttons = buttons;
  message_box.colorScheme = NULL;

  int buttonId;
  while (SDL_ShowMessageBox(&message_box, &buttonId) == 0) {
    switch (buttonId) {
    case 0: {
      return true;
    }
    case 1: {
      return false;
    }
    case 2: {
      number_of_players = std::min(++number_of_players, 2);
      SDL_Log("Increased number of players by one.");
      break;
    }
    case 3: {
      number_of_players = std::max(1, --number_of_players);
      SDL_Log("Decreased number of players by one.");
      break;
    }
    default: {
      assert(false && "This case has not been handled.");
    }
    }
    // update message box with new number of players
    message_box.message = generateMessage();
  }
  return true;
}

void ShowFinalScore(SDL_Window *parent_window,
                    const std::pair<std::string, int> &winner) {
  SDL_MessageBoxButtonData buttons[1];
  buttons[0] = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Ok"};

  char buffer[100];
  strcpy(buffer, "And the winner is: ");
  strcat(buffer, winner.first.c_str());
  strcat(buffer, " with a score of ");
  strcat(buffer, std::to_string(winner.second).c_str());
  strcat(buffer, ". Thank you for playing!");

  SDL_MessageBoxData message_box;
  message_box.flags = SDL_MESSAGEBOX_INFORMATION;
  message_box.window = parent_window;
  message_box.title = "Final result:";
  message_box.message = buffer;
  message_box.numbuttons = SDL_arraysize(buttons);
  message_box.buttons = buttons;
  message_box.colorScheme = NULL;

  int buttonId;
  SDL_ShowMessageBox(&message_box, &buttonId);
}
