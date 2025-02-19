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
import io.newgrounds.NG;
import api.APIStuff;
import api.Newgrounds;
import game.AchievementNotif;
import flixel.sound.FlxSound;

class QuizState extends FlxState
{
	private var questions:Array<Question>;
	private var currentQuestionIndex:Int = 0;
	private var correctAnswers:Int = 0;
	private var rightTeamChoices:Int = 0;
	private var wrongTeamChoices:Int = 0;
	
	private var questionText:FlxText;
	private var answerTexts:Array<FlxText>;
	private var audience:Audience;
	var questionBox:QuestionBox;
	private var rightSpeechBubble:SpeechBubble;
	private var wrongSpeechBubble:SpeechBubble;
	
	private var correctSound:FlxSound;
	private var wrongSound:FlxSound;
	
	private var usernameText:FlxText;
	private var medalText:FlxText;
	
	override public function create()
	{
		super.create();
				
		#if html5
		correctSound = FlxG.sound.load("assets/sounds/correct.mp3");
		wrongSound = FlxG.sound.load("assets/sounds/wrong.mp3");
		#else
		correctSound = FlxG.sound.load("assets/sounds/correct.ogg");
		wrongSound = FlxG.sound.load("assets/sounds/wrong.ogg");
		#end
		
		initializeQuestions();
		setupUI();
		showCurrentQuestion();

		usernameText = new FlxText(FlxG.width - 200, 10, 190, "Connecting...", 16);
		usernameText.alignment = RIGHT;
		usernameText.color = FlxColor.WHITE;
		usernameText.setBorderStyle(OUTLINE, FlxColor.BLACK, 2);
		
		medalText = new FlxText(FlxG.width - 200, 50, 190, "", 16);
		medalText.alignment = RIGHT;
		medalText.color = FlxColor.YELLOW;
		medalText.setBorderStyle(OUTLINE, FlxColor.BLACK, 2);
		
		add(usernameText);
		add(medalText);
		
		audience = new Audience();
		add(audience);
		
		if (FlxG.save.data.unlockedMedals == null) {
			FlxG.save.data.unlockedMedals = 0;
			FlxG.save.flush();
		}
		
		trace("Loaded medals: " + FlxG.save.data.unlockedMedals);
		medalText.text = "Medals: " + FlxG.save.data.unlockedMedals + "/2";
		
		#if html5
		try {
			var ng:Newgrounds = new Newgrounds(APIStuff.API, APIStuff.EncKey, FlxG.save.data.sessionId);
			trace('NEWGROUNDS LOL');

			NG.core.onLogin.add(function() {
				trace("Login event triggered");
				if (NG.core != null && NG.core.user != null)
				{
					trace("User logged in! Username: " + NG.core.user.name);
					usernameText.text = "Welcome, " + NG.core.user.name + "!";
					medalText.text = "Medals: " + FlxG.save.data.unlockedMedals + "/2";
					FlxG.save.data.sessionId = NG.core.sessionId;
					FlxG.save.flush();
				}
			});

			#if !debug
			if (NG.core.user == null)
			{
				usernameText.text = "Loading...";
				usernameText.color = FlxColor.WHITE;
				
				new FlxTimer().start(2.0, function(tmr:FlxTimer) {
					if (NG.core.user == null)
					{
						usernameText.text = "Not logged in";
					}
				});
			}
			else
			{
				usernameText.text = "Welcome, " + NG.core.user.name + "!";
				medalText.text = "Medals: " + FlxG.save.data.unlockedMedals + "/2";
			}
			#else
			usernameText.text = "Debug Mode";
			#end
		} catch(e) {
			trace("Newgrounds initialization failed: " + e);
			usernameText.text = "Offline Mode";
		}
		#else
		usernameText.text = "Desktop Build";
		#end
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
				[0], // Right Team
				[3, 1, 2] // Wrong Team
			),
			new Question(
				"Finish the sentence: 'I am '",
				["Him", "Human", "Alien", "God"],
				0,
				[3], // Right Team
				[0, 1, 2] // Wrong Team

			),
			new Question(
				"SDRAWKCAB NOITSEUQ SIHT REWSNA",
				["K.O", "What?", "I do not understand", "Tennis Elbow"],
				0,
				[0], // Right Team
				[1, 2, 3] // Wrong Team
			),
			new Question(
				"What was this quiz coded in?",
				["Javascript", "C#", "Java", "Haxe"],
				0,
				[3], // Right Team
				[0, 1, 2] // Wrong Team
			),
			new Question(
				"Who owns X.com?",
				["Elon Musk", "Jack Ma", "Satoshi Nakamoto", "Tim Cook"],
				0,
				[0], // Right Team
				[1, 2, 3] // Wrong Team
			),
			new Question(
				"Is scratch and its forks for babies?",
				["Yes", "Yes", "Yes", "No"],
				0,
				[0, 1, 2], // Right Team
				[3] // Wrong Team
			),
			new Question(
				"Finish the quote: 'Sonic's the name, ...'s my game! '",
				["Chilidogs", "What??", "speed", "No"],
				0,
				[0, 1, 2], // Right Team
				[3] // Wrong Team
			),
			new Question(
				"What is the capital of France?",
				["Paris", "London", "Berlin", "Madrid"],
				0,
				[0], // Right Team
				[1, 2, 3] // Wrong Team
			),
			new Question(
				"I can see you.",
				["What?", "Liar!", "Oh...", "Okay"],
				0,
				[2], // Right Team
				[0, 1, 3] // Wrong Team
			),
			new Question(
				"Who made this game/quiz?",
				["maybekoi", "idk lol", "Sega", "Nintendo"],
				0,
				[0], // Right Team
				[1, 2, 3] // Wrong Team
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

		#if html5
		if (FlxG.mouse.justPressed && usernameText.text == "Click here to login")
		{
			if (FlxG.mouse.overlaps(usernameText))
			{
				trace("Login text clicked, requesting login...");
				NG.core.requestLogin(function() {
					trace("Login callback triggered");
					if (NG.core != null && NG.core.user != null)
					{
						Newgrounds.onNGLogin();
						trace("Login successful! Username: " + NG.core.user.name);
						usernameText.text = "Welcome, " + NG.core.user.name + "!";
						medalText.text = "Medals: " + FlxG.save.data.unlockedMedals + "/2";
						FlxG.save.data.sessionId = NG.core.sessionId;
						FlxG.save.flush();
					}
				});
			}
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
			rightTeamChoices++;
			correctAnswers++;
			audience.celebrateRight();
			rightSpeechBubble.playEmote("wrong_angry");
			wrongSpeechBubble.playEmote("right_smiley");
			wrongSound.play();
		}
		else if (question.isWrongTeamAnswer(answerIndex))
		{
			wrongTeamChoices++;
			audience.celebrateWrong();
			rightSpeechBubble.playEmote("wrong_smiley");
			wrongSpeechBubble.playEmote("right_angry");
			correctSound.play();
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
			showEnding(rightTeamChoices > wrongTeamChoices);
		}
	}
	
