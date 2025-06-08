#ifndef MAPTILE_H
#define MAPTILE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "editor.h"


class MapTileGraphics: public QGraphicsPixmapItem
{
public:
    MapTileGraphics(QPixmap pixmap):QGraphicsPixmapItem()
    {
        m_pixmap = pixmap;
        this->setPixmap(pixmap.scaled(32,32));

        qDebug()<<"MapTileGraphics constructor";
        this->setFlag(QGraphicsItem::ItemIsSelectable);

    }

    void set_pixmap(QPixmap pixmap)
    {
        m_pixmap = pixmap.scaled(32,32);
        this->setPixmap(m_pixmap);
    }


    QPixmap get_pixmap()
    {
        return m_pixmap;
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        qDebug() << "tile clicked!";
;
        //m_pixmap = Editor::get_instance()->get_map_tile()->get_graphics()->get_pixmap();
        this->setPixmap(QPixmap(":/sprites/empty_tile.png"));
        this->setVisible(true);
        QGraphicsItem::mousePressEvent(event);
        //EditorToolType tool_type = Editor::get_instance()->get_editor_tool_type();
        /*if(tool_type == PaintBrush || tool_type == Eraser)
        {

            qDebug() << "Item clicked! It was"<< m_name;
            if(tool_type == PaintBrush)
            {

                //m_name = Editor::get_instance()->get_map_tile->get;
                m_pixmap = Editor::get_instance()->get_map_tile()->get_graphics()->get_pixmap();
                //m_can_walk = On;
                this->setPixmap(m_pixmap);
                this->setVisible(true);
            }
            if(tool_type == Eraser)
            {
                //m_name = "none";
                m_pixmap = QPixmap(":/sprites/empty_tile.png");
                //m_can_walk = NotAble;
                this->setPixmap(m_pixmap);
            }
            QGraphicsItem::mousePressEvent(event); // вызов базового обработчика, если нужно
        }*/

    }


private:

    QPixmap m_pixmap;

};

class MapTileGraphicsFactory
{
public:
    void register_graphics(QString sprite_path)
    {
        m_registered_graphics[sprite_path] = new MapTileGraphics(QPixmap(sprite_path));
    }
    MapTileGraphics*  get_concrete_graphics(QString sprite_path)
    {
        if(!m_registered_graphics.contains(sprite_path))
        {
            //m_registered_graphics[sprite_path] = new MapTileGraphics(QPixmap(sprite_path));
            //m_registered_graphics.            //register_graphics(sprite_path);
        }
        else
        {
            return m_registered_graphics[sprite_path];
        }
    }
    static MapTileGraphicsFactory& get_instance()
    {
        static MapTileGraphicsFactory instance = MapTileGraphicsFactory();
        return instance;
    }

private:
    MapTileGraphicsFactory(){
        qDebug()<<"MapTileGraphicsFactory constructor";}
    static QMap<QString, MapTileGraphics*> m_registered_graphics;
    //static MapTileGraphicsFactory& instance;

};


class MapTile
{
public:
    MapTile(unsigned int x_pos = 0, unsigned int y_pos = 0)
    {
        m_graphics = new MapTileGraphics(QPixmap("D:/QtProjects/LobsterGameEngine2.0/LobsterGameEngine/sprites/grass32.png"));
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
};



#endif // MAPTILE_H
