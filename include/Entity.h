#ifndef ENTITY_H
#define ENTITY_H

#include <SDL/SDL.h>
#include <string>

#include "AnimationSet.h"

class Entity
{
    public:
        /** Default constructor */
        Entity();
        /** Default destructor */
        virtual ~Entity();

        void Think(int iElapsedTime);
        void Draw(SDL_Surface* pDestination);

        void Init(std::string xmlFileName); //init takes the file name of the animation set xml file

        //move functions
        void Move(int iX, int iY);
        void SetXVelocity(int iXVel);
        void SetYVelocity(int iYVel);
        void AddXVelocity(int iXVel);
        void AddYVelocity(int iYVel);

        int GetSpeed();

        void SetAnimation(std::string sAnimation);

    protected:
    private:
        int m_iX, m_iY;
        int m_iXVel, m_iYVel;

        int m_iSpeed; //how fast the entity moves. this variable doesnt have any direct impact on the entity though

        SDL_Surface* image;

        void ApplySurface(int iX, int iY, SDL_Surface* pDestination, SDL_Rect* clip);

        AnimationSet m_asAnimations;
        std::string m_sCurrentAnimation;
};

#endif // ENTITY_H
