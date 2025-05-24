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

        MapTileFactory::get_instance().register_tile(QString("grass"),create_grass_tile);
        MapTileFactory::get_instance().register_tile(QString("water"),create_water_tile);
        m_height = 9;
        m_width = 9;
        for(int x = 0; x <m_width; x++)
        {
            QVector<MapTile*> row;
            for(int y = 0; y < m_height; y++)
            {
                int rand_num = QRandomGenerator::global()->bounded(1,3);
                qDebug()<<"rand_num="<<rand_num;
                //rand_num = 1;
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
            m_tiles.push_back(row);
            for(auto tile_row: m_tiles)
            {
                for(auto tile: tile_row)
                    if(tile->get_name().toStdString() == "grass")
                    {
                        qDebug()<<"grass tile";
                    }
                    else if(tile->get_name().toStdString() == "water")
                    {
                        qDebug()<<"water tile";
                    }
                    else
                    {
                        qDebug()<<"UKNOWN TILE";
                    }
            }
        }

    }

    ~MapTiles()
    {

    }
    QVector<QVector<MapTile*>> m_tiles;

private:

    int m_height;
    int m_width;

};

#endif // MAPTILES_H
