/* Copyright 2016 Tony Narlock. All rights reserved. */
#include <SDL2/SDL.h>
#include <sstream>
#include "config.h"
#include "game_panel.h"
#include "stage.h"
#include "util.h"

GamePanel::GamePanel(const std::shared_ptr<StatService>& stat_service,
                     const std::shared_ptr<LevelStage>& stage)
    : stat_service(stat_service), stage(stage), last_message_string("") {}

void GamePanel::Update() {
  DrawStats();
}

const std::shared_ptr<SDL2pp::Texture>& GamePanel::GetStatsTexture() {
  std::stringstream stats_stream;
  auto text_position = SDL2pp::Point{5, 25};

  std::string ship_text;
  if (stat_service->ship) {
    stats_stream << "health " << stat_service->ship->health << " / "
                 << stat_service->ship->health_max;
    ship_text = stats_stream.str();
  } else {
    ship_text = "ship not loaded";
  }

  if (last_message_string.empty() ||
      last_message_string.compare(ship_text) != 0) {
    stage->console->info("game_panel rendering new texture for message: {}",
                         ship_text);
    last_message_string = ship_text;
    stage->resource_manager->AddTexture(
        "game_panel_text",
        DrawText(ship_text, text_position,
                 stage->resource_manager->GetFont("terminus-18"),
                 stage->renderer, true));
  }
  return stage->resource_manager->GetTexture("game_panel_text");
}

void GamePanel::DrawStats() {
  stage->renderer->SetViewport(BOTTOM_VIEWPORT_RECT);
  auto message = GetStatsTexture();
  if (last_message_string.length() > 0) {
    SDL2pp::Rect message_rect = {5, 25, message->GetWidth(),
                                 message->GetHeight()};

    stage->renderer->Copy(*message, message_rect, message_rect);
  }
  stage->renderer->SetViewport(MAIN_VIEWPORT_RECT);
}
