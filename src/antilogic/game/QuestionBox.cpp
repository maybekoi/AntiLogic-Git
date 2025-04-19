#include "QuestionBox.h"
#ifdef __MINGW32__ || defined(__SWITCH__)
#include "../engine/core/Engine.h"
#else
#include <core/Engine.h>
#endif

QuestionBox::QuestionBox(float x, float y) {
    Engine* engine = Engine::getInstance();
    
    float windowWidth = engine->getWindowWidth();   // 1280
    float windowHeight = engine->getWindowHeight(); // 720
    
    CENTER_WIDTH = windowWidth * 0.7f;
    CENTER_HEIGHT = windowHeight * 0.7f;  

    float leftX = windowWidth * 0.15f;     
    float rightX = windowWidth * 0.85f;     
    float topY = windowHeight * 0.15f;    
    float bottomY = windowHeight * 0.85f;  
    
    centerPiece = new Sprite("assets/images/questionbox_center.png");
    centerPiece->setPosition(290, 270);
    
    topLeft = new AnimatedSprite();
    topLeft->loadFrames("assets/images/questionbox.png", "assets/images/questionbox.xml");
    topLeft->setPosition(leftX, topY);
    topLeft->addAnimation("idle", "question base instance", 24, true);
    topLeft->playAnim("idle");

    topRight = new AnimatedSprite();
    topRight->loadFrames("assets/images/questionbox.png", "assets/images/questionbox.xml");
    topRight->setPosition(rightX, topY);
    topRight->addAnimation("idle", "question base instance", 24, true);
    topRight->playAnim("idle");
    topRight->setScale(-1.0f, 1.0f);

    bottomLeft = new AnimatedSprite();
    bottomLeft->loadFrames("assets/images/questionbox.png", "assets/images/questionbox.xml");
    bottomLeft->setPosition(leftX, bottomY);
    bottomLeft->addAnimation("idle", "question base instance", 24, true);
    bottomLeft->playAnim("idle");
    bottomLeft->setScale(1.0f, -1.0f);

    bottomRight = new AnimatedSprite();
    bottomRight->loadFrames("assets/images/questionbox.png", "assets/images/questionbox.xml");
    bottomRight->setPosition(rightX, bottomY);
    bottomRight->addAnimation("idle", "question base instance", 24, true);
    bottomRight->playAnim("idle");
    bottomRight->setScale(-1.0f, -1.0f);

    engine->addSprite(centerPiece);
    engine->addAnimatedSprite(topLeft);
    engine->addAnimatedSprite(topRight);
    engine->addAnimatedSprite(bottomLeft);
    engine->addAnimatedSprite(bottomRight);
}

QuestionBox::~QuestionBox() {
    delete centerPiece;
    delete topLeft;
    delete topRight;
    delete bottomLeft;
    delete bottomRight;
}

void QuestionBox::update(float deltaTime) {
    topLeft->update(deltaTime);
    topRight->update(deltaTime);
    bottomLeft->update(deltaTime);
    bottomRight->update(deltaTime);
}

void QuestionBox::render() {
    centerPiece->render();
    topLeft->render();
    topRight->render();
    bottomLeft->render();
    bottomRight->render();
}