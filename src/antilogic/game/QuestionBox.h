#pragma once
#ifdef __MINGW32__ || defined(__SWITCH__)
#include "engine/Sprite.h"
#include "engine/AnimatedSprite.h"
#else
#include <Engine.h>
#include <AnimatedSprite.h>
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