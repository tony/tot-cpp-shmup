/* Copyright 2016 Tony Narlock. All rights reserved. */
#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

#include <SDL2pp/Rect.hh>

const int SHIP_MAX_BULLETS = 80;

const SDL2pp::Rect SCREEN_RECT = {0, 0, 630, 480};

const SDL2pp::Rect BOTTOM_VIEWPORT_RECT = {
    0, static_cast<int>(SCREEN_RECT.h * .9), SCREEN_RECT.w,
    static_cast<int>(SCREEN_RECT.h * .1)};

const SDL2pp::Rect MAIN_VIEWPORT_RECT = {0, 0, SCREEN_RECT.w,
                                         static_cast<int>(SCREEN_RECT.h * .9)};
#endif  // SRC_CONFIG_H_
