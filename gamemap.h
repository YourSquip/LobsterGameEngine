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

#include "mapgridborders.h"

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

class Tile:public QLabel
{
public:
    Tile(QWidget* parent = nullptr):QLabel(parent)
    {
        m_texture = QPixmap("D:/QtProjects/LobsterGameEngine/sprites/grass32.png");
        m_can_walk_on = true;
        this->setPixmap(m_texture);
    }
private:
    QPixmap m_texture;
    bool m_can_walk_on;
};


class GameMap: public QWidget
{

public:
    GameMap(QWidget* parent = nullptr):QWidget(parent)
    {
        m_grid_height = 0;
        m_grid_width = 0;
        m_grid = 0;
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
        m_grid->addWidget(new Tile());
        m_grid->addWidget(new QLabel("ASS"));

        //MapGridBorders* borders = new MapGridBorders(this);

    }

private:
    QGridLayout* m_grid;

    size_t m_grid_height;
    size_t m_grid_width;


    //QList<Tile*> tiles;
    QHash<QString, QSharedPointer<Tile>> tiles;

};

#endif // GAMEMAP_H
