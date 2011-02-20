#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <vector>

#include "Maps/Tile.h"

class Layer
{
    public:
        /** Default constructor */
        Layer();
        /** Default destructor */
        virtual ~Layer();
        /** Access m_sTileSet
         * \return The current value of m_sTileSet
         */
        std::string GetTileSet() { return m_sTileSet; }
        /** Set m_sTileSet
         * \param val New value to set
         */
        void SetTileSet(std::string val) { m_sTileSet = val; }
        /** Access m_iTileWidth
         * \return The current value of m_iTileWidth
         */
        int GetTileWidth() { return m_iTileWidth; }
        /** Set m_iTileWidth
         * \param val New value to set
         */
        void SetTileWidth(int val) { m_iTileWidth = val; }
        /** Access m_iTileHeight
         * \return The current value of m_iTileHeight
         */
        int GetTileHeight() { return m_iTileHeight; }
        /** Set m_iTileHeight
         * \param val New value to set
         */
        void SetTileHeight(int val) { m_iTileHeight = val; }

        void SetTiles(std::vector<Tile> vTiles);
        std::vector<Tile> GetTiles();
    protected:
    private:
        std::string m_sTileSet; //!< Member variable "m_sTileSet"
        int m_iTileWidth; //!< Member variable "m_iTileWidth"
        int m_iTileHeight; //!< Member variable "m_iTileHeight"

        std::vector<Tile> m_vTiles;
};

#endif // LAYER_H
