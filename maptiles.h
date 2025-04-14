#ifndef MAPTILES_H
#define MAPTILES_H

#include <QRandomGenerator>

#include "maptile.h"
#include "maptilefactory.h"

MapTile* create_grass_tile();

MapTile* create_water_tile();

class MapTiles
{
public:
    MapTiles()
    {
        //MapTileFactory factory;
        MapTileFactory::get_instance().register_tile(QString("grass"),create_grass_tile);
        MapTileFactory::get_instance().register_tile(QString("water"),create_water_tile);
        for(int x = 0; x < m_height; x++)
        {
            QVector<MapTile*> row;
            for(int y = 0; y < m_width; y++)
            {

                if(QRandomGenerator().bounded(1,2) == 1)
                {
                    row.append(MapTileFactory::get_instance().create_spec_tile("grass"));
                }
                else
                {
                    row.append(MapTileFactory::get_instance().create_spec_tile("water"));
                }
            }
            m_tiles.append(row);
        }

    }

    ~MapTiles()
    {

    }

    QVector<QVector<MapTile*>> m_tiles;

private:
    //QVector<QVector<QGraphicsPixmapItem*>> m_tiles;
    int m_height;
    int m_width;

};

#endif // MAPTILES_H
