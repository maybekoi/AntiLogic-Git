// PlayState.h
#pragma once
#include <State.h>
#include <Sprite.h>
#include <AnimatedSprite.h>
#include <Text.h>
#include "../game/Question.h"
#include "../game/QuestionBox.h"
#include "../game/Audience.h"
#include <vector>

class PlayState : public State {
public:
    PlayState();
    ~PlayState();

    void create() override;
    void update(float deltaTime) override;
    void render() override;
    void destroy() override;
    void initializeQuestions();
    void setupUI();
    void showCurrentQuestion();
    static PlayState* instance;

private:
    Sprite* bg;
    Text* questionText;
    std::vector<Question> questions;
    QuestionBox* questionBox;
    std::vector<Text*> answerTexts;
    Audience* audience;
};
