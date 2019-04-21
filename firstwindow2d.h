#ifndef FIRSTWINDOW2D_H
#define FIRSTWINDOW2D_H


#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialog>

class FirstWindow2D: public QDialog{
Q_OBJECT

    unsigned int size=25;
    unsigned int minimalNb=2;
    unsigned int maximalNb=3;
    unsigned int bornNb=3;


    QVBoxLayout* vboxMain;

    QLabel* title1;
    QSpinBox* choiceSize;

    QLabel* titleBorn;
    QSpinBox* choiceBorn;

    QLabel* title2;
    QSpinBox* choiceMinimal;

    QLabel* title3;
    QSpinBox* choiceMaximal;


    QPushButton* launch;

private slots:
    void launchChecking();
    void launchChangingSize(int);
    void launchChangingMini(int);
    void launchChangingMaxi(int);
    void launchChangingBorn(int);

public:
   explicit FirstWindow2D( QWidget* parent = 0);
};


#endif // FIRSTWINDOW2D_H
