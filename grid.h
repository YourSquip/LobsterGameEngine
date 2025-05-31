#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QVector>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
class Grid: public QGraphicsItemGroup
{
public:
    Grid(unsigned int width, unsigned int height, unsigned int cell_size, QGraphicsItem* parent = nullptr):QGraphicsItemGroup(parent)
    {
        m_width = width;
        m_height = height;
        m_cell_size = cell_size;

        for (int x=0; x<=m_width*cell_size; x+=cell_size)
            this->addToGroup(new QGraphicsLineItem(x,0,x,500));

        for (int y=0; y<=m_height*cell_size; y+=cell_size)
           this->addToGroup(new QGraphicsLineItem(0,y,500,y));

    }
private:

    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_cell_size;
};

#endif // GRID_H
