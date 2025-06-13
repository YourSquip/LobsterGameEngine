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


        if(m_is_map)
        {

            if(Editor::get_instance()->get_editor_tool_type() == 1)
            {

                m_pixmap_path = MapEditorSettings::get_instance()->get_paint_tile_pixmap_path();
                m_pixmap = QPixmap(m_pixmap_path);
                this->setPixmap(m_pixmap);
                //this->setVisible(true);
            }
            if(Editor::get_instance()->get_editor_tool_type() == 2)
            {
                m_pixmap_path = ":/sprites/grass32.png";
                m_pixmap = QPixmap(":/sprites/grass32.png");
                this->setPixmap(m_pixmap);
            }
            QGraphicsItem::mousePressEvent(event);
        }
        if(!m_is_map)
        {
            MapEditorSettings::get_instance()->set_paint_tile_pixmap_path(this->get_pixmap_path());
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

        }
        else
        {
            return m_registered_graphics[sprite_path];
        }
    }

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

private:
    MapTileGraphicsFactory()
    {
        qDebug()<<"MapTileGraphicsFactory constructor";
        register_graphics(":/sprites/water_tile.png");
        register_graphics(":/sprites/ground_tile.png");
        register_graphics(":/sprites/grass_tile.png");
    }

    QMap<QString, MapTileGraphics*> m_registered_graphics;
    QVector<QString> m_paths;
    QVector<MapTileGraphics*> m_graphics;
    static MapTileGraphicsFactory* instance;

};
#endif // MAPTILEGRAPHICS_H
