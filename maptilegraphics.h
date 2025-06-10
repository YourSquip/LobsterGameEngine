#ifndef MAPTILEGRAPHICS_H
#define MAPTILEGRAPHICS_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "editor.h"
#include "mapeditorsettings.h"


class MapTileGraphics: public QGraphicsPixmapItem
{
public:
    MapTileGraphics(QPixmap pixmap, QString pixmap_path):QGraphicsPixmapItem()
    {
        m_pixmap = pixmap;
        m_pixmap_path = pixmap_path;
        this->setPixmap(pixmap.scaled(32,32));

        qDebug()<<"MapTileGraphics constructor";
        this->setFlag(QGraphicsItem::ItemIsSelectable);
        m_is_map = true;

    }

    void set_pixmap(QPixmap pixmap)
    {
        m_pixmap = pixmap.scaled(32,32);
        this->setPixmap(m_pixmap);
    }

    QString get_pixmap_path()
    {
        return m_pixmap_path;
    }

    void set_pixmap_path(QString pixmap_path)
    {
        m_pixmap_path = pixmap_path;
    }

    QPixmap get_pixmap()
    {
        return m_pixmap;
    }

    void set_is_map(bool flag)
    {
        m_is_map = flag;
    }

    bool get_is_map()
    {
        return m_is_map;
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        qDebug() << "tile clicked!";

        //m_pixmap = Editor::get_instance()->get_map_tile()->get_graphics()->get_pixmap();
        //this->setPixmap(QPixmap(":/sprites/empty_tile.png"));
        //this->setVisible(true);
        //QGraphicsItem::mousePressEvent(event);
        //EditorToolType tool_type = Editor::get_instance()->get_editor_tool_type();
        if(m_is_map)
        {

            //qDebug() << "Item clicked! It was"<< m_name;
            if(Editor::get_instance()->get_editor_tool_type() == 1)
            {

                //m_name = Editor::get_instance()->get_map_tile->get;
                //m_pixmap = Editor::get_instance()->get_map_tile()->get_graphics()->get_pixmap();
                //m_can_walk = On;
                m_pixmap_path = MapEditorSettings::get_instance()->get_paint_tile_pixmap_path();
                m_pixmap = QPixmap(m_pixmap_path);
                this->setPixmap(m_pixmap);
                this->setVisible(true);
            }
            if(Editor::get_instance()->get_editor_tool_type() == 2)
            {
                //m_name = "none";
                m_pixmap_path = ":/sprites/empty_tile.png";
                m_pixmap = QPixmap(":/sprites/empty_tile.png");
                //m_can_walk = NotAble;
                this->setPixmap(m_pixmap);
            }
            QGraphicsItem::mousePressEvent(event); // вызов базового обработчика, если нужно
        }
        if(!m_is_map)
        {
            qDebug()<<"IT SHOULD BE CHANGING TO:";
            //MapEditorSettings::get_instance()->set_paint_tile_pixmap_path(m_pixmap_path);
            MapEditorSettings::get_instance()->set_paint_tile_pixmap_path(this->get_pixmap_path());
            qDebug()<<m_pixmap_path;
        }

    }


private:

    QPixmap m_pixmap;
    QString m_pixmap_path;
    bool m_is_map;

};


class MapTileGraphicsFactory
{
public:
    void register_graphics(QString sprite_path)
    {
        m_paths.push_back(sprite_path);
        MapTileGraphics* graphics = new MapTileGraphics(QPixmap(sprite_path), sprite_path);
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
    /*MapTileGraphicsFactory& get_instance()
    {
        static MapTileGraphicsFactory instance = MapTileGraphicsFactory();
        return instance;
    }*/
    static MapTileGraphicsFactory* get_instance()
    {
        if(instance) return  instance;
        instance = new MapTileGraphicsFactory();
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
    /*MapTileGraphics* get_paint_tile()
    {
        return paint_tile;
    }
    void set_paint_tile(MapTileGraphics* graphics)
    {
        paint_tile = graphics;
    }*/
private:
    MapTileGraphicsFactory()
    {
        qDebug()<<"MapTileGraphicsFactory constructor";
        register_graphics(":/sprites/water_tile.png");
        register_graphics(":/sprites/ground_tile.png");
        register_graphics(":/sprites/grass_tile.png");
        //paint_tile = new MapTileGraphics(QPixmap(":/sprites/water_tile.png"));
    }
    //MapTileGraphics* paint_tile;
    QMap<QString, MapTileGraphics*> m_registered_graphics;
    QVector<QString> m_paths;
    QVector<MapTileGraphics*> m_graphics;
    static MapTileGraphicsFactory* instance;

};
#endif // MAPTILEGRAPHICS_H
