#include "maptiles.h"

//MapTiles::MapTiles() {}
MapTile* create_grass_tile()
{
    QString tile_name = "grass";
    QPixmap m_pixmap = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/grass_tile.png");
    WalkPossibility m_can_walk = On;
    return new MapTile(tile_name,m_pixmap,m_can_walk);
}
MapTile* create_water_tile()
{
    QString tile_name = "water";
    QPixmap m_pixmap = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/water_tile_blue.png");
    WalkPossibility m_can_walk = NotAble;
    return new MapTile(tile_name,m_pixmap,m_can_walk);
}

MapTile* create_ground_tile()
{
    QString tile_name = "ground";
    QPixmap m_pixmap = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/ground_tile_border.png");
    WalkPossibility m_can_walk = On;
    return new MapTile(tile_name,m_pixmap,m_can_walk);
}
