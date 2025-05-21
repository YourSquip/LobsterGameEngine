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
        QGraphicsScene* scene = new QGraphicsScene();

        int i = 0;
        int j = 0;
        qDebug()<<"size[]"<<m_map_tiles->m_tiles.size();
        qDebug()<<"size[][]"<<m_map_tiles->m_tiles.size();
        for(int x = 0; i<m_map_tiles->m_tiles.size(); x+=32)
        {
            for(int y = 0;j<m_map_tiles->m_tiles.at(0).size(); y+=32)
            {
                QGraphicsPixmapItem* pix_item = m_map_tiles->m_tiles[i][j]->get_graphics_item();
                pix_item->setOffset(x,y);
                if(pix_item == nullptr) qDebug()<<"ITS NULL!";
                else qDebug()<<"ITS NOT NULL!";
                scene->addItem(pix_item);
                j++;

            }
            j=0;
            i++;

        }
        i=0;

        return scene;
    }

    void draw_grid()
    {
        for (int x=0; x<=320; x+=32)
        {
            scene->addLine(x,0,x,320, QPen(Qt::red));
        }
        for (int y=0; y<=320; y+=32)
        {
            scene->addLine(0,y,320,y, QPen(Qt::green));
        }
    }

    ~CentralView()
    {
        delete m_curr_scene;
        //delete m_game_scene;
        //delete m_map_editor_scene;
        //delete m_game_editor_scene;
    }

public slots:
    void show_grid()
    {
        if(is_grid_shown)
        {
            is_grid_shown = false;
            update();//может обновиться где-то ещё
        }
        else
        {
            draw_grid();
        }
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

    bool is_grid_shown;

    QGraphicsScene* m_curr_scene;

    QGraphicsScene* m_game_scene;
    QGraphicsScene* m_map_editor_scene;
    QGraphicsScene* m_game_editor_scene;

    MapTiles* m_map_tiles;

};

#endif //CENTRALVIEW_H
