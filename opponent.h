#ifndef OPPONENT_H
#define OPPONENT_H
#include <memory>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"
class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  void Draw(graphics::Image& image) override;
  void Move(const graphics::Image& screen) override;
  // storing for launch projectile
  void SetCounter() {
    if (counter_ <= 9) {
      counter_ += 1;
    } else {
      counter_ = 0;
    }
  }
  // int GetCounter() { return counter_; }
  // pretty sure I don't need that

 private:
  int counter_;
  const graphics::Color color1{255, 51, 0};
  const graphics::Color color2{255, 153, 0};
  const graphics::Color color3{255, 255, 26};
};
class Opponent : public GameElement {
 public:
  Opponent() : Opponent(0, 0) {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image& image) override;
  void Move(const graphics::Image& screen) override;
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();

 private:
  bool going_right_ = true;
  int rate_ = 0;
};
#endif
