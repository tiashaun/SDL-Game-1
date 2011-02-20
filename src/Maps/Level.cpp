#include "Maps/Level.h"

#include <tinyxml.h>
#include <string>
#include <vector>
#include <SDL/SDL_image.h>
#include <iostream>

#include "Maps/Tile.h"
#include "Maps/Layer.h"

Level::Level()
{
    //ctor
}

Level::~Level()
{
    //dtor
}

void Level::Draw ( SDL_Surface* pDest ) {
    for ( unsigned int i = 0; i < m_vRenderLayers.size(); i++ ) {
        Layer tempLayer = m_vRenderLayers.at(i);
        //first get the tileset
        std::string tileset1;
        tileset1 = tempLayer.GetTileSet();
        std::cout<< tileset1;
        SDL_Surface* tileset = m_mTileSets[tileset1.c_str()];

        std::vector<Tile> tiles = tempLayer.GetTiles();

        int tileWidth = tempLayer.GetTileWidth();
        int tileHeight = tempLayer.GetTileHeight();

        for ( unsigned int j = 0; j < tiles.size(); j++ ) {
            Tile tempTile = tiles.at(j);
            SDL_Rect clip;
            clip.x = tempTile.GetTileX();
            clip.y = tempTile.GetTileY();
            clip.w = tileWidth;
            clip.h = tileHeight;

            ApplySurface(tempTile.GetPosX(), tempTile.GetPosY(), tileset, pDest, &clip);
        }
    }
}

void Level::ApplySurface(int iX, int iY, SDL_Surface* pSource, SDL_Surface* pDestination, SDL_Rect* clip = NULL) {
    SDL_Rect offset;

    offset.x = iX;
    offset.y = iY;

    SDL_BlitSurface(pSource, clip, pDestination, &offset);
}

void Level::LoadProjectSettings(std::string projectSettingsFileName) {
    TiXmlDocument doc(projectSettingsFileName.c_str());
    if ( !doc.LoadFile()) return;

    TiXmlElement *root = doc.RootElement();

    std::string workingDirString;

    for ( TiXmlElement* node = root->FirstChildElement(); node; node = node->NextSiblingElement()) {
        std::string value = node->Value();
        if ( value == "settings" ) {
            TiXmlElement* workingDir = node->FirstChildElement()->NextSiblingElement()->NextSiblingElement();
            workingDirString = workingDir->GetText();

        } else if ( value == "tilesets" ) {
            for ( TiXmlElement* tileset = node->FirstChildElement(); tileset; tileset = tileset->NextSiblingElement()) {
                std::string tilesetName = tileset->Attribute("name");
                std::string tilesetImage = tileset->Attribute("image");
                int ckr, ckg, ckb;

                TiXmlElement* colorKey = tileset->FirstChildElement();
                ckr = atoi(colorKey->Attribute("red"));
                ckg = atoi(colorKey->Attribute("green"));
                ckb = atoi(colorKey->Attribute("blue"));
                std::cout<< ckr << " " << ckg << " " << ckb << std::endl;

                SDL_Surface* tilesetSurface = LoadImage(workingDirString + "/" + tilesetImage, ckr, ckg, ckb);
                m_mTileSets.insert(std::pair<std::string, SDL_Surface*>(tilesetName, tilesetSurface));
            }
        }
    }
}

SDL_Surface* Level::LoadImage(std::string fileName, int colorKeyR, int colorKeyG, int colorKeyB) {
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
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, colorKeyR, colorKeyG, colorKeyB ) );
            //SDL_SetAlpha(optimizedImage, SDL_SRCALPHA, 128);
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void Level::LoadLevel(std::string levelFileName) {
    TiXmlDocument doc(levelFileName.c_str());
    if (!doc.LoadFile()) return;

    TiXmlElement *root = doc.RootElement();

    for (TiXmlElement* layer = root->FirstChildElement(); layer; layer = layer->NextSiblingElement()) {
        std::string value = layer->Value();
        //ignore width/height
        if ( value == "width" || value == "height")
            continue;

        //ignore collision objects and actors for now.
        if ( value == "collisionObjects" || value == "actors")
            continue;

        if ( value == "mapTiles") {
            std::string tilesetName = layer->Attribute("set");
            int tileWidth = atoi(layer->Attribute("tileWidth"));
            int tileHeight = atoi(layer->Attribute("tileWidth"));

            std::vector<Tile> vTiles;
            for ( TiXmlElement* tile = layer->FirstChildElement(); tile; tile = tile->NextSiblingElement()) {
                Tile tempTile;

                tempTile.SetTileX(atoi(tile->Attribute("tx")));
                tempTile.SetTileY(atoi(tile->Attribute("ty")));
                tempTile.SetPosX(atoi(tile->Attribute("x")));
                tempTile.SetPosY(atoi(tile->Attribute("y")));

                vTiles.push_back(tempTile);
            }

            Layer tempLayer;
            tempLayer.SetTileSet(tilesetName);
            tempLayer.SetTileHeight(tileHeight);
            tempLayer.SetTileWidth(tileWidth);
            tempLayer.SetTiles(vTiles);

            m_vRenderLayers.push_back(tempLayer);
        }
    }
}
