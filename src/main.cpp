#include <Engine.h>
#include "../src/antilogic/states/PlayState.h"
#include <Discord.h>

int main(int argc, char** argv) {
    Discord::GetInstance().Initialize("1347011960088035368");
    
    Discord::GetInstance().SetState("hamburger engine");
    Discord::GetInstance().SetDetails("Playing: AntiLogic by MaybeKoi");
    Discord::GetInstance().SetLargeImage("hamburger");
    Discord::GetInstance().SetLargeImageText("hamburger engine by YoPhlox & MaybeKoi");
    Discord::GetInstance().SetSmallImage("miku");
    Discord::GetInstance().SetSmallImageText("HOLY SHIT IS THAT HATSUNE MIKU!?");    
    Discord::GetInstance().Update();

    Engine engine(1280, 720, "AntiLogic");
    PlayState* initialState = new PlayState();
    engine.pushState(initialState);
    
    engine.run();
    
    return 0;
}
