#pragma once
#include <string>
#include <vector>

class Question {
public:
    Question(const std::string& question, 
            const std::vector<std::string>& answers,
            int correctIndex,
            const std::vector<int>& rightTeamAnswers,
            const std::vector<int>& wrongTeamAnswers);

    const std::string& getQuestion() const { return question; }
    const std::vector<std::string>& getAnswers() const { return answers; }
    bool isRightTeamAnswer(int index) const;
    bool isWrongTeamAnswer(int index) const;

private:
    std::string question;
    std::vector<std::string> answers;
    int correctIndex;
    std::vector<int> rightTeamAnswers;
    std::vector<int> wrongTeamAnswers;
};

