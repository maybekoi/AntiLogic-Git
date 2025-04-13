// PlayState.h
#pragma once
#ifdef __MINGW32__ || defined(__SWITCH__)
#include "engine/State.h"
#include "engine/Sprite.h"
#include "engine/AnimatedSprite.h"
#include "engine/Text.h"
#include "engine/vector"
#include "engine/Input.h"
#else
#include <State.h>
#include <Sprite.h>
#include <AnimatedSprite.h>
#include <Text.h>
#include <vector>
#include <Input.h>
#endif
#include "../game/Question.h"
#include "../game/QuestionBox.h"
#include "../game/Audience.h"
#include "../game/SpeechBubble.h"

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
    void onAnswerClick(int answerIndex);
    void keyPressed(unsigned char key) override;
    static PlayState* instance;

private:
    Sprite* bg;
    Text* questionText;
    Text* credText;
    #ifdef __SWITCH__
    Text* controlsText;
    #endif
    Text* endingText = nullptr;
    std::vector<Question> questions;
    QuestionBox* questionBox;
    std::vector<Text*> answerTexts;
    Audience* audience;
    SpeechBubble* rightSpeechBubble;
    SpeechBubble* wrongSpeechBubble;
    std::vector<float> answerTextPositionsX;
    std::vector<float> answerTextPositionsY;
    int currentQuestionIndex;
    void showEnding(bool wasRightTeamDominant);
    int rightTeamChoices = 0;
    int wrongTeamChoices = 0;
    int correctAnswers = 0;
    bool isEnding = false;
};