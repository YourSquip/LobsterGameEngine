#ifndef MAPTILELISTWIDGET_H
#define MAPTILELISTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>

#include "maptiles.h"
#include "levelgraphicsview.h"

class MapTileListWidget : public QWidget
{
    Q_OBJECT
public:
    MapTileListWidget(QWidget *parent = nullptr)
    {
        init_tiles();
    }

    void init_tiles()
    {
        //MapTileFactory::get_instance().register_tile(QString("grass"),create_grass_tile);
        //MapTileFactory::get_instance().register_tile(QString("water"),create_water_tile);
        m_layout = new QHBoxLayout(this);
        QLabel* tile_label = new QLabel("Tiles list:",this);
        m_layout->addWidget(tile_label);
        for(auto tile_name: MapTileFactory::get_instance().get_all_tiles_names())
        {

            QLabel* tile_label = new QLabel(this);
            QLabel* tile_name_label = new QLabel(this);
            tile_label->setPixmap(MapTileFactory::get_instance().create_spec_tile(tile_name)->get_pixmap().scaled(32,32));
            tile_name_label->setText(tile_name);
            QVBoxLayout* tile_info = new QVBoxLayout();
            //tile_label-;
            tile_info->addWidget(tile_label);
            tile_info->addWidget(tile_name_label);
            m_layout->addLayout(tile_info);
        }
    }

private:
    QHBoxLayout* m_layout;

};

#endif // MAPTILELISTWIDGET_H
