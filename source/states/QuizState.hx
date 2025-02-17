package states;

import haxe.display.Display.Package;
import flixel.FlxG;
import flixel.FlxState;
import flixel.text.FlxText;
import flixel.ui.FlxButton;
import flixel.util.FlxColor;
import game.Question;
import game.Audience;
import game.QuestionBox;
import game.SpeechBubble;
import flixel.FlxSprite;
import flixel.util.FlxColor;
import flixel.util.FlxTimer;

class QuizState extends FlxState
{
	private var questions:Array<Question>;
	private var currentQuestionIndex:Int = 0;
	private var correctAnswers:Int = 0;
	
	private var questionText:FlxText;
	private var answerTexts:Array<FlxText>;
	private var audience:Audience;
	var questionBox:QuestionBox;
	private var rightSpeechBubble:SpeechBubble;
	private var wrongSpeechBubble:SpeechBubble;
	
	override public function create()
	{
		super.create();
		
		initializeQuestions();
		setupUI();
		showCurrentQuestion();
		
		audience = new Audience();
		add(audience);
	}
	
	private function initializeQuestions()
	{
		questions = [
			/*
			// MADE FOR TESTING PURPOSES LOL
			new Question(
				"Template Question",
				["Template Answer 1", "Template Answer 2", "Template Answer 3", "Template Answer 4"],
				0,
				[0, 1], // Right team supports answers 0 and 1
				[2, 3]  // Wrong team supports answers 2 and 3
			),
			new Question(
				"Are you gay?",
				["Yes", "No", "Maybe", "I don't know"],
				0,
				[0, 1],
				[2, 3]
			),
			*/
			new Question(
				"Whats the closest planet to the sun?",
				["Mercury", "Venus", "Earth", "Mars"],
				0,
				[3, 1, 2], // Wrong Team
				[0] // Right Team
			),
			new Question(
				"Finish the sentence: 'I am '",
				["Him", "Human", "Alien", "God"],
				0,
				[0, 1, 2], // Wrong Team
				[3] // Right Team
			),
			new Question(
				"SDRAWKCAB NOITSEUQ SIHT REWSNA",
				["K.O", "What?", "I do not understand", "Tennis Elbow"],
				0,
				[1, 2, 3], // Wrong Team
				[0] // Right Team
			),
			new Question(
				"What was this quiz coded in?",
				["Javascript", "C#", "Java", "Haxe"],
				0,
				[0, 1, 2], // Wrong Team
				[3] // Right Team
			),
			new Question(
				"Who owns X.com?",
				["Elon Musk", "Jack Ma", "Satoshi Nakamoto", "Tim Cook"],
				0,
				[1, 2, 3], // Wrong Team
				[0] // Right Team
			),
			new Question(
				"Is scratch and its forks for babies?",
				["Yes", "Yes", "Yes", "No"],
				0,
				[3], // Wrong Team
				[0, 1, 2] // Right Team
			),
			new Question(
				"Finish the quote: 'Sonic's the name, ...'s my game! '",
				["Chilidogs", "What??", "speed", "No"],
				0,
				[3], // Wrong Team
				[0] // Right Team
			),
			new Question(
				"What is the capital of France?",
				["Paris", "London", "Berlin", "Madrid"],
				0,
				[1, 2, 3], // Wrong Team
				[0] // Right Team
			),
			new Question(
				"I can see you.",
				["What?", "Liar!", "Oh...", "Okay"],
				0,
				[0, 1, 3], // Wrong Team
				[2] // Right Team
			),
			new Question(
				"Who made this game/quiz?",
				["maybekoi", "idk lol", "Sega", "Nintendo"],
				0,
				[1, 2, 3], // Wrong Team
				[0] // Right Team
			),	
		];
	}
	
	private function setupUI()
	{
		var bg:FlxSprite = new FlxSprite(-80).loadGraphic(Util.getImage("bg"));
		bg.scrollFactor.x = 0;
		bg.scrollFactor.y = 0.18;
		bg.setGraphicSize(Std.int(bg.width * 1.1));
		bg.updateHitbox();
		bg.screenCenter();
		bg.antialiasing = true;
		add(bg);

		questionBox = new QuestionBox(50, 50);
		add(questionBox);

		questionText = new FlxText(50, 50, FlxG.width - 100, "", 24);
		questionText.alignment = CENTER;
		add(questionText);
		
		answerTexts = [];
		var positions = [
			{x: 227, y: 158.5},  // Top Left
			{x: 877, y: 159.5},  // Top Right
			{x: 227, y: 512.5}, // Bottom Left
			{x: 877, y: 512.5}  // Bottom Right
		];
		
		for (i in 0...4)
		{
			var text = new FlxText(positions[i].x, positions[i].y, 200, "", 20);
			text.alignment = CENTER;
			text.color = FlxColor.BLACK;
			
			text.ID = i;
			text.setBorderStyle(OUTLINE, FlxColor.WHITE, 2);
			
			answerTexts.push(text);
			add(text);
		}

		rightSpeechBubble = new SpeechBubble(FlxG.width - 300, 450); 
		wrongSpeechBubble = new SpeechBubble(100, 450); 
		rightSpeechBubble.bubble.flipX = true;
		rightSpeechBubble.emoticon.flipX = true;
		rightSpeechBubble.visible = false;
		wrongSpeechBubble.visible = false;
		add(rightSpeechBubble);
		add(wrongSpeechBubble);

		var creditsText = new FlxText(10, 10, 0, "Made by maybekoi\nArt by hubbabubbagym/codie\nIdea by kennedy", 16);
		creditsText.alignment = LEFT;
		creditsText.color = FlxColor.WHITE;
		creditsText.setBorderStyle(OUTLINE, FlxColor.BLACK, 2);
		add(creditsText);
	}
	
