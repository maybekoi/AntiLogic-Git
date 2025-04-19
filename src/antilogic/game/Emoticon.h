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

class Emoticon : public Sprite {
public:
    Emoticon(float x = 0, float y = 0);
    ~Emoticon();

    void update(float deltaTime) override;
    void render() override;
    void setVisible(bool visible);

    AnimatedSprite* emoticon;
};