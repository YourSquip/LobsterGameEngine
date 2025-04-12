#ifndef CENTRALVIEW_H
#define CENTRALVIEW_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include "gamemap.h"

class CentralView: public QGraphicsView
{
public:
    CentralView(QWidget* parent = 0):QGraphicsView(parent)
    {
        QGraphicsScene* scene = new QGraphicsScene();
        setScene(scene);

        GameMap* map = new GameMap();
        map->make_grid(1,1);
        scene->addWidget(map);



        for (int x=0; x<=500; x+=50)
            scene->addLine(x,0,x,500, QPen(Qt::red));

        for (int y=0; y<=500; y+=50)
            scene->addLine(0,y,500,y, QPen(Qt::green));


    }

private:
    QGraphicsScene* m_curr_scene;
    //QGraphicsScene* m_game_scene;
    //QGraphicsScene* m_map_editor_scene;
    //QGraphicsScene* m_game_editor_scene;
};

#endif // CENTRALVIEW_H
