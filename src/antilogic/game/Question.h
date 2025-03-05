#pragma once
#include <string>
#include <vector>

class Question {
public:
    Question();
    Question(std::string question, std::vector<std::string> answers, int correctIndex, 
             std::vector<int> rightTeamAnswers, std::vector<int> wrongTeamAnswers);

    bool isRightTeamAnswer(int index);
    bool isWrongTeamAnswer(int index);

    std::string question;
    std::vector<std::string> answers;
    int correctIndex;
    std::vector<int> rightTeamAnswers;
    std::vector<int> wrongTeamAnswers;
};

