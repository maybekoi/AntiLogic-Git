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

class Audience : public Sprite {
public:
    Audience();
    ~Audience();

    void update(float deltaTime) override;
    void render() override;
    void celebrateRight();
    void celebrateWrong();

    const std::vector<AnimatedSprite*>& getRightTeam() const { return rightTeam; }
    const std::vector<AnimatedSprite*>& getWrongTeam() const { return wrongTeam; }

private:
    static const int MEMBERS_PER_TEAM = 3;
    static const int MEMBER_SPACING = 100;

    std::vector<AnimatedSprite*> rightTeam;
    std::vector<AnimatedSprite*> wrongTeam;
};