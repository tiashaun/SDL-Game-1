#include "Maps/Layer.h"
#include "Maps/CollisionRect.h"

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

std::vector<CollisionRect> Layer::GetCollRect() {
    return m_vCollRect;
}
void Layer::SetCollRect(std::vector<CollisionRect> vCollRect) {
    m_vCollRect = vCollRect;
}
