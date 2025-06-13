#ifndef MAP_H
#define MAP_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QVector>

#include "maptile.h"

class Map
{
public:
    Map(unsigned int width = 0, unsigned int heigth = 0)
    {

        qDebug()<<"Map constructor";
        m_width = width;
        m_height = heigth;
        m_cell_size = 32;
        for(int x = 0; x< m_width*m_cell_size; x+=m_cell_size)
        {
            QVector<MapTile*> row;
            for(int y = 0; y < m_height*m_cell_size; y+= m_cell_size)
            {
                MapTile* new_tile = new MapTile(x,y);
                row.push_back(new_tile);
            }
            m_maptiles.push_back(row);
        }
    }

    void add_map_to_scene(QGraphicsScene* scene)
    {
        for(int i = 0; i < m_width; i++)
        {
            for(int j = 0; j < m_height; j++)
            {
                scene->addItem(m_maptiles[i][j]->get_graphics());
            }
        }
    }

private:
    QVector<QVector<MapTile*>> m_maptiles;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_cell_size;
};

#endif // MAP_H
