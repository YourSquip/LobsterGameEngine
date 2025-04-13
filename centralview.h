#ifndef CENTRALVIEW_H
#define CENTRALVIEW_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVector.h>
#include <QString>
#include <QDebug>
#include <QHashIterator>
#include <QRandomGenerator>
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
    };

private:
    int m_x;
    int m_y;

    QString m_name;
    QPixmap m_pixmap;
    QGraphicsPixmapItem* m_item;
    WalkPossibility m_can_walk;

};



typedef MapTile* (*CreateTileFunc)();

class MapTileFactory
{
public:
    static MapTileFactory& get_instance()
    {
        static MapTileFactory instance = MapTileFactory();
        return instance;

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

    //static MapTileFactory* instance;
    MapTileFactory(){}
    ~MapTileFactory(){}
    QHash<QString, CreateTileFunc> registered_tiles;

    MapTileFactory(MapTileFactory const&) = delete;
    MapTileFactory& operator= (MapTileFactory const&) = delete;
};


MapTile* create_grass_tile();

MapTile* create_water_tile();


class MapTiles
{
public:
    MapTiles()
    {
        //MapTileFactory factory;
        MapTileFactory::get_instance().register_tile(QString("grass"),create_grass_tile);
        MapTileFactory::get_instance().register_tile(QString("water"),create_water_tile);
        for(int x = 0; x < m_height; x++)
        {
            QVector<MapTile*> row;
            for(int y = 0; y < m_width; y++)
            {

                if(QRandomGenerator().bounded(1,2) == 1)
                {
                    row.append(MapTileFactory::get_instance().create_spec_tile("grass"));
                }
                else
                {
                    row.append(MapTileFactory::get_instance().create_spec_tile("water"));
                }
            }
            m_tiles.append(row);
        }

    }

    QVector<QVector<MapTile*>> m_tiles;

private:
    //QVector<QVector<QGraphicsPixmapItem*>> m_tiles;
    int m_height;
    int m_width;

};
class CentralView: public QGraphicsView
{
public:
    CentralView(QWidget* parent = 0):QGraphicsView(parent)
    {
        m_map_tiles = new MapTiles();
        change_curr_scene(create_map_editor_scene());
        show_curr_scene();
    }


    QGraphicsScene* create_map_editor_scene()
    {
        QGraphicsScene* scene = new QGraphicsScene();;

        //QString filename = "D:/QtProjects/LobsterGameEngine/sprites/grass_tile.png";
        //QString filename = "D:/QtProjects/LobsterGameEngine/sprites/water_tile1.jpg";
        //QPixmap pix;
        //if(pix.load(filename)){
        //    pix = pix.scaled(QSize(32,32),Qt::KeepAspectRatio);
        //}


        for(int x = 0; x <= 320; x+=32)
        {
            for(int y = 0; y <= 320; y+=32)
            {
                QGraphicsPixmapItem* pix_item = m_map_tiles->m_tiles[x/32][y/32]->get_graphics_item();
                //QGraphicsPixmapItem* pix_item = new QGraphicsPixmapItem(pix);
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
        delete m_game_scene;
        delete m_map_editor_scene;
        delete m_game_editor_scene;
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


    QGraphicsScene* m_curr_scene;

    QGraphicsScene* m_game_scene;
    QGraphicsScene* m_map_editor_scene;
    QGraphicsScene* m_game_editor_scene;

    MapTiles* m_map_tiles;
};

#endif //CENTRALVIEW_H
