package game;

class Question {
    public var question:String;
    public var answers:Array<String>;
    public var correctIndex:Int;
    public var rightTeamAnswers:Array<Int>; 
    public var wrongTeamAnswers:Array<Int>;
    
    public function new(question:String, answers:Array<String>, correctIndex:Int, 
                       rightTeamAnswers:Array<Int>, wrongTeamAnswers:Array<Int>) {
        this.question = question;
        this.answers = answers;
        this.correctIndex = correctIndex;
        this.rightTeamAnswers = rightTeamAnswers;
        this.wrongTeamAnswers = wrongTeamAnswers;
    }

    public function isRightTeamAnswer(index:Int):Bool {
        return rightTeamAnswers.indexOf(index) != -1;
    }

    public function isWrongTeamAnswer(index:Int):Bool {
        return wrongTeamAnswers.indexOf(index) != -1;
    }
} 