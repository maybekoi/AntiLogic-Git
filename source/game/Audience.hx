package game;

import flixel.FlxSprite;
import flixel.FlxG;
import flixel.group.FlxGroup;

class Audience extends FlxGroup
{
    public var rightTeam:Array<FlxSprite>;
    public var wrongTeam:Array<FlxSprite>;
    
    private static inline var MEMBERS_PER_TEAM:Int = 3;
    private static inline var MEMBER_SPACING:Int = 100;
    
    public function new()
    {
        super();
        
        rightTeam = [];
        wrongTeam = [];
        
        var rightStartX = FlxG.width - (MEMBERS_PER_TEAM * MEMBER_SPACING) - 50; 
        for (i in 0...MEMBERS_PER_TEAM)
        {
            var member = new FlxSprite(rightStartX + (i * MEMBER_SPACING), 600);
            member.frames = Util.getSparrow("audience_wrong");
            member.animation.addByPrefix('idle', 'audience wrong idle instance', 24, true);
            member.animation.addByPrefix('yay', 'audience wrong yay instance', 24, true);
            member.animation.play('idle');
            wrongTeam.push(member);
            add(member);
        }
        
        var leftStartX = 50;
        for (i in 0...MEMBERS_PER_TEAM)
        {
            var member = new FlxSprite(leftStartX + (i * MEMBER_SPACING), 600);
            member.frames = Util.getSparrow("audience_right");
            member.animation.addByPrefix('idle', 'audience right idle instance', 24, true);
            member.animation.addByPrefix('yay', 'audience right yay instance', 24, true);
            member.animation.play('idle');
            rightTeam.push(member);
            add(member);
        }
    }
    
    public function celebrateRight()
    {
        for (member in rightTeam)
        {
            member.animation.play('yay');
            member.animation.finishCallback = function(name:String) {
                member.animation.play('idle');
            }
        }
    }
    
    public function celebrateWrong()
    {
        for (member in wrongTeam)
        {
            member.animation.play('yay');
            member.animation.finishCallback = function(name:String) {
                member.animation.play('idle');
            }
        }
    }
}
