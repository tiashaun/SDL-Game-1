#include "AnimationSet.h"

#include <tinyxml.h>
#include <string>

/** ANIMATION SET IMPLEMENTATION **/

AnimationSet::AnimationSet()
{
    //ctor
}

AnimationSet::~AnimationSet()
{
    //dtor
}

void AnimationSet::Init(std::string fileName) {
    TiXmlDocument doc(fileName.c_str());
    if (!doc.LoadFile()) return;

    TiXmlElement *root = doc.RootElement();

    m_sImageFileName = root->Attribute("file");
    m_iColorKeyR = atoi(root->Attribute("colorkeyR"));
    m_iColorKeyG = atoi(root->Attribute("colorkeyG"));
    m_iColorKeyB = atoi(root->Attribute("colorkeyB"));

    for (TiXmlElement* animation = root->FirstChildElement(); animation; animation = animation->NextSiblingElement()) {
        std::string sAnimationName = animation->Attribute("name");
        int iSpeed = atoi(animation->Attribute("speed"));
        std::vector<SDL_Rect> vClipList;

        for ( TiXmlElement* clip = animation->FirstChildElement(); clip; clip = clip->NextSiblingElement()) {
            SDL_Rect rTemp;

            rTemp.x = atoi(clip->Attribute("x"));
            rTemp.y = atoi(clip->Attribute("y"));
            rTemp.w = atoi(clip->Attribute("width"));
            rTemp.h = atoi(clip->Attribute("height"));

            vClipList.push_back(rTemp);

        }

        Animation aTempAnimation(vClipList, iSpeed);
        m_mAnimationList.insert(std::pair<std::string, Animation>(sAnimationName, aTempAnimation));
    }
}

std::string AnimationSet::GetImageFileName() {
    return m_sImageFileName;
}

int AnimationSet::GetColorKeyValue(char cAttribute) {
    switch (cAttribute) {
        case 'R':
        case 'r':
            return m_iColorKeyR;

        case 'G':
        case 'g':
            return m_iColorKeyG;

        case 'B':
        case 'b':
            return m_iColorKeyB;

        default:
            break;
    }

    return 0;
}

SDL_Rect AnimationSet::GetCurrentClip(std::string sCurrentAnimation) {
    /** Explaination about what is going on here **/
    /* I am using a map so I can easily look up animations by their name. When you get an item out of a map like this:
        Animation temp = myMap["name"];

       ...and then change the contents of 'temp', the version of it in the map doesn't get saved. I'm not sure if there is a way to call 'UpdateMap' or something
       similiar, or if you could have it return a pointer instead or something, but the first way I thought of doing this was by just accessing the elemnt from the map
       directly, like this:

         myMap["name"].SomeFunction();

       ...because when you do it like that, if SomeFunction() changes the contents of that element, it DOES get saved in the map's version.

       So I'm going to leave the two commented out lines in case I get confused on what I did. It's basically the same thing, but the line that I kept
       just combines the two lines above it into one.
    */

    //Animation aTempAnimation = (Animation)m_mAnimationList[sCurrentAnimation.c_str()];
    //SDL_Rect rCurrentClip = aTempAnimation.GetCurrentClip();

    SDL_Rect rCurrentClip = m_mAnimationList[sCurrentAnimation.c_str()].GetCurrentClip();

    return rCurrentClip;
}

void AnimationSet::UpdateFrames(int iElapsedTime, std::string sAnimation) {
    m_mAnimationList[sAnimation.c_str()].UpdateFrames( iElapsedTime );
}

/** ANIMATION IMPLEMENTATION **/

Animation::Animation(std::vector<SDL_Rect> vClipList, int iSpeed)
{
    m_vClipList = vClipList;

    m_iCurrentFrame = 0;
    m_iSpeed = iSpeed;
    m_iAccumulator = 0;
}

Animation::Animation() {

}

Animation::~Animation()
{
    //dtor
}

SDL_Rect Animation::GetCurrentClip() {
    SDL_Rect rectToReturn = m_vClipList[m_iCurrentFrame];

    return rectToReturn;
}

void Animation::UpdateFrames( int iElapsedTime ) {
    m_iAccumulator += iElapsedTime;

    if ( m_iAccumulator >= m_iSpeed) {

        int iSize = m_vClipList.size();
        if ( m_iCurrentFrame >= iSize -1)
            m_iCurrentFrame = 0;
        else
            m_iCurrentFrame++;

        m_iAccumulator = 0;
    }
}



















