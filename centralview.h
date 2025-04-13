#ifndef CENTRALVIEW_H
#define CENTRALVIEW_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "gamemap.h"

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
        m_scene_mode = MapEditor;
        curr_scene_dep_on_mode();
        show_curr_scene();
    }



    QGraphicsScene* create_map_editor_scene()
    {
        QGraphicsScene* scene = new QGraphicsScene();;
        //GameMap* map = new GameMap();
        //map->make_grid(10,10);
        //scene->addWidget(map);

        QString filename = "D:/QtProjects/LobsterGameEngine/sprites/grass_tile.png";
        //QLabel* lbl = new QLabel(this);
        /** set content to show center in label */
        QPixmap pix;

        /** to check wether load ok */
        if(pix.load(filename)){
            /** scale pixmap to fit in label'size and keep ratio of pixmap */
            pix = pix.scaled(QSize(32,32),Qt::KeepAspectRatio);
            //->setPixmap(pix);
        }
        //QGraphicsPixmapItem* pix_item = new QGraphicsPixmapItem(pix);

        for (int x=0; x<=320; x+=32)
        {
            QGraphicsPixmapItem* pix_item = new QGraphicsPixmapItem(pix);
            scene->addLine(x,0,x,320, QPen(Qt::red));
            pix_item->setOffset(x,0);
            scene->addItem(pix_item);
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
