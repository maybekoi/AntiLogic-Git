// PlayState.cpp
#ifdef __MINGW32__
#include "../src/antilogic/states/PlayState.h"
#include "../engine/core/Engine.h"
#include <iostream>
#include "../engine/input/Input.h"
#elif defined(__SWITCH__)
#include "../src/antilogic/states/PlayState.h"
#include "../engine/core/Engine.h"
#include <iostream>
#include "../engine/input/Input.h"
#include <switch.h>
#else
#include "../src/antilogic/states/PlayState.h"
#include <core/Engine.h>
#include <iostream>
#include <input/Input.h>
#include <utils/Discord.h>
#endif

PlayState* PlayState::instance = nullptr;

PlayState::PlayState() 
    : bg(nullptr)
    , questionText(nullptr)
    , credText(nullptr)
    , endingText(nullptr)
    , questionBox(nullptr)
    , audience(nullptr)
    , rightSpeechBubble(nullptr)
    , wrongSpeechBubble(nullptr)
    , currentQuestionIndex(0)
    , rightTeamChoices(0)
    , wrongTeamChoices(0)
    , correctAnswers(0)
    , isEnding(false) {
    instance = this;
}

PlayState::~PlayState() {
    destroy();
}

void PlayState::create() {
    Engine* engine = Engine::getInstance();

    initializeQuestions();
    setupUI();
    showCurrentQuestion();
}

void PlayState::setupUI() {
    Engine* engine = Engine::getInstance();

    bg = new Sprite("assets/images/bg.png");
    bg->setPosition(0, 0);
    engine->addSprite(bg);

    credText = new Text(0, 0, 1180);
    credText->setText(
    "Programmed by maybekoi\n"
    "Art by hubbabubbagym/codie\n"
    "Idea by kennedy\n"
    "Powered by hamburger engine!");
    credText->setFormat("assets/fonts/vcr.ttf", 16, 0xFFFFFFFF);
    engine->addText(credText);

    #ifdef __SWITCH__
    controlsText = new Text(1100, 0, 1180);
    controlsText->setText(
    "Controller Controls:\n"
    "A - Top Left\n"
    "B - Top Right\n"
    "X - Bottom Left\n"
    "Y - Bottom Right\n"
    "+ - Quit\n"
    "- - Quit");
    controlsText->setFormat("assets/fonts/vcr.ttf", 16, 0xFFFFFFFF);
    engine->addText(controlsText);
    #endif

    questionBox = new QuestionBox(50, 50);
    engine->addSprite(questionBox);

    questionText = new Text(390, 50, 1180);
    questionText->setText("epic question here lol");
    questionText->setFormat("assets/fonts/vcr.ttf", 24, 0xFFFFFFFF);
    engine->addText(questionText);

    answerTexts = std::vector<Text*>();
    
    answerTextPositionsX = {285.0f, 890.0f, 285.0f, 890.0f};
    answerTextPositionsY = {190.0f, 190.0f, 512.5f, 512.5f};

    for (int i = 0; i < 4; i++) {
        Text* text = new Text(answerTextPositionsX[i], answerTextPositionsY[i], 200);
        text->setText("answers here lol!");
        text->setFormat("assets/fonts/vcr.ttf", 20, 0xFFFFFFFF);
        engine->addText(text);
        answerTexts.push_back(text);
    }

    rightSpeechBubble = new SpeechBubble(1150, 450);
    wrongSpeechBubble = new SpeechBubble(77, 450);
    
    if (rightSpeechBubble && rightSpeechBubble->emoticon && rightSpeechBubble->emoticon->emoticon) {
        rightSpeechBubble->emoticon->emoticon->setPosition(1085, 465);
    }
    if (wrongSpeechBubble && wrongSpeechBubble->emoticon && wrongSpeechBubble->emoticon->emoticon) {
        wrongSpeechBubble->emoticon->emoticon->setPosition(135, 465);
    }
    
    if (rightSpeechBubble && rightSpeechBubble->bubble) {
        rightSpeechBubble->bubble->setScale(-1.0f, 1.0f);
    }
    if (rightSpeechBubble && rightSpeechBubble->emoticon && rightSpeechBubble->emoticon->emoticon) {
        rightSpeechBubble->emoticon->emoticon->setScale(-1.0f, 1.0f);
    }
    
    rightSpeechBubble->setVisible(false);
    wrongSpeechBubble->setVisible(false);
    if (rightSpeechBubble && rightSpeechBubble->emoticon) {
        rightSpeechBubble->emoticon->setVisible(false);
    }
    if (wrongSpeechBubble && wrongSpeechBubble->emoticon) {
        wrongSpeechBubble->emoticon->setVisible(false);
    }
    
    engine->addSprite(rightSpeechBubble);
    engine->addSprite(wrongSpeechBubble);

    audience = new Audience();
    engine->addSprite(audience);
}

