#ifdef __MINGW32__
#include "engine/Engine.h"
#include "../src/antilogic/states/PlayState.h"
#include "engine/Input.h"
#elif defined(__SWITCH__)
#include "engine/Engine.h"
#include "../src/antilogic/states/PlayState.h"
#include "engine/Input.h"
#include <switch.h>
#else
#include <Engine.h>
#include "../src/antilogic/states/PlayState.h"
#include <Input.h>
#include <Discord.h>
#endif

int main(int argc, char** argv) {
    #ifdef __MINGW32__
    // nun
    #elif defined(__SWITCH__)
    // nun
    #else
    Discord::GetInstance().Initialize("1347011960088035368");
    Discord::GetInstance().SetState("hamburger engine");
    Discord::GetInstance().SetDetails("Playing: AntiLogic by MaybeKoi");
    Discord::GetInstance().SetLargeImage("hamburger");
    Discord::GetInstance().SetLargeImageText("hamburger engine by YoPhlox & MaybeKoi");
    Discord::GetInstance().SetSmallImage("miku");
    Discord::GetInstance().SetSmallImageText("HOLY SHIT IS THAT HATSUNE MIKU!?");    
    Discord::GetInstance().Update();
    #endif
    
    Engine engine(1280, 720, "AntiLogic");
    PlayState* initialState = new PlayState();
    engine.pushState(initialState);
    
    engine.run();
    
    #ifdef __MINGW32__
    // nun
    #elif defined(__SWITCH__)
    // nun
    #else
    Discord::GetInstance().Shutdown();
    #endif
    return 0;
}