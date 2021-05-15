#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"
class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : PlayerProjectile(0, 0) {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& screen) override;

 private:
  const graphics::Color color1{51, 204, 255};
  const graphics::Color color2{0, 102, 255};
  const graphics::Color color3{0, 51, 204};
};
class Player : public GameElement {
 public:
  Player() : Player(0, 0) {}
  Player(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& screen) override {}
};
#endif
