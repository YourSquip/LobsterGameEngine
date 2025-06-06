#ifndef GAMEOBJECTINFOWIDGET_H
#define GAMEOBJECTINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMap>
#include <QMapIterator>

#include "gameobject.h"
#include "componentinfowidget.h"
#include "editor.h"
//#include "editorwidget.h"

class GameObjectInfoWidget: public QWidget
{
public:
    GameObjectInfoWidget(QWidget* parent = nullptr):QWidget(parent)
    {
        GameObject* selected_obj = Editor::get_instance()->get_selected_game_obj();
        if(selected_obj)
        {
            qDebug()<< "there is a selected object";
        }
        m_layout = new QVBoxLayout(this);
        m_game_object = nullptr;
        //m_layout->addWidget(new QLabel("BIPKA"));
        this->setMinimumWidth(512);
        /*if(selected_obj)
        {
            m_game_object = selected_obj;
            m_layout = new QVBoxLayout(this);
            //QHash<QString, Component*> map = m_game_object->get_all_components();
            //QHashIterator<QString, Component*> it(map);
            QMapIterator<QString, Component*> i(m_game_object->get_all_components());
            while (i.hasNext()) {
                i.next();
                qDebug()<< qPrintable(i.key()) << ": " << i.value();
            }
            if(m_game_object==nullptr) qDebug()<<"gameobj is null";
            if(m_game_object->get_all_components().empty()) qDebug()<<"components container is null";

            /*for (QHash<QString,Component*>::iterator i = m_game_object->get_all_components().begin(); i != m_game_object->get_all_components().end(); ++i)
            {    //cout << qPrintable(key()) << ": " << i.value() << endl;
                if (i.key() == "positon")
                {
                    m_layout->addWidget(new PositionComponentInfoWidget(i.value()));
                }
                if (i.key() == "sprite")
                {
                    m_layout->addWidget(new SpriteComponentInfoWidget(i.value()));
                }
            }
        }*/


    }

public slots:
    void show_obj_info()
    {
        delete m_layout;
        m_layout = new QVBoxLayout(this);
        qDebug()<< "show_obj_info";
        m_game_object = Editor::get_instance()->get_selected_game_obj();
        m_layout->addWidget(new QLabel(m_game_object->get_name()));
        if(m_game_object==nullptr) qDebug()<<"gameobj is null";
        if(m_game_object->get_all_components().empty()) qDebug()<<"components container is null";
        QMapIterator<QString, Component*> i(m_game_object->get_all_components());
        while (i.hasNext()) {
            i.next();
            qDebug()<<(i.key()) << ": " << i.value();

            if (i.key() == "position")
            {
                PositionComponentInfoWidget* pos_info = new PositionComponentInfoWidget(i.value(),this);
                m_components.push_back(pos_info);
                m_layout->addWidget(pos_info);
            }
            if (i.key() == "sprite")
            {
                SpriteComponentInfoWidget* sprite_info = new SpriteComponentInfoWidget(i.value(),this);
                m_components.push_back(sprite_info);
                m_layout->addWidget(sprite_info);

            }
        }

        /*for (QHash<QString,Component*>::iterator i = m_game_object->get_all_components().begin(); i != m_game_object->get_all_components().end(); ++i)
        {    //cout << qPrintable(key()) << ": " << i.value() << endl;
            if (i.key() == "positon")
            {
                m_layout->addWidget(new PositionComponentInfoWidget(i.value()));
            }
            if (i.key() == "sprite")
            {
                m_layout->addWidget(new SpriteComponentInfoWidget(i.value()));
            }
        }*/
    }
    ~GameObjectInfoWidget()
    {
        delete m_game_object;
        delete m_layout;
    }
private:
    QVector<ComponentInfoWidget*> m_components;
    GameObject* m_game_object;
    QVBoxLayout* m_layout;
};

#endif // GAMEOBJECTINFOWIDGET_H
