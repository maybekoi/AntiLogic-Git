#ifdef __MINGW32__
#include "../engine/core/Engine.h"
#include "../src/antilogic/states/PlayState.h"
#include "../engine/input/Input.h"
#elif defined(__SWITCH__)
#include "../engine/core/Engine.h"
#include "../src/antilogic/states/PlayState.h"
#include "../engine/input/Input.h"
#include <switch.h>
#else
#include <core/Engine.h>
#include "../src/antilogic/states/PlayState.h"
#include <input/Input.h>
#include <utils/Discord.h>
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
    
    int width = 1280;
    int height = 720;
    int fps = 60;
    bool debug = true;
    Engine engine(width, height, "AntiLogic", fps);
    engine.debugMode = debug;
    PlayState* initialState = new PlayState();
    engine.pushState(initialState);
    
    #ifdef __SWITCH__
    while (appletMainLoop()) {
        Input::UpdateControllerStates();
        if (Input::isControllerButtonPressed(SDL_CONTROLLER_BUTTON_BACK) || 
            Input::isControllerButtonPressed(SDL_CONTROLLER_BUTTON_START)) {
            engine.quit();
            break;
        }
        engine.run();
    }
    #else
    engine.run();
    #endif
    
    #ifdef __MINGW32__
    // nun
    #elif defined(__SWITCH__)
    // nun
    #else
    Discord::GetInstance().Shutdown();
    #endif
    return 0;
}