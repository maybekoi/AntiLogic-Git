#pragma once
#include <Engine.h>
#include <AnimatedSprite.h>
#include <vector>

class Emoticon : public Sprite {
public:
    Emoticon(float x = 0, float y = 0);
    ~Emoticon();

    void update(float deltaTime) override;
    void render() override;
    void setVisible(bool visible);

    AnimatedSprite* emoticon;
};