/* Copyright 2016 Tony Narlock. All rights reserved. */
#include "ship.h"
#include "config.h"
#include "resource.h"
#include "stage.h"
#include "util.h"

PlayerShip::PlayerShip(const std::shared_ptr<LevelStage>& stage,
                       const std::string& texture_key,
                       SDL2pp::Point position,
                       SDL2pp::Point velocity,
                       const std::shared_ptr<ShipStats>& stats,
                       int flip)
    : Ship(stage, texture_key, position, velocity, stats, flip) {}

Player::Player(const std::shared_ptr<LevelStage>& stage)
    : ship(std::make_shared<PlayerShip>(stage,
                                        "ship1",
                                        SDL2pp::Point{30, 30},
                                        SDL2pp::Point{0, 0})) {}

void Player::HandleInput(const std::shared_ptr<InputManager>& input) {
  ship->HandleInput(input);
}

void PlayerShip::HandleInput(const std::shared_ptr<InputManager>& input) {
  if (input->down(SDL_SCANCODE_UP) || input->down(SDL_SCANCODE_W) ||
      input->down(SDL_SCANCODE_K)) {
    state = ActorState::UP;
    position.y =
        clamp(position.y - static_cast<int>(MAIN_VIEWPORT_RECT.h * 0.01), 0,
              MAIN_VIEWPORT_RECT.h - GetSprite()->GetHeight());
  }

  if (input->down(SDL_SCANCODE_DOWN) || input->down(SDL_SCANCODE_S) ||
      input->down(SDL_SCANCODE_J)) {
    state = ActorState::DOWN;
    position.y =
        clamp(position.y + static_cast<int>(MAIN_VIEWPORT_RECT.h * 0.01), 0,
              MAIN_VIEWPORT_RECT.h - GetSprite()->GetHeight());
  }

  if (input->down(SDL_SCANCODE_LEFT) || input->down(SDL_SCANCODE_A) ||
      input->down(SDL_SCANCODE_H)) {
    state = ActorState::LEFT;
    position.x = clamp(position.x - static_cast<int>(SCREEN_RECT.w * 0.01), 0,
                       SCREEN_RECT.w - GetSprite()->GetWidth());
  }

  if (input->down(SDL_SCANCODE_RIGHT) || input->down(SDL_SCANCODE_D) ||
      input->down(SDL_SCANCODE_L)) {
    state = ActorState::RIGHT;
    position.x = clamp(position.x + static_cast<int>(SCREEN_RECT.w * 0.01), 0,
                       SCREEN_RECT.w - GetSprite()->GetWidth());
  }

  if (input->down(SDL_SCANCODE_SPACE)) {
    Uint32 now = SDL_GetTicks();
    if (now - last_shot >= shooting_delay) {
      SpawnBullet();
      last_shot = now;
    }
  }
}

Ship::Ship(const std::shared_ptr<LevelStage>& stage,
           const std::string& texture_key,
           SDL2pp::Point position,
           SDL2pp::Point velocity,
           const std::shared_ptr<ShipStats>& stats,
           int flip)
    : Actor(stage->renderer,
            stage->resource_manager,
            texture_key,
            position,
            velocity,
            flip),
      stats(std::move(stats)),
      stage(stage),
      console(stage->console) {}

void Ship::Update() {
  if (GetHit()) {
    renderer->Copy(
        *resource_manager->GetTexture("ship1_hit"),
        SDL2pp::Rect{0, 0, GetSubspriteRect().w, GetSubspriteRect().h},
        GetPosition(), 0, SDL2pp::NullOpt, GetFlip());
    Uint32 now = SDL_GetTicks();
    if (now - GetLastHit() >= 100) {
      SetHit(false);
    }
  } else {
    renderer->Copy(
        *resource_manager->GetTexture(GetTextureKey()),
        SDL2pp::Rect{0, 0, GetSubspriteRect().w, GetSubspriteRect().h},
        GetPosition(), 0, SDL2pp::NullOpt, GetFlip());
  }

  // bullet drawing and clean up
  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [](auto& b) { return !b->InBounds(); }),
                bullets.end());
  for (auto& bullet : bullets) {
    bullet->Update();
  }
}

void Ship::SpawnBullet() {
  if (bullets.size() < SHIP_MAX_BULLETS) {
    bullets.push_back(std::make_shared<Bullet>(
        stage, std::static_pointer_cast<Actor>(shared_from_this()), "bullet1"));
  }
}

void Ship::OnHitByBullet(std::shared_ptr<Bullet> bullet) {
  hit = true;
  last_hit = SDL_GetTicks();
  stats->health -= bullet->stats->damage;
  console->info("hit for {}, {}/{}", bullet->stats->damage, stats->health,
                stats->health_max);
}
