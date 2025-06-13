#ifndef COMPONENTINFOWIDGET_H
#define COMPONENTINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <QCheckBox>
#include <QFileDialog>

#include "component.h"

class ComponentInfoWidget:public QWidget
{
public:
    ComponentInfoWidget(Component* component, QWidget* parent = nullptr):QWidget(parent)
    {
        m_component = component;
        m_name = new QLabel(component->get_name(),this);

        qDebug()<<"name:"<<component->get_name();
        m_layout = new QVBoxLayout(this);
        //m_layout->
        m_layout->addWidget(m_name);
        qDebug()<<"ComponentInfoWidget";
        this->setVisible(true);
    }
    ~ComponentInfoWidget()
    {
        delete m_name;
        delete m_layout;
    }
    QLabel* get_name_lbl()
    {
        return m_name;
    }
protected:
    QLabel* m_name;
    QVBoxLayout* m_layout;
    Component* m_component;
};


class SpriteComponentInfoWidget:public ComponentInfoWidget
{
public:
    SpriteComponentInfoWidget(Component* component, QWidget* parent = nullptr):ComponentInfoWidget(component,parent)
    {

        qDebug()<<"SpriteComponentInfoWidget";
        m_sprite = dynamic_cast<Sprite*>(component);

        m_label =  new QLabel("pixmap:",this);
        m_pixmap = new QLabel(this);
        m_pixmap->setPixmap(m_sprite->get_pixmap().scaled(32,32));
        m_open_pixmap_button = new QPushButton("Choose sprite",this);
        connect(m_open_pixmap_button,m_open_pixmap_button->clicked,this,this->open_sprite_explorer);
        connect(m_sprite,m_sprite->item_changed,this,this->update_pixmap_component_info);

        QHBoxLayout* layout = new QHBoxLayout();


        layout->addWidget(m_label);
        layout->addWidget(m_pixmap);


        m_layout->addLayout(layout);
        m_layout->addWidget(m_open_pixmap_button);

    }
    Sprite* get_sprite()
    {
        return m_sprite;
    }

    ~SpriteComponentInfoWidget()
    {
        delete m_label;
        delete m_pixmap;
        //delete m_sprite;
        delete m_open_pixmap_button;
    }

public slots:
    void open_sprite_explorer()
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "../sprites", "Images (*.png *.xpm *.jpg)");
        if (!fileName.isEmpty())
        {
            QPixmap pixmap(fileName);
            m_sprite->set_pixmap(pixmap.scaled(32,32));
            qDebug()<<"file name:"<<fileName;
            emit m_sprite->pixmap_was_changed();
        }
    }
    void update_pixmap_component_info(Component* component)
    {
        m_sprite = dynamic_cast<Sprite*>(component);
        m_pixmap->setPixmap(m_sprite->get_pixmap());
        //emit pixmap_was_changed();
    }

private:
    QLabel* m_label;
    QLabel* m_pixmap;
    Sprite* m_sprite;
    QPushButton* m_open_pixmap_button;

};

class AudioComponentInfoWidget:public ComponentInfoWidget
{
public:
    AudioComponentInfoWidget(Component* component, QWidget* parent = nullptr):ComponentInfoWidget(component,parent)
    {

        qDebug()<<"AudioComponentInfoWidget";
        m_audio = dynamic_cast<Audio*>(component);
        m_label =  new QLabel("audio file:");
        m_audio_label = new QLabel(m_audio->get_audio_path());

        m_play_audio_button = new QPushButton("play");
        m_stop_audio_button = new QPushButton("stop");
        m_open_audio_button = new QPushButton("Choose audio file");
        connect(m_open_audio_button,m_open_audio_button->clicked,this,this->open_audio_explorer);
        connect(m_audio,m_audio->item_changed,this,this->update_audio_component_info);
        connect(m_play_audio_button,m_open_audio_button->clicked,this,this->play_audio);
        connect(m_stop_audio_button,m_open_audio_button->clicked,this,this->stop_audio);
        QHBoxLayout* layout = new QHBoxLayout();
        QHBoxLayout* bttn_layout = new QHBoxLayout();

        layout->addWidget(m_label);
        layout->addWidget(m_audio_label);

        bttn_layout->addWidget(m_play_audio_button);
        bttn_layout->addWidget(m_stop_audio_button);
        m_layout->addLayout(layout);
        m_layout->addLayout(bttn_layout);
        m_layout->addWidget(m_open_audio_button);

    }
    Audio* get_audio()
    {
        return m_audio;
    }

    ~AudioComponentInfoWidget()
    {
        delete m_label;
    }

public slots:
    void open_audio_explorer()
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "../audio", "Audio files (*.wav *.mp3)");
        if (!fileName.isEmpty())
        {
            m_audio->set_audio(fileName);
            qDebug()<<"file name:"<<fileName;
            emit m_audio->audio_was_changed();
        }
    }
    void update_audio_component_info(Component* component)
    {
        m_audio = dynamic_cast<Audio*>(component);
        m_label->setText(m_audio->get_audio_path());
    }
    void play_audio()
    {
        m_audio->play_audio();
    }
    void stop_audio()
    {
        m_audio->play_audio();
    }

private:
    QLabel* m_label;
    QLabel* m_audio_label;
    Audio* m_audio;
    QPushButton* m_open_audio_button;

    QCheckBox* m_autoplay_check;
    QCheckBox* m_play_when_interacted_check;

    QPushButton* m_play_audio_button;
    QPushButton* m_stop_audio_button;

};

#endif // COMPONENTINFOWIDGET_H
