#include "Entity.h"
#include <SDL/SDL_image.h>

Entity::Entity()
{
    m_iX = 0;
    m_iY = 0;
    m_iXVel = 0;
    m_iYVel = 0;

    m_iSpeed = 1;

    m_sCurrentAnimation = "Standing";
}

Entity::~Entity()
{
    SDL_FreeSurface( image );
}

void Entity::Init(std::string xmlFileName) {
    m_asAnimations.Init(xmlFileName);
    std::string imageFileName = m_asAnimations.GetImageFileName();

    int colorkeyR = m_asAnimations.GetColorKeyValue('r');
    int colorkeyG = m_asAnimations.GetColorKeyValue('g');
    int colorKeyB = m_asAnimations.GetColorKeyValue('b');

    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( imageFileName.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, colorkeyR, colorkeyG, colorKeyB ) );
        }
    } else {
        return;
    }

    //Return the optimized surface
    image = optimizedImage;
}

void Entity::ApplySurface(int iX, int iY, SDL_Surface* pDestination, SDL_Rect* clip = NULL) {
    SDL_Rect offset;

    offset.x = iX;
    offset.y = iY;

    SDL_BlitSurface(image, clip, pDestination, &offset);
}

void Entity::Draw(SDL_Surface* pDestination) {
    SDL_Rect currentClip = m_asAnimations.GetCurrentClip(m_sCurrentAnimation);

    ApplySurface(m_iX, m_iY, pDestination, &currentClip);
}

void Entity::Think(int iElapsedTime) {
    m_iX += m_iXVel;
    m_iY += m_iYVel;

    m_asAnimations.UpdateFrames( iElapsedTime, m_sCurrentAnimation );
}

void Entity::SetXVelocity(int iXVel) {
    m_iXVel = iXVel;
}

void Entity::SetYVelocity(int iYVel) {
    m_iYVel = iYVel;
}

void Entity::AddXVelocity(int iXVel) {
    m_iXVel += iXVel;
}

void Entity::AddYVelocity(int iYVel) {
    m_iYVel += iYVel;
}

int Entity::GetSpeed() {
    return m_iSpeed;
}

void Entity::SetAnimation(std::string sAnimationEnum) {
    m_sCurrentAnimation = sAnimationEnum;
}
























