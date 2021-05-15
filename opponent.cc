#include "opponent.h"
#include "cpputils/graphics/image.h"
void Opponent::Draw(graphics::Image& image) {
  graphics::Image picture1;
  picture1.Load("opponentSprite1.bmp");
  graphics::Color black(0, 0, 0);
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      graphics::Color curr_color = picture1.GetColor(j, i);
      if (curr_color != black) {
        image.SetColor(x_ + j, y_ + i, curr_color);
      }
    }
  }
}
void OpponentProjectile::Draw(graphics::Image& image) {
  image.DrawRectangle(x_ + 2, y_, 1, 5, color1);
  image.DrawRectangle(x_ + 1, y_ + 1, 3, 3, color1);
  image.DrawRectangle(x_, y_ + 2, 5, 1, color1);
  image.DrawRectangle(x_ + 2, y_ + 1, 1, 3, color2);
  image.DrawRectangle(x_ + 1, y_ + 2, 3, 1, color2);
  image.DrawRectangle(x_ + 2, y_ + 2, 1, 1, color3);
}
void Opponent::Move(const graphics::Image& image) {
  SetY(GetY() + 1);
  SetX(GetX() + 1);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}
void OpponentProjectile::Move(const graphics::Image& image) {
  SetY(GetY() + 1);
  SetX(GetX() + 1);
  if (IsOutOfBounds(image)) {
    SetIsActive(false);
  }
}
std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  if (rate >= 5) {
    rate = 0;
    std::unique_ptr<OpponentProjectile> FireBall;
    FireBall = std::make_unique<OpponentProjectile>();
    return std::move(FireBall);
  } else {
    rate++;
    return nullptr;
  }
}
