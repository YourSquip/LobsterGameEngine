#ifndef MAPTILE_H
#define MAPTILE_H

#include <QString>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

enum WalkPossibility{
    On = 1,
    Under = 2,
    NotAble = 3
};

class MapTile: public QGraphicsPixmapItem
{
public:
    MapTile(QGraphicsItem* parent=nullptr):QGraphicsPixmapItem(parent)
    {
        m_name = 0;
        m_can_walk = On;
    }

    MapTile( QString p_name, QPixmap p_pixmap, WalkPossibility p_can_walk,QGraphicsPixmapItem* parent=nullptr):QGraphicsPixmapItem(parent)
    {
        m_name = p_name;
        m_pixmap = p_pixmap;
        m_can_walk = p_can_walk;
        this->setPixmap(p_pixmap);
        m_item =  new QGraphicsPixmapItem(p_pixmap);
    }


    ~MapTile()
    {
        delete m_item;
    }


    void set_position(int p_x, int p_y)
    {
        this->setOffset(p_x,p_y);
    }

    QGraphicsPixmapItem* get_graphics_item()
    {
        return this;
    }

    QPixmap get_pixmap()
    {
        return m_pixmap;
    }

    QString get_name()
    {
        return m_name;
    }

    /*void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "Item clicked!";
        if(this->is)
        QGraphicsItem::mousePressEvent(event); // вызов базового обработчика, если нужно
    }*/

signals:
    /*void tile_was_clicked()
    {
        if()
    }*/
private:

    int m_x;
    int m_y;

    QString m_name;
    QPixmap m_pixmap;
    QGraphicsPixmapItem* m_item;
    WalkPossibility m_can_walk;

};

#endif // MAPTILE_H
