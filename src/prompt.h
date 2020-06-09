#ifndef PROMPT_H
#define PROMPT_H

#include "SDL.h"
#include "SDL_messagebox.h"
#include "SDL_video.h"
#include <string>

bool QueryForNumberOfPlayers(SDL_Window *parent_window, int &number_of_players);

void ShowFinalScore(SDL_Window *parent_window,
                    const std::pair<std::string, int> &winner);

#endif