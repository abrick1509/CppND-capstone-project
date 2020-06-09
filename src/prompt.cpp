#include "prompt.h"
#include "SDL_log.h"
#include "SDL_video.h"
#include <algorithm>
#include <assert.h>
#include <string>

Prompt::Prompt() {
  buttons[0] = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Ok"};
  buttons[1] = {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Quit"};
  buttons[2] = {0, 2, "Up"};
  buttons[3] = {0, 3, "Down"};
}

bool Prompt::Update(SDL_Window *parent_window, int &number_of_players) {
  number_of_players = 1;

  char buffer[100];

  auto generateMessage = [&]() -> char * {
    strcpy(buffer,
           "Please change number of players by UP/DOWN. Current Number: ");
    strcat(buffer, std::to_string(number_of_players).c_str());
    return buffer;
  };

  auto base_string = "Current number of players: ";
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
