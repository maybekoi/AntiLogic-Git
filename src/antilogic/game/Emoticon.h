#pragma once
#ifdef __MINGW32__ || defined(__SWITCH__)
#include "engine/Sprite.h"
#include "engine/AnimatedSprite.h"
#include <vector>
#else
#include <Engine.h>
#include <AnimatedSprite.h>
#include <vector>
#endif

class Emoticon : public Sprite {
public:
    Emoticon(float x = 0, float y = 0);
    ~Emoticon();

    void update(float deltaTime) override;
    void render() override;
    void setVisible(bool visible);

    AnimatedSprite* emoticon;
};