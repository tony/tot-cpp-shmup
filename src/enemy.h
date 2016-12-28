/* Copyright 2016 Tony Narlock. All rights reserved. */
#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

#include <spdlog/spdlog.h>
#include <array>
#include <memory>
#include <vector>
#include "actor.h"
#include "bullet.h"
#include "config.h"
#include "resource.h"
#include "ship.h"

class LevelStage;

typedef struct EnemyStats {
  unsigned int health = 2;
  unsigned int health_max = 2;
  unsigned int level = 1;
} EnemyStats;

class Enemy {
 public:
  Enemy(const std::shared_ptr<LevelStage>& stage,
        SDL2pp::Optional<SDL2pp::Point> position,
        SDL2pp::Point velocity = {-1, 0},
        int flip = 0);
  std::shared_ptr<Ship> ship;
  void Update();

 private:
  static SDL2pp::Point GenerateSpawnPosition() {
    int y = RandInt() % (MAIN_VIEWPORT_RECT.h - BOTTOM_VIEWPORT_RECT.h);
    return SDL2pp::Point(MAIN_VIEWPORT_RECT.w, y);
  }
};
#endif  // SRC_ENEMY_H_
