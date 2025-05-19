#ifndef RUNSTOPWINDOW_H
#define RUNSTOPWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class RunStopWindow: public QWidget
{
public:
    RunStopWindow(QWidget* parent = nullptr):QWidget(parent)
    {
        run_button_pressed = false;
        m_run_bttn = new QPushButton("Run",this);
        m_stop_bttn = new QPushButton("Stop",this);
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
private:
    QPushButton* m_run_bttn;
    QPushButton* m_stop_bttn;
    QLabel* m_game_state_lbl;
    QHBoxLayout* m_layout;
    bool run_button_pressed;

private slots:
    void run_game()
    {
        m_game_state_lbl->setText("Game mod");
        run_button_pressed = true;
    }
    void stop_game()
    {
        m_game_state_lbl->setText("Engine mod");
        run_button_pressed = false;
    }
};

#endif // RUNSTOPWINDOW_H
