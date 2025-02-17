package game;

import flixel.FlxSprite;
import flixel.group.FlxGroup;
import flixel.text.FlxText;
import flixel.util.FlxColor;
import flixel.tweens.FlxTween;
import flixel.FlxG;

class AchievementNotif extends FlxGroup
{
    var bg:FlxSprite;
    var text:FlxText;
    
    public function new(title:String)
    {
        super();
        
        bg = new FlxSprite(0, -50);
        bg.makeGraphic(300, 50, FlxColor.BLACK);
        bg.alpha = 0.7;
        
        text = new FlxText(0, -50, 300, "Achievement Unlocked!\n" + title, 16);
        text.alignment = CENTER;
        text.color = FlxColor.WHITE;
        
        add(bg);
        add(text);
        
        bg.x = (FlxG.width - bg.width) / 2;
        text.x = bg.x;
        
        FlxTween.tween(bg, {y: 10}, 0.5, {onComplete: function(tween:FlxTween) {
            FlxTween.tween(bg, {y: -50}, 0.5, {startDelay: 2, onComplete: function(tween:FlxTween) {
                kill();
            }});
        }});
        
        FlxTween.tween(text, {y: 15}, 0.5, {onComplete: function(tween:FlxTween) {
            FlxTween.tween(text, {y: -50}, 0.5, {startDelay: 2});
        }});
    }
} 