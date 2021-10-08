#include "game.h"
int main() {
  Game mainGame;
  mainGame.Init();
  mainGame.Start(mainGame.GetGameScreen());
  return 0;
}
