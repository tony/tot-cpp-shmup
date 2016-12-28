/* Copyright 2016 Tony Narlock. All rights reserved. */
#ifndef SRC_STAGE_H_
#define SRC_STAGE_H_

#include <spdlog/spdlog.h>
#include "actor.h"
#include "ship.h"
#include "enemy.h"
#include "game_panel.h"
#include "input.h"
#include <SDL2pp/SDL2pp.hh>
#include <vector>

class Stage {
 public:
  virtual void HandleInput(const std::shared_ptr<InputManager>& input) = 0;
  virtual void Update() = 0;
};

class LevelStage : public Stage,
                   public std::enable_shared_from_this<LevelStage> {
 public:
  LevelStage(const std::unique_ptr<SDL2pp::Renderer>& renderer,
             const std::unique_ptr<ResourceManager>& resource_manager,
             const std::shared_ptr<spdlog::logger>& console);
  void HandleInput(const std::shared_ptr<InputManager>& input) final;
  void Update() final;
  void SpawnEnemy();
  const std::unique_ptr<SDL2pp::Renderer>& renderer;
  const std::unique_ptr<ResourceManager>& resource_manager;
  const std::shared_ptr<spdlog::logger>& console;
  std::shared_ptr<GamePanel> game_panel;
  std::shared_ptr<Player> player;

 private:
  const std::shared_ptr<SDL2pp::Texture>& bg_texture;
  std::vector<std::shared_ptr<Enemy>> enemies;
  Uint32 last_enemy = 0;
  int bg_x_scroll = 0;
  Uint32 last_bg_scroll = 0;
};
#endif  // SRC_STAGE_H_
