#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QImage>
#include <QList>
#include <QHash>
#include <QSharedPointer>
#include <QSharedDataPointer>
#include <QSharedData>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsGridLayout>
#include <QGraphicsLayoutItem>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QStyle>
#include "mapgridborders.h"
#include "centralview.h"




class TileType
{

};

//typedef Tile*() create_tile;

class TileFactory
{
public:
    TileFactory get_instance()
    {
        if(instance == nullptr)
        {
            instance = new TileFactory();
        }
        else
        {
            return *instance;
        }
    }


private:

    TileFactory* instance;
    TileFactory() = default;
};

class Tile: public QLabel
{
public:

    Tile(QWidget* parent = nullptr):QLabel(parent)
    {
        //m_texture = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/grass32.png");
        //m_texture = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/grass_tile.png");
        //m_can_walk_on = true;
        //this->setPixmap(m_texture);
        //this->setWindowFlag(Qt::FramelessWindowHint);
        //this->setAttribute(Qt::WA_NoSystemBackground); // No background
        //this->setAttribute(Qt::WA_TranslucentBackground);
        QString filename = "D:/QtProjects/LobsterGameEngine/sprites/grass_tile.png";
        //QLabel* lbl = new QLabel(this);
        /** set content to show center in label */
        QPixmap pix;

        /** to check wether load ok */
        if(pix.load(filename)){
            /** scale pixmap to fit in label'size and keep ratio of pixmap */
            pix = pix.scaled(this->size(),Qt::KeepAspectRatio);
            this->setPixmap(pix);
        }
        m_texture = pix;
        m_can_walk_on = true;
        this->setAlignment(Qt::AlignLeft);
        this->setAlignment(Qt::AlignTop);
    }
private:
    QPixmap m_texture;
    bool m_can_walk_on;
    int x;
    int y;
};


class GameMap: public QWidget
{

public:
    GameMap(QWidget* parent = nullptr):QWidget(parent)
    {
        m_grid_height = 0;
        m_grid_width = 0;
        m_grid = 0;
        this->setAttribute(Qt::WA_NoSystemBackground); // No background
        this->setAttribute(Qt::WA_TranslucentBackground);

        //m_la
    }

    void set_grid_size(size_t height, size_t width)
    {
        m_grid_height = height;
        m_grid_width = width;
    }

    void make_grid(size_t height, size_t width)
    {

        set_grid_size(height,width);
        m_grid = new QGridLayout(this);
        //m_grid->addWidget(new Tile(this),0,0);
        for(int i = 0; i < m_grid_height; i++)
        {
            for(int j = 0; j < m_grid_width; j++)
            {
                m_grid->addWidget(new Tile(this),i,j);
            }
        }
        //m_grid->addItem(new QGraphicsLayoutItem(Tile(this)),1,1);


    }

private:
    QGridLayout* m_grid;

    size_t m_grid_height;
    size_t m_grid_width;


    //QList<Tile*> tiles;
    QHash<QString, QSharedPointer<Tile>> tiles;

};

#endif // GAMEMAP_H
