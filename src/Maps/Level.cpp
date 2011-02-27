#include "Maps/Level.h"

#include <tinyxml.h>
#include <string>
#include <vector>
#include <SDL/SDL_image.h>
#include <iostream>
#include <Box2D/Box2D.h>

#include "Maps/Tile.h"
#include "Maps/Layer.h"
#include "Maps/CollisionRect.h"

Level::Level()
{
    //ctor
}

Level::~Level()
{
    //dtor
}

void Level::Draw ( SDL_Surface* pDest )
{
    for ( unsigned int i = 0; i < m_vRenderLayers.size(); i++ )
    {
        Layer tempLayer = m_vRenderLayers.at(i);
        //first get the tileset
        std::string tileset1;
        tileset1 = tempLayer.GetTileSet();
        std::cout<< tileset1;
        SDL_Surface* tileset = m_mTileSets[tileset1.c_str()];

        std::vector<Tile> tiles = tempLayer.GetTiles();

        int tileWidth = tempLayer.GetTileWidth();
        int tileHeight = tempLayer.GetTileHeight();

        for ( unsigned int j = 0; j < tiles.size(); j++ )
        {
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

void Level::ApplySurface(int iX, int iY, SDL_Surface* pSource, SDL_Surface* pDestination, SDL_Rect* clip = NULL)
{
    SDL_Rect offset;

    offset.x = iX;
    offset.y = iY;

    SDL_BlitSurface(pSource, clip, pDestination, &offset);
}

void Level::LoadProjectSettings(std::string projectSettingsFileName)
{
    TiXmlDocument doc(projectSettingsFileName.c_str());
    if ( !doc.LoadFile()) return;

    TiXmlElement *root = doc.RootElement();

    std::string workingDirString;

    for ( TiXmlElement* node = root->FirstChildElement(); node; node = node->NextSiblingElement())
    {
        std::string value = node->Value();
        if ( value == "settings" )
        {
            TiXmlElement* workingDir = node->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement();
            workingDirString = workingDir->GetText();

        }
        else if ( value == "tilesets" )
        {
            for ( TiXmlElement* tileset = node->FirstChildElement(); tileset; tileset = tileset->NextSiblingElement())
            {
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

SDL_Surface* Level::LoadImage(std::string fileName, int colorKeyR, int colorKeyG, int colorKeyB)
{
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

void Level::LoadLevel(std::string levelFileName)
{
    TiXmlDocument doc(levelFileName.c_str());
    if (!doc.LoadFile()) return;

    TiXmlElement *root = doc.RootElement();

    for (TiXmlElement* layer = root->FirstChildElement(); layer; layer = layer->NextSiblingElement())
    {
        std::string value = layer->Value();
        Layer tempLayer;
        //ignore width/height
        if ( value == "width" || value == "height")
            continue;

        //ignore actors for now.
        if ( value == "actors")
            continue;

        if ( value == "collisionObjects" )
        {
            std::vector<CollisionRect> vCollRect;

            for (TiXmlElement* rect = layer->FirstChildElement(); rect; rect = rect->NextSiblingElement())
            {
                int x = atoi(rect->Attribute("x"));
                int y = atoi(rect->Attribute("y"));
                int w = atoi(rect->Attribute("w"));
                int h = atoi(rect->Attribute("h"));

                CollisionRect cr;
                cr.SetiHeight(h);
                cr.SetiWidth(w);
                cr.SetiPosX(x);
                cr.SetiPosY(y);
                vCollRect.push_back(cr);
            }

            tempLayer.SetCollRect(vCollRect);
        }

        if ( value == "mapTiles")
        {
            std::string tilesetName = layer->Attribute("set");
            int tileWidth = atoi(layer->Attribute("tileWidth"));
            int tileHeight = atoi(layer->Attribute("tileWidth"));

            std::vector<Tile> vTiles;
            for ( TiXmlElement* tile = layer->FirstChildElement(); tile; tile = tile->NextSiblingElement())
            {
                Tile tempTile;

                tempTile.SetTileX(atoi(tile->Attribute("tx")));
                tempTile.SetTileY(atoi(tile->Attribute("ty")));
                tempTile.SetPosX(atoi(tile->Attribute("x")));
                tempTile.SetPosY(atoi(tile->Attribute("y")));

                vTiles.push_back(tempTile);
            }

            tempLayer.SetTileSet(tilesetName);
            tempLayer.SetTileHeight(tileHeight);
            tempLayer.SetTileWidth(tileWidth);
            tempLayer.SetTiles(vTiles);

        }
        m_vRenderLayers.push_back(tempLayer);
    }
}

void Level::SetPhysicsCollisionRects(b2World* world)
{
    for ( unsigned int i = 0; i < m_vRenderLayers.size(); i++ )
    {
        Layer tempLayer = m_vRenderLayers.at(i);

        //get the collision rects
        std::vector<CollisionRect> vCollRect = tempLayer.GetCollRect();

        //for each collision rect
        for ( unsigned int i = 0; i < vCollRect.size(); i++ )
        {
            //get the coll rect
            CollisionRect tempRect = (CollisionRect)vCollRect.at(i);

            //get all of the rects info
            //i need to convert pixels to meters... divide by 10
            //i also need to invert the y coord... fucking sdl
            int x = tempRect.GetiPosX() * 0.1f;
            int y = -(tempRect.GetiPosY() * 0.1f);
            int width = tempRect.GetiWidth() * 0.1f;
            int height = tempRect.GetiHeight() * 0.1f;

            //get its Box2D position(the middle of it)
            int box2D_xPos = x + (width/2);
            int box2D_yPos = y + (height/2)+(16*.1f);

            //make its physical properties
            b2BodyDef bodyDef;
            b2Body*  body;
            b2PolygonShape rectBox;

            bodyDef.position.Set(box2D_xPos, box2D_yPos);
            body = world->CreateBody(&bodyDef); //add it to the world

            rectBox.SetAsBox(width/2, height/2);
            body->CreateFixture(&rectBox, 0.0f);
        }
    }
}
