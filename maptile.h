#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class MapTile
{
    MapTile(x_pos = 0, y_pos = 0)
    {
        m_graphics = new MapTileGraphicsFactory(":/sprites/grass32.png");
        m_graphics->setPos(x_pos,y_pos);
    }

    void set_graphics(MapTileGraphics* graphics)
    {
        m_graphics = graphics;
        m_graphics->setPos(x_pos,y_pos);
    }

    MapTileGraphics* get_graphics(s)
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
};

class MapTileGraphics: public QGraphicsPixmapItem
{
public:
    MapTileGraphics(QPixmap pixmap):QGraphicsPixmapItem()
    {
        //m_pixmap
        this->setPixmap(pixmap.scaled(32,32));

    }

    void set_pixmap(QPixmap pixmap)
    {
        m_pixmap = pixmap.scaled(32,32);
        this->setPixmap(m_pixmap);
    }



private:

    QPixmap m_pixmap;

};

class MapTileGraphicsFactory
{
    static register_graphics(QString sprite_path)
    {
        m_registered_graphics[sprite_path] = new MapTileGraphics(QPixmap(sprite_path));
    }
    static MapTileGraphics*  get_concrete_graphics(QString sprite_path)
    {
        if(!m_registered_graphics.contains(sprite_path))
        {
            register_graphics(sprite_path);
        }
        else
        {
            return m_registered_graphics[sprite_path];
        }
    }
private:
    static QMap<QString, MapTileGraphics*> m_registered_graphics;
    //static MapTileGraphic

};


#endif // MAPTILE_H
