#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "maptilegraphics.h"

class MapTile
{
public:
    MapTile(unsigned int x_pos = 0, unsigned int y_pos = 0)
    {
        m_graphics = new MapTileGraphics(QPixmap(":/sprites/grass32.png"));
        //m_graphics = MapTileGraphicsFactory::get_instance().get_concrete_graphics(QString::fromStdString(":/sprites/grass32.png"));
        m_graphics->setPos(x_pos,y_pos);
        qDebug()<<"MapTile constructor";
    }

    void set_graphics(MapTileGraphics* graphics)
    {
        m_graphics = graphics;
        m_graphics->setPos(x_pos,y_pos);
    }

    MapTileGraphics* get_graphics()
    {
        return  m_graphics;
    }


    void set_pos(float x, float y)
    {
        x_pos = x;
        y_pos = y;
        m_graphics->setPos(x_pos,y_pos);
    }

    float x()
    {
        return x_pos;
    }

    float y()
    {
        return y_pos;
    }

private:
    MapTileGraphics* m_graphics;

    float x_pos;
    float y_pos;

    bool can_walk_on;
};



#endif // MAPTILE_H
