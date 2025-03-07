#pragma once
#include <Engine.h>
#include <AnimatedSprite.h>
#include <vector>
#include "Emoticon.h"

class SpeechBubble : public Sprite {
public:
    SpeechBubble(float x = 0, float y = 0);
    ~SpeechBubble();

    void update(float deltaTime) override;
    void render() override;
    void setVisible(bool visible);

    AnimatedSprite* bubble;
    Emoticon* emoticon;
};