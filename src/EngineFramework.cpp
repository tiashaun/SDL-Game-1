#include "../include/EngineFramework.h"
#include <iostream>

EngineFramework::EngineFramework()
{
    m_lLastTick = 0;
    m_iWidth = 640;
    m_iHeight = 480;
    m_cTitle = 0;

    m_pScreen = 0;

    m_iFPSTickCounter = 0;
    m_iCurrentFPS = 0;
    m_iFPSCounter = 0;

    //these two variables should be initiallzed inside of the mygame class, not the framework class.
    //if the user of this framework doesn't want to limit the framerate, then dont
    //m_iFPSLimit = 60;
    //m_bLimitFPS = true;

    m_bMinimized = false;
}

EngineFramework::~EngineFramework()
{
    SDL_Quit();
}

void EngineFramework::SetSize(const int& iWidth, const int& iHeight) {
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_pScreen = SDL_SetVideoMode(iWidth, iHeight, 32, SDL_SWSURFACE);
}

void EngineFramework::Init() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr<< "Unable to init SDL: " << SDL_GetError();
        exit(1);
    }

    SetSize(m_iWidth, m_iHeight);

    if ( m_pScreen == NULL ) {
        std::cerr<< "Unable to set up video: " << SDL_GetError();
    }

    AdditionalInit();
}

/** The Main Loop **/
void EngineFramework::Start() {
    m_lLastTick = SDL_GetTicks();
    m_bQuit = false;

    while (!m_bQuit) {
        HandleInput();

        if (m_bMinimized) {

        } else {
            DoThink();

            DoRender();
        }

        //limit the frame rate
        if ( m_bLimitFPS && m_iElapsedTicks < 1000 / m_iFPSLimit ) {
            SDL_Delay((1000/m_iFPSLimit) - m_iElapsedTicks);
        }
    }

    End();
}

void EngineFramework::HandleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            if ( event.key.keysym.sym == SDLK_ESCAPE) {
                m_bQuit = true;
                break;
            }

            KeyDown(event.key.keysym.sym);
            break;

        case SDL_KEYUP:
            KeyUp(event.key.keysym.sym);
            break;

        case SDL_QUIT:
            m_bQuit = true;
            break;

        case SDL_MOUSEMOTION:
            MouseMoved(event.button.button,
                       event.motion.x,
                       event.motion.y,
                       event.motion.xrel,
                       event.motion.yrel);
            break;

        case SDL_MOUSEBUTTONUP:
            MouseButtonUp(event.button.button,
                       event.motion.x,
                       event.motion.y,
                       event.motion.xrel,
                       event.motion.yrel);
            break;

        case SDL_MOUSEBUTTONDOWN:
            MouseButtonDown(event.button.button,
                       event.motion.x,
                       event.motion.y,
                       event.motion.xrel,
                       event.motion.yrel);
            break;

        case SDL_ACTIVEEVENT:
            if ( event.active.state & SDL_APPACTIVE) {
                if ( event.active.gain) {
                    m_bMinimized = false;
                    WindowActive();
                } else {
                    m_bMinimized = true;
                    WindowInactive();
                }
            }
            break;

        default:
            break;
        } //end siwtch
    } //end while
}

void EngineFramework::DoThink() {
    m_iElapsedTicks = SDL_GetTicks() - m_lLastTick;
    m_lLastTick = SDL_GetTicks();

    Think( m_iElapsedTicks );

    m_iFPSTickCounter += m_iElapsedTicks;
}

void EngineFramework::DoRender() {
    ++m_iFPSCounter;
    if (m_iFPSTickCounter >= 1000 ) {
        m_iCurrentFPS = m_iFPSCounter;
        m_iFPSCounter = 0;
        m_iFPSTickCounter = 0;
    }

    SDL_FillRect(m_pScreen, 0, SDL_MapRGB(m_pScreen->format, 0, 0, 0));

    //lock surface if needed
    if ( SDL_MUSTLOCK( m_pScreen ))
        if ( SDL_LockSurface(m_pScreen) < 0 )
            return;

    Render( GetSurface() );

    if (SDL_MUSTLOCK(m_pScreen))
        SDL_UnlockSurface( m_pScreen );

    SDL_Flip(m_pScreen);
}

void EngineFramework::SetTitle(const char* cTitle) {
    m_cTitle = cTitle;
    SDL_WM_SetCaption(cTitle, 0);
}

const char* EngineFramework::GetTitle() {
    return m_cTitle;
}

SDL_Surface* EngineFramework::GetSurface() {
    return m_pScreen;
}

int EngineFramework::GetFPS() {
    return m_iCurrentFPS;
}
