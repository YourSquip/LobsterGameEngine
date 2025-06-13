#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include <QPixmap>
#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>


class Component: public QObject
{
    Q_OBJECT
public:
    Component()
    {

    }
    virtual ~Component()
    {

    }
    virtual QString get_name()=0;
    QString m_name;
signals:
    void item_changed(Component* component);
};


class Sprite: public Component
{
    Q_OBJECT
public:
    Sprite()
    {
        m_name = "sprite";
        m_pixmap = QPixmap(":/sprites/icons/object.png");
    }

    Sprite(QPixmap pixmap)
    {
        m_name = "sprite";
        m_pixmap = pixmap;
    }


    QPixmap get_pixmap()
    {
        return m_pixmap;
    }

    void set_pixmap(QPixmap pixmap)
    {
        m_pixmap = pixmap;
        emit item_changed(this);
    }

    QString get_name() override
    {
        return m_name;
    }
signals:
    void pixmap_was_changed();
private:
    QPixmap m_pixmap;
};


class Audio: public Component
{
    Q_OBJECT
public:
    Audio()
    {
        m_name = "audio";
        m_media_player = new QMediaPlayer();
        m_audio_output = new QAudioOutput();
        m_media_player->setAudioOutput(m_audio_output);
        //m_media_player->setSource(QUrl::fromLocalFile("D:/QtProjects/LobsterEngine2.0/LobsterEngine/audio/coin_sound.wav"));
        m_audio_path = "";
        m_audio_output->setVolume(50);
    }

    Audio(QString url)
    {
        m_name = "audio";
        m_audio_path = url;
        m_media_player = new QMediaPlayer();
        m_audio_output = new QAudioOutput();
        m_media_player->setSource(QUrl::fromLocalFile(url));
        m_audio_output->setVolume(50);
    }

    void play_audio()
    {
        m_media_player->play();
    }

    void stop_audio()
    {
        m_media_player->stop();
    }

    QString get_name() override
    {
        return m_name;
    }

    void set_audio(QString url)
    {
        m_media_player->setSource(QUrl::fromLocalFile(url));
        m_audio_path = url;
        emit audio_was_changed();
    }

    QString get_audio_path()
    {
        return m_audio_path;
    }
signals:
    void audio_was_changed();
private:
    QAudioOutput* m_audio_output;
    QMediaPlayer* m_media_player;
    QString m_audio_path;
};

#endif // COMPONENT_H
