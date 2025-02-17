package api;

import flixel.FlxG;
import flixel.util.FlxSignal;
import flixel.util.FlxTimer;
import io.newgrounds.NG;
import io.newgrounds.components.ScoreBoardComponent.Period;
import io.newgrounds.objects.Medal;
import io.newgrounds.objects.Score;
import io.newgrounds.objects.ScoreBoard;
import io.newgrounds.objects.events.Response;
import io.newgrounds.objects.events.Result.GetCurrentVersionResult;
import io.newgrounds.objects.events.Result.GetVersionResult;
import lime.app.Application;
import openfl.display.Stage;
import game.AchievementNotif;

using StringTools;

/**
 * stolen from fnf source code muhhaahahahsudojenrhuj, slightly modified by maybekoi
 */
class Newgrounds
{
	public static var isLoggedIn:Bool = false;
	public static var scoreboardsLoaded:Bool = false;
	public static var medalsInitialized:Bool = false;

	public static var scoreboardArray:Array<Score> = [];

	public static var ngDataLoaded(default, null):FlxSignal = new FlxSignal();
	public static var ngScoresLoaded(default, null):FlxSignal = new FlxSignal();

	public static var GAME_VER:String = "";
	public static var GAME_VER_NUMS:String = '';
	public static var gotOnlineVer:Bool = false;

	public static function noLogin(api:String)
	{
		trace('INIT NOLOGIN');
		GAME_VER = "v" + Application.current.meta.get('version');

		if (api.length != 0)
		{
			NG.create(api);

			new FlxTimer().start(2, function(tmr:FlxTimer)
			{
				var call = NG.core.calls.app.getCurrentVersion(GAME_VER).addDataHandler(function(response:Response<GetCurrentVersionResult>)
				{
					GAME_VER = response.result.data.currentVersion;
					GAME_VER_NUMS = GAME_VER.split(" ")[0].trim();
					trace('CURRENT NG VERSION: ' + GAME_VER);
					gotOnlineVer = true;
				});

				call.send();
			});
		}
	}

	public function new(api:String, encKey:String, ?sessionId:String)
	{
		trace("connecting to newgrounds");
		
		#if debug
		trace("Debug mode - skipping Newgrounds initialization");
		return;
		#end
		
		try {
			NG.createAndCheckSession(api, sessionId);
			NG.core.verbose = true;
            NG.core.setupEncryption(APIStuff.EncKey, AES_128, BASE_64);

			trace(NG.core.attemptingLogin);

			if (NG.core.attemptingLogin)
			{
				/* a session_id was found in the loadervars, this means the user is playing on newgrounds.com
				 * and we should login shortly. lets wait for that to happen
				 */
				trace("attempting login");
				NG.core.onLogin.add(onNGLogin);
			}
			else if (NG.core.loggedIn)
			{
				trace("already logged in, initializing medals");
				onNGLogin();
			}
		} catch(e) {
			trace("Newgrounds connection failed: " + e);
		}
	}

	public static function onNGLogin():Void
	{
		try {
			if (NG.core != null && NG.core.user != null)
			{
				trace('logged in! user:${NG.core.user.name}');
				isLoggedIn = true;
				FlxG.save.data.sessionId = NG.core.sessionId;
				FlxG.save.flush();
				
                NG.core.setupEncryption(APIStuff.EncKey, AES_128, BASE_64);
				
				trace("requesting medals...");
				NG.core.requestMedals(function() {
					trace("Medals loaded and ready!");
					medalsInitialized = true;
					ngDataLoaded.dispatch();
				});
			}
		} catch(e) {
			trace("Login failed: " + e);
		}
	}

	// --- MEDALS
	function onNGMedalFetch():Void {}

	// --- SCOREBOARDS
	function onNGBoardsFetch():Void
	{
		trace("shoulda got score by NOW!");
	}

	inline static public function postScore(score:Int = 0, song:String)
	{
		if (isLoggedIn)
		{
			for (id in NG.core.scoreBoards.keys())
			{
				var board = NG.core.scoreBoards.get(id);

				if (song == board.name)
				{
					board.postScore(score, "Uhh meow?");
				}
			}
		}
	}

	function onNGScoresFetch():Void
	{
		scoreboardsLoaded = true;

		ngScoresLoaded.dispatch();
	}

	inline static public function logEvent(event:String)
	{
		NG.core.calls.event.logEvent(event).send();
		trace('should have logged: ' + event);
	}

	inline static public function unlockMedal(id:Int)
	{
		try {
			if (NG.core != null && NG.core.loggedIn && NG.core.medals != null && medalsInitialized)
			{
                NG.core.setupEncryption(APIStuff.EncKey, AES_128, BASE_64);
				
				trace('attempting to unlock medal ${id}');
				var medal = NG.core.medals.get(id);
				if (medal != null && !medal.unlocked)
				{
					trace('sending unlock for medal ${id}');
					medal.sendUnlock();
					
					// Show achievement notification
					FlxG.state.add(new AchievementNotif(medal.name));
				}
				else
				{
					trace('medal ${id} already unlocked or not found');
				}
			}
			else
			{
				trace('cannot unlock medal ${id} - not logged in or medals not initialized (loggedIn: ${NG.core?.loggedIn}, medals: ${NG.core?.medals != null}, initialized: $medalsInitialized)');
			}
		} catch(e) {
			trace('Error unlocking medal ${id}: ${e}');
		}
	}
}