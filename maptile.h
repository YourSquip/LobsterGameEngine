#ifndef MAPTILE_H
#define MAPTILE_H

#include <QRandomGenerator>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include "editor.h"


enum WalkPossibility{
    On = 1,
    Under = 2,
    NotAble = 3
};

class MapTile: public QGraphicsPixmapItem
{
public:
    MapTile(QGraphicsItem* parent=nullptr);
    MapTile( QString p_name, QPixmap p_pixmap, WalkPossibility p_can_walk,QGraphicsPixmapItem* parent=nullptr);
    ~MapTile();

    void set_position(int p_x, int p_y);
    QGraphicsPixmapItem* get_graphics_item();
    QPixmap get_pixmap();
    QString get_name();
    WalkPossibility get_walk_possibilty();
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "Item clicked! It was"<< m_name;
        //Editor::get_instance().get_editor_tool_type();
        //EditorTool* tool = new EditorTool();
        EditorToolType tool_type = Editor::get_instance().get_editor_tool_type();

        if(tool_type == PaintBrush)
        {
            QString tile_name = "grass";
            QPixmap pixmap = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/grass_tile.png");
            WalkPossibility can_walk = On;
            copy_tile(new MapTile(tile_name,pixmap,can_walk));
        }
        QGraphicsItem::mousePressEvent(event); // вызов базового обработчика, если нужно
    }
    void copy_tile(MapTile* map_tile);
private:
    int m_x;
    int m_y;
    QString m_name;
    QPixmap m_pixmap;
    QGraphicsPixmapItem* m_item;
    WalkPossibility m_can_walk;

};

MapTile* create_grass_tile();

MapTile* create_water_tile();

MapTile* create_ground_tile();

typedef MapTile* (*CreateTileFunc)();

class MapTileFactory
{
public:
    static MapTileFactory& get_instance();
    static void register_tile(QString p_tile_name, CreateTileFunc p_create_func);
    MapTile* create_spec_tile(QString p_tile_name);
    static QVector<QString> get_all_tiles_names();
private:

    MapTileFactory(){}
    ~MapTileFactory(){}
    static QHash<QString, CreateTileFunc> registered_tiles;
    static QVector<QString> names_of_tiles;

    MapTileFactory(MapTileFactory const&) = delete;
    MapTileFactory& operator= (MapTileFactory const&) = delete;
};

#endif // MAPTILE_H
