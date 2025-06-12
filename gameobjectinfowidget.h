#ifndef GAMEOBJECTINFOWIDGET_H
#define GAMEOBJECTINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMap>
#include <QMapIterator>
#include <QSplitter>
#include <QCheckBox>

#include "gameobject.h"
#include "componentinfowidget.h"
#include "editor.h"
//#include "editorwidget.h"

class GameObjectInfoWidget: public QWidget
{
    //Q_OBJECT
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
        m_obj_name_line = new QLineEdit("");
        this->setMinimumWidth(300);

    }

    PositionComponentInfoWidget* get_pos_comp_widget()
    {
        for(auto widget: m_components)
        {
            if(dynamic_cast<PositionComponentInfoWidget*>(widget)->get_name() == "position")
            {
                return dynamic_cast<PositionComponentInfoWidget*>(widget);
            }
        }
    }

public slots:
    void show_obj_info()
    {
        delete m_layout;
        m_layout = new QVBoxLayout(this);
        qDebug()<< "show_obj_info";
        m_game_object = Editor::get_instance()->get_selected_game_obj();
        m_obj_name_line = new QLineEdit(m_game_object->get_name());
        m_controlable_check = new QCheckBox("is controlable");
        m_layout->addWidget(m_obj_name_line);
        m_layout->addWidget(m_controlable_check);
        m_layout->addWidget(new QSplitter(Qt::Horizontal));
        if(m_game_object==nullptr) qDebug()<<"gameobj is null";
        if(m_game_object->get_all_components().empty()) qDebug()<<"components container is null";
        QMapIterator<QString, Component*> i(m_game_object->get_all_components());
        m_new_comp_bttn = new QPushButton("add component");
        while (i.hasNext()) {
            i.next();
            qDebug()<<(i.key()) << ": " << i.value();

            if (i.key() == "position")
            {
                PositionComponentInfoWidget* pos_info = new PositionComponentInfoWidget(i.value(),this);
                m_components.push_back(pos_info);
                m_layout->addWidget(pos_info);
                //QObject::connect(,this,this->update_game_object_name);
                m_layout->addWidget(new QSplitter(Qt::Horizontal));
            }
            if (i.key() == "sprite")
            {
                SpriteComponentInfoWidget* sprite_info = new SpriteComponentInfoWidget(i.value(),this);
                m_components.push_back(sprite_info);
                m_layout->addWidget(sprite_info);

                m_layout->addWidget(new QSplitter(Qt::Horizontal));

            }
            if (i.key() == "audio")
            {
                AudioComponentInfoWidget* audio_info = new AudioComponentInfoWidget(i.value(),this);
                m_components.push_back(audio_info);
                m_layout->addWidget(audio_info);

                m_layout->addWidget(new QSplitter(Qt::Horizontal));

            }
        }
        QObject::connect(m_obj_name_line,m_obj_name_line->textEdited,this,this->update_game_object_name);
        QObject::connect(m_game_object,m_game_object->name_changed,this,this->update_line_name);
        QObject::connect(m_controlable_check,m_controlable_check->stateChanged,this, this->update_controlable);

        m_layout->addWidget(m_new_comp_bttn);
    }

    void update_line_name(QString new_name)
    {
        m_obj_name_line->setText(new_name);
    }

    void update_x(float x)
    {

        get_pos_comp_widget()->update_x_component_info(x);
        qDebug()<<"GameObjectsInfoWidget: get_pos_comp_widget()->update_x_component_info(x)";
    }

    void update_y(float y)
    {
        get_pos_comp_widget()->update_y_component_info(y);
        qDebug()<<"GameObjectsInfoWidget: get_pos_comp_widget()->update_y_component_info(y)";
    }


    void update_game_object_name(QString new_name)
    {
        m_game_object->set_name(new_name);
    }

    void update_controlable(bool controlable)
    {
        m_game_object->set_controlable(controlable);
    }
signals:
    void pixmap_x_pos_changed(float x);
    void pixmap_y_pos_changed(float y);
public:
    ComponentInfoWidget* get_component_info_widget(QString name)
    {
        for(auto comp: m_components)
        {
            if(comp->get_name_lbl()->text() == name)
            {
                return comp;
            }
        }
    }
    QLineEdit* get_obj_name_line()
    {
        return m_obj_name_line;
    }

    ~GameObjectInfoWidget()
    {
        delete m_game_object;
        delete m_layout;
        m_components.clear();
    }
private:
    QCheckBox* m_controlable_check;
    QLineEdit* m_obj_name_line;
    QVector<ComponentInfoWidget*> m_components;
    GameObject* m_game_object;
    QVBoxLayout* m_layout;
    QPushButton* m_new_comp_bttn;
};

#endif // GAMEOBJECTINFOWIDGET_H
