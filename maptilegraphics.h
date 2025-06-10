#ifndef MAPTILEGRAPHICS_H
#define MAPTILEGRAPHICS_H

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
        //this->setPixmap(QPixmap(":/sprites/empty_tile.png"));
        //this->setVisible(true);
        //QGraphicsItem::mousePressEvent(event);
        EditorToolType tool_type = Editor::get_instance()->get_editor_tool_type();
        if(tool_type == PaintBrush || tool_type == Eraser)
        {

            //qDebug() << "Item clicked! It was"<< m_name;
            if(tool_type == PaintBrush)
            {

                //m_name = Editor::get_instance()->get_map_tile->get;
                //m_pixmap = Editor::get_instance()->get_map_tile()->get_graphics()->get_pixmap();
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
        }

    }


private:

    QPixmap m_pixmap;

};

class MapTileGraphicsFactory
{
public:
    void register_graphics(QString sprite_path)
    {
        m_paths.push_back(sprite_path);
        MapTileGraphics* graphics = new MapTileGraphics(QPixmap(sprite_path));
        m_graphics.push_back(graphics);
        m_registered_graphics[sprite_path] = graphics;
    }
    MapTileGraphics*  get_concrete_graphics(QString sprite_path)
    {
        if(!m_registered_graphics.contains(sprite_path))
        {
            register_graphics(sprite_path);
            //m_paths.push_back(sprite_path);
            //MapTileGraphics* graphics = new MapTileGraphics(QPixmap(sprite_path));
            //m_registered_graphics[sprite_path] = graphics;
            //m_registered_graphics[sprite_path] = new MapTileGraphics(QPixmap(sprite_path));
            //m_registered_graphics.            //register_graphics(sprite_path);
        }
        else
        {
            return m_registered_graphics[sprite_path];
        }
    }
    MapTileGraphicsFactory& get_instance()
    {
        static MapTileGraphicsFactory instance = MapTileGraphicsFactory();
        return instance;
    }
    QVector<QString> get_all_paths()
    {
        return m_paths;
    }
    QVector<MapTileGraphics*> get_all_graphics()
    {
        return m_graphics;
    }
private:
    MapTileGraphicsFactory()
    {
        qDebug()<<"MapTileGraphicsFactory constructor";
    }
    QMap<QString, MapTileGraphics*> m_registered_graphics;
    QVector<QString> m_paths;
    QVector<MapTileGraphics*> m_graphics;
    //static MapTileGraphicsFactory& instance;

};
#endif // MAPTILEGRAPHICS_H
