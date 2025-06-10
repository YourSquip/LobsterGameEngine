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

#include "maptile.h"
#include "editor.h"
#include "viewport.h"

class MapTilesList : public QWidget
{
    Q_OBJECT
public:
    MapTilesList(QWidget *parent = nullptr)
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
        m_tiles.push_back(new MapTileGraphics(QPixmap(":/sprites/grass32.png")));
        for(auto text_path: MapTileGraphicsFactory::get_instance().get_all_paths())
        {
            //QPushButton* tile_bttn = new QPushButton(this);
            //QLabel* tile_name_label = new QLabel(this);
            MapTileGraphics* graphics = MapTileGraphicsFactory::get_instance().get_concrete_graphics(text_path);
            m_tiles.push_back(graphics);
            //m_tile_buttons.push_back(tile_bttn);
            //m_tile_labels.push_back(tile_name_label);
            m_layout->addItem(graphics);
            //QVBoxLayout* tile_info = new QVBoxLayout();
            //tile_info->addWidget(tile_bttn);
            //m_layout->addLayout(tile_info);
        }

    }

public slots:
    void change_paint_tile_graphics(QString path)
    {
        qDebug()<<"change_paint_tile";
        Editor::get_instance()->set_tile_graphics(MapTileGraphicsFactory::get_instance().get_concrete_graphics(path));
    }

    /*void tile_clicked(unsigned int id)
    {
        qDebug()<<"tile_clicked";
        emit clicked_button(id);
    }

    void change_paint_tile_grass(unsigned int id)
    {
        qDebug()<<"change_paint_tile";
        Editor::get_instance()->set_paint_tile_name(m_tile_labels[id]->text());
    }
signals:
    void clicked_button(unsigned int id)
    {
        emit QPushButton::clicked;
    }*/
    //void clicked_button(unsigned int id);
private:
    QHBoxLayout* m_layout;
    QVector<MapTileGraphics*> m_tiles;
    //QVector<QPushButton*> m_tile_buttons;
    //QVector<QLabel*> m_tile_labels;
    //QPushButton* m_grass_tile;
    //QPushButton* m_dirt_tile;
    //QPushButton* m_water_tile;
};

#endif // MAPTILESLIST_H
