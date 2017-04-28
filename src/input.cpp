/* Copyright 2016 Tony Narlock. All rights reserved. */
#include "input.h"
#include "SDL2/SDL.h"

InputManager::InputManager() {
  keys = SDL_GetKeyboardState(nullptr);
}
