#pragma once
#include <Engine.h>
#include <AnimatedSprite.h>
#include <vector>

class Audience : public Sprite {
public:
    Audience();
    ~Audience();

    void update(float deltaTime) override;
    void render() override;
    void celebrateRight();
    void celebrateWrong();

private:
    static const int MEMBERS_PER_TEAM = 3;
    static const int MEMBER_SPACING = 100;

    std::vector<AnimatedSprite*> rightTeam;
    std::vector<AnimatedSprite*> wrongTeam;
};