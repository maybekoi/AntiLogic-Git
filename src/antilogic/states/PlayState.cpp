// PlayState.cpp
#include "../src/antilogic/states/PlayState.h"
#include <Engine.h>
#include <iostream>

PlayState* PlayState::instance = nullptr;

PlayState::PlayState() 
    : bg(nullptr)
    , questionText(nullptr)
    , credText(nullptr)
    , questionBox(nullptr)
    , audience(nullptr)
    , rightSpeechBubble(nullptr)
    , wrongSpeechBubble(nullptr)
    , currentQuestionIndex(0)
    , canClick(true) {
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

    credText = new Text(1020, 0, 1180);
    credText->setText(
    "Programmed by maybekoi\n"
    "Art by hubbabubbagym/codie\n"
    "Idea by kennedy\n"
    "Powered by hamburger engine!");
    credText->setFormat("assets/fonts/vcr.ttf", 16, 0xFFFFFFFF);
    engine->addText(credText);

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

void PlayState::onAnswerClick(int answerIndex) {
    if (!canClick) return;
    
    canClick = false; 
    
    rightSpeechBubble->setVisible(true);
    wrongSpeechBubble->setVisible(true);
    rightSpeechBubble->emoticon->setVisible(true);
    wrongSpeechBubble->emoticon->setVisible(true);
    
    if (questions[currentQuestionIndex].isRightTeamAnswer(answerIndex)) {
        rightSpeechBubble->emoticon->emoticon->playAnim("wrong_angry");
        wrongSpeechBubble->emoticon->emoticon->playAnim("right_smiley");
        audience->celebrateRight();
    } else {
        rightSpeechBubble->emoticon->emoticon->playAnim("wrong_smiley");
        wrongSpeechBubble->emoticon->emoticon->playAnim("right_angry");
        audience->celebrateWrong();
    }
    
    Engine* engine = Engine::getInstance();
    engine->setTimeout([this]() {
        canClick = true;
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
        }
    }, 1.5f);
}

void PlayState::update(float deltaTime) {
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
}

void PlayState::keyPressed(unsigned char key) {
    if (!canClick) return;
    
    int answerIndex = -1;
    if (key >= '1' && key <= '4') {
        answerIndex = key - '1';
        onAnswerClick(answerIndex);
    }
}