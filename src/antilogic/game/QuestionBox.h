#pragma once
#ifdef __MINGW32__ || defined(__SWITCH__)
#include "../engine/graphics/Sprite.h"
#include "../engine/graphics/AnimatedSprite.h"
#else
#include <graphics/Sprite.h>
#include <graphics/AnimatedSprite.h>
#endif

class QuestionBox : public Sprite {
public:
    QuestionBox(float x, float y);
    ~QuestionBox();

    void update(float deltaTime) override;  
    void render() override; 

private:
    AnimatedSprite* topLeft;
    AnimatedSprite* topRight;
    AnimatedSprite* bottomLeft;
    AnimatedSprite* bottomRight;
    Sprite* centerPiece;

    float CENTER_WIDTH;
    float CENTER_HEIGHT;
};