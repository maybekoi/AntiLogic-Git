#include "Emoticon.h"
#include <Engine.h>

Emoticon::Emoticon(float x, float y) : Sprite() {
    Engine* engine = Engine::getInstance();
    float windowWidth = engine->getWindowWidth();

    emoticon = new AnimatedSprite();
    emoticon->loadFrames("assets/images/emotes.png", "assets/images/emotes.xml");
    emoticon->setPosition(x, y);
    emoticon->addAnimation("right_angry", "angry right 0000", 24, true);
    emoticon->addAnimation("wrong_angry", "angry wrong 0000", 24, true);
    emoticon->addAnimation("right_smiley", "smiley right 0000", 24, true);
    emoticon->addAnimation("wrong_smiley", "smiley wrong 0000", 24, true);
    emoticon->playAnim("right_angry");
    engine->addAnimatedSprite(emoticon);
}

Emoticon::~Emoticon() {
    if (emoticon) {
        delete emoticon;
    }
}

void Emoticon::update(float deltaTime) {
    if (emoticon) {
        emoticon->update(deltaTime);
    }
}

void Emoticon::render() {
    if (emoticon) {
        emoticon->render();
    }
}

void Emoticon::setVisible(bool visible) {
    Sprite::setVisible(visible);
    if (emoticon) {
        emoticon->setVisible(visible);
    }
}
