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
        m_obj_name_line = new QLineEdit("");
        this->setMinimumWidth(300);

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
        m_controlable_check->setChecked(m_game_object->get_states()->m_controlable);
        m_interactable_check = new QCheckBox("is interactable");
        m_interactable_check->setChecked(m_game_object->get_states()->m_interactable);
        m_can_interact_check = new QCheckBox("can interact");
        m_can_interact_check->setChecked(m_game_object->get_states()->m_can_interact);
        m_layout->addWidget(m_obj_name_line);
        m_layout->addWidget(new QLabel("States:"));

        m_layout->addWidget(m_controlable_check);
        m_layout->addWidget(m_interactable_check);
        m_layout->addWidget(m_can_interact_check);

        m_layout->addWidget(new QSplitter(Qt::Horizontal));
        if(m_game_object==nullptr) qDebug()<<"gameobj is null";
        if(m_game_object->get_all_components().empty()) qDebug()<<"components container is null";
        QMapIterator<QString, Component*> i(m_game_object->get_all_components());
        m_new_comp_bttn = new QPushButton("add component");
        while (i.hasNext()) {
            i.next();
            qDebug()<<(i.key()) << ": " << i.value();

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
        QObject::connect(m_interactable_check,m_interactable_check->stateChanged,this, this->update_interactable);
        QObject::connect(m_can_interact_check,m_can_interact_check->stateChanged,this, this->update_can_interact);
        m_layout->addWidget(m_new_comp_bttn);
    }

    void update_line_name(QString new_name)
    {
        m_obj_name_line->setText(new_name);
    }


    void update_game_object_name(QString new_name)
    {
        m_game_object->set_name(new_name);
    }

    void update_controlable(bool controlable)
    {
        m_game_object->get_states()->m_controlable = controlable;
    }
    void update_interactable(bool interactable)
    {
        m_game_object->get_states()->m_interactable = interactable;
    }
    void update_can_interact(bool can_interact)
    {
        m_game_object->get_states()->m_can_interact = can_interact;
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
    QLineEdit* m_obj_name_line;
    QVector<ComponentInfoWidget*> m_components;
    GameObject* m_game_object;
    QVBoxLayout* m_layout;
    QPushButton* m_new_comp_bttn;


    QCheckBox* m_controlable_check;
    QCheckBox* m_interactable_check;
    QCheckBox* m_can_interact_check;
};

#endif // GAMEOBJECTINFOWIDGET_H
