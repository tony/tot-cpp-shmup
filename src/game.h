/* Copyright 2016 Tony Narlock. All rights reserved. */
#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>
#include <memory>
#include <vector>
#include "spdlog/spdlog.h"

class Actor;
class GamePanel;
class InputManager;
class LevelStage;
class ResourceManager;
class Ship;
class StatService;
struct ShipStats;

class Game {
 public:
  explicit Game(const std::shared_ptr<spdlog::logger>& console);
  void MainLoop();

 private:
  SDL2pp::SDL sdl;
  SDL2pp::SDLTTF sdl_ttf;
  SDL2pp::SDLImage image;
  SDL2pp::Window window;
  std::unique_ptr<SDL2pp::Renderer> renderer;
  std::unique_ptr<ResourceManager> resource_manager;
  std::shared_ptr<StatService> stat_service;
  std::shared_ptr<InputManager> input;
  const std::shared_ptr<spdlog::logger>& console;
  std::shared_ptr<LevelStage> stage;
  bool quit = false;
  void HandleEvent(const SDL_Event* e, bool* quit);
};
#endif  // SRC_GAME_H_
