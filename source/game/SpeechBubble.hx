package game;

import flixel.FlxSprite;
import flixel.group.FlxGroup;
import flixel.FlxG;

class SpeechBubble extends FlxGroup
{
    public var bubble:FlxSprite;
    public var emoticon:Emoticon;
    
    public function new(x:Float, y:Float)
    {
        super();
        
        bubble = new FlxSprite(x, y);
        bubble.frames = Util.getSparrow("textbox");
        bubble.animation.addByPrefix('idle', 'text bubble instance', 24, true);
        
        emoticon = new Emoticon();
        emoticon.x = bubble.x + (bubble.width / 2) - (emoticon.width / 2);
        emoticon.y = bubble.y + (bubble.height / 2) - (emoticon.height / 2);
        
        add(bubble);
        add(emoticon);
    }
    
    public function playEmote(emoteName:String)
    {
        emoticon.playEmote(emoteName);
    }
    
    public function pop()
    {
        bubble.animation.finishCallback = function(name:String) {
            kill();
        }
    }
} 