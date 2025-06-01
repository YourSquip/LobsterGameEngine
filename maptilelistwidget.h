#ifndef MAPTILELISTWIDGET_H
#define MAPTILELISTWIDGET_H

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
            QPushButton* tile_bttn = new QPushButton(this);
            QLabel* tile_name_label = new QLabel(this);
            tile_bttn->setIcon(QIcon(MapTileFactory::get_instance().create_spec_tile(tile_name)->get_pixmap().scaled(32,32)));
            m_tile_buttons.push_back(tile_bttn);
            tile_name_label->setText(tile_name);
            m_tile_labels.push_back(tile_name_label);

            QVBoxLayout* tile_info = new QVBoxLayout();
            tile_info->addWidget(tile_bttn);
            tile_info->addWidget(tile_name_label);
            m_layout->addLayout(tile_info);
        }
        for(int i = 0; i < m_tile_buttons.size(); i++)
        {
            if(m_tile_labels[i]->text() == "grass")
            {
                connect(m_tile_buttons[i], &QPushButton::clicked, this, this->change_paint_tile_grass);
            }
            if(m_tile_labels[i]->text() == "ground")
            {
                connect(m_tile_buttons[i], &QPushButton::clicked, this, this->change_paint_tile_ground);
            }
            if(m_tile_labels[i]->text() == "water")
            {
                connect(m_tile_buttons[i], &QPushButton::clicked, this, this->change_paint_tile_water);
            }

        }
        /*m_layout->addWidget(tile_label);
        for(auto tile_name: MapTileFactory::get_instance().get_all_tiles_names())
        {
            QLabel* tile_label = new QLabel(this);
            QLabel* tile_name_label = new QLabel(this);
            tile_label->setPixmap(MapTileFactory::get_instance().create_spec_tile(tile_name)->get_pixmap().scaled(32,32));
            tile_name_label->setText(tile_name);

            QVBoxLayout* tile_info = new QVBoxLayout();
            tile_info->addWidget(tile_label);
            tile_info->addWidget(tile_name_label);
            m_layout->addLayout(tile_info);
        }*/
    }
public slots:
    void change_paint_tile_grass()
    {
        qDebug()<<"change_paint_tile";
        Editor::get_instance()->set_paint_tile_name("grass");
    }
    void change_paint_tile_ground()
    {
        qDebug()<<"change_paint_tile";
        Editor::get_instance()->set_paint_tile_name("ground");
    }
    void change_paint_tile_water()
    {
        qDebug()<<"change_paint_tile";
        Editor::get_instance()->set_paint_tile_name("water");
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
    QVector<QPushButton*> m_tile_buttons;
    QVector<QLabel*> m_tile_labels;
    //QPushButton* m_grass_tile;
    //QPushButton* m_dirt_tile;
    //QPushButton* m_water_tile;
};

#endif // MAPTILELISTWIDGET_H
