#include "mainwindow2D.h"
#include "firstwindowconfig.h"
#include "windowchoice.h"
#include "firstwindow2d.h"
#include "windowchoiceconfig.h"

FirstWindow2D::FirstWindow2D(QWidget* parent):QDialog(parent){

    /*
        Cette fenetre précèdera la MainWindow afin de connaitre les paramètres voulues du jeu de la Vie
        A savoir la taille de la matrice et les paramètres concernant les voisins et les règles de transitions
    */

    title1=new QLabel("Choix de la taille de la matrice", this);
    choiceSize = new QSpinBox(this);
    choiceSize->setMinimum(10);
    choiceSize->setMaximum(50);
    choiceSize->setValue(25);
    QObject::connect(choiceSize, SIGNAL(valueChanged(int)), this, SLOT(launchChangingSize(int)));

    titleBorn=new QLabel("Choix du nombre de voisin pour faire naître une cellule", this);
    choiceBorn = new QSpinBox(this);
    choiceBorn->setMinimum(0);
    choiceBorn->setMaximum(8);
    choiceBorn->setValue(3);
    QObject::connect(choiceBorn, SIGNAL(valueChanged(int)), this, SLOT(launchChangingBorn(int)));

    title2=new QLabel("Choix du nombre minimal de voisins pour la survie", this);
    choiceMinimal=new QSpinBox(this);
    choiceMinimal->setMinimum(0);
    choiceMinimal->setMaximum(8);
    choiceMinimal->setValue(2);
    QObject::connect(choiceMinimal, SIGNAL(valueChanged(int)), this, SLOT(launchChangingMini(int)));



    title3=new QLabel("Choix du nombre maximal de voisins", this);
    choiceMaximal=new QSpinBox(this);
    choiceMaximal->setMinimum(0);
    choiceMaximal->setMaximum(8);
    choiceMaximal->setValue(3);
    QObject::connect(choiceMaximal, SIGNAL(valueChanged(int)), this, SLOT(launchChangingMaxi(int)));


    launch = new QPushButton("Définir", this);
    QObject::connect(launch, SIGNAL(clicked()), this, SLOT(launchChecking()));

    vboxMain=new QVBoxLayout;

    vboxMain->addWidget(title1);
    vboxMain->addWidget(choiceSize);
    vboxMain->addWidget(titleBorn);
    vboxMain->addWidget(choiceBorn);
    vboxMain->addWidget(title2);
    vboxMain->addWidget(choiceMinimal);
    vboxMain->addWidget(title3);
    vboxMain->addWidget(choiceMaximal);
    vboxMain->addWidget(launch);

    this->setLayout(vboxMain);

}

/*

  A COMPLETER
  launchChecking vérifie que les paramètres sont corrects (pas de voisins >8 ou <0 par ex)
  Lance la fenêtre principal avec les paramètres choisis

*/

void FirstWindow2D::launchChecking(){
    hide();

   Window2D wind(size,bornNb,minimalNb,maximalNb,this);
   wind.setModal(true);//On est jamais trop prudent
   wind.exec();
}
void FirstWindow2D::launchChangingSize(int i){
    size=i;
}
void FirstWindow2D::launchChangingBorn(int i){
    bornNb=i;
}

void FirstWindow2D::launchChangingMini(int i){
    minimalNb=i;
    choiceMaximal->setMinimum(i); //On ne peut pas avoir un nombre maximal de voisins < au nombre minimal de voisins

}

void FirstWindow2D::launchChangingMaxi(int i){
    maximalNb=i;
}

