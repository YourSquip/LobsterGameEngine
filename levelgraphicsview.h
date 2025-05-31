#ifndef LEVELGRAPHICSVIEW_H
#define LEVELGRAPHICSVIEW_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QVector.h>
#include <QString>
#include <QDebug>
#include <QHashIterator>
#include <QRandomGenerator>
#include <QCheckBox>

#include "maptile.h"
#include "maptiles.h"
#include "grid.h"

enum SceneMode{
    MapEditor = 1,
    GameEditor = 2,
    GameMode = 3
};


class LevelGraphicsView: public QGraphicsView
{
public:
    LevelGraphicsView(QWidget* parent = 0):QGraphicsView(parent)
    {
        m_map_tiles = new MapTiles();
        is_grid_shown = false;
        m_grid = new Grid(m_map_tiles->m_tiles.size(),m_map_tiles->m_tiles.at(0).size(),32);
        //m_show_grid_check_box = new QCheckBox("show grid",this);
        //connect(m_show_grid_check_box,&QCheckBox::stateChanged, this,show_grid);
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
               // QGraphicsPixmapItem* pix_item = m_map_tiles->m_tiles[i][j]->get_graphics_item();
                //pix_item->setOffset(x,y);
               // m_map_tiles->m_tiles[i][j]->setOffset(x,y);
                //if(pix_item == nullptr) qDebug()<<"ITS NULL!";
                //else qDebug()<<"ITS NOT NULL!";
                m_map_tiles->m_tiles[i][j]->setOffset(x,y);
                scene->addItem(m_map_tiles->m_tiles[i][j]);
                j++;

            }
            j=0;
            i++;

        }
        i=0;

        return scene;
    }


    ~LevelGraphicsView()
    {
        delete m_curr_scene;
    }

public slots:
    void show_grid()
    {
        if(is_grid_shown && m_grid)
        {
            is_grid_shown = false;
            m_curr_scene->removeItem(m_grid);
        }
        else
        {
            is_grid_shown = true;
            m_curr_scene->addItem(m_grid);
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
    Grid* m_grid;
    //QCheckBox* m_show_grid_check_box;

};

#endif // LEVELGRAPHICSVIEW_H
