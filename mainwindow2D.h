#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTextEdit>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QPushButton>
#include <QFont>
#include <QApplication>
#include <QFormLayout>
#include <QObject>
#include <QtWidgets>
#include <QTimer>

#include "../jeuVie/jeuvie.h"


class Window2D : /*public Jeu_vie,*/public QDialog{
Q_OBJECT

    QHBoxLayout *layout;

    QTableWidget *simulation;

    QHBoxLayout *hboxMain;
    QVBoxLayout *vboxMain;


    QHBoxLayout *hboxAuto;
    QHBoxLayout *hboxManual;
    QHBoxLayout *hboxSave;

    //Execution Manuelle
    QPushButton *random;
    QPushButton *oneByOne;
    QPushButton *clear;

    //Execution automatique
    QPushButton *stop;
    QPushButton *launch;
    QSpinBox* frequency;
    double time;
    QLabel* chooseStep;

    //Partie sauvegarde
    QTextEdit* browse;
    QPushButton* import;
    QPushButton* xport;

    //Quitter
    QPushButton *quit;

    //Titres fenetre 1
    QHBoxLayout *ht1;
    QHBoxLayout *ht2;
    QHBoxLayout *ht3;


    QLabel* title1;
    QLabel* title2;
    QLabel* title3;

    unsigned int m_nbBorn;
    unsigned int m_nbMini;
    unsigned int m_nbMaxi;
    unsigned int dimension;

    QTimer *timer;

    bool stopOption;
    Etat_2D state;
    //Etat_2D etat;
    Jeu_vie jeu;

private slots:
    void launchRandom();
    void launchHome();
    void launchNext();
    void launchNonStop();
    void launchStop();
    void launchClear();
    void launchChangingTime(int i);
    void launchActivation(const QModelIndex& index);

     void launchTransition();
     void showTableSlot();

public:

    explicit Window2D(int size=10, QWidget* parent = 0);
    explicit Window2D(unsigned int size=10, unsigned int nbBorn=0, unsigned int nbMini=0, unsigned int nbMaxi=0, QWidget* parent = 0);
    void showTable();

signals:
    void iterationSignal();
};


#endif // MAINWINDOW_H
