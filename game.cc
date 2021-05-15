#include "game.h"
#include <iostream>
#include <memory>
#include <vector>
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
void Game::LaunchProjectiles() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> weapon;
      weapon = std::make_unique<OpponentProjectile>();
      weapon->SetX(opponents_[i]->GetX());
      weapon->SetY(opponents_[i]->GetY());
      opponent_projectiles_.push_back(std::move(weapon));
    }
  }
}
void Game::Init() {
  my_player_.SetX(375);
  my_player_.SetY(500);
  game_screen_.AddMouseEventListener(*this);
  game_screen_.AddAnimationEventListener(*this);
}
void Game::CreateOpponents() {
  for (int i = 0; i < 5; i++) {
    std::unique_ptr<Opponent> my_opponent;  // ((100 * i), 20) constructor
    opponents_.push_back(std::move(
        my_opponent));  // May need to be a * not an & or none of the above
  }
}
void Game::MoveGameElements() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive()) {  // -> derefrences the pointers
      opponents_[i]->Move(game_screen_);
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive()) {
      opponent_projectiles_[i]->Move(game_screen_);
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive()) {
      player_projectiles_[i]->Move(game_screen_);
    }
  }
}
void Game::FilterIntersections() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (my_player_.IntersectsWith(opponents_[i].get())) {
      my_player_.SetIsActive(false);
      opponents_[i]->SetIsActive(false);
      playerStatus_ = false;
    }
  }

  for (int i = 0; i < player_projectiles_.size(); i++) {
    for (int j = 0; j < opponents_.size(); j++) {
      if (player_projectiles_[i]->IntersectsWith(opponents_[j].get()) == true) {
        player_projectiles_[i]->SetIsActive(false);
        opponents_[j]->SetIsActive(false);
        score_++;
      }
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->IntersectsWith(&my_player_)) {
      my_player_.SetIsActive(false);
      opponent_projectiles_[i]->SetIsActive(false);
      playerStatus_ = false;
    }
  }
}
void Game::UpdateScreen() {
  game_screen_.DrawRectangle(0, 0, game_screen_.GetWidth(),
                             game_screen_.GetHeight(),
                             graphics::Color(255, 255, 255));
  if (my_player_.GetIsActive()) {
    my_player_.Draw(game_screen_);
  }
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive()) {
      opponents_[i]->Draw(game_screen_);
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive()) {
      opponent_projectiles_[i]->Draw(game_screen_);
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive()) {
      player_projectiles_[i]->Draw(game_screen_);
    }
  }
  const std::string text = "Score: " + std::to_string(score_);
  // x,y, const string& text, font size, red, green, blue
  game_screen_.DrawText(0, 0, text, 14, 10, 10, 10);
  if (playerStatus_ == false) {
    const std::string text = "GAME OVER";
    // x,y, const string& text, font size, red, green, blue
    game_screen_.DrawText(400, 300, text, 46, 10, 10, 10);
    // may need to make the player inactive
  }
}
void Game::Start() { game_screen_.ShowUntilClosed(); }
void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int new_x = event.GetX() - my_player_.GetWidth() / 2;
    int new_y = event.GetY() - my_player_.GetHeight() / 2;
    int old_x = my_player_.GetX();
    int old_y = my_player_.GetY();
    my_player_.SetX(new_x);
    my_player_.SetY(new_y);
    if (my_player_.IsOutOfBounds(game_screen_)) {
      my_player_.SetX(old_x);
      my_player_.SetY(old_y);
    }
  }
  // may be wrong and/or need to remove the first if
  if (event.GetMouseAction() == graphics::MouseAction::kPressed ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> projectile;
    player_projectiles_.push_back(std::move(projectile));
  }
}
void Game::OnAnimationStep() {
  Op_On_Screen = 0;
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive()) {
      Op_On_Screen += 1;
    }
  }
  if (Op_On_Screen == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  /*
  UpdateScreen();
  game_screen_.Flush();
  */
}
int Game::GetScore() { return score_; }
bool Game::HasLost() {
  return playerStatus_;  // may need an if else
}
void Game::RemoveInactive() {
  int opCount = opponents_.size();
  int opProCount = opponent_projectiles_.size();
  int playProCount = player_projectiles_.size();
  if (!(my_player_.GetIsActive())) {
    // erase my_player_
  }
  for (int i = opCount; i > 0; i--) {
    if (!(opponents_[i]->GetIsActive())) {
      opponents_.erase(opponents_.begin() + i);
    }
  }
  for (int i = opProCount; i > 0; i--) {
    if (!(opponent_projectiles_[i]->GetIsActive())) {
      opponent_projectiles_.erase(opponent_projectiles_.begin() + i);
    }
  }
  for (int i = playProCount; i > 0; i--) {
    if (!(player_projectiles_[i]->GetIsActive())) {
      player_projectiles_.erase(player_projectiles_.begin() + i);
    }
  }
}
