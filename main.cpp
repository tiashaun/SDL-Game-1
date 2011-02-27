#include "include/EngineFramework.h"
#include <stdlib.h>
#include <iostream>
#include <Box2D/Box2D.h>

#include "Entity.h"
#include "Maps/Level.h"

/* I will be making a level editor soon... */

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
    Level debugLevel;

    //Box2D World
    b2Vec2 m_v2Gravity;
    bool m_bDoSleep;
    b2World *m_b2PhysicsWorld;

    //temp box2d ground. after prototyping it will be apart of the level or something
    //b2BodyDef groundBodyDef;
    //b2PolygonShape groundBox;
    //b2Body* groundBody;
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
    //limit the fps to 60 fps
    m_iFPSLimit = 60;
    m_bLimitFPS = true;
    player.Init("data/animations/xeon_animation.xml");

    m_v2Gravity = b2Vec2(0.0f, -15.0f);
    m_bDoSleep = true;
    m_b2PhysicsWorld = new b2World(m_v2Gravity, m_bDoSleep);

    debugLevel.LoadProjectSettings("data/maps/SDL_Game.oep");
    debugLevel.LoadLevel("data/maps/Debug Level.oel");
    debugLevel.SetPhysicsCollisionRects(m_b2PhysicsWorld);


    //groundBodyDef.position.Set(0, -200.0f * 0.1);
    //groundBody = m_b2PhysicsWorld->CreateBody(&groundBodyDef);
    //groundBox.SetAsBox(300, 2);
    //groundBody->CreateFixture(&groundBox, 0.0f);

    player.InitPhysics(m_b2PhysicsWorld);
}

void MyGame::Think(const int& iElapsedTime) {
    float fPhysicsTimeStep = 1.0f / 60.0f;
    int iVelocityIterations = 10, iPositionIterations = 20;

    m_b2PhysicsWorld->Step(fPhysicsTimeStep, iVelocityIterations, iPositionIterations);
    m_b2PhysicsWorld->ClearForces();

    player.Think( iElapsedTime );
}

void MyGame::Render(SDL_Surface* pDestSurface) {
    debugLevel.Draw( pDestSurface );
    player.Draw( pDestSurface );
}

void MyGame::KeyDown(const int& iKeyEnum) {
    switch( iKeyEnum ) {
    case SDLK_a:
        player.SetAnimation("Walking");
        player.GetBody()->ApplyForce(b2Vec2(-400.0f, 0), player.GetBody()->GetPosition());
        //player.GetBody()->SetLinearVelocity(b2Vec2(-10.0f, 0));
        //player.AddXVelocity(-player.GetSpeed());
        break;
    case SDLK_d:
        player.SetAnimation("Walking");
        player.GetBody()->ApplyForce(b2Vec2(400.0f, 0.0f), player.GetBody()->GetPosition());
        //player.GetBody()->SetLinearVelocity(b2Vec2(10.0f, 0));
        //player.AddXVelocity(player.GetSpeed());
        break;
    case SDLK_w:
        player.SetAnimation("Walking");
        //player.AddYVelocity(-player.GetSpeed());
        break;
    case SDLK_s:
        player.SetAnimation("Walking");
        //player.AddYVelocity(player.GetSpeed());
        break;
    case SDLK_SPACE:
        player.GetBody()->ApplyLinearImpulse(b2Vec2(0, 150.0f), player.GetBody()->GetPosition());
        break;
    default:
        break;
    }
}

void MyGame::KeyUp(const int& iKeyEnum) {
    switch( iKeyEnum ) {
    case SDLK_a:
        player.SetAnimation("Standing");
        //player.AddXVelocity(player.GetSpeed());
        //player.GetBody()->SetLinearVelocity(b2Vec2(-0.0f, 0));
        break;
    case SDLK_d:
        player.SetAnimation("Standing");
        //player.AddXVelocity(-player.GetSpeed());
        //player.GetBody()->SetLinearVelocity(b2Vec2(0.0f, 0));
        break;
    case SDLK_w:
        player.SetAnimation("Standing");
        //player.AddYVelocity(player.GetSpeed());
        break;
    case SDLK_s:
        player.SetAnimation("Standing");
        player.AddYVelocity(-player.GetSpeed());
        break;
    case SDLK_SPACE:
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
    delete m_b2PhysicsWorld;
	// Clean up
}
