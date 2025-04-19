#pragma once
#ifdef __MINGW32__ || defined(__SWITCH__)
#include "../engine/graphics/Sprite.h"
#include "../engine/graphics/AnimatedSprite.h"
#include <vector>
#else
#include <graphics/Sprite.h>
#include <graphics/AnimatedSprite.h>
#include <vector>
#endif
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