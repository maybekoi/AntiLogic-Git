// PlayState.cpp
#include "../src/antilogic/states/PlayState.h"
#include <Engine.h>
#include <iostream>

PlayState* PlayState::instance = nullptr;

PlayState::PlayState() : bg(nullptr), questionText(nullptr), questionBox(nullptr), audience(nullptr) {
    instance = this;
}

PlayState::~PlayState() {
    destroy();
}

void PlayState::create() {
    Engine* engine = Engine::getInstance();

    initializeQuestions();
    setupUI();
}

void PlayState::setupUI() {
    Engine* engine = Engine::getInstance();
    bg = new Sprite("assets/images/bg.png");
    bg->setPosition(0, 0);
    engine->addSprite(bg);

    questionBox = new QuestionBox(50, 50);
    engine->addSprite(questionBox);

    questionText = new Text(50, 50, 1180);
    questionText->setText("epic question here lol");
    questionText->setFormat("assets/fonts/vcr.ttf", 24, 0xFFFFFFFF);
    engine->addText(questionText);

    answerTexts = std::vector<Text*>();
    
    answerTextPositionsX = {235.0f, 815.0f, 235.0f, 815.0f};
    answerTextPositionsY = {190.0f, 190.0f, 512.5f, 512.5f};

    for (int i = 0; i < 4; i++) {
        Text* text = new Text(answerTextPositionsX[i], answerTextPositionsY[i], 200);
        text->setText("answers here lol!");
        text->setFormat("assets/fonts/vcr.ttf", 20, 0xFFFFFFFF);
        engine->addText(text);
        answerTexts.push_back(text);
    }

    audience = new Audience();
    engine->addSprite(audience);
}

void PlayState::initializeQuestions() {
    std::vector<Question> newQuestions;
    
    newQuestions.push_back(Question(
        "What's the closest planet to the sun?",
        std::vector<std::string>{"Mercury", "Venus", "Earth", "Mars"},
        0,
        std::vector<int>{0},
        std::vector<int>{3, 1, 2}
    ));
    
    newQuestions.push_back(Question(
        "What is 2+2?",
        std::vector<std::string>{"3", "4", "5", "22"},
        1,
        std::vector<int>{1},
        std::vector<int>{0, 2, 3}
    ));
    
    newQuestions.push_back(Question(
        "What color is the sky?",
        std::vector<std::string>{"Red", "Green", "Blue", "Yellow"},
        2,
        std::vector<int>{2},
        std::vector<int>{0, 1, 3}
    ));
    
    newQuestions.push_back(Question(
        "What is a dog?",
        std::vector<std::string>{"A cat", "A fish", "A bird", "A mammal"},
        3,
        std::vector<int>{3},
        std::vector<int>{0, 1, 2}
    ));
    
    newQuestions.push_back(Question(
        "Who am I?",
        std::vector<std::string>{"A robot", "A human", "An alien", "Unknown"},
        1,
        std::vector<int>{1},
        std::vector<int>{0, 2, 3}
    ));
    
    questions = newQuestions;
}

void PlayState::update(float deltaTime) {
    if (questionBox) {
        questionBox->update(deltaTime);
    }
    if (audience) {
        audience->update(deltaTime);
    }
}

void PlayState::render() {
    if (bg) {
        bg->render();
    }
    if (questionBox) {
        questionBox->render();
    }
    if (questionText) {
        questionText->render();
    }
    if (audience) {
        audience->render();
    }
    for (Text* text : answerTexts) {
        if (text) {
            text->render();
        }
    }
}

void PlayState::destroy() {
    if (bg) {
        delete bg;
        bg = nullptr;
    }
    if (questionBox) {
        delete questionBox;
        questionBox = nullptr;
    }
    if (questionText) {
        delete questionText;
        questionText = nullptr;
    }
    if (audience) {
        delete audience;
        audience = nullptr;
    }
    for (Text* text : answerTexts) {
        if (text) {
            delete text;
            text = nullptr;
        }
    }
    answerTexts.clear();
}