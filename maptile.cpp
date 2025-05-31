#include "maptile.h"

//MapTiles::MapTiles() {}
MapTile* create_grass_tile()
{
    QString tile_name = "grass";
    QPixmap m_pixmap = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/grass_tile.png");
    WalkPossibility m_can_walk = On;
    MapTile* new_tile = new MapTile(tile_name,m_pixmap,m_can_walk);
    new_tile->setPixmap(m_pixmap);
    return new_tile;
}
MapTile* create_water_tile()
{
    QString tile_name = "water";
    QPixmap m_pixmap = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/water_tile_blue.png");
    WalkPossibility m_can_walk = NotAble;
    MapTile* new_tile = new MapTile(tile_name,m_pixmap,m_can_walk);
    new_tile->setPixmap(m_pixmap);
    return new_tile;
}

MapTile* create_ground_tile()
{
    QString tile_name = "ground";
    QPixmap m_pixmap = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/ground_tile_border.png");
    WalkPossibility m_can_walk = On;
    MapTile* new_tile = new MapTile(tile_name,m_pixmap,m_can_walk);
    new_tile->setPixmap(m_pixmap);
    return new_tile;
}


void MapTile::copy_tile(MapTile* map_tile)
{
    m_pixmap = map_tile->get_pixmap();
    m_name = map_tile->get_name();
    m_can_walk = map_tile->get_walk_possibilty();

}

WalkPossibility MapTile::get_walk_possibilty(){return m_can_walk;}


MapTile::MapTile(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    m_name = 0;
    m_can_walk = On;
}

MapTile::MapTile( QString p_name, QPixmap p_pixmap, WalkPossibility p_can_walk,QGraphicsPixmapItem* parent):QGraphicsPixmapItem(parent)
{
    m_name = p_name;
    m_pixmap = p_pixmap;
    m_can_walk = p_can_walk;
    this->setPixmap(p_pixmap);
    m_item =  new QGraphicsPixmapItem(p_pixmap);
}


MapTile::~MapTile()
{
    delete m_item;
}


void MapTile::set_position(int p_x, int p_y)
{
    this->setOffset(p_x,p_y);
}

QGraphicsPixmapItem* MapTile::get_graphics_item()
{
    return this;
}

QPixmap MapTile::get_pixmap()
{
    return m_pixmap;
}

    QString MapTile::get_name()
    {
        return m_name;
    }




MapTileFactory& MapTileFactory::get_instance()
{
    static MapTileFactory instance = MapTileFactory();
    return instance;
}

void MapTileFactory::register_tile(QString p_tile_name, CreateTileFunc p_create_func)
{
    if(!registered_tiles.contains(p_tile_name))
    {
        registered_tiles.emplace(p_tile_name,p_create_func);
        names_of_tiles.push_back(p_tile_name);
    }
}

MapTile* MapTileFactory::create_spec_tile(QString p_tile_name)
{
    if(registered_tiles.contains(p_tile_name))
    {
        CreateTileFunc func = registered_tiles.find(p_tile_name).value();
        return func();
    }
    else
    {
        qDebug()<< "There's no such tile";
    }
    return nullptr;
}

QVector<QString> MapTileFactory::get_all_tiles_names()
{
        return names_of_tiles;
}
    
QVector<QString> MapTileFactory::names_of_tiles;
QHash<QString, CreateTileFunc> MapTileFactory::registered_tiles;
