#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <SDL/SDL.h>
#include "Maps/Structure.h"
#include "Maps/Imagesheet.h"

class Map
{
    public:
        Map();
        virtual ~Map();

        void LoadMap(std::string fileName);
        void Draw( SDL_Surface* pDest );
    protected:
    private:
        void ApplySurface(SDL_Surface* source, int iX, int iY, SDL_Surface* pDestination, SDL_Rect* clip);

        std::string m_sMapName;
        std::vector<Structure> m_vStructureList;
        std::vector<Imagesheet> m_vImagesheetList;
};

#endif // MAP_H
