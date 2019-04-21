#ifndef WINDOWCHOICE_H
#define WINDOWCHOICE_H
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QFont>


class WindowChoice: public QDialog{
Q_OBJECT
    QLabel *title;

    QPushButton *buttonOneD;

    QPushButton *buttonTwoD;

    QPushButton *buttonThreeD;
    QVBoxLayout * verticalUpBox;


private slots:
    void launchWindow2D();
public:
   explicit WindowChoice( QWidget* parent = 0);
};

#endif // WINDOWCHOICE_H
