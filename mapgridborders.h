#ifndef MAPGRIDBORDERS_H
#define MAPGRIDBORDERS_H

#include <QWidget>
#include <QGraphicsView>

class MapGridBorders: public QGraphicsView
{
public:
    MapGridBorders(QWidget* parent = nullptr):QGraphicsView(parent)
    {
        QGraphicsScene* scene = new QGraphicsScene;
        setScene(scene);

        // Add the vertical lines first, paint them red
        for (int x=0; x<=500; x+=50)
            scene->addLine(x,0,x,500, QPen(Qt::red));

        // Now add the horizontal lines, paint them green
        for (int y=0; y<=500; y+=50)
            scene->addLine(0,y,500,y, QPen(Qt::green));

        // Fit the view in the scene's bounding rect
        //fitInView(scene->itemsVBoundingRect());
    }
};

#endif // MAPGRIDBORDERS_H
