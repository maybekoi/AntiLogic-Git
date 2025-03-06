#include <string>
#include <vector>
#include <algorithm>

#include "Question.h"

Question::Question(const std::string& question, 
                  const std::vector<std::string>& answers,
                  int correctIndex,
                  const std::vector<int>& rightTeamAnswers,
                  const std::vector<int>& wrongTeamAnswers)
    : question(question)
    , answers(answers)
    , correctIndex(correctIndex)
    , rightTeamAnswers(rightTeamAnswers)
    , wrongTeamAnswers(wrongTeamAnswers) {
}

bool Question::isRightTeamAnswer(int index) const {
    return std::find(rightTeamAnswers.begin(), rightTeamAnswers.end(), index) != rightTeamAnswers.end();
}

bool Question::isWrongTeamAnswer(int index) const {
    return std::find(wrongTeamAnswers.begin(), wrongTeamAnswers.end(), index) != wrongTeamAnswers.end();
}
