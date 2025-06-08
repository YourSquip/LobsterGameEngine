#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include <QPixmap>
#include <QObject>
//#include <Q>
//#include <Q
#include <QtMultimedia/QAudioInput>


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


class Position: public Component
{
public:
    Position()
    {
        m_name = "position";
        m_x = 0;
        m_y = 0;
    }
    Position(unsigned int x, unsigned int y)
    {
        m_name = "position";
        m_x = x;
        m_y = y;
    }
    float x()
    {
        return m_x;
    }
    float y()
    {
        return m_y;
    }

    void set_x(unsigned int x)
    {
        m_x = x;
        emit item_changed(this);
    }
    void set_y(unsigned int y)
    {
        m_y = y;
        emit item_changed(this);
    }

    QString get_name() override
    {
        return m_name;
    }
private:
    float m_x;
    float m_y;
};

class Sprite: public Component
{
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

private:
    QPixmap m_pixmap;
};


/*class Audio: public Component
{
public:
    Audio()
    {
        m_name = "sprite";
        m_pixmap = QPixmap(":/sprites/icons/object.png");
    }

    Audio(QPixmap pixmap)
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

private:
    //QPixmap m_pixmap;
};*/

#endif // COMPONENT_H
