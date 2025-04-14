#ifndef MAPTILES_H
#define MAPTILES_H

#include <QRandomGenerator>
#include <QDebug>

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
        m_height = 10;
        m_width = 10;
        for(int x = 0; x < m_height; x++)
        {
            QVector<MapTile*> row;
            for(int y = 0; y < m_width; y++)
            {
                int rand_num = QRandomGenerator::global()->bounded(0,3);
                qDebug()<<"rand_num="<<rand_num;

                if(rand_num == 1)
                {

                    MapTile* tile = MapTileFactory::get_instance().create_spec_tile("grass");
                    if(tile == nullptr) qDebug()<<"TILE IS NULL!!!!";
                    tile->set_position(x,y);
                    row.push_back(tile);
                }
                else
                {
                    MapTile* tile = MapTileFactory::get_instance().create_spec_tile("water");
                    if(tile == nullptr) qDebug()<<"TILE IS NULL!!!!";
                    tile->set_position(x,y);
                    row.push_back(tile);
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
