#include "include/EngineFramework.h"
#include <stdlib.h>
#include <iostream>
//#include <boost/lexical_cast.hpp>

#include "Entity.h"

/* This is a test to see if git is working */

class MyGame : public EngineFramework {
public:

    void AdditionalInit();
    void Think(const int& iElapsedTime);
    void Render(SDL_Surface* pDestSurface);

    void KeyUp(const int& iKeyEnum);
    void KeyDown(const int& iKeyEnum);

    void MouseMoved(const int& iButton,
                    const int& iX,
                    const int& iY,
                    const int& iRelX,
                    const int& iRelY);

    void MouseButtonUp(const int& iButton,
                       const int& iX,
                       const int& iY,
                       const int& iRelX,
                       const int& iRelY);

    void MouseButtonDown(const int& iButton,
                         const int& iX,
                         const int& iY,
                         const int& iRelX,
                         const int& iRelY);

    void WindowInactive();
    void WindowActive();

    void End();

private:
    Entity player;
};

int main(int argc, char* argv[]) {
    MyGame myGame;

    myGame.SetTitle("Loading...");
    myGame.Init();

    myGame.SetTitle("SDL_Testing!");
    myGame.Start();

    myGame.SetTitle("Quiting...");

    return EXIT_SUCCESS;
}

void MyGame::AdditionalInit() {
    player.Init("data/animations/xeon_animation.xml");
}

void MyGame::Think(const int& iElapsedTime) {
    player.Think( iElapsedTime );
}

void MyGame::Render(SDL_Surface* pDestSurface) {
    player.Draw( pDestSurface );

    //std::string val = boost::lexical_cast<std::string>(GetFPS());
    //val = "FPS: " + val;

    //SetTitle(val.c_str());
}

void MyGame::KeyDown(const int& iKeyEnum) {
    switch( iKeyEnum ) {
    case SDLK_a:
        player.SetAnimation("Walking");
        player.AddXVelocity(-player.GetSpeed());
        break;
    case SDLK_d:
        player.SetAnimation("Walking");
        player.AddXVelocity(player.GetSpeed());
        break;
    case SDLK_w:
        player.SetAnimation("Walking");
        player.AddYVelocity(-player.GetSpeed());
        break;
    case SDLK_s:
        player.SetAnimation("Walking");
        player.AddYVelocity(player.GetSpeed());
        break;
    default:
        break;
    }
}

void MyGame::KeyUp(const int& iKeyEnum) {
    switch( iKeyEnum ) {
    case SDLK_a:
        player.SetAnimation("Standing");
        player.AddXVelocity(player.GetSpeed());
        break;
    case SDLK_d:
        player.SetAnimation("Standing");
        player.AddXVelocity(-player.GetSpeed());
        break;
    case SDLK_w:
        player.SetAnimation("Standing");
        player.AddYVelocity(player.GetSpeed());
        break;
    case SDLK_s:
        player.SetAnimation("Standing");
        player.AddYVelocity(-player.GetSpeed());
        break;
    default:
        break;
    }
}

void MyGame::MouseMoved(const int& iButton,
                           const int& iX,
                           const int& iY,
                           const int& iRelX,
                           const int& iRelY) {

}

void MyGame::MouseButtonUp(const int& iButton,
                           const int& iX,
                           const int& iY,
                           const int& iRelX,
                           const int& iRelY) {

}

void MyGame::MouseButtonDown(const int& iButton,
                           const int& iX,
                           const int& iY,
                           const int& iRelX,
                           const int& iRelY) {

}

void MyGame::WindowInactive()
{
	// Pause game
}

void MyGame::WindowActive()
{
	// Un-pause game
}


void MyGame::End()
{
	// Clean up
}
