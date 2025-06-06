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
        qDebug()<< "show_obj_info";
        m_game_object = Editor::get_instance()->get_selected_game_obj();
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
        }*/
    }
    ~GameObjectInfoWidget()
    {
        delete m_game_object;
        delete m_layout;
    }
private:
    GameObject* m_game_object;
    QVBoxLayout* m_layout;
};

#endif // GAMEOBJECTINFOWIDGET_H
