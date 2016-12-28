/* Copyright 2016 Tony Narlock. All rights reserved. */
#include "SDL2/SDL.h"
#include "input.h"

InputManager::InputManager() {
  keys = SDL_GetKeyboardState(nullptr);
}
