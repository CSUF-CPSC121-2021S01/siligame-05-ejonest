#include <memory>
#include "game_element.h"
#ifndef OPPONENT_H
#define OPPONENT_H
class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile(int x, int y) : GameElement(0, 0, 0, 0) {}
  OpponentProjectile() : GameElement(0, 0, 5, 5) {}
  void Draw(graphics::Image &screen_);
  void Move(const graphics::Image &image);

 private:
  const graphics::Color color1{255, 51, 0};
  const graphics::Color color2{255, 153, 0};
  const graphics::Color color3{255, 255, 26};
};
class Opponent : public GameElement {
 public:
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  Opponent() : GameElement(0, 0, 50, 50) {}
  void Draw(graphics::Image &screen_);
  void Move(const graphics::Image &image);
  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int rate = 0;
  bool going_right_ = true;
};
#endif
