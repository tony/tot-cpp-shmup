/* Copyright 2016 Tony Narlock. All rights reserved. */
#ifndef SRC_INPUT_H_
#define SRC_INPUT_H_

class InputManager {
 public:
  InputManager();
  const Uint8* keys;
  inline constexpr bool down(const int key) {
    return static_cast<bool>(keys[key]);
  }
};
#endif  // SRC_INPUT_H_
