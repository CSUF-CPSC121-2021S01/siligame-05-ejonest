#include "game.h"
void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent.size(); i++) {
    if (opponent[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> weapon;
      weapon = std::make_unique<OpponentProjectile>();
      weapon->SetX(opponent[i]->GetX());
      weapon->SetY(opponent[i]->GetY());
      opProj.push_back(std::move(weapon));
    }
  }
}
void Game::Init() {
  player.SetX(screen_.GetWidth() / 2);
  player.SetY(screen_.GetHeight() - 75);
  screen_.AddMouseEventListener(*this);
  screen_.AddAnimationEventListener(*this);
}
void Game::MoveGameElements() {
  for (int i = 0; i < playProj.size(); i++) {
    playProj[i]->Move(screen_);
  }
  for (int i = 0; i < opProj.size(); i++) {
    opProj[i]->Move(screen_);
  }
  for (int i = 0; i < opponent.size(); i++) {
    opponent[i]->Move(screen_);
  }
}
void Game::FilterIntersections() {
  for (int i = 0; i < opponent.size(); i++) {
    if (player.IntersectsWith(opponent[i].get())) {
      player.SetIsActive(false);
      opponent[i]->SetIsActive(false);
      playerStatus_ = false;
    }
  }
  for (int i = 0; i < playProj.size(); i++) {
    for (int j = 0; j < opponent.size(); j++) {
      if (playProj[i]->IntersectsWith(opponent[j].get()) == true) {
        playProj[i]->SetIsActive(false);
        opponent[j]->SetIsActive(false);
        score++;
      }
    }
  }
  for (int i = 0; i < opProj.size(); i++) {
    if (opProj[i]->IntersectsWith(&player)) {
      player.SetIsActive(false);
      opProj[i]->SetIsActive(false);
      playerStatus_ = false;
    }
  }
}
void Game::UpdateScreen() {
  screen_.DrawRectangle(0, 0, screen_.GetWidth(), screen_.GetHeight(),
                        graphics::Color(255, 255, 255));
  if (player.GetIsActive()) {
    player.Draw(screen_);
  }
  for (int i = 0; i < opponent.size(); i++) {
    if (opponent[i]->GetIsActive()) {
      opponent[i]->Draw(screen_);
    }
  }
  for (int i = 0; i < opProj.size(); i++) {
    if (opProj[i]->GetIsActive()) {
      opProj[i]->Draw(screen_);
    }
  }
  for (int i = 0; i < playProj.size(); i++) {
    if (playProj[i]->GetIsActive()) {
      playProj[i]->Draw(screen_);
    }
  }
  const std::string text = "Score: " + std::to_string(score);
  // x,y, const string& text, font size, red, green, blue
  screen_.DrawText(0, 0, text, 14, 10, 10, 10);
  if (playerStatus_ == false) {
    const std::string text = "GAME OVER";
    // x,y, const string& text, font size, red, green, blue
    screen_.DrawText(300, 256, text, 46, 10, 10, 10);
    // may need to make the player inactive
  }
}
void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  if (event.GetX() > 0 && event.GetY() > 0 &&
      event.GetX() < screen_.GetWidth() && event.GetY() < screen_.GetHeight()) {
    player.SetX(event.GetX() - 20);
    player.SetY(event.GetY() - 20);
  }
  if (event.GetMouseAction() == graphics::MouseAction::kPressed) {
    std::unique_ptr<PlayerProjectile> FireBall =
        std::make_unique<PlayerProjectile>(event.GetX(), event.GetY() + 20);
    playProj.push_back(std::move(FireBall));
  }
  if (event.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> FireBall =
        std::make_unique<PlayerProjectile>(event.GetX(), event.GetY() + 20);
    playProj.push_back(std::move(FireBall));
  }
}
void Game::OnAnimationStep() {
  if (opponent.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen_.Flush();
}
void Game::CreateOpponents() {
  for (int i = 0; i < 5; i++) {
    opponent.push_back(std::make_unique<Opponent>(100 * i, 50));
  }
}
void Game::RemoveInactive() {
  for (int i = opponent.size() - 1; i >= 0; i--) {
    if (!(opponent[i]->GetIsActive())) {
      opponent.erase(opponent.begin() + i);
    }
  }
  for (int i = opProj.size() - 1; i >= 0; i--) {
    if (!(opProj[i]->GetIsActive())) {
      opProj.erase(opProj.begin() + i);
    }
  }
  for (int i = playProj.size() - 1; i >= 0; i--) {
    if (!(playProj[i]->GetIsActive())) {
      playProj.erase(playProj.begin() + i);
    }
  }
}
