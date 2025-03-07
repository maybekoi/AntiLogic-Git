#include "Audience.h"
#include <Engine.h>

Audience::Audience() : Sprite() {
    Engine* engine = Engine::getInstance();
    float windowWidth = engine->getWindowWidth();

    float rightStartX = windowWidth - (MEMBERS_PER_TEAM * MEMBER_SPACING) - 50;
    for (int i = 0; i < MEMBERS_PER_TEAM; i++) {
        AnimatedSprite* member = new AnimatedSprite();
        member->loadFrames("assets/images/audience_wrong.png", "assets/images/audience_wrong.xml");
        member->setPosition(rightStartX + (i * MEMBER_SPACING), 600);
        member->addAnimation("idle", "audience wrong idle instance", 24, true);
        member->addAnimation("yay", "audience wrong yay instance", 24, true);
        member->playAnim("idle");
        wrongTeam.push_back(member);
        engine->addAnimatedSprite(member);
    }

    float leftStartX = 50;
    for (int i = 0; i < MEMBERS_PER_TEAM; i++) {
        AnimatedSprite* member = new AnimatedSprite();
        member->loadFrames("assets/images/audience_right.png", "assets/images/audience_right.xml");
        member->setPosition(leftStartX + (i * MEMBER_SPACING), 600);
        member->addAnimation("idle", "audience right idle instance", 24, true);
        member->addAnimation("yay", "audience right yay instance", 24, true);
        member->playAnim("idle");
        rightTeam.push_back(member);
        engine->addAnimatedSprite(member);
    }
}

Audience::~Audience() {
    for (auto member : rightTeam) {
        delete member;
    }
    for (auto member : wrongTeam) {
        delete member;
    }
}

void Audience::update(float deltaTime) {
    for (auto member : rightTeam) {
        member->update(deltaTime);
    }
    for (auto member : wrongTeam) {
        member->update(deltaTime);
    }
}

void Audience::render() {
    for (auto member : rightTeam) {
        member->render();
    }
    for (auto member : wrongTeam) {
        member->render();
    }
}

void Audience::celebrateRight() {
    for (auto member : rightTeam) {
        member->playAnim("yay", true);
    }
}

void Audience::celebrateWrong() {
    for (auto member : wrongTeam) {
        member->playAnim("yay", true);
    }
}
