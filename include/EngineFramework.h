#ifndef ENGINEFRAMEWORK_H
#define ENGINEFRAMEWORK_H

/* SDL ENGINE FRAMEWORK BASED ON http://gpwiki.org/index.php/SDL:Tutorials:Simple_Engine_Framework */

#include "SDL/SDL.h"

class EngineFramework
{
    public:
        EngineFramework();
        virtual ~EngineFramework();

        void Init();
        void Start();

        /**OVERLOADED - all extra things that are loaded **/
        virtual void AdditionalInit() {}

        /**OVERLOADED - all calulations **/
        virtual void Think( const int& iElapsedTime) {}

        /**OVERLOADED - all rendering **/
        virtual void Render( SDL_Surface* pDestSurface ) {}

        /**OVERLOADED - clean up everything you need to **/
        virtual void End() {}

        virtual void WindowActive() {}
        virtual void WindowInactive() {}

        virtual void KeyUp(const int& iKeyEnum) {}
        virtual void KeyDown(const int& iKeyEnum) {}

        virtual void MouseMoved(const int& iButton,
                                const int& iX,
                                const int& iY,
                                const int& iRelX,
                                const int& iRelY) {}

        virtual void MouseButtonUp(const int& iButton,
                                const int& iX,
                                const int& iY,
                                const int& iRelX,
                                const int& iRelY) {}

        virtual void MouseButtonDown(const int& iButton,
                                const int& iX,
                                const int& iY,
                                const int& iRelX,
                                const int& iRelY) {}

        void SetTitle(const char* cTitle);
        const char* GetTitle();

        SDL_Surface* GetSurface();

        int GetFPS();
    protected:
        void DoThink();
        void DoRender();

        void SetSize(const int& iWidth, const int& iHeight);

        void HandleInput();
    private:
        long m_lLastTick;

        int m_iWidth, m_iHeight;
        int m_iFPSTickCounter;
        int m_iFPSCounter;
        int m_iCurrentFPS;

        bool m_bQuit;
        bool m_bMinimized;

        const char* m_cTitle;

        SDL_Surface* m_pScreen;

};

#endif // ENGINEFRAMEWORK_H
