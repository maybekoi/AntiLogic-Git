#include "SpeechBubble.h"
#include <Engine.h>

SpeechBubble::SpeechBubble(float x, float y) : Sprite() {
    Engine* engine = Engine::getInstance();
    float windowWidth = engine->getWindowWidth();

    bubble = new AnimatedSprite();
    bubble->loadFrames("assets/images/textbox.png", "assets/images/textbox.xml");
    bubble->setPosition(x, y);
    bubble->addAnimation("idle", "text bubble instance", 24, true);
    bubble->playAnim("idle");
    engine->addAnimatedSprite(bubble);

    emoticon = new Emoticon(x, y);
    engine->addSprite(emoticon);
}

SpeechBubble::~SpeechBubble() {
    if (bubble) {
        delete bubble;
        bubble = nullptr;
    }
    if (emoticon) {
        delete emoticon;
        emoticon = nullptr;
    }
}

void SpeechBubble::update(float deltaTime) {
    if (bubble) {
        bubble->update(deltaTime);
    }
    if (emoticon) {
        emoticon->update(deltaTime);
    }
}

void SpeechBubble::render() {
    if (bubble) {
        bubble->render();
    }
    if (emoticon) {
        emoticon->render();
    }
}

void SpeechBubble::setVisible(bool visible) {
    if (bubble) {
        bubble->setVisible(visible);
    }
    if (emoticon) {
        emoticon->setVisible(visible);
        if (emoticon->emoticon) {
            emoticon->emoticon->setVisible(visible);
        }
    }
}
