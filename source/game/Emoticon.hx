package game;

import flixel.FlxSprite;

class Emoticon extends FlxSprite
{
    public function new()
    {
        super(0, 0);
        
        frames = Util.getSparrow("emotes");
        animation.addByPrefix('right_angry', 'angry right 0000', 24, true);
        animation.addByPrefix('wrong_angry', 'angry wrong 0000', 24, true);
        animation.addByPrefix('right_smiley', 'smiley right 0000', 24, true);
        animation.addByPrefix('wrong_smiley', 'smiley wrong 0000', 24, true);
        
        animation.play('right_angry');
    }
    
    public function playEmote(emoteName:String)
    {
        if (animation.exists(emoteName))
            animation.play(emoteName);
    }
} 