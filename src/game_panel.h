/* Copyright 2016 Tony Narlock. All rights reserved. */
#ifndef SRC_GAME_PANEL_H_
#define SRC_GAME_PANEL_H_

#include <SDL2pp/Font.hh>
#include <SDL2pp/SDL.hh>
#include <memory>
#include "resource.h"
#include "spdlog/spdlog.h"
#include "stats.h"

class LevelStage;

class GamePanel {
 public:
  GamePanel(const std::shared_ptr<StatService>& stat_service,
            const std::shared_ptr<LevelStage>& stage);
  void Update();
  const std::shared_ptr<StatService>& stat_service;
  const std::shared_ptr<SDL2pp::Texture>& GetStatsTexture();
  const std::shared_ptr<LevelStage>& stage;

 private:
  void DrawStats();

  std::string last_message_string;
};
#endif  // SRC_GAME_PANEL_H_
