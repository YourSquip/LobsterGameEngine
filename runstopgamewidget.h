#ifndef RUNSTOPGAMEWIDGET_H
#define RUNSTOPGAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include "gamewindow.h"
#include "editor.h"

class RunStopGameWidget: public QWidget
{
public:
    RunStopGameWidget(QWidget* parent = nullptr):QWidget(parent)
    {
        run_button_pressed = false;
        m_run_bttn = new QPushButton("PLAY", this);
        //m_run_bttn->setIcon(QIcon(QStyle::standardIcon()->));
        m_stop_bttn = new QPushButton("STOP", this);
        m_game_state_lbl = new QLabel("Engine mod",this);
        m_layout = new QHBoxLayout(this);
        m_layout->addWidget(m_run_bttn);
        m_layout->addWidget(m_stop_bttn);
        m_layout->addWidget(m_game_state_lbl);

        connect(m_run_bttn, &QPushButton::pressed, this, &run_game);
        connect(m_stop_bttn, &QPushButton::pressed, this, &stop_game);
    }

    bool is_game_running()
    {
        return run_button_pressed;
    }

    void set_game_window(QWidget* game_window)
    {
        m_game_window = game_window;
    }
private:
    QPushButton* m_run_bttn;
    QPushButton* m_stop_bttn;
    QLabel* m_game_state_lbl;
    QHBoxLayout* m_layout;
    QWidget* m_game_window;
    bool run_button_pressed;

private slots:
    void run_game()
    {
        m_game_state_lbl->setText("Game mod");
        run_button_pressed = true;
        if(run_button_pressed)
        {
            QLabel* lbl = new QLabel("bipka",m_game_window);
            m_game_window->show();
            Editor::get_instance()->get_game()->run_timer();
        }
        //m_game_window->show();//сюда бы копию вьюпорт окна
    }
    void stop_game()
    {
        //а здесь бы это окно закрывать
        m_game_state_lbl->setText("Engine mod");
        run_button_pressed = false;
        Editor::get_instance()->get_game()->get_timer().invalidate();
        //m_game_window->close();
    }
};


#endif // RUNSTOPGAMEWIDGET_H
