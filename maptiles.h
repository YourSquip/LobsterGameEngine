#ifndef MAPTILES_H
#define MAPTILES_H

#include "maptile.h"

class MapTiles
{
public:

    MapTiles();
    QVector<QVector<MapTile*>> m_tiles;

private:
    int m_height;
    int m_width;
};


#endif // MAPTILES_H
