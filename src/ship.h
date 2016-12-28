/* Copyright 2016 Tony Narlock. All rights reserved. */
#ifndef SRC_SHIP_H_
#define SRC_SHIP_H_

#include <spdlog/spdlog.h>
#include <memory>
#include <vector>
#include "actor.h"
#include "bullet.h"
#include "input.h"
#include "resource.h"

class LevelStage;

typedef struct ShipStats {
  int health = 100;
  int health_max = 100;
  int level = 1;
} ShipStats;

class Ship : public Actor, public std::enable_shared_from_this<Ship> {
 public:
  Ship(const std::shared_ptr<LevelStage>& stage,
       const std::string& texture_key,
       SDL2pp::Point position,
       SDL2pp::Point velocity = {0, 0},
       const std::shared_ptr<ShipStats>& stats = std::make_shared<ShipStats>(),
       int flip = 0);

  void Update() final;
  void OnHitByBullet(std::shared_ptr<Bullet> bullet);
  int GetFlip() const { return flip; }
  void SetHit(bool h) { hit = h; }
  void SpawnBullet(void);
  std::shared_ptr<ShipStats> stats;
  std::vector<std::shared_ptr<Bullet>> bullets;
  const std::shared_ptr<LevelStage>& stage;
  const std::shared_ptr<spdlog::logger>& console;
};

class PlayerShip : public Ship {
 public:
  PlayerShip(
      const std::shared_ptr<LevelStage>& stage,
      const std::string& texture_key,
      SDL2pp::Point position,
      SDL2pp::Point velocity = {0, 0},
      const std::shared_ptr<ShipStats>& stats = std::make_shared<ShipStats>(),
      int flip = 0);
  void HandleInput(const std::shared_ptr<InputManager>& input);
};

class Player {
 public:
  Player(const std::shared_ptr<LevelStage>& stage);

  void HandleInput(const std::shared_ptr<InputManager>& input);
  std::shared_ptr<PlayerShip> ship;
};
#endif  // SRC_SHIP_H_
