package game;

import flixel.FlxSprite;
import flixel.group.FlxGroup;
import flixel.FlxG;

class QuestionBox extends FlxGroup
{
    public var topLeft:FlxSprite;
    public var topRight:FlxSprite;
    public var bottomLeft:FlxSprite;
    public var bottomRight:FlxSprite;
    public var centerPiece:FlxSprite;
    
    private static inline var CENTER_WIDTH:Int = 100;
    private static inline var CENTER_HEIGHT:Int = 100;
    
    public function new(x:Float, y:Float)
    {
        super();
        
        centerPiece = new FlxSprite(0, 0);
        centerPiece.loadGraphic(Util.getImage("questionbox_center"));
        centerPiece.screenCenter();
        
        var centerX = centerPiece.x;
        var centerY = centerPiece.y;
        
        topLeft = new FlxSprite(170, 94.5);
        topLeft.frames = Util.getSparrow("questionbox");
        topLeft.animation.addByPrefix('idle', 'corner idle', 24, true);
        topLeft.animation.play('idle');
        
        topRight = new FlxSprite(824, 90.5);
        topRight.frames = Util.getSparrow("questionbox");
        topRight.animation.addByPrefix('idle', 'corner idle', 24, true);
        topRight.animation.play('idle');
        topRight.flipX = true;
        
        bottomLeft = new FlxSprite(170, 437.5);
        bottomLeft.frames = Util.getSparrow("questionbox");
        bottomLeft.animation.addByPrefix('idle', 'corner idle', 24, true);
        bottomLeft.animation.play('idle');
        bottomLeft.flipY = true;
        
        bottomRight = new FlxSprite(824, 434.5);
        bottomRight.frames = Util.getSparrow("questionbox");
        bottomRight.animation.addByPrefix('idle', 'corner idle', 24, true);
        bottomRight.animation.play('idle');
        bottomRight.flipX = true;
        bottomRight.flipY = true;
        
        add(centerPiece);
        add(topLeft);
        add(topRight);
        add(bottomLeft);
        add(bottomRight);
    }
}