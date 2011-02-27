#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <SDL/SDL.h>
#include <Box2D/Box2D.h>

#include "Maps/Layer.h"
#include "Maps/Tileset.h"

class Level
{
    public:
        /** Default constructor */
        Level();
        /** Default destructor */
        virtual ~Level();

        void LoadProjectSettings(std::string projectSettingsFileName);
        void LoadLevel(std::string levelFileName);
        SDL_Surface* LoadImage(std::string fileName, int colorKeyR, int colorKeyG, int colorKeyB);

        void SetPhysicsCollisionRects(b2World* world);

        void Draw ( SDL_Surface* pDest );
    protected:
    private:
        void ApplySurface(int iX, int iY, SDL_Surface* pSource, SDL_Surface* pDestination, SDL_Rect* clip);

        //project settings
        std::string m_sWorkingDirectory;

        //other stuff
        std::map<std::string, SDL_Surface*> m_mTileSets;
        std::vector<Layer> m_vRenderLayers;

        Layer m_lCollisionLayer;
};

#endif // LEVEL_H
