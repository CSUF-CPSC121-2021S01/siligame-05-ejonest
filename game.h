#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"
#ifndef GAME_H
#define GAME_H
class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() { screen_.Initialize(800, 600); }
  Game(int width, int height) { screen_.Initialize(width, height); }
  graphics::Image &GetGameScreen() { return screen_; }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return playProj;
  }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return opProj;
  }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return opponent; }
  Player &GetPlayer() { return player; }
  void Init();
  void CreateOpponents();
  void MoveGameElements();
  void FilterIntersections();
  void UpdateScreen();
  void Start(graphics::Image &game) { game.ShowUntilClosed(); }
  void OnMouseEvent(const graphics::MouseEvent &event);
  void OnAnimationStep();
  void RemoveInactive();
  int GetScore() { return score; }
  bool HasLost() { return playerStatus_; }
  void LaunchProjectiles();

 private:
  graphics::Image screen_;
  std::vector<std::unique_ptr<Opponent>> opponent;
  std::vector<std::unique_ptr<OpponentProjectile>> opProj;
  std::vector<std::unique_ptr<PlayerProjectile>> playProj;
  Player player;
  int score = 0;
  bool playerStatus_ = true;
  int Op_On_Screen = 0;
};
#endif
