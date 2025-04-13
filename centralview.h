#ifndef CENTRALVIEW_H
#define CENTRALVIEW_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVector.h>
#include <QString>
#include <QDebug>
#include <QHashIterator>
#include "gamemap.h"

enum SceneMode{
    MapEditor = 1,
    GameEditor = 2,
    GameMode = 3
};

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
        can_walk_on = On;

    }
    virtual ~MapTile()
    {
        delete m_item;
    }

private:
    QString m_name;
    bool can_walk_on;
    QPixmap m_pixmap;
    QGraphicsPixmapItem* m_item;
    WalkPossibility m_can_walk;
};
//typedef MapTile*()(QString p_name, QPixmap p_pixmap, WalkPossibility p_walk_mod) CreateTile;
//typedef MapTile* (*CreateTileFunc)(QString p_name, QPixmap p_pixmap, WalkPossibility p_walk_mod);
typedef MapTile* (*CreateTileFunc)();

class MapTileFactory
{
public:
    MapTileFactory get_instance()
    {
        if(instance == nullptr)
        {
            instance = new MapTileFactory();
        }
        else
        {
            return *instance;
        }
    }

    void register_tile(QString p_tile_name, CreateTileFunc p_create_func)
    {
        if(!registered_tiles.contains(p_tile_name))
        {
            registered_tiles.emplace(p_tile_name,p_create_func);
        }
    }

    MapTile* create_spec_tile(QString p_tile_name)
    {
        if(registered_tiles.contains(p_tile_name))
        {
           CreateTileFunc func = registered_tiles.find(p_tile_name).value();
           return func();
        }
        else
        {
            qDebug()<< "There's no such tile";
        }
        return nullptr;
    }

private:

    MapTileFactory* instance;
    MapTileFactory() = default;
    QHash<QString, CreateTileFunc> registered_tiles;
};



class MapTiles
{
public:
    MapTiles()
    {

    }
private:
    QVector<QVector<QGraphicsPixmapItem*>> m_tiles;
};

class CentralView: public QGraphicsView
{
public:
    CentralView(QWidget* parent = 0):QGraphicsView(parent)
    {
        m_scene_mode = MapEditor;
        curr_scene_dep_on_mode();
        show_curr_scene();
    }


    QGraphicsScene* create_map_editor_scene()
    {
        QGraphicsScene* scene = new QGraphicsScene();;

        //QString filename = "D:/QtProjects/LobsterGameEngine/sprites/grass_tile.png";
        QString filename = "D:/QtProjects/LobsterGameEngine/sprites/water_tile1.jpg";
        QPixmap pix;
        if(pix.load(filename)){
            pix = pix.scaled(QSize(32,32),Qt::KeepAspectRatio);
        }


        for(int x = 0; x <= 320; x+=32)
        {
            for(int y = 0; y <= 320; y+=32)
            {
                QGraphicsPixmapItem* pix_item = new QGraphicsPixmapItem(pix);
                pix_item->setOffset(x,y);
                scene->addItem(pix_item);
            }

        }
        for (int x=0; x<=320; x+=32)
        {
            scene->addLine(x,0,x,320, QPen(Qt::red));
        }
        for (int y=0; y<=320; y+=32)
        {
            scene->addLine(0,y,320,y, QPen(Qt::green));
        }

        return scene;
    }

    ~CentralView()
    {
        delete m_curr_scene;
    }

private:

    void change_curr_scene(QGraphicsScene* p_scene)
    {
        m_curr_scene = p_scene;
    }

    void show_curr_scene()
    {
        setScene(m_curr_scene);
    }

    void curr_scene_dep_on_mode()
    {
        if(m_scene_mode == MapEditor)
        {
            m_curr_scene = create_map_editor_scene();
        }
        else m_curr_scene = nullptr;
    }
    QGraphicsScene* m_curr_scene;
    SceneMode m_scene_mode;
    //QGraphicsScene* m_game_scene;
    //QGraphicsScene* m_map_editor_scene;
    //QGraphicsScene* m_game_editor_scene;
};

#endif // CENTRALVIEW_H
