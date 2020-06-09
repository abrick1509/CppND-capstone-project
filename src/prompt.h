#ifndef PROMPT_H
#define PROMPT_H

#include "SDL.h"
#include "SDL_messagebox.h"
#include "SDL_video.h"

class Prompt {
public:
  Prompt();

  bool Update(SDL_Window *parent_window, int &number_of_players);

private:
  SDL_MessageBoxData message_box;
  SDL_MessageBoxButtonData buttons[4];
};

#endif