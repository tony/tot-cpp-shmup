/* Copyright 2016 Tony Narlock. All rights reserved. */
#include "bullet.h"
#include "stage.h"
#include "config.h"

LevelStage::LevelStage(const std::unique_ptr<SDL2pp::Renderer>& renderer,
                       const std::unique_ptr<ResourceManager>& resource_manager,
                       const std::shared_ptr<spdlog::logger>& console)
    : renderer(renderer),
      resource_manager(resource_manager),
      console(console),
      bg_texture(resource_manager->GetTextureSheet("bg1")) {}

void LevelStage::HandleInput(const std::shared_ptr<InputManager>& input) {
  player->HandleInput(input);
}

void LevelStage::SpawnEnemy() {
  auto enemy =
      std::make_shared<Enemy>(shared_from_this(), SDL2pp::NullOpt,
                              SDL2pp::Point{-1, 0}, SDL_FLIP_HORIZONTAL);
  enemies.push_back(enemy);
}

void LevelStage::Update() {
  Uint32 now = SDL_GetTicks();
  if (now - last_bg_scroll >= 150) {
    bg_x_scroll++;
    last_bg_scroll = now;
  }
  if (bg_x_scroll >= bg_texture->GetWidth()) {
    bg_x_scroll = 0;
  }
  renderer->Copy(*bg_texture, SCREEN_RECT + SDL2pp::Point(bg_x_scroll, 0),
                 SDL2pp::NullOpt);

  game_panel->Update();
  player->ship->Update();

  // spawn enemies at interval since last spawn
  if (now - last_enemy >= 600) {
    SpawnEnemy();
    last_enemy = now;
  }

  // enemy update loop
  for (auto enemy = enemies.begin(); enemy != enemies.end();) {
    bool enemy_destroyed = false;
    (*enemy)->Update();
    for (auto bullet = player->ship->bullets.begin();
         bullet != player->ship->bullets.end();) {
      if ((*enemy)->ship->GetSubspriteRect().Intersects(
              (*bullet)->GetSubspriteRect())) {
        (*enemy)->ship->OnHitByBullet(*bullet);
        player->ship->bullets.erase(bullet);
        if ((*enemy)->ship->stats->health < 1) {
          enemy_destroyed = true;
        }
      } else {
        ++bullet;
      }
    }

    if (enemy_destroyed) {
      enemies.erase(enemy);
    } else {
      ++enemy;
    }
  }
}
