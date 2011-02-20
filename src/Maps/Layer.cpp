#include "Maps/Layer.h"

Layer::Layer()
{
    //ctor
}

Layer::~Layer()
{
    //dtor
}

std::vector<Tile> Layer::GetTiles() {
    return m_vTiles;
}
void Layer::SetTiles(std::vector<Tile> vTiles) {
    m_vTiles = vTiles;
}
