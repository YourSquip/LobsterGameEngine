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
#include "maptile.h"
#include "maptiles.h"

enum SceneMode{
    MapEditor = 1,
    GameEditor = 2,
    GameMode = 3
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

        int i = 0;
        int j = 0;
        qDebug()<<"size[]"<<m_map_tiles->m_tiles.size();
        qDebug()<<"size[][]"<<m_map_tiles->m_tiles.size();
        for(int x = 0; x <= 320 && i<m_map_tiles->m_tiles.size(); x+=32)
        {
            for(int y = 0; y <= 320 && j<m_map_tiles->m_tiles.at(0).size(); y+=32)
            {
                QGraphicsPixmapItem* pix_item = m_map_tiles->m_tiles[i][j]->get_graphics_item();
                //QGraphicsPixmapItem* pix_item = new QGraphicsPixmapItem(pix);
                pix_item->setOffset(x,y);
                if(pix_item == nullptr) qDebug()<<"ITS NULL!";
                else qDebug()<<"ITS NOT NULL!";
                scene->addItem(pix_item);
                j++;

            }
            i++;

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
        //delete m_game_scene;
        //delete m_map_editor_scene;
        //delete m_game_editor_scene;
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
