// PlayState.h
#pragma once
#include <State.h>
#include <Sprite.h>
#include <AnimatedSprite.h>
#include <Text.h>
#include <vector>
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