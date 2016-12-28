/* Copyright 2016 Tony Narlock. All rights reserved. */
#ifndef SRC_BULLET_H_
#define SRC_BULLET_H_

#include <SDL2pp/Rect.hh>
#include <SDL2pp/SDL2pp.hh>
#include <memory>
#include "actor.h"
#include "resource.h"

class LevelStage;

typedef struct BulletStats {
  int speed = 1;
  int size = 1;
  int rate = 1;
  int damage = 1;
  bool knockback = false;
} BulletStats;

class Bullet : public Actor {
 public:
  Bullet(const std::shared_ptr<LevelStage>& stage,
         const std::shared_ptr<Actor>& parent,
         std::string texture_key = "bullet1",
         SDL2pp::Point position = {0, 0},
         SDL2pp::Point velocity = {9, 0});
  bool InBounds() const { return MAIN_VIEWPORT_RECT.Contains(position); }
  void Update() final;
  std::shared_ptr<BulletStats> stats;
  const std::shared_ptr<LevelStage>& stage;

 private:
  double tilt = 0;
  Uint32 last_scale = 0;
};
#endif  // SRC_BULLET_H_
