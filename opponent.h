#ifndef OPPONENT_H
#define OPPONENT_H
#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"
class OpponentProjectile : public GameElement { 
    public:  
    OpponentProjectile() : OpponentProjectile(0, 0) {}  
    OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}  
    void Draw(graphics::Image& image) override;  
    void Move(const graphics::Image& screen) override; 
    private:  
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
    private:    
    bool going_right_ = true;
};
#endif
