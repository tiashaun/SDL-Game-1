#ifndef IMAGESHEET_H
#define IMAGESHEET_H

#include <string>
#include <SDL/SDL.h>

class Imagesheet
{
    public:
        /** Default constructor */
        Imagesheet(int keyR, int keyG, int keyB, int size, std::string fileName);
        /** Default destructor */
        virtual ~Imagesheet();

        SDL_Surface* LoadImage(std::string fileName);

        unsigned int GetiColorKeyR();
        void SetiColorKeyR(unsigned int val);

        unsigned int GetiColorKeyG();
        void SetiColorKeyG(unsigned int val);

        unsigned int GetiColorKeyB();
        void SetiColorKeyB(unsigned int val);

        unsigned int GetiSpriteSize();
        void SetiSpriteSize(unsigned int val);

        std::string GetsImage();
        void SetsImage(std::string val);

        SDL_Surface* GetSurface();

        void Destroy();
    protected:
    private:
        unsigned int m_iColorKeyR; //!< Member variable "m_iColorKeyR"
        unsigned int m_iColorKeyG; //!< Member variable "m_iColorKeyG"
        unsigned int m_iColorKeyB; //!< Member variable "m_iColorKeyB"
        unsigned int m_iSpriteSize; //!< Member variable "m_iSpriteSize"

        SDL_Surface *m_sImagesheet;
};

#endif // IMAGESHEET_H
