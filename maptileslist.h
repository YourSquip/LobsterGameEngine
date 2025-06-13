#ifndef MAPTILESLIST_H
#define MAPTILESLIST_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QIcon>
#include <QVector>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "maptile.h"
//#include "editor.h"
#include "mapeditorsettings.h"
#include "viewport.h"

class MapTilesList : public QGraphicsView
{
    Q_OBJECT
public:
    MapTilesList(QWidget *parent = nullptr)
    {
        init_tiles();
    }

    void init_tiles()
    {

        this->setMaximumHeight(32);
        m_tiles_scene = new QGraphicsScene();
        m_tiles.push_back(new MapTileGraphics(QPixmap(":/sprites/grass32.png"),":/sprites/grass32.png"));
        m_tiles_scene->addItem(new MapTileGraphics(QPixmap(":/sprites/grass32.png"),":/sprites/grass32.png" ));
        int cell_size = 32;
        int curr_cell = 0;
        for(auto text_path: MapTileGraphicsFactory::get_instance()->get_all_paths())
        {
            MapTileGraphics* graphics = MapTileGraphicsFactory::get_instance()->get_concrete_graphics(text_path);
            graphics->setPos(curr_cell,0);
            graphics->set_is_map(false);
            m_tiles.push_back(graphics);
            m_tiles_scene->addItem(graphics);
            curr_cell += cell_size;
        }
        this->setScene(m_tiles_scene);

    }

public slots:

private:
    QHBoxLayout* m_layout;
    QVector<MapTileGraphics*> m_tiles;
    QGraphicsScene* m_tiles_scene;

};

#endif // MAPTILESLIST_H
