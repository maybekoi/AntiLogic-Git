#include <string>
#include <vector>

#include "Question.h"

Question::Question() {
    question = "";
    answers = {};
    correctIndex = 0;
    rightTeamAnswers = {};
    wrongTeamAnswers = {};
}

Question::Question(std::string question, std::vector<std::string> answers, int correctIndex, std::vector<int> rightTeamAnswers, std::vector<int> wrongTeamAnswers) {
    this->question = question;
    this->answers = answers;
    this->correctIndex = correctIndex;
    this->rightTeamAnswers = rightTeamAnswers;
    this->wrongTeamAnswers = wrongTeamAnswers;
}

bool Question::isRightTeamAnswer(int index) {
    return std::find(rightTeamAnswers.begin(), rightTeamAnswers.end(), index) != rightTeamAnswers.end();
}

bool Question::isWrongTeamAnswer(int index) {
    return std::find(wrongTeamAnswers.begin(), wrongTeamAnswers.end(), index) != wrongTeamAnswers.end();
}
