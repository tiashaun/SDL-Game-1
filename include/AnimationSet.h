#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include <SDL/SDL.h>
#include <string>
#include <vector>
#include <map>

class Animation {
    public:
        Animation();
        Animation(std::vector<SDL_Rect> vClipList, int iSpeed);
        virtual ~Animation();

        SDL_Rect GetCurrentClip();

        void UpdateFrames( int iElapsedTime );
    private:
        std::vector<SDL_Rect> m_vClipList;

        int m_iCurrentFrame;

        int m_iSpeed; //how long each frame should last in seconds
        int m_iAccumulator; //keeps track of when to switch frames. when this is more than Speed, increase frame and reset this
};

class AnimationSet
{
    public:
        /** Default constructor */
        AnimationSet();
        /** Default destructor */
        virtual ~AnimationSet();

        void Init(std::string fileName); //fileName is the xml file for the animationset

        std::string GetImageFileName();

        int GetColorKeyValue(char cAttribute);

        SDL_Rect GetCurrentClip(std::string sCurrentAnimation);

        void UpdateFrames(int iElapsedTime, std::string sAnimation);
    protected:
    private:
        std::map<std::string, Animation> m_mAnimationList;

        std::string m_sImageFileName;
        int m_iColorKeyR, m_iColorKeyG, m_iColorKeyB;
};

#endif // ANIMATIONSET_H