	private function showCurrentQuestion()
	{
		if (currentQuestionIndex >= questions.length)
		{
			showEnding(false);
			return;
		}
		
		rightSpeechBubble.revive();
		wrongSpeechBubble.revive();
		
		var question = questions[currentQuestionIndex];
		questionText.text = question.question;
		
		for (i in 0...question.answers.length)
		{
			answerTexts[i].text = question.answers[i];
		}
	}
	
	override public function update(elapsed:Float)
	{
		super.update(elapsed);
		
		if (currentQuestionIndex < questions.length && FlxG.mouse.justPressed)
		{
			for (text in answerTexts)
			{
				if (FlxG.mouse.overlaps(text))
				{
					onAnswerClick(text.ID);
					break;
				}
			}
		}
		
		if (currentQuestionIndex < questions.length)
		{
			for (text in answerTexts)
			{
				if (FlxG.mouse.overlaps(text))
				{
					text.color = FlxColor.GRAY;
				}
				else
				{
					text.color = FlxColor.BLACK;
				}
			}
		}
		
		#if debug
		if (FlxG.keys.justPressed.ONE)
		{
			trace("topLeft X: " + questionBox.topLeft.x + " Y: " + questionBox.topLeft.y);
		}
		else if (FlxG.keys.justPressed.TWO)
		{
			trace("topRight X: " + questionBox.topRight.x + " Y: " + questionBox.topRight.y);
		}
		else if (FlxG.keys.justPressed.THREE)
		{
			trace("bottomLeft X: " + questionBox.bottomLeft.x + " Y: " + questionBox.bottomLeft.y);
		}
		else if (FlxG.keys.justPressed.FOUR)
		{
			trace("bottomRight X: " + questionBox.bottomRight.x + " Y: " + questionBox.bottomRight.y);	
		}

		if (FlxG.keys.justPressed.FIVE)
		{
			trace("answerTexts X: " + answerTexts[0].x + " Y: " + answerTexts[0].y);
		}

		if (FlxG.keys.justPressed.SIX)
		{
			trace("answerTexts X: " + answerTexts[1].x + " Y: " + answerTexts[1].y);
		}

		if (FlxG.keys.justPressed.SEVEN)
		{
			trace("answerTexts X: " + answerTexts[2].x + " Y: " + answerTexts[2].y);
		}
		
		if (FlxG.keys.justPressed.EIGHT)
		{
			trace("answerTexts X: " + answerTexts[3].x + " Y: " + answerTexts[3].y);
		}
		
		#end
	}
	
	private function onAnswerClick(answerIndex:Int)
	{
		var question = questions[currentQuestionIndex];
		rightSpeechBubble.visible = true;
		wrongSpeechBubble.visible = true;
		
		if (question.isRightTeamAnswer(answerIndex))
		{
			correctAnswers++;
			audience.celebrateRight();
			rightSpeechBubble.playEmote("wrong_angry");
			wrongSpeechBubble.playEmote("right_smiley");
		}
		else if (question.isWrongTeamAnswer(answerIndex))
		{
			audience.celebrateWrong();
			rightSpeechBubble.playEmote("wrong_smiley");
			wrongSpeechBubble.playEmote("right_angry");
		}
		
		currentQuestionIndex++;
		
		if (currentQuestionIndex < questions.length) {
			new FlxTimer().start(1.5, function(tmr:FlxTimer)
			{
				rightSpeechBubble.visible = false;
				wrongSpeechBubble.visible = false;
				
				for (member in audience.rightTeam)
					member.animation.play('idle');
				for (member in audience.wrongTeam)
					member.animation.play('idle');
			});
			showCurrentQuestion();
		} else {
			showEnding(question.isRightTeamAnswer(answerIndex));
		}
	}
	
	private function showEnding(wasRightTeamAnswer:Bool)
	{
		remove(questionText);
		for (text in answerTexts)
			remove(text);
		
		var endingText = new FlxText(50, 50, FlxG.width - 100, "", 24);
		endingText.alignment = CENTER;
		
		if (wasRightTeamAnswer)
		{
			endingText.text = "You got everything right...\nbut at what cost?\nThe audience leaves disappointed.\nBAD ENDING";
			endingText.color = FlxColor.RED;
		}
		else
		{
			endingText.text = "You listened to the audience!\nEveryone had fun and made new friends.\nGOOD ENDING";
			endingText.color = FlxColor.GREEN;
		}
		
		add(endingText);
	}
}