void PlayState::showCurrentQuestion() {
    questionText->setText(questions[currentQuestionIndex].getQuestion());
    for (int i = 0; i < 4; i++) {
        answerTexts[i]->setText(questions[currentQuestionIndex].getAnswers()[i]);
    }
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
        "Finish the sentence: 'I am '",
        std::vector<std::string>{"Him", "Human", "Alien", "God"},
        0,
        std::vector<int>{3},
        std::vector<int>{0, 1, 2}
    ));

    newQuestions.push_back(Question(
        "SDRAWKCAB NOITSEUQ SIHT REWSNA",
        std::vector<std::string>{"KO", "What?", "I do not understand", "Tennis Elbow"},
        0,
        std::vector<int>{0},
        std::vector<int>{1, 2, 3}
    ));   

    newQuestions.push_back(Question(
        "What was the original vesion of this quiz coded in?",
        std::vector<std::string>{"Javascript", "C#", "Java", "Haxe"},
        0,
        std::vector<int>{3},
        std::vector<int>{0, 1, 2}
    ));   

    newQuestions.push_back(Question(
        "Who owns X.com?",
        std::vector<std::string>{"Elon Musk", "Jack Ma", "Satoshi Nakamoto", "Tim Cook"},
        0,
        std::vector<int>{0},
        std::vector<int>{1, 2, 3}
    ));  
    
    newQuestions.push_back(Question(
        "Is scratch and its forks for babies?",
        std::vector<std::string>{"Yes", "Yes", "Yes", "No"},
        0,
        std::vector<int>{0, 1, 2},
        std::vector<int>{3}
    ));

    newQuestions.push_back(Question(
        "Finish the quote: 'Sonic's the name, ...'s my game! '",
        std::vector<std::string>{"Chilidogs", "What??", "speed", "No"},
        0,
        std::vector<int>{0, 1, 2},
        std::vector<int>{3}
    ));

    newQuestions.push_back(Question(
        "What is the capital of France?",
        std::vector<std::string>{"Paris", "London", "Berlin", "Madrid"},
        0,
        std::vector<int>{0},
        std::vector<int>{1, 2, 3}
    ));

    newQuestions.push_back(Question(
        "I can see you.",
        std::vector<std::string>{"What?", "Liar!", "Oh...", "Okay"},
        0,
        std::vector<int>{2},
        std::vector<int>{0, 1, 3}
    ));

    newQuestions.push_back(Question(
        "Who made this game/quiz?",
        std::vector<std::string>{"maybekoi", "idk lol", "Sega", "Nintendo"},
        0,
        std::vector<int>{0},
        std::vector<int>{1, 2, 3}
    ));
    
    questions = newQuestions;
}

void PlayState::showEnding(bool wasRightTeamDominant) {
    isEnding = true;
    questionText->setVisible(false);
    questionBox->setVisible(false);
    for (auto text : answerTexts) {
        text->setVisible(false);
    }

    endingText = new Text(390, 50, 1180);
    
    if (wasRightTeamDominant) {
        endingText->setText(
            "You sided with the right team most of the time...\n"
            "but at what cost?\n"
            "Half of the audience leaves disappointed.\n"
            "BAD ENDING?..."
        );
        endingText->setFormat("assets/fonts/vcr.ttf", 24, 0xFF0000FF);
    } else {
        endingText->setText(
            "You mostly listened to wrong team's answers!\n"
            "Some people had fun and made new friends.\n"
            "GOOD ENDING?..."
        );
        endingText->setFormat("assets/fonts/vcr.ttf", 24, 0x00FF00FF);
    }

    Engine* engine = Engine::getInstance();
    engine->addText(endingText);
}

