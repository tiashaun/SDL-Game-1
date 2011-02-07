#include "Maps/Map.h"

#include <tinyxml.h>

Map::Map()
{
    //ctor
}

Map::~Map()
{
    for ( unsigned int i = 0; i < m_vImagesheetList.size(); i++ ) {
        m_vImagesheetList.at(i).Destroy();
    }
}

void Map::LoadMap(std::string fileName) {
    TiXmlDocument doc(fileName.c_str());
    if (!doc.LoadFile()) return;
    TiXmlElement *root = doc.RootElement();

    m_sMapName = root->Attribute("name");

    for ( TiXmlElement* node = root->FirstChildElement(); node; node = node->NextSiblingElement()) {
        const char* nodeName = node->Value();
        std::string sImagesheet = "imagesheet";
        std::string sLayer = "Layer";

        //if its an imagesheet, add a new imagesheet
        if ( strcmp(sImagesheet.c_str(), nodeName) == 0 ) {
            int keyR = atoi(node->Attribute("colorkeyR"));
            int keyG = atoi(node->Attribute("colorkeyG"));
            int keyB = atoi(node->Attribute("colorkeyB"));
            int size = atoi(node->Attribute("spriteSize"));
            std::string fileName = node->Attribute("image");

            Imagesheet isTemp(keyR, keyG, keyB, size, fileName);

            m_vImagesheetList.push_back(isTemp);
        }

        //if it's a layer, go through and add the structures
        else if ( strcmp(sLayer.c_str(), nodeName) == 0 ) {
            for ( TiXmlElement* structure = node->FirstChildElement(); structure; structure = structure->NextSiblingElement()) {
                int iImagesheetID = atoi(structure->Attribute("imagesheetID"));
                int iImagesheetRow = atoi(structure->Attribute("imagesheetRow"));
                int iImagesheetCol = atoi(structure->Attribute("imagesheetColumn"));
                int iPosX = atoi(structure->Attribute("posX"));
                int iPosY = atoi(structure->Attribute("posY"));

                Structure sTemp(iImagesheetID, iImagesheetRow, iImagesheetCol, iPosX, iPosY);

                m_vStructureList.push_back(sTemp);
            }

        }

    }
}

void Map::Draw( SDL_Surface* pDest ) {
    /* How to draw a map:
        Go through each structure and draw it to the screen...
        simple enough!
    */

    for ( unsigned int i = 0; i < m_vStructureList.size(); i++ ) {
        //get the structure
        Structure stTemp = (Structure)m_vStructureList.at(i);

        //get the imagesheet
        int imagesheetID = stTemp.GetiImagesheetID();
        Imagesheet isTemp = (Imagesheet)m_vImagesheetList.at(imagesheetID);

        //get the actual image to use
        SDL_Surface *sdlSurface = isTemp.GetSurface();

        //get the clip to use
        SDL_Rect clip;
        clip.w = isTemp.GetiSpriteSize(); //width and height are easy, they're just the size of the IS's sprites
        clip.h = isTemp.GetiSpriteSize();

        clip.x = stTemp.GetiImagesheetX() * isTemp.GetiSpriteSize(); //for the x of the imagesheet, its the row * the size of a row
        clip.y = stTemp.GetiImagesheetY() * isTemp.GetiSpriteSize(); //same for y but with columns

        //render the image
        ApplySurface(sdlSurface, stTemp.GetiPosX(), stTemp.GetiPosY(), pDest, &clip);
    }
}

void Map::ApplySurface(SDL_Surface* source, int iX, int iY, SDL_Surface* pDestination, SDL_Rect* clip = NULL) {
    SDL_Rect offset;

    offset.x = iX;
    offset.y = iY;

    SDL_BlitSurface(source, clip, pDestination, &offset);
}


