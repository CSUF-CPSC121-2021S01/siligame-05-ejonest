#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  Game mainGame;
  mainGame.Init();
  // mainGame.UpdateScreen(); from project 3
  mainGame.Start();
  return 0;
}

