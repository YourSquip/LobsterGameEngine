#ifndef MAPTILE_H
#define MAPTILE_H

#include <QString>
#include <QPixmap>
#include <QGraphicsPixmapItem>

enum WalkPossibility{
    On = 1,
    Under = 2,
    NotAble = 3
};

class MapTile
{
public:
    MapTile()
    {
        m_name = 0;
        m_can_walk = On;

    }

    MapTile( QString p_name, QPixmap p_pixmap, WalkPossibility p_can_walk)
    {
        m_name = p_name;
        m_pixmap = p_pixmap;
        m_can_walk = p_can_walk;
        m_item =  new QGraphicsPixmapItem(p_pixmap);
    }


    ~MapTile()
    {
        delete m_item;
    }


    void set_position(int p_x, int p_y)
    {
        m_item->setOffset(p_x,p_y);
    }

    QGraphicsPixmapItem* get_graphics_item()
    {
        return m_item;
    }

    QString get_name()
    {
        return m_name;
    }

private:

    int m_x;
    int m_y;

    QString m_name;
    QPixmap m_pixmap;
    QGraphicsPixmapItem* m_item;
    WalkPossibility m_can_walk;

};

#endif // MAPTILE_H
