#include "Maps/Imagesheet.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

Imagesheet::Imagesheet(int keyR, int keyG, int keyB, int size, std::string fileName)
{
    m_iColorKeyB = keyB;
    m_iColorKeyG = keyG;
    m_iColorKeyR = keyR;

    m_iSpriteSize = size;

    m_sImagesheet = LoadImage(fileName);
}

Imagesheet::~Imagesheet()
{
    //SDL_FreeSurface(m_sImagesheet);
}

void Imagesheet::Destroy() {
    SDL_FreeSurface(m_sImagesheet);
}

SDL_Surface* Imagesheet::LoadImage(std::string fileName) {
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( fileName.c_str() );

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
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, m_iColorKeyR, m_iColorKeyG, m_iColorKeyB ) );
        }
    } else {
    }

    //Return the optimized surface
    return optimizedImage;
}

unsigned int Imagesheet::GetiColorKeyR()
{
    return m_iColorKeyR;
}
/** Set m_iColorKeyR
 * \param val New value to set
 */
void Imagesheet::SetiColorKeyR(unsigned int val)
{
    m_iColorKeyR = val;
}
/** Access m_iColorKeyG
 * \return The current value of m_iColorKeyG
 */
unsigned int Imagesheet::GetiColorKeyG()
{
    return m_iColorKeyG;
}
/** Set m_iColorKeyG
 * \param val New value to set
 */
void Imagesheet::SetiColorKeyG(unsigned int val)
{
    m_iColorKeyG = val;
}
/** Access m_iColorKeyB
 * \return The current value of m_iColorKeyB
 */
unsigned int Imagesheet::GetiColorKeyB()
{
    return m_iColorKeyB;
}
/** Set m_iColorKeyB
 * \param val New value to set
 */
void Imagesheet::SetiColorKeyB(unsigned int val)
{
    m_iColorKeyB = val;
}
/** Access m_iSpriteSize
 * \return The current value of m_iSpriteSize
 */
unsigned int Imagesheet::GetiSpriteSize()
{
    return m_iSpriteSize;
}
/** Set m_iSpriteSize
 * \param val New value to set
 */
void Imagesheet::SetiSpriteSize(unsigned int val)
{
    m_iSpriteSize = val;
}

SDL_Surface* Imagesheet::GetSurface() {
    return m_sImagesheet;
}