	private function showEnding(wasRightTeamDominant:Bool)
	{
		remove(questionText);
		for (text in answerTexts)
			remove(text);
		
		var endingText = new FlxText(50, 50, FlxG.width - 100, "", 24);
		endingText.alignment = CENTER;
		
		if (wasRightTeamDominant)
		{
			#if html5
			Newgrounds.unlockMedal(83098);
			#end
			
			if (FlxG.save.data.unlockedMedals < 1) {
				FlxG.save.data.unlockedMedals++;
				FlxG.save.flush();
				trace("Saved medals: " + FlxG.save.data.unlockedMedals);
				add(new AchievementNotif("Bad Ending?..."));
			}
			
			#if html5
			medalText.text = "Medals: " + FlxG.save.data.unlockedMedals + "/2";
			#else
			medalText.text = "Achievements: " + FlxG.save.data.unlockedMedals + "/2";
			#end
			
			endingText.text = "You sided with the left team most of the time...\nbut at what cost?\nHalf of the audience leaves disappointed.\nBAD ENDING?...";
			endingText.color = FlxColor.RED;
		}
		else
		{
			#if html5
			Newgrounds.unlockMedal(83097);
			#end
			
			if (FlxG.save.data.unlockedMedals < 2) {
				FlxG.save.data.unlockedMedals++;
				FlxG.save.flush();
				trace("Saved medals: " + FlxG.save.data.unlockedMedals);
				add(new AchievementNotif("Good Ending?..."));
			}
			
			#if html5
			medalText.text = "Medals: " + FlxG.save.data.unlockedMedals + "/2";
			#else
			medalText.text = "Achievements: " + FlxG.save.data.unlockedMedals + "/2";
			#end
			
			endingText.text = "You mostly listened to right team's answers!\nSome people had fun and made new friends.\nGOOD ENDING?...";
			endingText.color = FlxColor.GREEN;
		}
		
		add(endingText);
	}
}