void PlayState::onAnswerClick(int answerIndex) {    
    rightSpeechBubble->setVisible(true);
    wrongSpeechBubble->setVisible(true);
    rightSpeechBubble->emoticon->setVisible(true);
    wrongSpeechBubble->emoticon->setVisible(true);
    
    Question& question = questions[currentQuestionIndex];
    if (question.isRightTeamAnswer(answerIndex)) {
        rightTeamChoices++;
        correctAnswers++;
        audience->celebrateRight();
        rightSpeechBubble->emoticon->emoticon->playAnim("wrong_angry");
        wrongSpeechBubble->emoticon->emoticon->playAnim("right_smiley");
    } else if (question.isWrongTeamAnswer(answerIndex)) {
        wrongTeamChoices++;
        audience->celebrateWrong();
        rightSpeechBubble->emoticon->emoticon->playAnim("wrong_smiley");
        wrongSpeechBubble->emoticon->emoticon->playAnim("right_angry");
    }
    
    Engine* engine = Engine::getInstance();
    engine->setTimeout([this]() {
        rightSpeechBubble->setVisible(false);
        wrongSpeechBubble->setVisible(false);        
        for (auto member : audience->getRightTeam()) {
            member->playAnim("idle");
        }
        for (auto member : audience->getWrongTeam()) {
            member->playAnim("idle");
        }
        currentQuestionIndex++;
        if (currentQuestionIndex < questions.size()) {
            showCurrentQuestion();
        } else {
            showEnding(rightTeamChoices > wrongTeamChoices);
        }
    }, 1.5f);
}

void PlayState::update(float deltaTime) {
    if (isEnding) return;

    Input::UpdateKeyStates();
    Input::UpdateControllerStates();

    if (Input::isControllerButtonJustPressed(SDL_CONTROLLER_BUTTON_A)) {
        onAnswerClick(0);
    } else if (Input::isControllerButtonJustPressed(SDL_CONTROLLER_BUTTON_B)) {
        onAnswerClick(1);
    } else if (Input::isControllerButtonJustPressed(SDL_CONTROLLER_BUTTON_X)) {
        onAnswerClick(2);
    } else if (Input::isControllerButtonJustPressed(SDL_CONTROLLER_BUTTON_Y)) {
        onAnswerClick(3);
    }

    Engine* engine = Engine::getInstance();
    
    if (questionBox) {
        questionBox->update(deltaTime);
    }
    if (audience) {
        audience->update(deltaTime);
    }
    if (rightSpeechBubble) {
        rightSpeechBubble->update(deltaTime);
    }
    if (wrongSpeechBubble) {
        wrongSpeechBubble->update(deltaTime);
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
    if (rightSpeechBubble) {
        rightSpeechBubble->render();
    }
    if (wrongSpeechBubble) {
        wrongSpeechBubble->render();
    }
    for (Text* text : answerTexts) {
        if (text) {
            text->render();
        }
    }
    if (credText) {
        credText->render();
    }
    if (endingText) {
        endingText->render();
    }
    #ifdef __SWITCH__
    if (controlsText) {
        controlsText->render();
    }
    #endif
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
    if (rightSpeechBubble) {
        delete rightSpeechBubble;
        rightSpeechBubble = nullptr;
    }
    if (wrongSpeechBubble) {
        delete wrongSpeechBubble;
        wrongSpeechBubble = nullptr;
    }
    for (Text* text : answerTexts) {
        if (text) {
            delete text;
        }
    }
    answerTexts.clear();
    if (endingText) {
        delete endingText;
        endingText = nullptr;
    }
}

void PlayState::keyPressed(unsigned char key) {
    if (isEnding) return;

    int keyNum = key - '0';
    if (keyNum >= 1 && keyNum <= 4) {
        onAnswerClick(keyNum - 1);
    }
}